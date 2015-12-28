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
 *	Based on:	Modeling the effect of sleep regulation on a neural mass model.
 *				M Schellenberger Costa, J Born, JC Claussen, T Martinetz.
 *				Journal of Computational Neuroscience (in review)
 */

/************************************************************************************************/
/*							Header file of a sleep regulation module							*/
/************************************************************************************************/
#pragma once
#include <cmath>
#include <vector>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/normal_distribution.hpp>
#include <boost/random/variate_generator.hpp>
using std::vector;
class Cortical_Column;

/****************************************************************************************************/
/*										Typedefs for RNG											*/
/****************************************************************************************************/
typedef boost::random::mt11213b                    	ENG;    /* Mersenne Twister		*/
typedef boost::random::normal_distribution<double>	DIST;   /* Normal Distribution	*/
typedef boost::random::variate_generator<ENG,DIST> 	GEN;    /* Variate generator	*/
/****************************************************************************************************/
/*										 		end			 										*/
/****************************************************************************************************/


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
/*								Implementation of the sleep regulatory model						*/
/****************************************************************************************************/
class Sleep_Regulation {
public:
	/* Constructors */
	Sleep_Regulation(void)
	{ C_E = _INIT(tanh(f_W[0]/gamma_E));
	  C_G = _INIT(tanh(f_N[0]/gamma_G));
	  C_A = _INIT(tanh(f_R[0]/gamma_A));
	}

	Sleep_Regulation(double* Par)
	: f_W(_INIT(Par[0])), f_N(_INIT(Par[1])), f_R(_INIT(Par[2])), h(_INIT(Par[3]))
	{ C_E = _INIT(tanh(f_W[0]/gamma_E));
	  C_G = _INIT(tanh(f_N[0]/gamma_G));
	  C_A = _INIT(tanh(f_R[0]/gamma_A));
	}

	/* Input functions */
	double I_W(int) const;
	double I_N(int) const;
	double I_R(int) const;

	/* ODE functions */
	void 	set_RK		(int);
	void 	add_RK	 	(void);
	void	iterate_ODE	(void);

	/* Data storage  access */
	friend void get_data (int, Cortical_Column&, Sleep_Regulation&, vector<double*>);
	friend class Cortical_Column;

private:
	/* Declaration and Initialization of parameters */
	/* Membrane time in [s] */
	const int		tau_W 		= 1500E3;
	const int		tau_N 		= 600E3;
	const int		tau_R 		= 60E3;

	/* Neurotransmitter time constants in [ms] */
	const int		tau_E 		= 25E1;
	const int		tau_G 		= 10E1;
	const int		tau_A 		= 10E1;

	/* Maximum firing rate in [s^-1] */
	const double 	F_W_max		= 6.5;
	const double 	F_N_max		= 5.;
	const double 	F_R_max		= 5.;

	/* Sigmoid slope parameters in [aU] */
	const double 	alpha_W		= 0.5;
	const double 	alpha_N		= 0.175;
	const double 	alpha_R		= 0.13;

	/* Sigmoid threshold parameters in [aU] */
	const double 	beta_W		= -0.4;
/*  const double	beta_N		= k * h(t); */
	const double 	beta_R		= -0.9;

	/* Neurotransmitter release scaling in [s^-1] */
	const double 	gamma_E		= 5.;
	const double	gamma_G		= 4.;
	const double	gamma_A		= 2.;

	/* Weights for neurotransmitter efficacy in [aU]*/
	const double 	g_GW		= -1.68;
	const double 	g_AW		= 1.;
	const double 	g_GR		= -1.3;
	const double 	g_AR		= 1.6;
	const double 	g_ER		= -4.;
	const double 	g_EN		= -2.;

	/* Sleep Homeostasis parameter */
	const double	H_max		= 1.;		/* in [aU] */
	const double	theta_W		= 2.;		/* in [s] */
	const int		tau_hw		= 34830E3;	/* 580.5 min in [s] */
	const int		tau_hs		= 30600E3;	/* 510 min in [s] */
	const double	k			= 1.5;		/* in [aU] */

	/* Bifurcation parameters */
	/* KNa */
	const double	g_KNa_0		= 1.33;
	const double	tau_g		= 10;

	/* Sigmoid gain in mV */
	const double	sigma_e_0	= 7;
	const double	tau_s		= 10;

	/* SRK integration parameters */
	const vector<double> A = {0.5, 0.5, 1.0, 1.0};
	const vector<double> B = {0.75, 0.75, 0.0, 0.0};

	/* Population variables */
	vector<double> 	f_W		= _INIT(6.),	/* Wake promoting activity	in [s^-1]	*/
					f_N		= _INIT(1E-3),	/* Sleep promoting activity	in [s^-1] 	*/
					f_R		= _INIT(1E-3),	/* REM promoting activity	in [s^-1] 	*/
					C_E		= _INIT(0.9),	/* Norephrine concentration	in [aU]		*/
					C_G		= _INIT(1E-3),	/* GABA concentration		in [aU] 	*/
					C_A		= _INIT(1E-3),	/* Acetylcholin concentration in [aU] 	*/
					h		= _INIT(0.5);	/* Homeostatic sleep drive	in [aU] 	*/
};
/****************************************************************************************************/
/*										 		end			 										*/
/****************************************************************************************************/

