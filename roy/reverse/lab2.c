#include <stdio.h>
#include <string.h>
#include <stdint.h>

const size_t enc_len = 22;
char enc[] = {0xc9, 0xce, 0xd4, 0xd5, 0xc6, 0xfc, 0xd8, 0xdf, 0xc8, 0xd5, 0xd8, 0xe2, 0xe9, 0xe4, 0xf5, 0xfe, 0xf7, 0xf3, 0xe2, 0xe3, 0xd8, 0xfa};

void decode_flag(char *s)
{
    for (int i = 0; i < enc_len; i++)
    {
        s[i] = enc[i] ^ 0x87;
    }
}

const char pass[] = "NotFLAG{Super_SEcrE7_Passw0RD}";

int validate()
{
    char sec[32];
    fgets(sec, 32, stdin);
    sec[strcspn(sec, "\n")] = '\0';
    return strncmp(sec, pass, strlen(pass)) == 0;
}

int main()
{
    puts("This is lab2 ");
    printf("Give me the code: ");

    char tmp[30];

    if (validate())
    {
        decode_flag(tmp);
        puts("Not bad huh");
    }
    else
        puts("You have the wrong password LOL");
}