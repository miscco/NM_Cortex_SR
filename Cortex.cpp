/*
*	Copyright (c) 2014 Michael Schellenberger Costa
*
*	Permission is hereby granted, free of charge, to any person obtaining a copy
*	of this software and associated documentation files (the "Software"), to deal
*	in the Software without restriction, including without limitation the rights
*	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*	copies of the Software, and to permit persons to whom the Software is
*	furnished to do so, subject to the following conditions:
*
*	The above copyright notice and this permission notice shall be included in
*	all copies or substantial portions of the Software.
*
*	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
*	THE SOFTWARE.
*/

/****************************************************************************************************/
/* 		Implementation of the simulation as MATLAB routine (mex compiler)							*/
/* 		mex command is given by:																	*/
/* 		mex CXXFLAGS="\$CXXFLAGS -std=c++11" Cortex.cpp Cortical_Column.cpp						*/
/*		The Simulation requires the following boost libraries:	Preprocessor						*/
/*																Random								*/
/****************************************************************************************************/
#include "mex.h"
#include "matrix.h"
#include "Cortical_Column.h"
#include "Stimulation.h"
#include "saves.h"

/****************************************************************************************************/
/*										Fixed simulation settings									*/
/****************************************************************************************************/
extern const int onset	= 10;								/* Time until data is stored in  s		*/
extern const int res 	= 1E4;								/* Number of iteration steps per s		*/
extern const int red 	= 1E2;								/* Number of iterations steps not saved	*/
extern const double dt 	= 1E3/res;							/* Duration of a time step in ms		*/
extern const double h	= sqrt(dt);							/* Square root of dt for SRK iteration	*/
/****************************************************************************************************/
/*										 		end			 										*/
/****************************************************************************************************/

/****************************************************************************************************/
/*										Simulation routine	 										*/
/*										lhs defines outputs											*/
/*										rhs defines inputs											*/
/****************************************************************************************************/
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
	/* Set the seed */
	srand(time(NULL));

	/* Fetch inputs */
	const int T				= (int) (mxGetScalar(prhs[0]));	/* Duration of simulation in s 			*/
	const int Time 			= (T+onset)*res;				/* Total number of iteration steps 		*/
	double* Param_Cortex	= mxGetPr (prhs[1]);			/* Parameters of cortical module 		*/
	double* var_stim	 	= mxGetPr (prhs[2]);			/* Parameters of stimulation protocol 	*/

	/* Initialize the population */
	Cortical_Column Cortex(Param_Cortex);

	/* Initialize the stimulation protocol */
	Stim	Stimulation(Cortex, var_stim);

	/* Data container in MATLAB format */
	mxArray* Ve		= SetMexArray(1, T*res/red);
	mxArray* Na		= SetMexArray(1, T*res/red);
	mxArray* S_ee	= SetMexArray(1, T*res/red);
	mxArray* S_ei	= SetMexArray(1, T*res/red);
	mxArray* S_ie	= SetMexArray(1, T*res/red);
	mxArray* S_ii	= SetMexArray(1, T*res/red);

	/* Pointer to the actual data block */
	double* Pr_Ve	= mxGetPr(Ve);
	double* Pr_Na	= mxGetPr(Na);
	double* Pr_S_ee	= mxGetPr(S_ee);
	double* Pr_S_ei	= mxGetPr(S_ei);
	double* Pr_S_ie	= mxGetPr(S_ie);
	double* Pr_S_ii	= mxGetPr(S_ii);

	/* Simulation */
	int count = 0;
	for (int t=0; t<(T+onset)*res; ++t) {
		Cortex.iterate_ODE();
		Stimulation.check_stim(t);
		if(t>=onset*res && t%red==0){
			get_data(count, Cortex, Pr_Ve, Pr_Na, Pr_S_ee, Pr_S_ei, Pr_S_ie, Pr_S_ii);
			++count;
		}
	}

	plhs[0] = Ve;
	plhs[1] = Na;
	plhs[2] = S_ee;
	plhs[3] = S_ei;
	plhs[4] = S_ie;
	plhs[5] = S_ii;
	plhs[6] = Stimulation.get_marker();
	return;
}
/****************************************************************************************************/
/*												end													*/
/****************************************************************************************************/
