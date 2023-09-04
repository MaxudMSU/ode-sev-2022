#include <graphics.h>
#include <math.h>
#include <stdio.h>
#include <iostream>
#include "diffur.h"

using namespace std;
double delta, g, omega;

double f(double t, double x, double y){
    return x-pow(x,3)-delta*y+g*cos(omega*t);
}

int main(){
    setlocale(LC_ALL, "Russian");
    cout<<"EULER METHOD"<<endl;
    double a=0, b; //время
    double h=0.01;
    double x0, y0;
    omega=1;delta=0.25;g=0.3;
    cout<<"Enter time value"<<endl;
    cin>>b;
    cout<<"Enter initial values: x(0) and dx/dt(0)"<<endl;
    cin>>x0>>y0;

    int n=(b-a)/h;
    double T[n]; double X[n]; double Y[n];
    T[0]=a; X[0]=x0; Y[0]=y0;

    for(int i=1; i<=n; i++){
        Y[i]=Y[i-1]+h*f(T[i-1],X[i-1],Y[i-1]);
        X[i]=X[i-1]+h*Y[i-1];
        T[i]=T[i-1]+h;
    }

    init_Window((char*)"EULER METHOD");
    clear_Screen(WHITE);
    set_Coords(BLACK);
    for(int j=1;j<=n;j++){
        draw_Line(X[j-1],Y[j-1],X[j],Y[j],GREEN);
    }
    getch();
    closegraph;
    return 0;
}