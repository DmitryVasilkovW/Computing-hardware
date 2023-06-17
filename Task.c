#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int size;

void write_file(const char *fileName, int arr[], int length) 
{

    FILE *file;

    if ((file = fopen(fileName, "w")) == NULL)
	{
        printf("UnableToOpen");
    }

    for (int i = 0; i < length; i++)
	{
        fprintf(file, "%d\n", arr[i]);
    }


    fclose(file);
}

int numberCount(FILE* input) 
{
    fseek(input, 0, SEEK_SET);
    int counter = 0;
    while (1) 
	{
        int value;
        if (fscanf(input, "%d", &value) == 1)
            counter++;
        fread(&value, sizeof(char), 1, input);
        if (feof(input))
            break;
    }
    return counter;
}

void read_numbers(FILE* input, int* numbers) 
{
    fseek(input, 0, SEEK_SET);
    for (int i = 0; i < size; ++i) 
	{
        fscanf(input, "%d", &numbers[i]);
    }
}

int *read_file(const char *filename) 
{

    FILE *file;
    int *arr;

    if ((file = fopen(filename, "r")) == NULL) 
	{
        printf("UnableToOpen");
    }

    size = numberCount(file);
    arr = (int*)malloc(sizeof(int) * size);
    read_numbers(file, arr);

    fclose(file);

    return arr;

}

int main() 
{
    srand(time(NULL));

    const char *filename = "newFile.txt";
    const char *sortedFileName = "sortedFile.txt";

    int *arr;

    arr = read_file(filename);





    int maxTen[10];


    __asm__ __volatile__
	(          

            "movq %0, %%r8 \n\t"
            "movq $0, %%r9 \n\t"

            "loop_second : \n\t"
            "cmpl %%r9d, %1 \n\t"
            "je break \n\t"

            "movq $0, %%r10 \n\t"
            "movq $0, %%rax \n\t"

            "movq %%r8, %%rax \n\t"
            "movl %%r9d, %%r10d \n\t"
            "jmp loop_first \n\t"



            "loop_first :\n\t"
            "cmpl $0, %%r10d \n\t"
            "je iteration_second \n\t"
            "jmp compare \n\t"



            "compare: \n\t"
            "movq $0, %%rbx \n\t"
            "movq $0, %%rcx \n\t"
            "movq $0, %%rdx \n\t"

            "lea -4(%%rax), %%rbx \n\t"
            "movl (%%rbx), %%ecx\n\t"
            "movl (%%rax), %%edx \n\t"
            "cmpl %%edx, %%ecx \n\t"
            "jg swap \n\t"
            "jmp iteration_second \n\t"

            "swap:\n\t"
            "movq $0, %%rbx \n\t"
            "movq $0, %%rcx \n\t"
            "movq $0, %%rdx \n\t"
            "movl (%%rax), %%ebx\n\t"
            "lea -4(%%rax), %%rcx\n\t"
            "movl (%%rcx), %%edx \n\t"
            "movl %%ebx, (%%rcx)\n\t"
            "movl %%edx, (%%rax) \n\t"
            "jmp iteration_first \n\t"

            "iteration_first: \n\t"
            "dec %%r10d \n\t"
            "subq $4, %%rax \n\t"
            "jmp loop_first\n\t"


            "iteration_second : \n\t"
            "addq $4, %%r8 \n\t"
            "inc %%r9d \n\t"
            "jmp loop_second \n\t"



            "break :"



            :
            :"D"(arr), "p"(size)
            :"%rax", "%rbx", "%rcx", "%rdx", "r8", "r9", "r10", "r11"
            );


    __asm__ 
	(
            "movq $0, %%r8 \n\t"
            "movq $0, %%r9 \n\t" 
            "movq $0, %%rcx \n\t"
            "movq $0, %%rbx \n\t"

            "movq %0, %%r8 \n\t"
            "movl %1, %%ecx \n\t" 
            "dec %%ecx \n\t"
            "leaq (%%r8, %%rcx,4), %%rbx \n\t" 
            "movq %%rbx, %%r8 \n\t" 

            "movq $0, %%rcx \n\t"

            "movq %2, %%rax \n\t" 
            "movl $9, %%ecx \n\t"
            "leaq (%%rax, %%rcx,4), %%rbx \n\t"
            "movq %%rbx, %%rax \n\t"

            "movq $0, %%rcx \n\t"
            "movl $10, %%ecx \n\t" 


            "put : \n\t"  
            "movl (%%r8), %%r9d \n\t"    
            "movl %%r9d, (%%rax) \n\t"  
            "subq $4, %%r8 \n\t"    
            "subq $4, %%rax \n\t"

            " loop put\n\t"
            :
            :"m"(arr), "m"(size), "a"(maxTen)
            : "%rbx", "%rcx", "r8"

            );

    write_file(sortedFileName, maxTen, 10);

    free(arr);
    return 0;
}

