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
// mex CXXFLAGS="\$CXXFLAGS -std=gnu++0x -fpermissive" Cortex.cpp Cortical_Column.cpp

extern const int res 	= 1E4;
extern const int red 	= res/100;
extern const double dt 	= 1E3/res;
extern const double h	= sqrt(dt);


// simulation of the model proposed in Steyn-Ross2004

// input arguments are a vector of length 8 with the connectivities and an integer setting the resolution of the grid
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
	// Initializing the mersenne twister.
	MTRand mtrand;

	// inputs
	const int T			= (int) (mxGetScalar(prhs[0]));
	const int onset			= (int) (mxGetScalar(prhs[1]));
	double* Input	 		= mxGetPr (prhs[2]);
	double* var_stim	 	= mxGetPr (prhs[3]);

	const int Time 			= (T+onset)*res;

	// creating the random input
	//*
	vector<double> u_e1 = rand_var(mtrand, Time, mphi_sc, dphi_sc);
	vector<double> u_e2 = rand_var(mtrand, Time, mphi_sc, dphi_sc);
	vector<double> u_i1 = rand_var(mtrand, Time, mphi_sc, dphi_sc);
	vector<double> u_i2 = rand_var(mtrand, Time, mphi_sc, dphi_sc);
	//*/

	/*
	vector<double> u_e1 = rand_inp(mtrand, res, T, onset, var_stim[4], var_stim[2], mphi_sc, dphi_sc, var_stim[0]);
	vector<double> u_e2 = rand_inp(mtrand, res, T, onset, var_stim[4], var_stim[2], mphi_sc, dphi_sc, var_stim[0]);
	vector<double> u_i1 = rand_inp(mtrand, res, T, onset, var_stim[4], var_stim[2], mphi_sc, dphi_sc, var_stim[0]);
	vector<double> u_i2 = rand_inp(mtrand, res, T, onset, var_stim[4], var_stim[2], mphi_sc, dphi_sc, var_stim[0]);
	/*/

	// Initializing the populations;
	Cortical_Column Col(Input);

	// setting up the data containers
	vector<double> Ve 	 	(T*res/red);
	vector<double> Na 	 	(T*res/red);

	// simulation
	int count = 0;
	for (int t=0; t<Time; ++t) {
		ODE (Col, u_e1[t], u_e2[t], u_i1[t], u_i2[t]);
		if(t>=onset*res && t%red==0){
		get_data(count, Col, Ve, Na);
		//Stim.Start(Ve, u_e1, u_e2, u_i1, u_i2, count);
		++count;
		}
	}

	plhs[0]  = getMexArray(Ve);
	plhs[1]  = getMexArray(Na);
	return;
}
