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
 *	Based on:	A Fast-Slow Analysis of the Dynamics of REM Sleep.
 *				CG Diniz Behn and V Booth
 *				SIAM Journal on Applied Dynamical Systems 11(1), 212–242 (2012)
 */

/******************************************************************************/
/*				Implementation of a sleep regulation module					  */
/******************************************************************************/
#pragma once
#include <cmath>
#include <vector>
class Cortical_Column;

class Sleep_Regulation {
public:
    /* Constructors */
    Sleep_Regulation(void)
    { C_E = init(tanh(f_W[0]/gamma_E));
        C_G = init(tanh(f_N[0]/gamma_G));
        C_A = init(tanh(f_R[0]/gamma_A));
    }

    Sleep_Regulation(double* Par)
        : f_W(init(Par[0])), f_N(init(Par[1])), f_R(init(Par[2])), h(init(Par[3]))
    { C_E = init(tanh(f_W[0]/gamma_E));
        C_G = init(tanh(f_N[0]/gamma_G));
        C_A = init(tanh(f_R[0]/gamma_A));
    }

    /* ODE functions */
    void 	set_RK (int);
    void 	add_RK (void);

private:
    /* Input functions */
    double I_W(int) const;
    double I_N(int) const;
    double I_R(int) const;


    /* Helper functions */
    inline std::vector<double> init (double value)
    {return {value, 0.0, 0.0, 0.0, 0.0};}

    inline void add_RK (std::vector<double>& var)
    {var[0] = (-3*var[0] + 2*var[1] + 4*var[2] + 2*var[3] + var[4])/6;}

    /* Declaration and initialization of parameters */
    /* Membrane time in [s] */
    const int		tau_W 		= 1500E3;
    const int		tau_N 		= 600E3;
    const int		tau_R 		= 60E3;

    /* Neurotransmitter time constants in [ms] */
    const int		tau_E 		= 25E3;
    const int		tau_G 		= 10E3;
    const int		tau_A 		= 10E3;

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
    /*  const double	beta_N		= kappa * h(t); */
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
    const double	kappa		= 1.5;		/* in [aU] */

    /* SRK integration parameters */
    const std::vector<double> A = {0.5, 0.5, 1.0, 1.0};
    const std::vector<double> B = {0.75, 0.75, 0.0, 0.0};

    /* Declaration and initialization of variables */
    /* Population variables */
    std::vector<double>	f_W		= init(6.),	/* Wake promoting activity	in [s^-1]	*/
    f_N		= init(1E-3),	/* Sleep promoting activity	in [s^-1] 	*/
    f_R		= init(1E-3),	/* REM promoting activity	in [s^-1] 	*/
    C_E		= init(0.9),	/* Norephrine concentration	in [aU]		*/
    C_G		= init(1E-3),	/* GABA concentration		in [aU] 	*/
    C_A		= init(1E-3),	/* Acetylcholin concentration in [aU] 	*/
    h		= init(0.5);	/* Homeostatic sleep drive	in [aU] 	*/
    /* Data storage  access */
    friend void get_data (unsigned, Cortical_Column&, Sleep_Regulation&, std::vector<double*>);
    friend class Cortical_Column;
};

