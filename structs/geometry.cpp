#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <vector>

class Shape
{
protected:
    virtual std::ostream& print(std::ostream &) const = 0;
public:
    friend std::ostream& operator<<(std::ostream&, const Shape &);
    virtual ~Shape() {}
};

std::ostream& operator<<(std::ostream& out, const Shape & a)
{
    return a.print(out);
}

class Point
{
private:
    int m_x = 0;
    int m_y = 0;
    int m_z = 0;
public:
    Point(int x, int y, int z): m_x(x), m_y(y), m_z(z){}
    
    friend std::ostream & operator << (std::ostream&, const Point &);
};

std::ostream & operator<<(std::ostream & out, const Point & p)
{
    out << '(' << p.m_x << ',' << p.m_y << ',' << p.m_z << ')';
    return out;
}

class Triangle: public Shape
{
    Point p1, p2, p3;
    
public:
    Triangle(const Point& p1_, const Point& p2_, const Point& p3_): p1(p1_), p2(p2_), p3(p3_){}
    
    virtual std::ostream& print(std::ostream & out) const override
    {
        out << "Triangle("<< p1 << ',' << p2 << ',' << p3 << ')';
        return out;
    }
};

class Circle: public Shape
{
    Point c;
    int R;
public:
    Circle(const Point& p, int r): c(p), R(r) {}
    
    virtual std::ostream& print(std::ostream & out) const override
    {
        out << "Circle(" << c << ',' << R << '}';
        return out;
    }
    
    int getRadius() const {return R;}
};

int getLargestRadius(std::vector<Shape *> v)
{
    int max = -1;
    Circle * S;
    for (auto it : v)
    {
        S = dynamic_cast<Circle *>(it);
        if (S == nullptr) continue;
        max = std::max(S->getRadius(), max);
    }
    return max;
}

int main()
{
    std::vector<Shape*> v;
    v.push_back(new Circle(Point(1, 2, 3), 7));
    v.push_back(new Triangle(Point(1, 2, 3), Point(4, 5, 6), Point(7, 8, 9)));
    v.push_back(new Circle(Point(4, 5, 6), 3));
 
    // Вывод элементов вектора v здесь
    
    for (auto it : v)
    {
        std::cout << *it << std::endl;
    }
 
    std::cout << "The largest radius is: " << getLargestRadius(v) << '\n'; // реализуйте эту функцию
 
    // Удаление элементов вектора v здесь
}
