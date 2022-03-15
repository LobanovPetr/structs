#pragma once
#ifndef Header_h
#define Header_h

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <math.h>

typedef struct point point;

struct point
{
    double x;
    double y;
};


typedef struct polygon polygon;

struct polygon {
    int NumberOfPoints;
    point * points;
};

typedef struct line line;

struct line {
    double A;
    double B;
    double C;
};

void define_point(point *, double x, double y);
int define_polygon(polygon *p, char * name);
void create_line_by_two_points(line * l, const point *p1, const point * p2);
int compare(double x, double y);
int distance_between_point_and_line(const line * l, const point * p1);
int check_polygon(polygon * P);
void norm(line *l);
void new_cordinates(polygon *P, point * new_coor, double h);
void sum_of_points(point * p, const point p2);
int model(int x, int y);
int prepare(point *ar, int l, int r);
void quick_sort(point * ar, int l, int r);

point make_point(double x, double y);
point intersection(line *l1, line *l2);

#endif /* Header_h */
