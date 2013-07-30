#include <cmath>
#include "Cortical_Column.h"

/*****************************************************************************************************/
/**********************************		 Firing Rate functions 		**********************************/
/*****************************************************************************************************/
// pyramidal firing rate
double Cortical_Column::get_Qe	(int N) const{
	_SWITCH((Ve))
	double q = Qe_max / (1 + exp(-C * (var_Ve - theta_e) / sigma_e));
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

// sodium dependent potassium current
double Cortical_Column::I_KNa		(int N)  const{
	_SWITCH((Ve)(Na))
	double w_KNa  = 0.37/(1+pow(38.7/var_Na, 3.5));
	double I_KNa  = g_KNa * w_KNa * (var_Ve - E_K);
	return I_KNa;
}
/*****************************************************************************************************/
/**********************************		 		end			 		**********************************/
/*****************************************************************************************************/


/*****************************************************************************************************/
/**********************************		 potassium concentration 		**********************************/
/*****************************************************************************************************/
double Cortical_Column::Na_pump		(int N) const{
	_SWITCH((Na))
	double Na_pump = R_pump*( pow(var_Na, 3)/(pow(var_Na, 3)+3375)  -  pow(Na_eq, 3)/(pow(Na_eq, 3)+3375));
	return Na_pump;
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
	double n = 1  / h * (B1[N-1] * u_1 + B2[N-1] * u_2);
	return n;
}
/*****************************************************************************************************/
/**********************************		 		end			 		**********************************/
/*****************************************************************************************************/


/*****************************************************************************************************/
/**********************************		 	ODE functions 			**********************************/
/*****************************************************************************************************/
// function that calculates the Nth RK term
void Cortical_Column::set_RK		(int N, double u_e1, double u_e2, double u_i1, double u_i2) {
	extern const double dt;
	_SWITCH((Ve)	(Vi)
			(Phi_ee)(Phi_ei)(Phi_ie)(Phi_ii)
			(x_ee) 	(x_ei)	(x_ie)	(x_ii))
	Ve	  	[N] = dt/tau_e * ( - var_Phi_ee * (var_Ve - V_rev_e) - var_Phi_ie * (var_Ve - V_rev_i) - c * (I_L_e(N) + I_KNa(N)));
	Vi	  	[N] = dt/tau_i * ( - var_Phi_ei * (var_Vi - V_rev_e) - var_Phi_ii * (var_Vi - V_rev_i) - c * (I_L_i(N)));
	Na		[N] = dt*(alpha_Na*get_Qe(N) - Na_pump(N))/tau_Na;
	Phi_ee	[N] = dt*(var_x_ee);
	Phi_ei	[N] = dt*(var_x_ei);
	Phi_ie	[N] = dt*(var_x_ie);
	Phi_ii	[N] = dt*(var_x_ii);
	x_ee  	[N] = dt*(pow(gamma_e, 2) * (N_ee * get_Qe(N) + noise_xRK(N, u_e1, u_e2)	- var_Phi_ee) - 2 * gamma_e * var_x_ee);
	x_ei  	[N] = dt*(pow(gamma_e, 2) * (N_ei * get_Qe(N) + noise_xRK(N, u_i1, u_i2)	- var_Phi_ei) - 2 * gamma_e * var_x_ei);
	x_ie  	[N] = dt*(pow(gamma_i, 2) * (N_ie * get_Qi(N) 			  			    	- var_Phi_ie) - 2 * gamma_i * var_x_ie);
	x_ii  	[N] = dt*(pow(gamma_i, 2) * (N_ii * get_Qi(N)		 	  			 	  	- var_Phi_ii) - 2 * gamma_i * var_x_ii);
}

// function that ads all the RK terms together
void Cortical_Column::add_RK(double u_e, double u_i) {
	extern const double h;
	Ve	  	[0] += (Ve		[1] + Ve	[2] * 2 + Ve	[3] * 2 + Ve	[4])/6;
	Vi	  	[0] += (Vi		[1] + Vi	[2] * 2 + Vi	[3] * 2 + Vi	[4])/6;
	Na		[0] += (Na		[1] + Na	[2] * 2 + Na	[3] * 2 + Na	[4])/6;
	Phi_ee	[0] += (Phi_ee	[1] + Phi_ee[2] * 2 + Phi_ee[3] * 2 + Phi_ee[4])/6;
	Phi_ei	[0] += (Phi_ei	[1] + Phi_ei[2] * 2 + Phi_ei[3] * 2 + Phi_ei[4])/6;
	Phi_ie	[0] += (Phi_ie	[1] + Phi_ie[2] * 2 + Phi_ie[3] * 2 + Phi_ie[4])/6;
	Phi_ii	[0] += (Phi_ii	[1] + Phi_ii[2] * 2 + Phi_ii[3] * 2 + Phi_ii[4])/6;
	x_ee  	[0] += (x_ee	[1] + x_ee	[2] * 2 + x_ee	[3] * 2 + x_ee	[4])/6 + pow(gamma_e, 2) * h * u_e;
	x_ei  	[0] += (x_ei	[1] + x_ei	[2] * 2 + x_ei	[3] * 2 + x_ei	[4])/6 + pow(gamma_e, 2) * h * u_i;
	x_ie  	[0] += (x_ie	[1] + x_ie	[2] * 2 + x_ie	[3] * 2 + x_ie	[4])/6;
	x_ii  	[0] += (x_ii	[1] + x_ii	[2] * 2 + x_ii	[3] * 2 + x_ii	[4])/6;
}
/*****************************************************************************************************/
/**********************************		 		end			 		**********************************/
/*****************************************************************************************************/
