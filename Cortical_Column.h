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
	: Ve	(_INIT(E_L_e)),	Vi 	   	(_INIT(E_L_i)),	Na	 	(_INIT(Na_eq)),	h_A		(_INIT(0.0)),
	  m_KS	(_INIT(0.0)),
	  Phi_ee(_INIT(0.0)), 	Phi_ei 	(_INIT(0.0)), 	Phi_ie 	(_INIT(0.0)), 	Phi_ii	(_INIT(0.0)),
	  phi_e	(_INIT(0.0)),
	  x_ee 	(_INIT(0.0)), 	x_ei   	(_INIT(0.0)),	x_ie   	(_INIT(0.0)), 	x_ii	(_INIT(0.0)),
	  y_e  	(_INIT(0.0)),
	  N_ee  (40), 			N_ei   	(40), 		  	N_ie	(80),		   	N_ii 	(80),
	  N_ep  (40)
	{}

	Cortical_Column(double* Con)
	: Ve	(_INIT(E_L_e)),	Vi 	   	(_INIT(E_L_i)),	Na	 	(_INIT(Na_eq)),	h_A		(_INIT(0.0)),
	  m_KS	(_INIT(0.0)),
	  Phi_ee(_INIT(0.0)), 	Phi_ei 	(_INIT(0.0)), 	Phi_ie 	(_INIT(0.0)), 	Phi_ii	(_INIT(0.0)),
	  phi_e	(_INIT(0.0)),
	  x_ee 	(_INIT(0.0)), 	x_ei   	(_INIT(0.0)),	x_ie   	(_INIT(0.0)), 	x_ii	(_INIT(0.0)),
	  y_e  	(_INIT(0.0)),
	  N_ee  (Con[0]), 	 	N_ei	(Con[1]), 	  	N_ie	(Con[2]),	   	N_ii 	(Con[3]),
	  N_ep  (Con[4])
	{}

	// firing rate functions
	double 	get_Qe		(int) const;
	double 	get_Qi		(int) const;

	// membrane respone functions
	double 	psi_ee		(int) const;
	double 	psi_ei		(int) const;
	double 	psi_ie		(int) const;
	double 	psi_ii		(int) const;

	// current functions
	double 	I_L_e		(int) const;
	double 	I_L_i		(int) const;
	double 	I_A			(int) const;
	double 	I_KNa		(int) const;
	double 	I_KS		(int) const;
	double 	I_NaP		(int) const;
	double 	I_AR 		(int) const;

	// gating functions
	double 	h_inf_A		(int) const;
	double 	m_inf_KS	(int) const;
	double 	tau_m_KS	(int) const;

	// potassium concentration
	double 	Na_pump		(int) const;

	// noise functions
	double 	noise_xRK 	(int, double, double) const;

	// ODE functions
	void 	set_RK		(int, _REPEAT(double, 4));
	void 	add_RK	 	(_REPEAT(double, 2));

	friend void get_data (int, Cortical_Column&, _REPEAT(vector<double>&, 8));

private:
	// population variables
	vector<double> 	Ve,			// exitatory 		  membrane voltage
					Vi,			// exitatory 		  membrane voltage
					Na,			// Na concentration
					h_A,		// deactivation of A  channel
					m_KS,		// activation 	of KS channel
					Phi_ee,		// PostSP from exitatory  		  to exitatory  		population
					Phi_ei,		// PostSP from exitatory  		  to inhibitory 		population
					Phi_ie,		// PostSP from inhibitory 		  to exitatory  		population
					Phi_ii,		// PostSP from inhibitory 		  to inhibitory 		population
					phi_e,		// axonal flux from pyramidal 	   population
					x_ee,		// derivative of Phi_ee
					x_ei,		// derivative of Phi_ei
					x_ie,		// derivative of Phi_ie
					x_ii,		// derivative of Phi_ii
					y_e;		// derivative of phi_e

	// connectivities
	double			N_ee,		// exitatory  		  to exitatory
					N_ei,		// exitatory  		  to inhibitory
					N_ie,		// inhibitory 		  to exitatory
					N_ii,		// inhibitory 		  to inhibitory
					N_ep;		// exitatory  		  to exitatory	(long range)
};

