#include <iostream>
#include <cmath>
#include <math.h>
#include <conio.h>
using  namespace std;

struct Section {
    double x0;
    double x1;
};

class funcs {
    int height;
    int column;
    double x0;
    double x1;
    double step;
    double *arrX;
    double *arrY;
    short sign;
public:
    funcs(int column, int height, double x0, double x1) {
        this->column = column+1;
        this->height = height+1;
        this->x0 = x0;
        this->x1 = x1;
        step = (x1 - x0) / column;
        step = round(step * 10000) / 10000;
        arrX = new double[ this->column];
        arrX[0] = x0;
        arrX[ this->column-1] = x1;
        for (int i = 1; i <  this->column; i++) {
            arrX[i] = arrX[i - 1] + step;
        }
        if(column>height){
            sign = -1;
        }else if(column<height){
            sign = 1;
        }else{
            sign = 0;
        }
        for (int i = 0; i <  this->column; i++) {
            cout<<arrX[i]<<" ";
        }
        cout<<"\n";
    }

    ~funcs() {
        delete[] arrX;
        delete[] arrY;
    }
    int strainPercentage(){
        return 0;
    };

    void deformationY(double * arrYTemp, int MAX){
        arrY = new double[column];
        for(int i=0; i<column; i++){
            arrY[i] = arrYTemp[i] * height/MAX;
        }
    }
    void powerFunctionTwo() {
        int min;
        int max;
        double MIN;
        double MAX;
        double *arrYTemp = new double[column];
        arrYTemp[0] = arrX[0] * arrX[0];
        MAX = arrYTemp[0];
        MIN = arrYTemp[0];
        for (int i = 1; i < column; i++) {
            arrYTemp[i] = arrX[i] * arrX[i];
            if(arrYTemp[i] > MAX){
                MAX = arrYTemp[i];
                max = i;
            }
            if(arrYTemp[i] < MIN){
                MIN = arrYTemp[i];
                min = i;
            }
        }
        for(int i=0; i<column; i++){
            cout<<arrYTemp[i]<<" ";
        }
        cout<<"\n";
        deformationY(arrYTemp, MAX);
    };


    void printXY() {
        for(int i=0; i<column; i++){
            cout<<arrY[i]<<" ";
        }
        cout<<"\n";
    }
};

int main() {
    funcs a(10, 5, -5, 5);
    a.powerFunctionTwo();
    a.printXY();

    return 0;
}
