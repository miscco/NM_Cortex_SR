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

/****************************************************************************************************/
/*								Functions of the sleep regulation model								*/
/****************************************************************************************************/
#include "Sleep_Regulation.h"

/****************************************************************************************************/
/*									Parameters for SRK4	iteration									*/
/****************************************************************************************************/
double Heaviside(double X) {
 double y = 0.0;
 if (X>=0)
	 y=1.0;
 return y;}

/****************************************************************************************************/
/*										 		end													*/
/****************************************************************************************************/


/****************************************************************************************************/
/*										 Firing Rate functions 										*/
/****************************************************************************************************/
/* Wake input */
double Sleep_Regulation::I_W	(int N) const{
	//return g_GW * C_G[N] + g_AW * C_A[N] * (h[N]/0.35);
	return g_GW * C_G[N] + g_AW * C_A[N];
}

/* NREM input */
double Sleep_Regulation::I_N	(int N) const{
	return g_EN * C_E[N];
}

/* REM input */
double Sleep_Regulation::I_R	(int N) const{
	//return g_ER * C_E[N] * (h[N]/0.5) + g_GR * C_G[N] + g_AR * C_A[N];
	return g_ER * C_E[N] + g_GR * C_G[N] + g_AR * C_A[N];
}
/****************************************************************************************************/
/*										 		end			 										*/
/****************************************************************************************************/


/****************************************************************************************************/
/*										Calculate the Nth SRK term									*/
/****************************************************************************************************/
void Sleep_Regulation::set_RK (int N) {
	extern const double dt;
	f_W	[N+1] = f_W [0] + A[N] * dt*(F_W_max *0.5*(1 + tanh((I_W(N) - beta_W)/alpha_W)) - f_W [N])/tau_W;
	f_N	[N+1] = f_N [0] + A[N] * dt*(F_N_max *0.5*(1 + tanh((I_N(N) + k*h[N])/alpha_N)) - f_N [N])/tau_N;
	f_R	[N+1] = f_R [0] + A[N] * dt*(F_R_max *0.5*(1 + tanh((I_R(N) - beta_R)/alpha_R)) - f_R [N])/tau_R;
	C_E [N+1] = C_E [0] + A[N] * dt*(tanh(f_W[N+1]/gamma_E) - C_E[N])/tau_E;
	C_G [N+1] = C_G [0] + A[N] * dt*(tanh(f_N[N+1]/gamma_G) - C_G[N])/tau_G;
	C_A [N+1] = C_A [0] + A[N] * dt*(tanh(f_R[N+1]/gamma_A) - C_A[N])/tau_A;
	h	[N+1] = h	[0] + A[N] * dt*((H_max-h[N])/tau_hw*Heaviside(f_W[N]-theta_W) - h[N]/tau_hs*Heaviside(theta_W- f_W[N]));
}
/****************************************************************************************************/
/*										 		end			 										*/
/****************************************************************************************************/


/****************************************************************************************************/
/*									Function that adds all SRK terms								*/
/****************************************************************************************************/
void Sleep_Regulation::add_RK(void) {
	f_W	[0] = (-3*f_W [0] + 2*f_W [1] + 4*f_W [2] + 2*f_W [3] + f_W [4])/6;
	f_N	[0] = (-3*f_N [0] + 2*f_N [1] + 4*f_N [2] + 2*f_N [3] + f_N [4])/6;
	f_R	[0] = (-3*f_R [0] + 2*f_R [1] + 4*f_R [2] + 2*f_R [3] + f_R [4])/6;
	C_E	[0] = (-3*C_E [0] + 2*C_E [1] + 4*C_E [2] + 2*C_E [3] + C_E [4])/6;
	C_G	[0] = (-3*C_G [0] + 2*C_G [1] + 4*C_G [2] + 2*C_G [3] + C_G [4])/6;
	C_A	[0] = (-3*C_A [0] + 2*C_A [1] + 4*C_A [2] + 2*C_A [3] + C_A [4])/6;
	h  	[0] = (-3*h   [0] + 2*h   [1] + 4*h   [2] + 2*h   [3] + h   [4])/6;
}
/****************************************************************************************************/
/*										 		end			 										*/
/****************************************************************************************************/
