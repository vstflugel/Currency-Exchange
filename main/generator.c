#include <stdio.h>
#include <time.h>
#include <stdlib.h>

//COMPILE USING THE FOLLOWING INSTRUCTIONS:
/*
    Run these instructions on the terminal:
    1) gcc generator.c
    2) ./a.out > file.txt
*/
#define N 6
//N refers to the maximum number of currencies
#define MAX 6
//MAX refers to the maximum number of banks

#define MAX_INSTRUCTIONS 40
#define MAXWEIGHT 20
/*
Instructions: 1. AddBank
              2. DeleteBank
              3. AddCurrencyInBank
              4. DeleteCurrencyInBank
              5. AddConversion
              6. DeleteConversion
              7. BestWay
              8. PrintBankInfo
              9. Exit
*/
int ranNo(int max)
{
    return rand() % max;
}

void genStr(char arr[], int size)
{
    // srand(time(0));
    for (int i = 0; i < size - 1; i++)
    {
        arr[i] = ranNo(26) + 65;
    }
    arr[size - 1] = 0;
}

int main(void)
{
    srand(time(0));
    FILE* fp;
    fp = fopen("names.txt", "w");
    char names[N][4];
    for (int i=0; i<N; i++)
    {
        genStr(names[i], 4);
        fprintf(fp, "%s\n", names[i]);
    }
    fclose(fp);
    int c;
    int curr, nBank, src, dest, wei, vert, edg;
    char name_bank[5];
    
    for (int a = 0; a < MAX_INSTRUCTIONS; a++)
    {
        
        c = rand() % 9 + 1;
        switch (c)
        {
        case (1):
            printf("AddBank\n");
            genStr(name_bank, 5);
            vert = ranNo(N + 1);
            edg = ranNo(vert * (vert - 1));
            printf("%s %d %d\n", name_bank, vert, edg);
            for (int i=0; i<vert; i++)
            {
                curr = ranNo(N);
                printf("%s\n", names[curr]);
            }
            for (int i = 0; i < edg; i++)
            {
                src = ranNo(N);
                dest = ranNo(N);
                wei = ranNo(MAXWEIGHT);
                printf("%d %d %d\n", src, dest, wei);
            }
            break;

        case (2):
            printf("DeleteBank\n");
            nBank = ranNo(MAX);
            printf("%d\n", nBank);
            break;

        case (3):
            printf("AddCurrencyInBank\n");
            curr = ranNo(N);
            nBank = ranNo(MAX);
            printf("%d %s\n", nBank, names[curr]);
            break;            

        case (4):
            printf("DeleteCurrencyInBank\n");
            curr = ranNo(N);
            nBank = ranNo(MAX);
            printf("%d %s\n", nBank, names[curr]);
            break;

        case (5):
            printf("AddConversion\n");
            nBank = ranNo(MAX);
            src = ranNo(N);
            dest = ranNo(N);
            wei = ranNo(MAXWEIGHT);
            printf("%d %s %s %d\n", nBank, names[src], names[dest], wei);
            break;

        case (6):
            printf("DeleteConversion\n");
            nBank = ranNo(MAX);
            src = ranNo(N);
            dest = ranNo(N);
            wei = ranNo(MAXWEIGHT);
            printf("%d %s %s %d\n", nBank, names[src], names[dest], wei);
            break;

        case (7):
            printf("BestWay\n");
            src = ranNo(N);
            dest = ranNo(N);
            printf("%s %s\n", names[src], names[dest]);
            break;

        case (8):
            printf("PrintBankInfo\n");
            nBank = ranNo(MAX);
            printf("%d\n", nBank);
            break;

        case (9):
            printf("Exit\n");
            exit(0);
            break;
        }
    }
}
