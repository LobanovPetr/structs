#include "Figures.h"

void define_point(point * p, double x, double y)
{
    p->x = x;
    p->y = y;
}

int define_polygon(polygon * pol, char * name)
{
    double a;
    double b;
    point * points;
    int n = 0; // number of coordinates
    FILE *f = fopen(name, "r");
    if (f == NULL)
    {
        return -2; // incorrect file
    }
    else
    {
        while (fscanf(f, "%lf", &a) == 1)
        {
            n++;
        }
        if (n & 1 || n <= 4 ) // if n is odd or less than 4
        {
            fclose(f);
            return 0; // inccorect kit of numbers
        }
        else
        {
            points = (point *)malloc(sizeof(point) * n / 2);
            rewind(f);
            for (int i = 0 ; i < n / 2; ++i)
            {
                fscanf(f, "%lf %lf", &a, &b);
                define_point(&points[i], a, b);
            }
        }
        pol->NumberOfPoints = n / 2;
        pol->points = points;
    }
    fclose(f);
    return 1;
}

void create_line_by_two_points(line * l, const point * p1, const point * p2)
{
    l->A = p1->y - p2->y;
    l->B = p2->x - p1->x;
    l->C = (p1->x * p2->y) - (p2->x * p1->y);
}

int compare(double x, double y)
{
    if (fabs(x - y) <= 0.000000000001)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int model(int x, int y)
{
    if (x >= 0)
    {
        return x % y;
    }
    else
    {
        return y - ((-x) % y);
    }
}

int distance_between_point_and_line(const line * l, const point * p1)
{
    if (compare(l->A * p1->x + l->B * p1->y + l->C, 0))
    {
        return 0;
    }
    else
    {
        return (l->A * p1->x) + (l->B * p1->y) + l->C;
    }
}


int prepare(point * ar, int l, int r)
{
    int idx = l + 1 + rand() % (r - l - 1); // generate random index
    int start = idx;
    for (int i = idx - 1; i > l; --i)
    {
        if (i == idx - 1 && (ar[i].x > ar[idx].x || (compare(ar[i].x, ar[idx].x) && ar[i].y > ar[idx].y)))
        {
            point p = ar[i];
            ar[i] = ar[idx];
            ar[idx] = p;
            idx = idx - 1;
        }
        else if (i < idx - 1 && (ar[i].x > ar[idx].x || (compare(ar[i].x, ar[idx].x) && ar[i].y > ar[idx].y)))
        {
            point p = ar[idx - 1];
            ar[idx - 1] = ar[idx];
            ar[idx] = ar[i];
            ar[i] = p;
            idx = idx - 1;
        }
    }
    for (int i = start + 1; i < r; ++i)
    {
        if (i == idx + 1 && (ar[i].x < ar[idx].x || (compare(ar[i].x, ar[idx].x) && ar[i].y < ar[idx].y)))
        {
            point p = ar[i];
            ar[i] = ar[idx];
            ar[idx] = p;
            idx = idx + 1;
        }
        else if (i > idx + 1 && (ar[i].x < ar[idx].x || (compare(ar[i].x, ar[idx].x) && ar[i].y < ar[idx].y)))
        {
            point p = ar[idx + 1];
            ar[idx + 1] = ar[idx];
            ar[idx] = ar[i];
            ar[i] = p;
            idx = idx + 1;
        }
    }
    return idx;
}

void quick_sort(point * ar, int l, int r)
{
    if (r - l <= 2)
    {
        return;
    }
    else
    {
        int q = prepare(ar, l, r);
        quick_sort(ar, l, q);
        quick_sort(ar, q, r);
    }
}

int check_polygon(polygon * P)
{
    line l;
    // find left down coordinate and right up
    point * points = P->points;
    int NumOfPoint = P->NumberOfPoints;
    
    quick_sort(points, -1, NumOfPoint);
    for (int i = 0; i < NumOfPoint - 1; i++)
    {
        if (compare(points[i].x, points[i + 1].x) && compare(points[i].y, points[i + 1].y))
        {
            free(points);
            return -1; // there are the same points
        }
    }
    
    create_line_by_two_points(&l, points, points + 1);
    
    for (int i = 0; i < NumOfPoint; ++i)
    {
        if (distance_between_point_and_line(&l, points + i))
        {
            break;
        }
        if (i == NumOfPoint - 1)
        {
            free(points);
            return 0;
        }
    }
    
    point LD = points[0];
    point RU = points[0];
    
    for (int i = 0 ; i < NumOfPoint; i++)
    {
        if (points[i].x < LD.x || (compare(points[i].x,LD.x) && points[i].y < LD.y))
        {
            LD = points[i];
        }
        if (points[i].x > RU.x || (compare(points[i].x,RU.x) && points[i].y > RU.y))
        {
            RU = points[i];
        }
    }
    
    if (compare(LD.x, RU.x))
    {
        free(points);
        return 0; // wrong polygon
    }
    
    
    create_line_by_two_points(&l, &LD, &RU);
    
    int UP = 0;
    int DOWN = 0;
    
    for (int i = 0 ; i < NumOfPoint; i++)
    {
        if ((compare(points[i].x, LD.x) && compare(points[i].y, LD.y)) || ((compare(points[i].x, RU.x) &&  compare(points[i].y, RU.y))))
        {
            UP++;
            DOWN++;
            continue;
        }
        if (distance_between_point_and_line(&l, &points[i]) > 0)
        {
            UP++;
        }
        else
        {
            DOWN++;
        }
    }
    
    point * Down_Pnt = (point *)malloc(sizeof(point) * DOWN);
    point * Up_Pnt = (point *)malloc(sizeof(point) * UP);
    
    UP = 0;
    DOWN = 0;
    for (int i = 0; i < NumOfPoint; i++)
    {
        if(((compare(points[i].x, LD.x) && compare(points[i].y, LD.y))) || (compare(points[i].x, RU.x) && compare(points[i].y, RU.y)))
        {
            point p = points[i];
            Down_Pnt[DOWN] = p;
            Up_Pnt[UP] = p;
            UP++;
            DOWN++;
            continue;
        }
        if (distance_between_point_and_line(&l, &points[i]) > 0)
        {
            point p = points[i];
            Up_Pnt[UP] = p;
            UP++;
        }
        else
        {
            point p = points[i];
            Down_Pnt[DOWN] = p;
            DOWN++;
        }
    }
    
    quick_sort(Down_Pnt, -1, DOWN);
    quick_sort(Up_Pnt, -1, UP);
    
    for (int i = 2; i < DOWN ; i++) // check down points
    {
        point vec1;
        point vec2;
        point left_point = Down_Pnt[i - 2];
        point mid_point = Down_Pnt[i - 1];
        point right_point = Down_Pnt[i];
        
        vec1.x = left_point.x - mid_point.x;
        vec1.y = left_point.y - mid_point.y;
        
        vec2.x = right_point.x - mid_point.x;
        vec2.y = right_point.y - mid_point.y;
        
        if (vec2.x * vec1.y - vec1.x * vec2.y < 0)
        {
            free(Down_Pnt);
            free(Up_Pnt);
            free(points);
            return 0; // wrong polygon
        }
    }
    
    for (int i = 2; i < UP ; i++) // check down points
    {
        point vec1;
        point vec2;
        point left_point = Up_Pnt[i - 2];
        point mid_point = Up_Pnt[i - 1];
        point right_point = Up_Pnt[i];
        
        vec1.x = left_point.x - mid_point.x;
        vec1.y = left_point.y - mid_point.y;
        
        vec2.x = right_point.x - mid_point.x;
        vec2.y = right_point.y - mid_point.y;
        
        if (vec2.x * vec1.y - vec1.x * vec2.y > 0)
        {
            free(Down_Pnt);
            free(Up_Pnt);
            free(points);
            return 0; // wrong polygon
        }
    }
    
    for (int i = 0; i < UP; i++)
    {
        points[i] = Up_Pnt[i];
    }
    int k = UP;
    for (int i = DOWN - 2; i > 0; i--)
    {
        points[k] = Down_Pnt[i];
        k++;
    }
    free(Down_Pnt);
    free(Up_Pnt);
    return 1;
}

void norm(line *l)
{
    double i;
    double A = l->A;
    double B = l->B;
    double C = l->C;
    i = sqrt(A * A + B * B);
    l->A = A / i;
    l->B = B / i;
    l->C = C / i;
}

void sum_of_points(point * p1, const point p2)
{
    p1->x += p2.x;
    p1->y += p2.y;
}

point make_point(double x, double y)
{
    point p;
    p.x = x;
    p.y = y;
    return p;
}

point intersection(line * l1, line * l2)
{
    point p;
    p.x = ((-l1->C )* l2->B - (-l2->C) * l1->B) / (l1->A * l2->B - l2->A * l1 ->B);
    p.y = (l1->A * (-l2->C) - l2->A * (-l1->C)) / (l1->A * l2->B - l2->A * l1 ->B);
    return p;
}

void new_cordinates(polygon *P, point * new_coor, double h)
{
    point * points = P->points;
    int Num_of_Points = P->NumberOfPoints;
    for (int i = 0; i < Num_of_Points; i++)
    {
        point left_point, mid_point, right_point, mid_point2;
        left_point = points[model(i - 1, Num_of_Points)];
        mid_point = points[i];
        right_point = points[model(i + 1, Num_of_Points)];
        
        mid_point2 = mid_point;
        
        line l1, l2;
        
        create_line_by_two_points(&l1, &left_point, &mid_point);
        create_line_by_two_points(&l2, &mid_point, &right_point);
        
        norm(&l1);
        norm(&l2);
        
        sum_of_points(&mid_point, make_point(l1.A * h, l1.B * h));
        sum_of_points(&mid_point2, make_point(l2.A * h, l2.B * h));
        
        sum_of_points(&right_point, make_point(l2.A * h, l2.B * h));
        sum_of_points(&left_point, make_point(l1.A * h, l1.B * h));
        
        line l1h, l2h;
        
        create_line_by_two_points(&l1h, &left_point, &mid_point);
        create_line_by_two_points(&l2h, &mid_point2, &right_point);
        
        point inter = intersection(&l1h, &l2h);
        
        new_coor[i] = inter;
    }
}

//int first_more(double x, double y)
//{
//    if (x > y)
//    {
//        return 1;
//    }
//    else if (compare(x, y))
//    {
//        return 2;
//    }
//    else
//    {
//        return 0;
//    }
//}
//
//int first_less(double x, double y)
//{
//    if (y > x)
//    {
//        return 1;
//    }
//    else if (compare(x, y))
//    {
//        return 2;
//    }
//    else
//    {
//        return 0;
//    }
//}
//
//void change_point(point * ChangablePoint, const point * NewPoint, char PriorityCoordiante, int priorfun1(double x, double y), int priorfun2(double x, double y))// PriorityCoordinate x, y PriorityDirection1 > < PriorityDirection2 > <
//{
//    if (PriorityCoordiante == 'x')
//    {
//        if (priorfun1(NewPoint->x, ChangablePoint->x) == 1 || ((priorfun1(NewPoint->x, ChangablePoint->x) == 2) && priorfun2(NewPoint->y, ChangablePoint->y)))
//        {
//            ChangablePoint->x = NewPoint->x;
//            ChangablePoint->y = NewPoint->y;
//        }
//    }
//    else
//    {
//        if (priorfun1(NewPoint->y, ChangablePoint->y) == 1 || ((priorfun1(NewPoint->y, ChangablePoint->y) == 2) && priorfun2(NewPoint->x, ChangablePoint->x)))
//        {
//            ChangablePoint->x = NewPoint->x;
//            ChangablePoint->y = NewPoint->y;
//        }
//    }
//}
//
//int check_polygon(polygon * P) // -3 it is a line
//{
//    int Number_of_Points = P->NumberOfPoints;
//    point * points = P->points;
//
//    if (Number_of_Points == 3)
//    {
//        line l;
//        create_line_by_two_points(&l, points, points + 1);
//        if(check_if_point_belongs_to_line(&l, points + 2))
//        {
//            return -3;
//        }
//        else
//        {
//            return 1; // it is okay
//        }
//    }
//    else
//    {
//        point LeftUp = points[0], LeftDown = points[0], DownLeft = points[0], DownRight = points[0], RightDown = points[0], RightUp = points[0], UpRight = points[0], UpLeft = points[0];
//        for (int i = 0; i < Number_of_Points; i++)
//        {
//            change_point(&LeftUp, points + i, 'x', first_less, first_more);
//            change_point(&LeftDown, points + i, 'x', first_less, first_less);
//            change_point(&DownLeft, points + i, 'y', first_less, first_less);
//            change_point(&DownRight, points + i, 'y', first_less, first_more);
//            change_point(&RightDown, points + i, 'x', first_more, first_less);
//            change_point(&RightUp, points + i, 'x', first_more, first_more);
//            change_point(&UpLeft, points + i, 'y', first_more, first_less);
//            change_point(&UpRight, points + i, 'y', first_more, first_more);
//        }
//        int LU, LR, DL, DR;
//        for (int i = 0; i < Number_of_Points; i++)
//        {
//            if (LeftUp.x <= points[i].x <= UpLeft.x)
//            {
//                if ()
//                {
//
//                }
//                LU++;
//            }
//            else if (UpRight.x <= points[i].x <= LeftUp.x)
//            {
//                RU++
//            }
//            else if ()
//        }
//    }
//    return 1;
//}
