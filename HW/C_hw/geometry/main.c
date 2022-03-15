// Move all sides of polygon on h distance out

#include "Figures.h"

int main()
{
    polygon P;
    double h;
    char c[100];
    
    printf("Please, enter the file name\n");
    scanf("%s", c);
    
    switch (define_polygon(&P, c))
    {
        case -2:
            printf("Incorrect file\n");
            return -1;
            break;
            
        case 0:
            printf("Incorrect kit of numbers\n");
            return -1;
            break;
    } 
    
    printf("Number of points is %d\n", P.NumberOfPoints);
    for (int i = 0; i < P.NumberOfPoints; ++i)
    {
        printf("(%.3lf %.3lf)\n", P.points[i].x, P.points[i].y);
    }
    
    switch (check_polygon(&P)) {
        case -1:
            printf("There is the same points. Please change them\n");
            return -1;
            break;
        case 0:
            printf("Wrong polygon. Please change polygon\n");
            return -1;
            break;
    }
    printf("Please enter the H\n");
    scanf("%lf", &h);
    point * new_cor = (point *)malloc(sizeof(point) * P.NumberOfPoints);
    new_cordinates(&P, new_cor, h);
    
    printf("Previous coordinates -> New coordinates\n");
    for (int i = 0; i < P.NumberOfPoints; ++i)
    {
        printf("(%.3lf %.3lf) -> (%.3lf %.3lf)\n", P.points[i].x, P.points[i].y, new_cor[i].x, new_cor[i].y);
    }
    free(P.points);
    free(new_cor);
}
