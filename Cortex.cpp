#include <ctime>
#include <vector>
#include "mex.h"
#include "matrix.h"
#include "randoms.h"
#include "Cortical_Column.h"
#include "saves.h"
#include "ODE.h"
using std::vector;

// Implementation of the main file for mex compiler
// mex command is given by:
// mex CXXFLAGS="\$CXXFLAGS -std=gnu++0x -fpermissive" SteynRoss.cpp Cortical_Colun.cpp

extern const int res 	= 1E4;
extern const double dt 	= 1E3/res;
extern const double h	= sqrt(dt);


// simulation of the model proposed in Steyn-Ross2004

// input arguments are a vector of length 8 with the connectivities and an integer setting the resolution of the grid
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
	// Initializing the mersenne twister.
	MTRand mtrand;

	// inputs
	double* Connectivity 	= mxGetPr (prhs[0]);
	const int T				= (int)(mxGetScalar(prhs[1]));
	const int onset			= (int)(mxGetScalar(prhs[2]));

	const int Time 			= (T+onset)*res;

	// creating the random input
	vector<double> u_e1 = rand_var(mtrand, Time, phi_sc, phi_sc);
	vector<double> u_e2 = rand_var(mtrand, Time, phi_sc, phi_sc);
	vector<double> u_i1 = rand_var(mtrand, Time, phi_sc, phi_sc);
	vector<double> u_i2 = rand_var(mtrand, Time, phi_sc, phi_sc);

	//vector<double> u_e1 = rand_inp(mtrand, res, T, onset, 5, 5E2, phi_sc, phi_sc, phi_inp);
	//vector<double> u_e2 = rand_inp(mtrand, res, T, onset, 5, 5E2, phi_sc, phi_sc, phi_inp);

	// Initializing the populations;
	Cortical_Column Col(Connectivity);

	// setting up the data containers
	vector<double> Ve 	 	(T*res);
	vector<double> Vi 	 	(T*res);
	vector<double> Na 		(T*res);
	vector<double> I_KS 	(T*res);
	vector<double> I_A 		(T*res);
	vector<double> I_KNa 	(T*res);

	int count = 0;

	// simulation
	for (int t=0; t<Time; ++t) {
		ODE (Col, u_e1[t], u_e2[t], u_i1[t], u_i2[t]);
		if(t>=onset*res){
		get_data(count, Col, Ve, Vi, Na, I_KS, I_A, I_KNa);
		++count;
		}
	}

	plhs[0]  = getMexArray(Ve);
	plhs[1]  = getMexArray(Vi);
	plhs[2]  = getMexArray(Na);
	plhs[3]  = getMexArray(I_KS);
	plhs[4]  = getMexArray(I_A);
	plhs[5]  = getMexArray(I_KNa);

	return;
}
