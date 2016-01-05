/*
 *	Copyright (c) 2015 University of Lübeck
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
 *
 *	AUTHORS:	Michael Schellenberger Costa: mschellenbergercosta@gmail.com
 *
 *	Based on:	Characterization of K-Complexes and Slow Wave Activity in a Neural Mass Model
 *				A Weigenand, M Schellenberger Costa, H-VV Ngo, JC Claussen, T Martinetz
 *				PLoS Computational Biology. 2014;10:e1003923
 * 
 *				Modeling the effect of sleep regulation on a neural mass model.
 *				M Schellenberger Costa, J Born, JC Claussen, T Martinetz.
 *				Journal of Computational Neuroscience (in review)
 */

/************************************************************************************************/
/*								Header file of a cortical module								*/
/************************************************************************************************/
#pragma once
#include <cmath>
#include <vector>
#include "Random_Stream.h"
#include "Sleep_Regulation.h"
using std::vector;

/****************************************************************************************************/
/*									Macro for vector initialization									*/
/****************************************************************************************************/
#ifndef _INIT
#define _INIT(x)	{x, 0.0, 0.0, 0.0, 0.0}
#endif
/****************************************************************************************************/
/*										 		end			 										*/
/****************************************************************************************************/


/****************************************************************************************************/
/*									Definition of the cortical module 								*/
/****************************************************************************************************/
class Cortical_Column {
public:
	/* Constructors */
	Cortical_Column(void)
	{set_RNG();}

	/* Initialize the RNGs */
	void 	set_RNG		(void);

	/* Set strength of input */
	void	set_input	(double I) {input = I;}

	/* Connect cortex to the sleep regulatory network */
	void	connect_SR (Sleep_Regulation& SR_Network) {SR = &SR_Network;}

	/* Firing rates */
    double 	get_Qp		(int) const;
	double 	get_Qi		(int) const;

	/* Currents */
    double 	I_ep		(int) const;
	double 	I_ei		(int) const;
    double 	I_gp		(int) const;
    double 	I_gi		(int) const;
    double 	I_L_p		(int) const;
	double 	I_L_i		(int) const;
	double 	I_KNa		(int) const;

	/* Potassium pump */
	double 	Na_pump		(int) const;

	/* Bifurcation Parameter update */
	void	Update_Bifurcation_Parameters (void);

	/* Noise function */
	double 	noise_xRK 	(int, int) const;
	double 	noise_aRK 	(int) const;

	/* ODE functions */
	void 	set_RK		(int);
	void 	add_RK	 	(void);

	/* Data storage  access */
	friend void get_data (int, Cortical_Column&, Sleep_Regulation&, vector<double*>);

private:
	/* Declaration and initialization of parameters */
	/* Membrane time in ms */
    const double 	tau_p 		= 30;
	const double 	tau_i 		= 30;

	/* Maximum firing rate in ms^-1 */
    const double 	Qp_max		= 30.E-3;
	const double 	Qi_max		= 60.E-3;

	/* Sigmoid threshold in mV */
    const double 	theta_p		= -58.5;
	const double 	theta_i		= -58.5;

	/* Sigmoid gain in mV */
    const double	sigma_p_0	= 7;
	const int		tau_s		= 100;
	const double 	sigma_i		= 6;

	/* Scaling parameter for sigmoidal mapping (dimensionless) */
	const double 	C1		= (3.14159265/sqrt(3));

	/* Parameters of the firing adaption */
	const double 	alpha_Na	= 2.;			/* Sodium influx per spike  in mM ms 	*/
	const double 	tau_Na		= 1.;			/* Sodium time constant	    in ms		*/

	const double 	R_pump   	= 0.09;        	/* Na-K pump constant	    in mM/ms 	*/
	const double 	Na_eq    	= 9.5;         	/* Na-eq concentration	    in mM		*/

	/* PSP rise time in ms^-1 */
	const double 	gamma_e		= 70E-3;
    const double 	gamma_g		= 58.6E-3;

	/* Conductivities in aU */
	/* Leak */
	const double 	g_L    		= 1.;
	const double 	g_AMPA 		= 1.;
	const double 	g_GABA 		= 1.;

	/* KNa */
	const double	g_KNa_0		= 1.33;
	const int		tau_g		= 10;

	/* Reversal potentials in mV */
	/* Synaptic */
	const double 	E_AMPA  	= 0;
	const double 	E_GABA  	= -70;

	/* Leak */
    const double 	E_L_p 		= -66;
	const double 	E_L_i 		= -64;

	/* Potassium */
	const double 	E_K    		= -100;

	/* Noise parameters in ms^-1 */
	const double 	mphi		= 0.0;
	const double	dphi		= 20E-1;
	double			input		= 0.0;

	/* Connectivities (dimensionless) */
	/* Label indicates N_{from -> to} */
    const double 	N_pp		= 120;
    const double 	N_ip		= 72;
    const double 	N_pi		= 90;
	const double 	N_ii		= 90;

	/* SRK integration parameters */
	const vector<double> A		= {0.5, 0.5, 1.0, 1.0};
	const vector<double> B		= {0.75, 0.75, 0.0, 0.0};
	
	/* Declaration and initialization of variables */	
	/* Random number generators */
    vector<random_stream_normal> MTRands;

	/* Container for noise */
	vector<double>	Rand_vars;

	/* Pointer to sleep regulatory network */
	Sleep_Regulation* SR		= NULL;

	/* Population variables */
    vector<double> 	Vp		= _INIT(E_L_p),		/* Pyramidal  membrane voltage						*/
					Vi		= _INIT(E_L_i),		/* Inhibitory membrane voltage						*/
					Na		= _INIT(Na_eq),		/* Na concentration									*/
                    y_ep	= _INIT(0.0),		/* PostSP excitatory input to pyramidal  population	*/
                    y_ei	= _INIT(0.0),		/* PostSP excitatory input to inhibitory population	*/
                    y_gp	= _INIT(0.0),		/* PostSP inhibitory input to pyramidal  population	*/
                    y_gi	= _INIT(0.0),		/* PostSP inhibitory input to inhibitory population	*/
                    x_ep	= _INIT(0.0),		/* Derivative of y_ep								*/
					x_ei	= _INIT(0.0),		/* Derivative of y_ei								*/
                    x_gp	= _INIT(0.0),		/* Derivative of y_gp				 				*/
                    x_gi	= _INIT(0.0),		/* Derivative of y_gi								*/
					g_KNa	= _INIT(g_KNa_0),	/* Adaptation strength								*/
                    sigma_p	= _INIT(sigma_p_0);	/* Inverse neural gain								*/
};
/****************************************************************************************************/
/*										 		end			 										*/
/****************************************************************************************************/

