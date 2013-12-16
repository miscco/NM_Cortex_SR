/*****************************************************************************************************/
/*******************	header file of a complete thalamocirtical module	**************************/
/*****************************************************************************************************/
#pragma once
#include <iostream>
#include <cmath>
#include <vector>
#include "macros.h"
#include "parameters.h"
using std::vector;

// implementation of the cortical module after Zavaglia2006

class Cortical_Column {
public:
	// Constructors
	Cortical_Column(void)
	: Ve	(_INIT(E_L_e)),	Vi 	   	(_INIT(E_L_i)),	Na	 	(_INIT(Na_eq)),
	  Phi_ee(_INIT(0.0)), 	Phi_ei 	(_INIT(0.0)), 	Phi_ie 	(_INIT(0.0)), 	Phi_ii	(_INIT(0.0)),
	  x_ee 	(_INIT(0.0)), 	x_ei   	(_INIT(0.0)),	x_ie   	(_INIT(0.0)), 	x_ii	(_INIT(0.0)),
	  N_ee  (40), 			N_ei   	(40), 		  	N_ie	(80),		   	N_ii 	(80)
	{}

	Cortical_Column(double* Con)
	: Ve	(_INIT(E_L_e)),	Vi 	   	(_INIT(E_L_i)),	Na	 	(_INIT(Na_eq)),
	  Phi_ee(_INIT(0.0)), 	Phi_ei 	(_INIT(0.0)), 	Phi_ie 	(_INIT(0.0)), 	Phi_ii	(_INIT(0.0)),
	  x_ee 	(_INIT(0.0)), 	x_ei   	(_INIT(0.0)),	x_ie   	(_INIT(0.0)), 	x_ii	(_INIT(0.0)),
	  N_ee  (Con[0]), 	 	N_ei	(Con[1]), 	  	N_ie	(Con[2]),	   	N_ii 	(Con[3])
	{}

	// firing rate functions
	double 	get_Qe		(int) const;
	double 	get_Qi		(int) const;

	// current functions
	double 	I_ee		(int) const;
	double 	I_ei		(int) const;
	double 	I_ie		(int) const;
	double 	I_ii		(int) const;
	double 	I_L_e		(int) const;
	double 	I_L_i		(int) const;
	double 	I_KNa		(int) const;

	// potassium concentration
	double 	Na_pump		(int) const;

	// noise functions
	double 	noise_xRK 	(int, double, double) const;

	// ODE functions
	void 	set_RK		(int, _REPEAT(double, 4));
	void 	add_RK	 	(_REPEAT(double, 2));

	friend void get_data (int, Cortical_Column&, _REPEAT(vector<double>&, 2));

private:
	// population variables
	vector<double> 	Ve,			// exitatory 		  membrane voltage
					Vi,			// exitatory 		  membrane voltage
					Na,			// Na concentration
					Phi_ee,		// PostSP from exitatory  		  to exitatory  		population
					Phi_ei,		// PostSP from exitatory  		  to inhibitory 		population
					Phi_ie,		// PostSP from inhibitory 		  to exitatory  		population
					Phi_ii,		// PostSP from inhibitory 		  to inhibitory 		population
					x_ee,		// derivative of Phi_ee
					x_ei,		// derivative of Phi_ei
					x_ie,		// derivative of Phi_ie
					x_ii;		// derivative of Phi_ii

	// connectivities
	double			N_ee,		// exitatory  		  to exitatory
					N_ei,		// exitatory  		  to inhibitory
					N_ie,		// inhibitory 		  to exitatory
					N_ii;		// inhibitory 		  to inhibitory
};

