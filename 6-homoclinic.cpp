#include <graphics.h>
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <tuple>
#include "diffur.h"

using namespace std;

double h = 0.001;

vector<Point> gen(Point a, Point b){
    Point p1 = a.homoMap(1.35);
    Point p2 = b.homoMap(1.35);

    if (distance(p1,p2) > h){
        Point m = mid(a, b);
        vector<Point> g1 = gen(a, m);
        vector<Point> g2 = gen(m, b);
        g1.insert(g1.end(), g2.begin(), g2.end());
        return g1;
    }
    else{
        return vector<Point> {p1,p2};
    }
}

vector<Point> revGen(Point a, Point b){
    Point p1 = a.homoMapReverse(1.35);
    Point p2 = b.homoMapReverse(1.35);

    if (distance(p1,p2) > h){
        Point m = mid(a, b);
        vector<Point> g1 = revGen(a, m);
        vector<Point> g2 = revGen(m, b);
        g1.insert(g1.end(), g2.begin(), g2.end());
        return g1;
    }
    else{
        return vector<Point> {p1,p2};
    }
}

pair<Point,int> coef(Point p0, Point p1, Point p2, Point p3){
    if (p0.x == 0){
        return make_pair(Point(0,0),0);
    }
    double temp1 = p1.x - p0.x;
    double temp2 = p1.y - p0.y;
    double a = (p2.x - p0.x) / temp1; double b = (p3.x - p2.x) / temp1;
    double c = (p2.y - p0.y) / temp2; double d = (p3.y - p2.y) / temp2;

    double t2 = (c - a) / (b - d);
    double t1 = a + b * t2;

    if ((t1 >= 0) && (t1 <= 1) && (t2 >= 0) && (t2 <= 1)){
        return make_pair(Point(p0.x + temp1*t1, p0.y + temp2*t1),1);
    }
    else{
        return make_pair(Point(0,0),0);
    }
}

tuple<vector<Point>,vector<Point>,Point> intersection(vector<Point> v1, vector<Point> v2){
    vector<Point> newV1, newV2;
    for (int i = 0; i < v1.size(); i++){
        for (int j = 0; j < v2.size(); j++){
            pair<Point,int> saver = coef(v1[i],v1[i+1],v2[j],v2[j+1]);
            if (saver.second){
                for (int k = 0; k < i+1; k++){
                    newV1.push_back(v1[k]);
                }
                newV1.push_back(saver.first);
                for (int m = 0; m < j+1; m++){
                    newV2.push_back(v2[m]);
                }
                newV2.push_back(saver.first);
                return make_tuple(newV1, newV2, saver.first);
            }
        }
    }
}

int main(){
    init_Window();
    clear_Screen(WHITE);
    set_Grid(LIGHTGRAY);
    set_Coords(BLACK);
    
    vector<Point> V1{Point(0,0), Point(2.1583123951777, 1)}, V2{Point(0,0),Point(1.1583123951777, -1)};
    V1.push_back(V1[1].homoMap(1.35));
    V2.push_back(V2[1].homoMapReverse(1.35));


    vector<Point> gv1 = gen(V1[0], V1[1]);

    vector<Point> gv2 = revGen(V2[0], V2[1]);

    
    tuple<vector<Point>,vector<Point>,Point> u = intersection(gv1, gv2);
    vector<Point> newgv1 = get<0>(u);
    vector<Point> newgv2 = get<1>(u);
    Point homoklin = get<2>(u);

    for(int i = 1; i < newgv1.size(); i++){
        draw_Line(newgv1[i-1].x, newgv1[i-1].y, newgv1[i].x, newgv1[i].y, RED);

    }
    for(int j = 1; j < newgv2.size(); j++){
        draw_Line(newgv2[j-1].x, newgv2[j-1].y, newgv2[j].x, newgv2[j].y, GREEN);
    }
    getch();
    closegraph();
    return 0;
}