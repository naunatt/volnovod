#include <iostream>
#include <sstream>  //string converter library
#include <omp.h>
#include <ctime>
#include "oscillators.h"

using namespace std;

int main()
{
    Oscillators rod;
    vector<double> x0(rod.x.size(),0),v0(rod.x.size(),0); // zero initial conditions

    double const eps = 0.1;
    unsigned int N = rod.x.size();

    double t = clock(); // start time
//omp_set_num_threads(2);
#pragma omp parallel
    {
        cout << "hi from thread number "<< omp_get_thread_num()<<endl;

#pragma omp for
    for (int i=0;i<N;i++) x0[i]=rod.h*i*eps; //static excitation of oscillations
//    v0[N-1] =20; //dynamic excitation of oscillations (impact)

    rod.SetInitialConditions(x0,v0);                    // set initial conditions

    double tfin = 3;
    double timestep = 0.001;  //time inegration step
    int num_steps = tfin/timestep;     //number of time steps
    double outstep = 0.1;
    int num_outsteps = outstep/timestep;        // define output frequency

    // loop over time:

    for (int i=0;i<num_steps;i++) // loop over timesteps
    {
#pragma omp for
        for (int j=1;j<N;j++) //loop over oscillators
        {
            if (j==(N-1))
                    rod.v[j]+= timestep*(-rod.b/rod.m*rod.v[j]-
                                     rod.c/rod.m*(rod.x[j]-rod.x[j-1]));
            else    rod.v[j]+= timestep*(-rod.b/rod.m*rod.v[j]-
                                 rod.c/rod.m*(2*rod.x[j]-rod.x[j+1]-rod.x[j-1]));          //semi-implicit Euler scheme
        }

#pragma omp for
        for(int j=1;j<N;j++)  rod.x[j]+= timestep*rod.v[j];

#pragma omp single
{
        if (!(i%num_outsteps)) {cout << i*timestep << " sec , U(L)= "<< rod.x[N-1] <<
                               ", V(L)= "<< rod.v[N-1]<<endl;
         stringstream ss;
         ss << i/num_outsteps;
         string str = ss.str(); //convert integer to string
         str = "../state" + str + ".csv";
         rod.PrintState(str);
        }
} //end of single
    } //end of time loop
    }// end of parallel section

    cout << "It took me "<< (clock()-t)/CLOCKS_PER_SEC
         << " seconds" << endl;
    return 0;
}

