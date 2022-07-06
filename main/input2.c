#include <stdio.h>
#include <string.h>
#include "new2.c"

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

char curr_names[N][4];

int findpos(char arr[])
{
      for (int i = 0; i < N; i++)
      {
            if (!strcmp(arr, curr_names[i]))
            {
                  return i;
            }
      }
}

int main()
{
      FILE *fp2;
      fp2 = fopen("names.txt", "r");

      for (int i = 0; i < N; i++)
      {
            fscanf(fp2, "%s", curr_names[i]);
      }
      fclose(fp2);
      FILE *fp;
      int ins, n, name, curr, V, b = 0, src, dest, weight;
      char buf, Name_bank[5], instruction[21], curren[4], curren2[4];
      bank *arr_banks[MAX];
      int delete[MAX] = {0};
      fp = fopen("file.txt", "r");

      while (!feof(fp) && ins != 9)
      {
            fscanf(fp, "%s", instruction);
            if (strcmp(instruction, "AddBank") == 0)
                  ins = 1;
            else if (strcmp(instruction, "DeleteBank") == 0)
                  ins = 2;
            else if (strcmp(instruction, "AddCurrencyInBank") == 0)
                  ins = 3;
            else if (strcmp(instruction, "DeleteCurrencyInBank") == 0)
                  ins = 4;
            else if (strcmp(instruction, "AddConversion") == 0)
                  ins = 5;
            else if (strcmp(instruction, "DeleteConversion") == 0)
                  ins = 6;
            else if (strcmp(instruction, "BestWay") == 0)
                  ins = 7;
            else if (strcmp(instruction, "PrintBankInfo") == 0)
                  ins = 8;
            else if (strcmp(instruction, "Exit") == 0)
                  ins = 9;

            switch (ins)
            {
            case (1):
                  fscanf(fp, "%c%s %d %d", &buf, Name_bank, &V, &n);
                  int *ver = (int *)malloc(V * sizeof(int));
                  for (int i = 0; i < V; i++)
                  {
                        //  fscanf(fp,"%d",&ver[i]);
                        fscanf(fp, "%c%s", &buf, curren);
                        ver[i] = findpos(curren);
                  }
                  struct Edge *arr = (struct Edge *)malloc(n * sizeof(struct Edge));
                  for (int i = 0; i < n; i++)
                  {
                        fscanf(fp, "%c%s %s %d", &buf, curren, curren2, &arr[i].weight);
                        arr[i].src = findpos(curren);
                        arr[i].dest = findpos(curren2);
                  }
                  if (num < MAX)
                  {
                        delete[num] = 1;
                        arr_banks[num] = createGraph(Name_bank, ver, V);
                  }
                  else
                        printf("Banks can't be added anymore\n");
                  for (int i = 0; i < n; i++)
                  {
                        if (arr[i].src != arr[i].dest && arr_banks[num - 1]->refer[arr[i].dest] == 1 && arr_banks[num - 1]->refer[arr[i].src] == 1)
                              AddConversion(&arr_banks[num - 1]->head[arr[i].src], arr[i].dest, arr[i].weight);
                        else
                              printf("CONVERSION FROM %s TO %s IS NOT POSSIBLE IN %d BANK\n", curr_names[arr[i].src], curr_names[arr[i].dest], delete[num - 1]);
                  }
                  free(arr);
                  free(ver);
                  //getchar();
                  break;
            case (2):
                  fscanf(fp, "%c%d", &buf, &name);
                  if (delete[name] == 0)
                  {
                        printf("%d BANK IS NOT PRESENT\n", name);
                  }
                  else
                        DeleteBank(arr_banks[name]);
                  delete[name] = 0;
                  //getchar();
                  break;
            case (3):
                  fscanf(fp, "%c%d %s", &buf, &name, curren);
                  curr = findpos(curren);
                  if (delete[name] == 1 && arr_banks[name]->refer[curr] != 1)
                        AddCurrency(curr, arr_banks[name]);
                  else if (delete[name] != 1)
                        printf("%s IS NOT POSSIBLE TO ADD IN %d BANK \n", curr_names[curr], name);
                  else if (delete[name] == 1 && arr_banks[name]->refer[curr] == 1)
                        printf("%s IS ALREADY PRESENT IN %d BANK\n", curr_names[curr], name);
                  // getchar();
                  break;
            case (4):
                  fscanf(fp, "%c%d %s", &buf, &name, curren);
                  curr = findpos(curren);
                  if (delete[name] == 1 && arr_banks[name]->refer[curr] == 1)
                        deleteCurrency(arr_banks[name], curr);
                  else
                        printf("%s HAS NOT BEEN ADDED TO %d BANK\n", curr_names[curr], name);
                  // getchar();
                  break;
            case (5):
                  fscanf(fp, "%c%d %s %s %d", &buf, &name, curren, curren2, &weight);
                  src = findpos(curren);
                  dest = findpos(curren2);
                  if (delete[name] == 1 && src != dest && arr_banks[name]->refer[dest] == 1 && arr_banks[name]->refer[src] == 1)
                        AddConversion(&arr_banks[name]->head[src], dest, weight);
                  else
                  {
                        if (delete[name] == 1)
                              printf("%s TO %s NOT POSSIBLE IN %d BANK\n", curr_names[src], curr_names[dest], name);
                        else
                              printf("%s TO %s NOT POSSIBLE in %d BANK\n", curr_names[src], curr_names[dest], name);
                  }
                  // getchar();
                  break;
            case (6):
                  fscanf(fp, "%c%d %s %s", &buf, &name, curren, curren2);
                  src = findpos(curren);
                  dest = findpos(curren2);
                  if (delete[name] == 1 && arr_banks[name]->refer[dest] == 1 && arr_banks[name]->refer[src] == 1)
                        deleteNode(&arr_banks[name]->head[src], dest);
                  else
                  {
                        if (delete[name] == 1)
                              printf("%s TO %s NOT POSSIBLE IN %d BANK \n", curr_names[src], curr_names[dest], name);
                        else
                              printf("%s TO %s NOT POSSIBLE in %d BANK\n", curr_names[src], curr_names[dest], name);
                  } //getchar();
                  break;
            case (7):
                  fscanf(fp, "%c%s %s", &buf, curren, curren2);
                  src = findpos(curren);
                  dest = findpos(curren2);
                  bestpath(arr_banks, src, dest, delete, curr_names);
                  //getchar();
                  break;
            case (8):
                  fscanf(fp, "%c%d", &buf, &name);
                  if (delete[name] == 1)
                        printGraph(arr_banks[name], curr_names);
                  else
                        printf("%d BANK IS NOT PRESENT\n", name);
                  //getchar();
            }
      }
      fclose(fp);
}
