#ifndef DIFFUR_H_INCLUDED
#define DIFFUR_H_INCLUDED

#include <graphics.h>
#include "types.h"

/*КОНСТАНТЫ*/
#define wWidth 600  //ширина окна
#define wHeight 600 //высота окна
#define scale 150   //масштаб картинки: размер единичного отрезка в пикселях

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
    // circle(xx,yy ,2);
    // setfillstyle(SOLID_FILL, color);
    // floodfill(xx, yy, WHITE);
    setcolor(color);
    fillellipse(xx,yy,2,2);
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


    //метод для рисования области по заданному размеру ячейки
//    void Area::set_area(double h){
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
void Area::color_сell(int num, double h,int color){
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

void Point::draw(int color){
    draw_Point_bycrcl(x, y, color);
}


// class Line{
// public:
//     Point start, end;
//     Line *parts = this;
//     Line(Point s, Point e){start=s; end=e;}

//     Point middle(){
//         double xm = (start.getx() + end.getx())/2;
//         double ym = (start.gety() + end.gety())/2;
//         return Point(xm, ym);
//     }

//     void draw(int color){
//         draw_Line(start.getx(), start.gety(), end.getx(), end.gety(), color);
//     }

// };

#endif // DIFFUR_H_INCLUDED
