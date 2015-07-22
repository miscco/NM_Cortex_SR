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
/*									Functions for data storage										*/
/****************************************************************************************************/
#pragma once
#include "Cortical_Column.h"

/****************************************************************************************************/
/*											Save data												*/
/****************************************************************************************************/
inline void get_data(int counter, Cortical_Column& Col, vector<double*> pData) {
	pData[0][counter] = Col.Ve		[0];
	pData[1][counter] = Col.Vi		[0];
	pData[2][counter] = Col.SR.f_W	[0];
	pData[3][counter] = Col.SR.f_N	[0];
	pData[4][counter] = Col.SR.f_R	[0];
	pData[5][counter] = Col.SR.C_E	[0];
	pData[6][counter] = Col.SR.C_G	[0];
	pData[7][counter] = Col.SR.C_A	[0];
	pData[8][counter] = Col.SR.h	[0];
	pData[9][counter] = Col.g_KNa;
	pData[10][counter]= Col.sigma_e;

}
/****************************************************************************************************/
/*										 		end													*/
/****************************************************************************************************/


/****************************************************************************************************/
/*									Create MATLAB data container									*/
/****************************************************************************************************/
mxArray* SetMexArray(int N, int M) {
	mxArray* Array	= mxCreateDoubleMatrix(0, 0, mxREAL);
	mxSetM(Array, N);
	mxSetN(Array, M);
	#pragma omp critical
	{mxSetData(Array, mxMalloc(sizeof(double)*M*N));}
	return Array;
}
/****************************************************************************************************/
/*										 		end													*/
/****************************************************************************************************/
