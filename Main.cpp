/*****************************************************************************************************/
/**********************************		file for code verification	**********************************/
/*****************************************************************************************************/
#include <iostream>
#include <ctime>
#include <vector>

#include "Cortical_Column.h"
#include "ODE.h"

using std::vector;

extern const int T 		= 60;
extern const int res 	= 1E4;
extern const double dt 	= 1E3/res;
extern const double h	= sqrt(dt);


// simulation of the thalamo-cortical model
int main(void) {

	// Initializing the populations;
	Cortical_Column Col;

	// takes the time of the simulation
	time_t start,end;
	time (&start);

	// simulation
	for (int t=0; t< T*res; ++t) {
		ODE (Col);
	}

	time (&end);
	// time consumed by the simulation
	double dif = difftime(end,start);
	std::cout << "simulation done!\n";
	std::cout << "took " << dif 	<< " seconds" << "\n";
	std::cout << "end\n";
}
