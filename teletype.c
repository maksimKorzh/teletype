/*********************************************************************************\
;---------------------------------------------------------------------------------;
;                                                                                 ;
;                                 Teletype v0.0.1                                 ;
;                                                                                 ;
;---------------------------------------------------------------------------------;
;---------------------------------------------------------------------------------;
;                                                                                 ;
;            A simple tool to output text file char by char with a delay          ;
;                                                                                 ;
;---------------------------------------------------------------------------------;
;---------------------------------------------------------------------------------;
;                                                                                 ;
;                                by Maksim Korzh                                  ;
;                                                                                 ;
;---------------------------------------------------------------------------------;
;*********************************************************************************;
;---------------------------------------------------------------------------------;
;                                                                                 ;
;       THIS PROGRAM IS FREE SOFTWARE. IT COMES WITHOUT ANY WARRANTY, TO          ;
;        THE EXTENT PERMITTED BY APPLICABLE LAW. YOU CAN REDISTRIBUTE IT          ;
;       AND/OR MODIFY IT UNDER THE TERMS OF THE DO WHAT THE FUCK YOU WANT         ;
;          TO PUBLIC LICENCE, VERSION 2, AS PUBLISHED BY SAM HOCEVAR.             ;
;                SEE http://www.wtfpl.net/ FOR MORE DETAILS.                      ;
;                                                                                 ;
;---------------------------------------------------------------------------------;
;*********************************************************************************;
;---------------------------------------------------------------------------------;
;                                                                                 ;
;                   DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE                   ;
;                           Version 2, December 2004                              ;
;                                                                                 ;
;        Copyright (C) 2004 Sam Hocevar <sam@hocevar.net>                         ;
;                                                                                 ;
;        Everyone is permitted to copy and distribute verbatim or modified        ;
;        copies of this license document, and changing it is allowed as long      ;
;        as the name is changed.                                                  ;
;                                                                                 ;
;                   DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE                   ;
;          TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION        ;
;                                                                                 ;
;         0. You just DO WHAT THE FUCK YOU WANT TO.                               ;
;                                                                                 ;
;---------------------------------------------------------------------------------;
;---------------------------------------------------------------------------------;
;             please let me know if you find this code/project useful             ;
;---------------------------------------------------------------------------------;
;*********************************************************************************;
;---------------------------------------------------------------------------------;
;                                                                                 ;
;         Copyright © 2019  Maksim Korzh  <freesoft.for.people@gmail.com>         ;
;                                                                                 ;
;---------------------------------------------------------------------------------;
\*********************************************************************************/

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
