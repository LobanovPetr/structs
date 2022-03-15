#include "func.h"

int main()
{
    srand(time(NULL));
    int size, num;
    printf("This program sorts array\n");
    printf("Choose the way to solve your task: \n1) file  \n2) generation random numbers\n");
        scanf ("%d", &num);
    
    double * ar;
    
    switch (num) {
        case 1:
        {
            double a;
            int n = 0;
            char filename[256];
            FILE* fp;
            printf("Enter your filename: \n");
            scanf("%s", filename);
            fp = fopen(filename, "r");
            if (fp==NULL) {
                printf("Cannot open the file!\n");
                return -1;
            }
            if (fscanf(fp, "%lf", &a) != 1) {
                printf("Error data format!\n");
                return -2;
            }
            do {
                n++;
            } while (fscanf(fp, "%lf", &a) == 1);
            if (n > 10000)
            {
                printf("The size is too big\n");
                return -4;
            }
            printf("Size of arr = %d\n", n);
            rewind(fp);
            size = n;
            ar = (double *)malloc(n *sizeof(double));
            for (int i = 0; i < n; i++) {
                fscanf(fp, "%lf", &ar[i]);
                printf("arr[%d] = %lf\n", i, ar[i]);
            }
            fclose(fp);
            break;
        }
        case 2:
        {
            double min, max;
            printf("Enter the length of array: ");
            scanf("%d", &size);
            if (size > 10000)
            {
                printf("Size is to big\n");
                return -4;
            }
            printf("Enter the min and max range of number: ");
            scanf("%lf%lf", &min, &max);
            ar = (double *)malloc(size *sizeof(double));
            for (int i = 0; i < size; i++) {
                ar[i] = (double)(rand()) / RAND_MAX * (max - min) + min;
                printf("ar[%d] = %lf\n", i, ar[i]);
            }
            break;
        }
        default:
            printf("Wrong number!\n");
            return -3;
    }
    
    int time;
    time = clock();
    
    quick_sort(ar, -1, size);
    
    time = clock() - time;
    
    printf("\n");
    
    if (size > 20)
    {
        for (int i = 0; i < 5 ; i++)
        {
            printf("ar[%d] = %lf\n", i, ar[i]);
        }
        printf("...\n");
        for (int i = size - 5; i < size; ++i)
        {
            printf("ar[%d] = %lf\n", i, ar[i]);
        }
    }
    else
    {
        for (int i = 0; i < size ; i++)
        {
            printf("ar[%d] = %lf\n", i, ar[i]);
        }
    }
    free(ar);
    printf("Time of sorting : %5.3lf ms\n", (double)time / CLOCKS_PER_SEC * 1000);
    return 0;
}
