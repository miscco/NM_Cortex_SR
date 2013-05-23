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
inline void get_data(int counter, Cortical_Column& Col, vector<double>& Ve, 	 vector<double>& Vi, 	 vector<double>& Na,
														vector<double>& I_KS, 	 vector<double>& I_A, 	 vector<double>& I_KNa,
														vector<double>& I_AR, 	 vector<double>& I_NaP) {
	Ve	 	[counter] = Col.Ve		[0];
	Vi	 	[counter] = Col.Vi		[0];
	Na	 	[counter] = Col.phi_e	[0];
	I_KS 	[counter] = Col.I_KS	(0);
	I_A 	[counter] = Col.I_A		(0);
	I_KNa 	[counter] = Col.I_KNa	(0);
	I_AR 	[counter] = Col.I_AR	(0);
	I_NaP 	[counter] = Col.I_NaP	(0);
}
