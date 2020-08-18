#include <stdio.h>
#include <string.h>

const char pass[] = "NISRA{First try}";

int main()
{
    char sec[30];
    puts("Hello, Hacker~");
    printf("Give me the code: ");
    fgets(sec, 30, stdin);
    sec[strcspn(sec, "\n")] = '\0';

    if(strncmp(sec, pass, strlen(pass)) == 0)
        puts("Not bad huh");
    else
        puts("You have the wrong password LOL");
}