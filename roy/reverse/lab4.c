#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <assert.h>
#include <sys/stat.h>

#include "md5.h"

// d0abc064c7ea882ca2bdef4be41b2801

// NISRA{d0abc064c7ea882ca2bdef4be41b2801}

int checkPasswordMD5(char *pass)
{
    char md5ed[40];
    md5(pass, md5ed, 40);
    return strcmp(md5ed, "9ac9594db28729e95b9334e1ca9c256b") == 0;
}

char* safe_gets(char *buf, size_t siz)
{
    char *res = fgets(buf, siz, stdin);
    if(res != NULL)
        buf[strcspn(buf, "\n")] = '\0';
    return res;
}

int login()
{
    char buf[40];
    printf("\nPlease enter the password: ");
    fflush(stdin);
    safe_gets(buf, sizeof(buf));
    getchar();
    return checkPasswordMD5(buf);
}

void banner()
{
    printf("Welcome to lab4.\n");
    printf("(1.) Encrypt the file\n");
    printf("(2.) Decrypt the file\n");
    printf("(3.) Exit\n");
    printf("> ");
}

char enc_table[64] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '{', '}', '_'};

int encrypt_find_pair(char c, int *a, int *b)
{
    for(int i = 0; i < 64; i++)
    {
        if(c == enc_table[i])
        {
            *a = i / 8;
            *b = i % 8;
            return 1;
        }
    }
    return 0;
}

int check_file_exist(char *filename)
{
    struct stat buffer;
    return (stat(filename, &buffer) == 0);
}

char* read_whole_file(char *filename, size_t *siz)
{
    // Open the file and get the size
    FILE *fp = fopen(filename, "r+");
    fseek(fp, 0, SEEK_END);
    *siz = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    // Read the while file
    char *s = malloc(sizeof(char) * (*siz + 10));
    fread(s, sizeof(char), siz, fp);
    fclose(fp);

    return s;
}

void encrypt_write_dots(FILE *fp, size_t num)
{
    if(!fp)
    {
        printf("File pointer is NULL\n");
        abort();
    }

    for(int i = 0; i < num; i++)
        fputc('.', fp);
}

void encrypt_file(char *filename)
{
    size_t siz;
    char *s = read_whole_file(filename, &siz);

    // Open the file for writing enc
    char fwName[strlen(filename)+5];
    sprintf(fwName, "%s.enc", filename);
    FILE *fw = fopen(fwName, "w");

    // Encrypt the file
    int a, b;
    for(int i = 0; i < siz; i++)
    {
        if(encrypt_find_pair(s[i], &a, &b))
        {
            a++, b++;

            encrypt_write_dots(fw, a);
            fputc(' ', fw);
            encrypt_write_dots(fw, b);
            fputc('\n', fw);
        }
        else
        {
            puts("The file contains INVALID char");
            break;
        }
    }

    printf("Contents of %s is encrypted to %s\n", filename, fwName);

    fclose(fw);
    free(s);
}

void encrypt_handler()
{
    char buf[40];
    printf("Enter the filename: ");
    safe_gets(buf, sizeof(buf));

    if (!check_file_exist(buf))
    {
        printf("The file is not exist\n");
        return;
    }

    encrypt_file(buf);
}

enum decrypt_parse_state
{
    DP_FIRST_CH,
    DP_SECOND_CH
};

char decrypt_index(int i)
{
    assert(i >= 0 && i < 64);
    return enc_table[i];
}

void decrypt_file(char *filename)
{
    size_t siz;
    char *s = read_whole_file(filename, &siz);

    int cur_state = DP_FIRST_CH;
    int cnt = 0;
    int idx = 0;

    for(int i = 0; i < siz; i++)
    {
        if(s[i] == '.')
            cnt++;
        else if(s[i] == ' ' || s[i] == '\n')
        {
            if(cur_state == DP_FIRST_CH)
            {
                idx += (cnt-1) * 8;
                // printf("a = %d ", cnt);
                cnt = 0;
                cur_state = DP_SECOND_CH;
            }
            else if(cur_state == DP_SECOND_CH)
            {
                idx += cnt-1;
                // printf("b = %d\n", cnt);
                cnt = 0;

                putchar(decrypt_index(idx));
                idx = 0;

                cur_state = DP_FIRST_CH;
            }
        }
    }

    putchar('\n');
    free(s);
}

void decrypt_handler()
{
    // Login
    int res = login();
    if(!res)
    {
        printf("Wrong password!");
        return;
    }

    char filename[40];
    printf("Enter the filename: ");
    safe_gets(filename, sizeof(filename));

    // Check file exist?
    if (!check_file_exist(filename))
    {
        printf("The file is not exist\n");
        return;
    }

    decrypt_file(filename);
}


int main()
{
    int opt = -1;
    while(1)
    {
        banner();
        scanf("%d", &opt);
        getchar();

        switch(opt)
        {
            case 1:
                encrypt_handler();
            break;

            case 2:
                decrypt_handler();
            break;

            case 3:
                return 0;
            break;

            default:
                printf("Worng option\n");
            break;
        }
        putchar('\n');
    }

    return 0;
}