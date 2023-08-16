#ifndef DIFFUR_H_INCLUDED
#define DIFFUR_H_INCLUDED

#include <graphics.h>

/*КОНСТАНТЫ*/
#define wWidth 600  //ширина окна
#define wHeight 600 //высота окна
#define scale 200   //масштаб картинки: размер единичного отрезка в пикселях

/*ФУНКЦИИ ДЛЯ ПОДГОТОВКИ ОКНА*/
//создание окна с заданными выше размерами
void init_Window(char* header=(char*)""){
    initwindow(wWidth,wHeight);
}

//заливка цветом
void clear_Screen(int color){
    setcolor(color);
    setfillstyle(SOLID_FILL, color);
    bar(0,0,wWidth,wHeight);
}

//координатные оси с центром в середине окна
void set_Coords(int color, char* horizontal=(char*)"",char* vertical=(char*)""){
    setcolor(color);
    line(wWidth/2,0,wWidth/2,wHeight);
    line(0,wHeight/2,wWidth,wHeight/2);
    line(wWidth-30,wHeight/2 - 10, wWidth, wHeight/2);
    line(wWidth-30,wHeight/2 + 10, wWidth, wHeight/2);
    line(wWidth/2,0,wWidth/2 + 10,30);
    line(wWidth/2,0,wWidth/2 - 10,30);
    setbkcolor(WHITE);
    outtextxy(wWidth-20, wHeight/2+12, horizontal);
    outtextxy(wWidth/2 - 50, 12, vertical);
}

//сетка координат
void set_Grid(int color){
    setcolor(color);
    for(int k=0;k<wHeight/2;k+=scale){
        line(0,wHeight/2 + k,wWidth,wHeight/2 + k);
        line(0,wHeight/2 -k, wWidth, wHeight/2 -k);
    }
    for(int j=0;j<wWidth/2;j+=scale){
        line(wWidth/2 + j,0,wWidth/2 + j,wHeight);
        line(wWidth/2 - j,0,wWidth/2 - j,wHeight);
    }
}

/*НЕОБХОДИМЫЕ ФУНКЦИИ ДЛЯ РИСОВАНИЯ*/
//рисование точки в виде пикселя
void draw_Point_bypxl(double x, double y, int color){
    int xx=wWidth/2 + int(x*scale);
    int yy=wHeight/2 - int(y*scale);
    putpixel(xx,yy,color);
}

//рисование точки в виде круга радиусом 2 пикселя
void draw_Point_bycrcl(double x, double y, int color){
    int xx=wWidth/2 + int(x*scale);
    int yy=wHeight/2 - int(y*scale);
    setfillstyle(SOLID_FILL, color);
    circle(xx,yy ,2);
    floodfill(xx, yy, WHITE);
}

//рисование отрезка по координатам начала и конца
void draw_Line(double startPosX, double startPosY, double endPosX, double endPosY, int color){
    setcolor(color);
//    setlinestyle(0, 0, 3);
    line(wWidth/2 + int(startPosX*scale),wHeight/2 - int(startPosY*scale),wWidth/2 + int(endPosX*scale),wHeight/2 - int(endPosY*scale));
}

//рисование прямоугольника по координатам верхнего левого и нижнего правого угла
void draw_Rectangle(double a, double b, double c, double d, int color){
    setcolor(color);
    rectangle(wWidth/2 + a*scale, wHeight/2 - b*scale, wWidth/2 + c*scale, wHeight/2 - d*scale);
}
//рисование прямоугольника по координатам верхнего левого и нижнего правого угла с заливкой цветом
void draw_Rectangle_filled(double a, double b, double c, double d, int color){
    setcolor(color);
    setfillstyle(SOLID_FILL, color);
    bar(wWidth/2 + a*scale, wHeight/2 - b*scale, wWidth/2 + c*scale, wHeight/2 - d*scale);
}

/*НЕОБХОДИМЫЕ КЛАССЫ*/

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
    //метод для рисования области по заданному размеру ячейки
//    void set_area(double h){
//        int hh=h*scale;
//        int hy=2*y_top*scale;
//        int hx=-2*x_left*scale;
//        draw_Rectangle(x_left, y_top, x_right, y_down);
//
//        for(int k=0;k<=hy;k+=hh){
//            draw_Line(x_left,y_top + k,x_right,y_top + k);
//        }
//        for(int j=0;j<=hx;j+=hh){
//            line(x_left + j,y_down,x_left + j,y_down);
//        }
//    }
    //метод для закрашивания ячейки области по номеру ячейки
   void color_cell(int num, double h,int color){
       int otstup_x, otstup_y;
       int hx=get_hx(h);
       if(num%hx==0){
           otstup_x=hx-1;
           otstup_y=(num/hx)-1;
       }
       else{
           otstup_x=(num % hx)-1;
           otstup_y=floor(num/hx);
       }
       double xl=x_left+h*otstup_x;
       double yt=y_top-h*otstup_y;
       double xr=xl+h;
       double yd=yt-h;
       draw_Rectangle_filled(xl,yt,xr,yd,color);
   }
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
};

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

#endif // DIFFUR_H_INCLUDED
