#include <stdio.h>
#include <string.h>
#include "array.h"


int find_num_of_strings(FILE *f)
{
    char c;
    int in_line = 0;
    int num_of_lines = 0;
    while (fscanf(f, "%c", &c) != EOF)
    {
        if (!in_line && c > 47 && c < 58)
        {
            in_line = 1;
        }
        if (c == '\n' && in_line)
        {
            num_of_lines++;
            in_line = 0;
        }
    }
    return num_of_lines;
}

struct array ** delete_string(struct array ** main_arr, int idx, int size)
{
    free(main_arr[idx]);
    for (int i = idx; i < size - 1; i++)
    {
        main_arr[i] = main_arr[i + 1];
    }
    main_arr = (struct array **)realloc(main_arr, sizeof(struct array *) * (size - 1));
    return main_arr;
}


int main(int argc, char* argv[])
{
    struct array ** main_arr;
    int size= 0;
    int num_size = 0;// amount of numbers
    int len_of_str = 0; // amount of chars in string
    int num = 0; // number (%d)
    int cur_str = 0;
    int in_line = 0; // flag
    int max_wide = 0;
    char c;
    
    FILE *f = NULL;
//    if (argc <= 1)
//    {
//        printf("Incorrect comand\n");
//        return 0;
//    }
    
    f = fopen("/Users/petrlobanov/Desktop/Studying/CS/HW/XcodeHW/curved_array/curved_array/data.txt", "r");
    
    if (f == NULL)
    {
        printf("Icorrect path\n");
        return -1;
    }
    
    //count lines
    
    size = find_num_of_strings(f);
    main_arr = (struct array**)(malloc(sizeof(struct array*) * size));
    rewind(f);
    while (fscanf(f, "%c", &c) != EOF)
    {
        len_of_str++;
        if (c > 47 && c < 58)
        {
            in_line = 1;
            num_size++;
            while(c > 47 && c < 58 && (fscanf(f, "%c", &c) != EOF))
            {
                len_of_str++;
            }
        }
        if (c == '\n' && in_line)
        {
            fseek(f, -len_of_str, SEEK_CUR);
            main_arr[cur_str] = create(num_size);
            for (int i = 0; i < num_size; i++)
            {
                fscanf(f, "%d", &num);
                main_arr[cur_str]->ptr[i] = num;
            }
            (num_size > max_wide)? max_wide = num_size: 0;
            num_size = 0;
            len_of_str = 0;
            in_line = 0;
            cur_str++;
        }
    }
    
    for (int i = 0; i < size; i++)
    {
        print(main_arr[i]);
    }
    printf("\n---------------------\n\n");
    
    
    for (int j = 0; j < max_wide; j++)
    {
        int mean = 0;
        int quantity = 0;
        for (int i = 0; i < size; i++)
        {
            if (main_arr[i]->size <= j)
            {
                continue;
            }
            else
            {
                quantity++;
                mean += main_arr[i]->ptr[j];
            }
        }
        if (mean%quantity)
        {
            continue;
        }
        mean = mean / quantity;
        
        
        for (int i = 0; i < size; i++)
        {
            if (main_arr[i]->size <= j)
            {
                continue;
            }
            else if(main_arr[i]->ptr[j] == mean)
            {
                for (int tmp = 0; tmp < size; tmp++)
                {
                    if (main_arr[tmp]->size <= j)
                    {
                        continue;
                    }
                    else
                    {
                        main_arr[tmp] = delete_el(main_arr[tmp], j);
                        if (main_arr[tmp]->size == 0)
                        {
                            main_arr = delete_string(main_arr, tmp, size);
                            tmp--;
                            size--;
                        }
                    }
                }
                j--;
                max_wide--;
                break;
            }
        }
    }
    
    for (int i = 0; i < size; i++)
    {
        print(main_arr[i]);
    }
    
    for (int tmp = 0; tmp < size; tmp++)
    {
        del(main_arr[tmp]);
        free(main_arr[tmp]);
    }
    free(main_arr);
    
    return 0;
}
