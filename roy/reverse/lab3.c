#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>

#include "lab3_lib.h"

int main()
{
    srand(time(NULL));
    puts("This is lab3 ");
    printf("Give me the number of what i am thinking: ");

    int now = rand(), input = 0;

    char tmp[300];

    scanf("%d", &input);

    if (now == input)
    {
        decode_flag(tmp, 300);
        puts("Not bad huh");
    }
    else
        puts("You have the wrong password LOL");
}