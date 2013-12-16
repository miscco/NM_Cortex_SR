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
	const int T				= (int) (mxGetScalar(prhs[0]));
	const int onset			= (int) (mxGetScalar(prhs[1]));
	double* Input		 	= mxGetPr (prhs[2]);

	/*
	const int 		T		= 30;
	const int 		onset	= 10;
	*/
	const int 		Time 	= (T+onset)*res;

	//const double	mphi_sc	= Input[6];
	//const double	dphi_sc	= Input[7];

	// creating the random input
	//*
	vector<double> u_e1 = rand_var(mtrand, Time, mphi_sc, dphi_sc);
	vector<double> u_e2 = rand_var(mtrand, Time, mphi_sc, dphi_sc);
	vector<double> u_i1 = rand_var(mtrand, Time, mphi_sc, dphi_sc);
	vector<double> u_i2 = rand_var(mtrand, Time, mphi_sc, dphi_sc);
	//*/

	/*
	vector<double> u_e1 = rand_inp(mtrand, res, T, onset, var_stim[4], var_stim[2], phi_sc, phi_sc, 1);
	vector<double> u_e2 = rand_inp(mtrand, res, T, onset, var_stim[4], var_stim[2], phi_sc, phi_sc, 1);
	vector<double> u_i1 = rand_inp(mtrand, res, T, onset, var_stim[4], var_stim[2], phi_sc, phi_sc, 1);
	vector<double> u_i2 = rand_inp(mtrand, res, T, onset, var_stim[4], var_stim[2], phi_sc, phi_sc, 1);
	*/

	// Initializing the populations;
	Cortical_Column Col(Input);

	// setting up the data containers
	vector<double> Ve (T*res/red);

	// simulation
	int count = 0;
	for (int t=0; t<Time; ++t) {
		ODE (Col, u_e1[t], u_e2[t], u_i1[t], u_i2[t]);
		if(t>=onset*res && t%red==0){
		get_data(count, Col, Ve);
		++count;
		}
	}

	plhs[0]  = getMexArray(Ve);
	return;
}
