#include <graphics.h>
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <list>
#include <stack>
#include <chrono>
#include <algorithm>
#include <vector>
#include <iterator>
#include "types.h"
#include "diffur.h"

#define NIL -1

using namespace std;
//using namespace chrono;

const double p_a=0.2, p_b=-0.2;

int ones_amount(TwoDimArray<int> a){
    int temp=0;
    for (int i=0; i<a.m; i++)
        for (int j=0; j<a.n; j++)
            if (a.M[i][j]) temp++;
    return temp;
}

//void TwoDimArray::division(Area& a, double h){
//    int ny=0, nx;
//    TwoDimArray<int> t(a,h/2);
//    for (int i=0; i<m;i++){
//        nx=0;
//        for(int j=0;j<n;j++){
//            t.M[i+ny][j+nx]=M[i][j];
//            t.M[i+ny][j+1+nx]=M[i][j];
//            t.M[i+1+ny][j+nx]=M[i][j];
//            t.M[i+1+ny][j+1+nx]=M[i][j];
//        nx++;
//        }
//        ny++;
//    }
//    *this=t;
//}

void zero(int num, Area& a, TwoDimArray<int> b, double h){
    int hx=a.get_hx(h);
    int otstup_x, otstup_y;
    if(num%hx==0){
        otstup_x=hx-1;
        otstup_y=(num/hx)-1;
    }
    else{
        otstup_x=(num % hx)-1;
        otstup_y=floor(num/hx);
    }
    b.M[otstup_y][otstup_x]=0;
}

Area w(-1.5,1.5,1.5,-1.5); double h=0.5;
TwoDimArray<int> vozvrat(w,h);

//void color_cell(int num, Area& a, double h){
//    setcolor(BLACK);
//    setfillstyle(SOLID_FILL, BLACK);
//    int otstup_x, otstup_y;
//    int hx=(a.x_right-a.x_left)/h;
//    if(num%hx==0){
//        otstup_x=hx-1;
//        otstup_y=(num/hx)-1;
//    }
//    else{
//        otstup_x=(num % hx)-1;
//        otstup_y=floor(num/hx);
//    }
//    double xl=a.x_left+h*otstup_x;
//    double yt=a.y_top-h*otstup_y;
//    double xr=xl+h;
//    double yd=yt-h;
//    drawRectangle(xl,yt,xr,yd);
//}

class Graph{
    int V;    // ���������� ������
    list<int> *adj;    // ������������ ������ ������� ���������
    void SCCUtil(int u, int disc[], int low[], stack<int> *st, bool stackMember[], Area& wrkng, double h);
public:
    Graph(){};
    Graph(int V);
    void addEdge(int v, int w);
    void SCC(Area& wrkng, double h);
};

Graph::Graph(int V){
    this->V = V;
    adj = new list<int>[V];
}

void Graph::addEdge(int v, int w){
    adj[v].push_back(w);
}

void Graph::SCCUtil(int u, int disc[], int low[], stack<int> *st, bool stackMember[], Area& wrkng, double h){
    static int time = 0;

    disc[u] = low[u] = ++time;
    st->push(u);
    stackMember[u] = true;
    list<int>::iterator i;

    for (i = adj[u].begin(); i != adj[u].end(); ++i){
        int v = *i;
        if (disc[v] == -1){
            SCCUtil(v, disc, low, st, stackMember, wrkng, h);
            low[u]  = min(low[u], low[v]);
        }
        else if (stackMember[v] == true)
            low[u]  = min(low[u], disc[v]);
    }

    int w = 0;

    if (low[u] == disc[u]){
        while (st->top() != u){
            w = (int) st->top();
            wrkng.color_сell(w+1, h,RED);
            stackMember[w] = false;
            st->pop();
        }
        w = (int) st->top();
        zero(w+1,wrkng,vozvrat,h);
        stackMember[w] = false;
        st->pop();
    }
}

void Graph::SCC(Area& wrkng, double h){
    int *disc = new int[V];
    int *low = new int[V];
    bool *stackMember = new bool[V];

    stack<int> *st = new stack<int>();

    for (int i = 0; i < V; i++){
        disc[i] = NIL;
        low[i] = NIL;
        stackMember[i] = false;
    }

    for (int i = 0; i < V; i++)
        if (disc[i] == NIL)
            SCCUtil(i, disc, low, st, stackMember, wrkng, h);
}

