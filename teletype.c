#include <stdio.h>
#include <errno.h>
#include <unistd.h>

#define SOURCE_SIZE 10000
#define PRINT_DELAY 50000
#define NEW_LINE_DELAY 500000

char source[SOURCE_SIZE];
char *src = source;

int main(int argc,char *argv[])
{
    if(argc == 1)
    {
        printf("usage: teletype [filename]\n");
        return 1;
    }

    else if(argc == 2)
    {
        FILE *file = fopen(argv[1], "r");

        if(errno)
        {
            printf("File '%s' doesn't exist!\n", argv[1]);
            return 0;
        }

        fread(source, 1, SOURCE_SIZE, file);
        printf("\x1b[2J\x1b[;H");

        while(*src)
        {
            putchar(*src++);
            fflush(stdout);
                        
            switch(*src)
            {
                case '\n': usleep(NEW_LINE_DELAY); break;
                case ' ': usleep(0); break;
                default: usleep(PRINT_DELAY); break;
            } 
        }
    }

    getchar();
    return 0;
}