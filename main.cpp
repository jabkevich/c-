#include <iostream>
#include <cmath>
#include <math.h>
#include <conio.h>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
using  namespace std;

class funcs {
    int height;
    int heightP=0;
    int heightN=0;
    int column;
    vector<double> arrX;
    vector<double> arrYPositive;
    vector<double>arrYNegative ;
    vector<double> arrXYP;
    vector<double>arrXYN ;
    int min;
    int max;

    double MIN;
    double MAX;
    vector<double> arrYTemp;

    void clear(){
        MIN =0;
        MAX =0;
        min =0;
        max =0;
        heightP=0;
        heightN=0;
        arrYPositive.clear();
        arrYNegative.clear();
        arrXYP.clear();
        arrXYN.clear();
        arrYPositive.resize(this->column);
        arrYNegative.resize(this->column);
        arrXYP.resize(this->column);
        arrXYN.resize(this->column);
        arrYTemp.resize(this->column);
    }

    void MaxAndMin(int &min, int &max, double &MIN, double &MAX, double Y, int i){
            if (Y > 0) {
                heightP++;
            } else if (Y < 0) {
                heightN++;
            }
        if(MAX!=MAX||MIN!=MIN){
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

    void deformationY( vector<double> arrYTemp){
        while(heightN+heightP<height){
            if(heightN!=0){
                heightN++;
            }
            if(heightN+heightP==height) break;
            if(heightP!=0) {
                heightP++;
            }
        }
        while(heightN+heightP>height){
            if(heightN>0){
                heightN--;
            }
            if(heightN+heightP==height) break;
            if(heightP>0) {
                heightP--;
            }
        }
        int k=0;
        int j=0;
        if(MAX==0){MAX++;}
        for(int i=0; i<column; i++){
            if(arrYTemp[i]>=0) {arrYPositive[k] = round(arrYTemp[i] * (heightP) / abs(MAX));while(arrYPositive[k]>heightP){arrYPositive[k]--;}arrXYP[k++] =i;  }
            if(arrYTemp[i]<0) {arrYNegative[j] = round(arrYTemp[i] * (heightN) / abs(MIN))*-1;while(arrYNegative[j] >heightN){arrYNegative[j]--;}arrXYN[j++] =i;}
        }
        arrXYP.resize(k);
        arrYPositive.resize(k);
        arrXYN.resize(j);
        arrYNegative.resize(j);
    }
public:
    funcs(int column, int height, double x0, double x1) {
        this->column = column+1;
        this->height = height+1;

        //шаг по x от x0 до x1
        double step = (x1 - x0) / column;
        step = round(step * 10000) / 10000;
        //шаг

        //отрезок от x0 до x1
        arrX.resize(this->column);
        arrX[0] = x0;
        arrX[ this->column-1] = x1;
        //

        //массив с индексами в конечном графике
        arrYPositive.resize(this->column);
        arrYNegative.resize(this->column);

        arrXYP.resize(this->column);
        arrXYN.resize(this->column);
        //

        //массив с вычисленными точками по Y
        arrYTemp.resize(this->column);
        //

        for (int i = 1; i < this->column-1; i++) {
            arrX[i] = arrX[i - 1] + step;
        }
    }


    void Test(vector<double> arr, string  str){
        int size = arr.size();
        cout<<str<<":\n";
        for (int i = 0; i <arr.size(); i++) {
            cout<<arr[i]<<" ";
        }
        cout<<"\n";
    }
    void LogFunctionTwo() {
        clear();
        for (int i = 0; i < column; i++) {
            arrYTemp[i] = -arrX[i]*log(arrX[i]);
            MaxAndMin(min, max, MIN, MAX,  arrYTemp[i], i );
        }
        Test(arrX, "arrX");
        Test(arrYTemp,"arrYTemp");
        deformationY(arrYTemp);
        Test(arrYPositive, "arrYPositive");
        Test(arrYNegative, "arrYNegative");
        Test(arrXYP, "arrXYP");
        Test(arrXYN, "arrXYN");
        cout<<"MAX: "<<MAX<<"\n";
        cout<<"MIN: "<<MIN<<"\n";
        cout<<"P: "<< heightP<<"\n";
        cout<<"N: "<< heightN<<"\n";
    };
    void rootFunctionTwo() {
        clear();
        for (int i = 0; i < column; i++) {
            arrYTemp[i] = arrX[i];
            MaxAndMin(min, max, MIN, MAX,  arrYTemp[i], i );
        }

        deformationY(arrYTemp);


    };
    void powerFunctionTwo() {
        clear();
        for (int i = 0; i < column; i++) {
            arrYTemp[i] =arrX[i]*arrX[i];
            MaxAndMin(min, max, MIN, MAX,  arrYTemp[i], i );
        }

        deformationY(arrYTemp);
    };

    void Print(){
        if(heightN>0){
        heightN++;
        }
        if(heightP>0) {
            heightP++;
        }
        vector<vector<char>> arrP(heightP,  vector<char>(column));
        vector<vector<char>> arrN(heightN,  vector<char>(column));

        for(int i=0; i<heightP; i++){
            for(int j=0; j<column; j++){
                arrP[i][j] ='+';
            }
        }
        for(int i=0; i<heightN; i++){
            for(int j=0; j<column; j++){
                arrN[i][j] ='+';
            }
        }
        for(int i=0; i<arrYPositive.size(); i++){
            if(int(int(arrYPositive[i])==0)){
                for(int j=0; j<column; j++) {
                    arrP[int(arrYPositive[i])][j] = '-';
                }
            }
        }
        for(int i=0; i<arrYPositive.size(); i++){
            arrP[int(arrYPositive[i])][int(arrXYP[i])]='#';
        }
        for(int i=0; i<arrYNegative.size(); i++) {
            arrN[int(arrYNegative[i])][int(arrXYN[i])] = '#';
        }
        ofstream fout;
        fout.open("file.txt");
        for(int i=heightP-1; i>=0; i--){
            for(int j=0; j<column; j++){
                fout <<arrP[i][j];
            }
            fout<<"\n";
        }
        for(int i=1; i<heightN; i++){
            for(int j=0; j<column; j++){
                fout <<arrN[i][j];
            }
            fout<<"\n";
        }
        fout.close();
    }

};

int main() {
    funcs a(100, 40, 0, 2);
    a.LogFunctionTwo();
    a.Print();
    return 0;
}