//void simv_obraz(Area& a, double h, Graph& g){
//    int n_x=(a.x_right-a.x_left)/h;
//    int n_y=(a.y_top-a.y_down)/h;
//    int cell_amount=n_x*n_y, cell_num, current_cell,points_amount=100;
//    int randh=(h*1000)+1;
//    MATRIX<int> celling(cell_amount);
//    Point points[points_amount];
//    g=cell_amount;
//    srand(time(NULL));
//    for(int k=0; k<n_y; k++){
//        for(int i=0; i<n_x; i++){
//            if(vozvrat.M[k][i]){
//                current_cell=k*n_x+i;
//                for (int j=0; j<points_amount; j++){
//                    points[j] = Point(0.001*(rand()%randh +1000*a.x_left+h*1000*i),0.001*(rand()%randh+1000*(a.y_top-h)-h*1000*k));
//                    points[j].julia(p_a,p_b);
//                    cell_num=points[j].cell(a, n_x, h);
//                    celling.M[current_cell][cell_num-1]=1;
//                }
//                for (int l=0; l<cell_amount; l++){
//                    if (celling.M[current_cell][l]==1){
//                        g.addEdge(current_cell,l);
//                        celling.M[current_cell][l]=0;
//                    };
//                }
//            }
//            else continue;
//        }
//    }
//}

//double xfunc (double x, double y){
//    return (1+y-a*x*x);
//}
//
//double yfunc (double x, double y){
//    return (b*x);
//}

void symb_image(Area& a, double h, Graph& g){
    double x0=a.x_left, x1=a.x_right, y0=a.y_down, y1=a.y_top;
    int pt = 10;       // squrt of point number
    int k = 0;
    int counter = 1;
    double xrez, yrez, cellrez ;
    double xtemp = x0;
    double ytemp = y1;
    Point temp(x0,y1);
    double xcikl = x0;
    double ycikl = y1;
    vector<int> cell_list;
    double leng = abs(x1 - x0) / h;
    while (ycikl > y0){
        while (xcikl < x1){
            for (int i=0;i<pt;i++) {
                for (int j=0;j<pt;j++){
                    //xrez = xfunc(xtemp, ytemp);
                    //yrez = yfunc(xtemp, ytemp);
                    temp.julia(p_a,p_b);
                    temp.x += 1.0/pt*h;
                    cellrez = temp.cell(a,leng,h);
                    if ((find(begin(cell_list), end(cell_list), cellrez) == end(cell_list)) && (cellrez != 0))
                        cell_list.push_back(cellrez);
                }
                temp.x = xcikl;
                temp.x -= 1.0/pt*h;
            }
            xcikl += h;
            temp.x = xcikl;
            temp.y = ycikl;
            sort(begin(cell_list), end(cell_list));
            for (int jf=0;jf<cell_list.size();jf++)
                g.addEdge(counter,jf);
                // cout<<cell_list[jf]<<" ";
            ++counter;
            cell_list.clear();
        }
    ycikl -= h;
    xcikl = x0;
    temp.x = xcikl;
    temp.y = ycikl;
    }
    //return 0;
}

int main(){
    //auto begin = steady_clock::now();
    setlocale(LC_ALL, "Russian");
    int iter_num=2;


    Graph graphs[iter_num];

    for (int i=0;i<iter_num;i++){
        symb_image(w, h/pow(2,i), graphs[i]);
        init_Window((char*)"chain recursion set");
        clear_Screen(WHITE);
        //set_area(w,h);
        graphs[i].SCC(w, h/pow(2,i));
        //auto end = steady_clock::now();
        //auto elapsed_ms = duration_cast<milliseconds>(end - begin);
        //cout <<"Iteration � "<<i+1<<", time: " << elapsed_ms.count() << " ms, cells: "<<vozvrat.ones_amount()<<endl;
        //cout
        vozvrat.division(w,h/pow(2,i+1));
    }

    closegraph;
    system("PAUSE");
    return 0;
}
