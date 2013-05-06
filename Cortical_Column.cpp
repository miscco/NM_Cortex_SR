#include <cmath>
#include "Cortical_Column.h"

/*****************************************************************************************************/
/**********************************		 Firing Rate functions 		**********************************/
/*****************************************************************************************************/
// pyramidal firing rate
double Cortical_Column::get_Qe	(int N) const{
	_SWITCH((Ve)(theta))
	double q = Qe_max / (1 + exp(-C * (var_Ve - var_theta) / sigma_e));
	return q;
}

// cortical inhibitory firing rate
double Cortical_Column::get_Qi	(int N) const{
	_SWITCH((Vi))
	double q = Qi_max / (1 + exp(-C * (var_Vi - theta_i) / sigma_i));
	return q;
}
/*****************************************************************************************************/
/**********************************		 		end			 		**********************************/
/*****************************************************************************************************/


/*****************************************************************************************************/
/**********************************		 weighting functions 		**********************************/
/*****************************************************************************************************/
// exitatory input to pyramidal population
double Cortical_Column::psi_ee	(int N) const{
	_SWITCH((Ve))
	double psi = (V_rev_e-var_Ve);
	return psi;
}

// exitatory input to inhibitory population
double Cortical_Column::psi_ei	(int N) const{
	_SWITCH((Vi))
	double psi = (V_rev_e-var_Vi);
	return psi;
}

// inhibitory input to pyramidal population
double Cortical_Column::psi_ie	(int N) const{
	_SWITCH((Ve))
	double psi = (V_rev_i-var_Ve);
	return psi;
}

// inhibitory input to inhibitory population
double Cortical_Column::psi_ii	(int N) const{
	_SWITCH((Vi))
	double psi = (V_rev_i-var_Vi);
	return psi;
}
/*****************************************************************************************************/
/**********************************		 		end			 		**********************************/
/*****************************************************************************************************/


/*****************************************************************************************************/
/**********************************		 Current functions 			**********************************/
/*****************************************************************************************************/
// Leak current of pyramidal population
double Cortical_Column::I_L_e	(int N) const{
	_SWITCH((Ve))
	double I = gL_e * (var_Ve - E_L_e) + gLK_e * (var_Ve - E_LK_e);
	return I;
}

// Leak current of inhibitory population
double Cortical_Column::I_L_i	(int N) const{
	_SWITCH((Vi))
	double I = gL_i * (var_Vi - E_L_i) + gLK_i * (var_Vi - E_LK_i);
	return I;
}
/*****************************************************************************************************/
/**********************************		 		end			 		**********************************/
/*****************************************************************************************************/


/*****************************************************************************************************/
/**********************************		 RK noise scaling 			**********************************/
/*****************************************************************************************************/
// function that returns the noise to exitatory population for stochastic RK4
double Cortical_Column::noise_xRK(int N, double u_1, double u_2) const{
	extern const double h;
	extern const vector<double> B1, B2;
	double n = s  / h * (B1[N-1] * u_1 + B2[N-1] * u_2);
	return n;
}
/*****************************************************************************************************/
/**********************************		 		end			 		**********************************/
/*****************************************************************************************************/


