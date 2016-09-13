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
/*						Functions of the sleep regulation module			  */
/******************************************************************************/
#include "Sleep_Regulation.h"

inline double Heaviside(double X) {
 return X >= 0 ? 1.0 : 0.0;
}

/******************************************************************************/
/*                              Input functions 							  */
/******************************************************************************/
/* Wake input */
double Sleep_Regulation::I_W	(int N) const{
    return g_GW * C_G[N] + g_AW * C_A[N];
}

/* NREM input */
double Sleep_Regulation::I_N	(int N) const{
    return g_EN * C_E[N];
}

/* REM input */
double Sleep_Regulation::I_R	(int N) const{
    return g_ER * C_E[N] + g_GR * C_G[N] + g_AR * C_A[N];
}

/******************************************************************************/
/*                              SRK iteration                                 */
/******************************************************************************/
void Sleep_Regulation::set_RK (int N) {
    extern const double dt;
    f_W	[N+1] = f_W [0] + A[N] * dt*(F_W_max *0.5*(1 + tanh((I_W(N) - beta_W)/alpha_W))     - f_W [N])/tau_W;
    f_N	[N+1] = f_N [0] + A[N] * dt*(F_N_max *0.5*(1 + tanh((I_N(N) + kappa*h[N])/alpha_N)) - f_N [N])/tau_N;
    f_R	[N+1] = f_R [0] + A[N] * dt*(F_R_max *0.5*(1 + tanh((I_R(N) - beta_R)/alpha_R))     - f_R [N])/tau_R;
    C_E [N+1] = C_E [0] + A[N] * dt*(tanh(f_W[N+1]/gamma_E) - C_E[N])/tau_E;
    C_G [N+1] = C_G [0] + A[N] * dt*(tanh(f_N[N+1]/gamma_G) - C_G[N])/tau_G;
    C_A [N+1] = C_A [0] + A[N] * dt*(tanh(f_R[N+1]/gamma_A) - C_A[N])/tau_A;
    h	[N+1] = h	[0] + A[N] * dt*((H_max-h[N])/tau_hw*Heaviside(f_W[N]-theta_W) - h[N]/tau_hs*Heaviside(theta_W- f_W[N]));
}

void Sleep_Regulation::add_RK(void) {
    add_RK(f_W);
    add_RK(f_N);
    add_RK(f_R);
    add_RK(C_E);
    add_RK(C_G);
    add_RK(C_A);
    add_RK(h);
}
