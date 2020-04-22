#include <iostream>
#include <cmath>
#include <math.h>
#include <conio.h>
#include <fstream>
using  namespace std;

class funcs {
    int height;
    int column;
    double x0;
    double x1;
    double step;
    double *arrX;
    double *arrY;
    char **arr;
    int min;
    int max;
    double MIN;
    double MAX;
    double *arrYTemp;

    void MaxAndMin(int &min, int &max, double &MIN, double &MAX, double Y, int i){
        if(i==0) {
            MAX = Y;
            MIN = Y;
        }
        if(Y> MAX){
            MAX = Y;
            max = i;
        }
        if(Y < MIN){
            MIN = Y;
            min = i;
        }
    }

    void deformationY(double * arrYTemp, int MAX){
        for(int i=0; i<column; i++){
            arrY[i] = round(arrYTemp[i] * (height-1)/MAX);
        }
    }
public:
    funcs(int column, int height, double x0, double x1) {
        this->column = column+1;
        this->height = height+1;
        this->x0 = x0;
        this->x1 = x1;

        //шаг по x от x0 до x1
        step = (x1 - x0) / column;
        step = round(step * 10000) / 10000;
        //шаг

        //отрезок от x0 до x1
        arrX = new double[ this->column];
        arrX[0] = x0;
        arrX[ this->column-1] = x1;
        //

        //массив с индексами в конечном графике
        arrY = new double[column];
        //

        //массив с вычисленными точками по Y
        arrYTemp = new double[column];
        //

        for (int i = 1; i < this->column-1; i++) {
            arrX[i] = arrX[i - 1] + step;
        }
    }
    ~funcs() {
        delete[] arrX;
        delete[] arrY;
        delete[] arrYTemp;
    }



    void powerFunctionTwo() {
        for (int i = 0; i < column; i++) {
            arrYTemp[i] = arrX[i] * arrX[i];
            MaxAndMin(min, max, MIN, MAX,  arrYTemp[i], i );
        }
        deformationY(arrYTemp, MAX);
    };


    void printXY() {
        arr=new char*[height];
        for(int i=0; i<height; i++){
            arr[i] = new char[column];
            for(int j=0; j<column; j++){
                arr[i][j]= ' ';
            }
        }
        for(int i=0; i<column; i++){
//            for(int j=0; j<=int(arrY[i]); j++){
//                arr[j][i]='#';
//            }
            arr[int(arrY[i])][i]='#';
        }
        ofstream fout;
        fout.open("file.txt");
        for(int i=height-1; i>=0; i--){
            for(int j=column-1; j>=0; j--){
                fout <<arr[i][j];
            }
            fout<<"\n";
        }
        fout.close();
    }
};

int main() {
    funcs a(10, 20, -5, 5);
    a.powerFunctionTwo();
    a.printXY();

    return 0;
}



