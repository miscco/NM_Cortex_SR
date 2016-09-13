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

/******************************************************************************/
/*							Functions of the cortical module				  */
/******************************************************************************/
#include "Cortical_Column.h"

/******************************************************************************/
/*							Initialization of RNG 							  */
/******************************************************************************/
void Cortical_Column::set_RNG(void) {
    extern const double dt;
    unsigned numRandomVariables = 2;

    MTRands.reserve(2*numRandomVariables);
    Rand_vars.reserve(2*numRandomVariables);
    for (unsigned i=0; i < numRandomVariables; ++i){
        /* Add the RNG for I_{l}*/
        MTRands.push_back(random_stream_normal(0.0, dphi*dt));

        /* Add the RNG for I_{l,0} */
        MTRands.push_back(random_stream_normal(0.0, dt));

        /* Get the random number for the first iteration */
        Rand_vars.push_back(MTRands[2*i]());
        Rand_vars.push_back(MTRands[2*i+1]());
    }
}

/******************************************************************************/
/*                          RK noise scaling 								  */
/******************************************************************************/
double Cortical_Column::noise_xRK(int N, int M) const{
    return gamma_e * gamma_e * (Rand_vars[2*M] + Rand_vars[2*M+1]/std::sqrt(3))*B[N];
}

double Cortical_Column::noise_aRK(int M) const{
    return gamma_e * gamma_e * (Rand_vars[2*M] - Rand_vars[2*M+1]*std::sqrt(3))/4;
}

/******************************************************************************/
/*                          Firing Rate functions 							  */
/******************************************************************************/
double Cortical_Column::get_Qp	(int N) const{
    return Qp_max / (1 + exp(-C1 * (Vp[N] - theta_p) / sigma_p[N]));
}

double Cortical_Column::get_Qi	(int N) const{
    return Qi_max / (1 + exp(-C1 * (Vi[N] - theta_i) / sigma_i));
}

/******************************************************************************/
/*							Synaptic currents								  */
/******************************************************************************/
/* Excitatory input to pyramidal population */
double Cortical_Column::I_ep (int N) const{
    return g_AMPA * s_ep[N] * (Vp[N] - E_AMPA);
}

/* Inhibitory input to pyramidal population */
double Cortical_Column::I_gp (int N) const{
    return g_GABA * s_gp[N] * (Vp[N] - E_GABA);
}
/* Excitatory input to inhibitory population */
double Cortical_Column::I_ei (int N) const{
    return g_AMPA * s_ei[N] * (Vi[N] - E_AMPA);
}

/* Inhibitory input to inhibitory population */
double Cortical_Column::I_gi (int N) const{
    return g_GABA * s_gi[N] * (Vi[N] - E_GABA);
}

/******************************************************************************/
/*							Intrinsic currents                                */
/******************************************************************************/
/* Leak current of pyramidal population */
double Cortical_Column::I_L_p (int N) const{
    return g_L * (Vp[N] - E_L_p);
}

/* Leak current of inhibitory population */
double Cortical_Column::I_L_i (int N) const{
    return g_L * (Vi[N] - E_L_i);
}

/* Sodium dependent potassium current */
double Cortical_Column::I_KNa (int N)  const{
    double w_KNa  = 0.37/(1+pow(38.7/Na[N], 3.5));
    return g_KNa[N] * w_KNa * (Vp[N] - E_K);
}

/******************************************************************************/
/*                              Potassium pump	 							  */
/******************************************************************************/
double Cortical_Column::Na_pump (int N) const{
    return R_pump*(Na[N]*Na[N]*Na[N]/(Na[N]*Na[N]*Na[N]+3375) -
                   Na_eq*Na_eq*Na_eq/(Na_eq*Na_eq*Na_eq+3375));
}

/******************************************************************************/
/*							Update bifurcation parameters                     */
/******************************************************************************/
void Cortical_Column::Update_Bifurcation_Parameters	(void) {
    g_KNa  [0] = g_KNa_0   * (2./3. * SR->C_G[0]  * (3 - 2*(SR->C_E[0] + SR->C_A[0])));
    sigma_p[0] = sigma_p_0 - (4 * SR->C_E[0] + 2 * SR->C_A[0]);
}

/******************************************************************************/
/*                              SRK iteration                                 */
/******************************************************************************/
void Cortical_Column::set_RK (int N) {
    extern const double dt;
    Vp		[N+1] = Vp  [0] + A[N] * dt*(-(I_L_p(N) + I_ep(N) + I_gp(N))/tau_p - C_m * I_KNa(N));
    Vi		[N+1] = Vi  [0] + A[N] * dt*(-(I_L_i(N) + I_ei(N) + I_gi(N))/tau_i);
    Na		[N+1] = Na  [0] + A[N] * dt*(alpha_Na * get_Qp(N) - Na_pump(N))/tau_Na;
    s_ep	[N+1] = s_ep[0] + A[N] * dt*(x_ep[N]);
    s_ei	[N+1] = s_ei[0] + A[N] * dt*(x_ei[N]);
    s_gp	[N+1] = s_gp[0] + A[N] * dt*(x_gp[N]);
    s_gi	[N+1] = s_gi[0] + A[N] * dt*(x_gi[N]);
    x_ep	[N+1] = x_ep[0] + A[N] * dt*(pow(gamma_e, 2) * (N_pp * get_Qp(N) - s_ep[N]) - 2 * gamma_e * x_ep[N]) + noise_xRK(N, 0);
    x_ei	[N+1] = x_ei[0] + A[N] * dt*(pow(gamma_e, 2) * (N_ip * get_Qp(N) - s_ei[N]) - 2 * gamma_e * x_ei[N]) + noise_xRK(N, 1)	;
    x_gp	[N+1] = x_gp[0] + A[N] * dt*(pow(gamma_g, 2) * (N_pi * get_Qi(N) - s_gp[N]) - 2 * gamma_g * x_gp[N]);
    x_gi	[N+1] = x_gi[0] + A[N] * dt*(pow(gamma_g, 2) * (N_ii * get_Qi(N) - s_gi[N]) - 2 * gamma_g * x_gi[N]);
    g_KNa	[N+1] = g_KNa[0]+ A[N] * dt*(g_KNa_0 * (2*SR->C_G[N])*(1-0.6*SR->C_E[N])*(1-0.95*SR->C_A[N]) - g_KNa[N])/tau_g;
    sigma_p [N+1] = sigma_p[0]+A[N]* dt*(sigma_p_0 - (4*SR->C_E[N] + 2*SR->C_A[N]) - sigma_p[N])/tau_s;
}

void Cortical_Column::add_RK(void) {
    add_RK(Vp);
    add_RK(Vi);
    add_RK(Na);
    add_RK(s_ep);
    add_RK(s_ei);
    add_RK(s_gp);
    add_RK(s_gi);
    add_RK_noise(x_ep, 0);
    add_RK_noise(x_ei, 1);
    add_RK(x_gp);
    add_RK(x_gi);
    add_RK(g_KNa);
    add_RK(sigma_p);

    /* Generate noise for the next iteration */
    for (unsigned i=0; i<Rand_vars.size(); ++i) {
        Rand_vars[i] = MTRands[i]() + input;
    }
}
