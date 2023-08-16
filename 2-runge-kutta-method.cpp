#include <graphics.h>
#include <math.h>
#include <stdio.h>
#include <iostream>
#include "diffur.h"

using namespace std;

double delta, gamma, omega;

double f(double t, double x, double y){
    return x-pow(x,3)-delta*y+gamma*cos(omega*t);
}

int main(){
    setlocale(LC_ALL, "Russian");

    cout<<"RUNGE-KUTTA METHOD"<<endl;
    double a=0, b;
    double h=0.01;
    double x0, y0;
    double k1,k2,k3,k4,m1,m2,m3,m4;

    omega=1;delta=0.25;gamma=0.3;
    
    cout<<"Enter time value"<<endl;
    cin>>b;
    cout<<"Enter initial values: x(0) and dx/dt(0)"<<endl;
    cin>>x0>>y0;

    int n=(b-a)/h;
    double T[n]; double X[n]; double Y[n];
    T[0]=a; X[0]=x0; Y[0]=y0;

    for(int i=1; i<=n;i++){
        k1=Y[i-1];
        m1=f(T[i-1],X[i-1],Y[i-1]);
        k2=Y[i-1]+(h*m1)/2;
        m2=f(T[i-1]+h/2,X[i-1]+(h*k1)/2,Y[i-1]+(h*m1)/2);
        k3=Y[i-1]+(h*m2)/2;
        m3=f(T[i-1]+h/2,X[i-1]+(h*k2)/2,Y[i-1]+(h*m2)/2);
        k4=Y[i-1]+h*m3;
        m4=f(T[i-1]+h,X[i-1]+h*k3,Y[i-1]+h*m3);
        X[i]=X[i-1]+(h/6)*(k1+2*k2+2*k3+k4);
        Y[i]=Y[i-1]+(h/6)*(m1+2*m2+2*m3+m4);
        T[i]=T[i-1]+h;
    }

    init_Window((char*)"RUNGE-KUTTA METHOD");
    clear_Screen(WHITE);
    set_Coords(BLACK);
    for(int j=1;j<=n;j++){
        draw_Line(X[j-1],Y[j-1],X[j],Y[j],GREEN);
    }
    closegraph;
    system("PAUSE");
    return 0;
}
