#include <graphics.h>
#include <math.h>
#include <stdio.h>
#include <iostream>
#include "diffur.h"

using namespace std;

int main(){
    setlocale(LC_ALL, "Russian");

    int n=10000;
    double x0=0,y0=0,a=1.4,b=0.3;
    double X[n],Y[n];
    cout<<"Enter coordinates of the initail point"<<endl;
    cin>>x0>>y0;
    X[0]=x0, Y[0]=y0;

    for(int i=1;i<=n;i++){
        X[i]=1+Y[i-1]-a*pow(X[i-1],2);
        Y[i]=b*X[i-1];
    }
    init_Window((char*)"Trajectory of Henon's diffeomorphism");
    clear_Screen(BLACK);
    set_Coords(WHITE);
    for(int j=1;j<=n;j++){
        draw_Point_bypxl(X[j-1],Y[j-1],YELLOW);
    }
    getch();
    closegraph;
    return 0;
}
