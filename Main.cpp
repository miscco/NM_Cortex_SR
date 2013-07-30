/*****************************************************************************************************/
/**********************************		file for code verification	**********************************/
/*****************************************************************************************************/
#include <iostream>
#include <ctime>
#include <vector>

#include "randoms.h"
#include "Cortical_Column.h"
#include "ODE.h"

using std::vector;

extern const int T 		= 50;
extern const int res 	= 1E4;
extern const double dt 	= 1E3/res;
extern const double h	= sqrt(dt);


// simulation of the thalamo-cortical model
int main(void) {
	// Initializing the mersenne twister.
	MTRand mtrand;

	// creating the random input
	vector<double> u_e1 = rand_var(mtrand, T*res, mphi_sc, dphi_sc);
	vector<double> u_e2 = rand_var(mtrand, T*res, mphi_sc, dphi_sc);
	vector<double> u_i1 = rand_var(mtrand, T*res, mphi_sc, dphi_sc);
	vector<double> u_i2 = rand_var(mtrand, T*res, mphi_sc, dphi_sc);

	// Initializing the populations;
	Cortical_Column Col;

	// takes the time of the simulation
	time_t start,end;
	time (&start);

	// simulation
	for (int t=0; t< T*res; ++t) {
		ODE (Col, u_e1[t], u_e2[t], u_i1[t], u_i2[t]);
	}

	time (&end);
	// time consumed by the simulation
	double dif = difftime(end,start);
	std::cout << "simulation done!\n";
	std::cout << "took " << dif 	<< " seconds" << "\n";
	std::cout << "end\n";
}