/*****************************************************************************************************/
/**********************************		 	ODE functions 			**********************************/
/*****************************************************************************************************/
// function that calculates the Nth RK term
void Cortical_Column::set_RK		(int N, double u_e1, double u_e2) {
	extern const double dt;
	_SWITCH((Ve)	(theta)
			(Phi_ee)(Phi_ei)(Phi_ie)(Phi_ii)(Phi_ep)(phi_e)
			(x_ee) 	(x_ei)	(x_ie)	(x_ii)	(x_ep)	(y_e))
	Ve	  	[N] = dt/tau_e * ( psi_ee(N) * (var_Phi_ee + var_Phi_ep	) + psi_ie(N) * var_Phi_ie	- c * (I_L_e(N)));
	Vi	  	[N] = dt/tau_i * ( psi_ei(N) * (var_Phi_ei				) + psi_ii(N) * var_Phi_ii	- c * (I_L_i(N)));
	theta 	[N] = dt*(eta*(lambda* var_Ve - var_theta));
	Phi_ee	[N] = dt*(var_x_ee);
	Phi_ei	[N] = dt*(var_x_ei);
	Phi_ie	[N] = dt*(var_x_ie);
	Phi_ii	[N] = dt*(var_x_ii);
	Phi_ep	[N] = dt*(var_x_ep);
	phi_e 	[N] = dt*(var_y_e);
	x_ee  	[N] = dt*(pow(gamma_e, 2) * (N_ee * get_Qe(N) 								- var_Phi_ee) - 2 * gamma_e * var_x_ee);
	x_ei  	[N] = dt*(pow(gamma_e, 2) * (N_ei * get_Qe(N)  								- var_Phi_ei) - 2 * gamma_e * var_x_ei);
	x_ie  	[N] = dt*(pow(gamma_i, 2) * (N_ie * get_Qi(N) 			  			    	- var_Phi_ie) - 2 * gamma_i * var_x_ie);
	x_ii  	[N] = dt*(pow(gamma_i, 2) * (N_ii * get_Qi(N)		 	  			 	  	- var_Phi_ii) - 2 * gamma_i * var_x_ii);
	x_ep  	[N] = dt*(pow(gamma_e, 2) * (N_ep * var_phi_e + noise_xRK(N, u_e1, u_e2)	- var_Phi_ep) - 2 * gamma_e * var_x_ep);
	y_e	 	[N] = dt*(pow(nu, 2) 	  * (	    get_Qe(N)							  	- var_phi_e)  - 2 * nu 	  	* var_y_e);
}

// function that ads all the RK terms together
void Cortical_Column::add_RK(double u_e) {
	extern const double h;
	Ve	  	[0] += (Ve		[1] + Ve	[2] * 2 + Ve	[3] * 2 + Ve	[4])/6;
	Vi	  	[0] += (Vi		[1] + Vi	[2] * 2 + Vi	[3] * 2 + Vi	[4])/6;
	theta 	[0] += (theta	[1] + theta	[2] * 2 + theta	[3] * 2 + theta	[4])/6;
	Phi_ee	[0] += (Phi_ee	[1] + Phi_ee[2] * 2 + Phi_ee[3] * 2 + Phi_ee[4])/6;
	Phi_ei	[0] += (Phi_ei	[1] + Phi_ei[2] * 2 + Phi_ei[3] * 2 + Phi_ei[4])/6;
	Phi_ie	[0] += (Phi_ie	[1] + Phi_ie[2] * 2 + Phi_ie[3] * 2 + Phi_ie[4])/6;
	Phi_ii	[0] += (Phi_ii	[1] + Phi_ii[2] * 2 + Phi_ii[3] * 2 + Phi_ii[4])/6;
	Phi_ep	[0] += (Phi_ep	[1] + Phi_ep[2] * 2 + Phi_ep[3] * 2 + Phi_ep[4])/6;
	phi_e 	[0] += (phi_e	[1] + phi_e	[2] * 2 + phi_e	[3] * 2 + phi_e	[4])/6;
	x_ee  	[0] += (x_ee	[1] + x_ee	[2] * 2 + x_ee	[3] * 2 + x_ee	[4])/6;
	x_ei  	[0] += (x_ei	[1] + x_ei	[2] * 2 + x_ei	[3] * 2 + x_ei	[4])/6;
	x_ie  	[0] += (x_ie	[1] + x_ie	[2] * 2 + x_ie	[3] * 2 + x_ie	[4])/6;
	x_ii  	[0] += (x_ii	[1] + x_ii	[2] * 2 + x_ii	[3] * 2 + x_ii	[4])/6;
	x_ep  	[0] += (x_ep	[1] + x_ep	[2] * 2 + x_ep	[3] * 2 + x_ep	[4])/6 + pow(gamma_e, 2) * s * h * u_e;
	y_e   	[0] += (y_e		[1] + y_e	[2] * 2 + y_e	[3] * 2 + y_e	[4])/6;
}
/*****************************************************************************************************/
/**********************************		 		end			 		**********************************/
/*****************************************************************************************************/
