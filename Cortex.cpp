#include <ctime>
#include <vector>
#include "mex.h"
#include "matrix.h"
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
	// Set the seed.
	srand(time(NULL));

	// Fetch inputs
	const int T				= (int) (mxGetScalar(prhs[0]));
	const int onset			= (int) (mxGetScalar(prhs[1]));
	double* Input	 		= mxGetPr (prhs[2]);
	double* var_stim	 	= mxGetPr (prhs[3]);

	// Initializing the populations;
	Cortical_Column Col(Input);

	// Data container in MATLAB format
	mxArray* Ve		= SetMexArray(1, T*red);

	// Pointer to the actual data block
	double* Pr_Ve	= mxGetPr(Ve);

	// simulation
	int count = 0;
	for (int t=0; t<(T+onset)*res; ++t) {
		ODE (Col);
		if(t>=onset*res && t%red==0){
		get_data(count, Col, Pr_Ve);
		++count;
		}
	}

	plhs[0]  = Ve;
	return;
}
