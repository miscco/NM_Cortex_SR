/*****************************************************************************************************/
/***********************			functions for data storage			******************************/
/*****************************************************************************************************/
#include <iostream>
#include <vector>
#include "Cortical_Column.h"
using std::vector;

// saving file for the mex compilation

// function to copy a std::vector into a matlab matrix
mxArray * getMexArray(const std::vector<double>& v){
    mxArray * mx = mxCreateDoubleMatrix(1,v.size(), mxREAL);
    std::copy(v.begin(), v.end(), mxGetPr(mx));
    return mx;
}

// saving the fluctuations of the populations
inline void get_data(int counter, Cortical_Column& Col, vector<double>& Ve, vector<double>& Na) {
	Ve	 	[counter] = Col.Ve		[0];
	Na	 	[counter] = Col.Na		[0];
}
