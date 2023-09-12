#include <math.h>
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include "types.h"

using namespace std;

int main(){
    setlocale(LC_ALL, "Russian");

    double x_left=-1, y_top=1.5, x_right=1, y_down=-1.5, h=0.5, a=0.2,b=-0.2;
    Area area(x_left, y_top, x_right, y_down);
    int n_x, n_y, cell_num, current_cell,points_amount=50;

    n_x=(x_right-x_left)/h;
    n_y=(y_top-y_down)/h;
    int cell_amount=n_x*n_y;

    int randh=(h*1000)+1;

    TwoDimArray<int> celling(cell_amount);
    Point points[points_amount];

//    int prov[n_y][n_x];
//    prov[1][1]=1;

    //cout<<"-----------------------------------------"<<endl;
    srand(time(NULL));
    for(int k=0; k<n_y; k++){
        for(int i=0; i<n_x; i++){
            //if(!prov[k][i]) continue;
            current_cell=k*n_x+i;
            for (int j=0; j<points_amount; j++){
                points[j] = Point(0.001*(rand()%randh +1000*x_left+h*1000*i),0.001*(rand()%randh+1000*(y_top-h)-h*1000*k));
                points[j].julia(a,b);
                // cell_num=points[j].cell2(x_left, y_top, x_right, y_down, n_x, h);
                cell_num=points[j].cell(area, n_x, h);
                celling.M[current_cell][cell_num-1]=1;
            }
            if(current_cell<9) cout<<"  "<<current_cell+1<<" => ";
            else cout<<" "<<current_cell+1<<" => ";
            for (int l=0; l<cell_amount; l++){
                if (celling.M[current_cell][l]==1){
                    cout<<l+1<<" ";
                    celling.M[current_cell][l]=0;
                };
                //cout<<celling[current_cell][l];
            }
            cout<<endl;
        }
    }
    return 0;
}
