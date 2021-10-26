#include "oscillators.h"

Oscillators::Oscillators()
{

   L=50.0, M=1.0*L, ES = 20000.0;

   std::cout<< "Enter number of elements"<<std::endl;
   int nel;
   std::cin >> nel;

   h=L/(double)nel; m=M/(double)(nel+1), c = ES/h;
   b=0.001;

   x.resize(nel+1,0);
   v.resize(nel+1,0);

   std::cout << "Created a set of "<< (nel+1)<< " oscillators"<<std::endl;

}

void Oscillators::SetInitialConditions(vector<double> x0, vector<double> v0)
{
#pragma omp for
for (int i=0;i<x.size();i++) {x[i]=x0[i];v[i]=v0[i];}
}
void Oscillators::PrintState(string fname)
{
    ofstream wave(fname, ios_base::out);
    if (wave.is_open()) {
        wave << "   X   ,   Y   ,   Z   "<< endl;
        for (int j=0;j<x.size();j++)
            wave << j*h+x[j]<< " , 0 , 0 " << endl;
        wave.close();}
    else {cout << "Error! could not open file for write"<<endl;
        return;}
}

Oscillators::~Oscillators()
{
std::cout << "Good-bye! "<<std::endl;
}

