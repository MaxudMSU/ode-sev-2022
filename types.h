#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

#include <math.h>
#include <fstream>

class Area{
public:
    double x_left, y_top, x_right, y_down;
    Area (double a, double b, double c, double d): x_left(a),y_top(b),x_right(c),y_down(d){}
    int get_hx(double h){return (x_right-x_left)/h;}
    int get_hy(double h){return (y_top-y_down)/h;}
    double get_xleft(){return x_left;}
    double get_ytop(){return y_top;}
    double get_xright(){return x_right;}
    double get_ydown(){return y_down;}
    void color_сell(int num, double h,int color);
    // void set_area(double h);
};

class Point{
    
public:
    double x,y;
    Point(){}
    Point(float xx,float yy){x=xx; y=yy;}
    double getx() {return x;}
    double gety() {return y;}
    //метод для определения номера ячейки, в которой находится точка
    int cell(Area& a, int n, double h){
        if(x<a.x_left || x>a.x_right || y>a.y_top || y<a.y_down) return 0;
        int nomer = floor((fabs(a.y_top-y))/h)*n + (ceil ((fabs(a.x_left-x))/h));
        if (x==a.x_left) nomer++;
        if (y==a.y_down) nomer-=n;
        return nomer;
    }

    int cell2(double x_left, double y_top, double x_right, double y_down, int n, double h){
        if(x<x_left || x>x_right || y>y_top || y<y_down) return 0;
        int nomer = floor((fabs(y_top-y))/h)*n + (ceil ((fabs(x_left-x))/h));
        if (x==x_left) nomer++;
        if (y==y_down) nomer-=n;
        return nomer;
    }
    Point& julia(double a,double b){
        double xj=pow(x,2)-pow(y,2)+a;
        double yj=2*x*y+b;
        x=xj;
        y=yj;
        return *this;
    }
    Point& henon(double a,double b){
        double xh=1+y-a*pow(x,2);
        double yh=b*x;
        x=xh;
        y=yh;
        return *this;
    }
    Point homoMap(double a){
        double xhm=x+y+a*x*(1-x);
        double yhm=y+a*x*(1-x);
        return Point(xhm,yhm);
    }
    Point homoMapReverse(double a){
        double xhmr = x - y;
        double yhmr = y - a*(x-y)*(1-x+y);
        return Point(xhmr, yhmr);
    }
    void print(){
        std::cout << x << ", " << y << std::endl;
    }

    void fprint(std::ofstream fout){
        fout << x << ", " << y << std::endl;
    }

    void draw(int color);
};

double distance(Point a, Point b){
    return sqrt(pow(a.x - b.x,2) + pow(a.y - b.y,2));
}

Point mid(Point a, Point b){
    return Point((a.x+b.x)/2, (a.y+b.y)/2);
}

template <typename T>
class TwoDimArray{
public:
    T** M; int m, n; 
    TwoDimArray(){
        n = m = 0; M = nullptr;
    }
    TwoDimArray(int _n){
        m = _n;
        n = _n;
        M = (T**) new T*[m];

        for (int i = 0; i < m; i++) 
            M[i] = (T*)new T[n];

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                M[i][j] = 0;
    }
    TwoDimArray(Area& a, double h){
        m = a.get_hy(h);
        n = a.get_hx(h);
        M = (T**) new T*[m];

        for (int i = 0; i < m; i++)
            M[i] = (T*)new T[n];
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                M[i][j] = 1;
    }
    TwoDimArray(const TwoDimArray& _M){
        m = _M.m;
        n = _M.n;
        M = (T**) new T*[m];

        for (int i = 0; i < m; i++)
            M[i] = (T*) new T[n];

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                M[i][j] = _M.M[i][j];
    }
    TwoDimArray operator=(const TwoDimArray& _M){
        if (n > 0){
            for (int i = 0; i < m; i++)
                delete[] M[i];
        }

        if (m > 0) delete[] M;
    
        m = _M.m;
        n = _M.n;
        M = (T**) new T*[m];
        for (int i = 0; i < m; i++)
            M[i] = (T*) new T[n];
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                M[i][j] = _M.M[i][j];
        return *this;
    }
    ~TwoDimArray(){
        if (n > 0){
            for (int i = 0; i < m; i++)
                delete[] M[i];
        }

        if (m > 0) delete[] M;
    }
    void division(Area& a, double h){
        int ny=0, nx;
        TwoDimArray<int> t(a,h/2);
        for (int i=0; i<m;i++){
            nx=0;
            for(int j=0;j<n;j++){
                t.M[i+ny][j+nx]=M[i][j];
                t.M[i+ny][j+1+nx]=M[i][j];
                t.M[i+1+ny][j+nx]=M[i][j];
                t.M[i+1+ny][j+1+nx]=M[i][j];
                nx++;
            }
            ny++;
        }
        *this=t;
    }
};

#endif // TYPES_H_INCLUDED
