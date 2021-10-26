#ifndef OSCILLATORS_H
#define OSCILLATORS_H

#include <vector>
#include <iostream>
#include <fstream>  //file io

using namespace std;


class Oscillators
{
public:
    double L,M,ES,b; // характеристики волновода
    double h,m,c;  //параметры дискретизации
    std::vector<double> x, v; // массив смещений грузов от положения равновесия
                              // и массив скоростей смещений

    void SetInitialConditions(vector<double> x0, vector<double> v0);
    void PrintState(string fname);
    Oscillators();
    ~Oscillators();
};

#endif // OSCILLATORS_H
