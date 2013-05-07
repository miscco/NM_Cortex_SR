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

// potassium rectifying current
double Cortical_Column::I_KS		(int N)  const{
	_SWITCH((Ve)(m_KS))
	double I_KS  	= g_KS * var_m_KS	* (var_Ve - V_K);
	return I_KS;
}

// A-type current
double Cortical_Column::I_A			(int N)  const{
	_SWITCH((Ve)(h_A))
	double m_inf_A 	= 1/(1+exp(-(var_Ve+50)/20));
	double I_A 		= g_A * pow(m_inf_A, 3) * var_h_A * (var_Ve - V_K);
	return I_A;
}

// inward rectifier current
double Cortical_Column::I_AR	(int N)  const{
	_SWITCH((Ve))
	double h_inf_AR  	= 1/(1+exp( (var_Ve+75)/4));
	double I_AR  		= g_AR * h_inf_AR * (var_Ve - V_K);
	return I_AR;
}

// natrium dependent potassium current
double Cortical_Column::I_KNa		(int N)  const{
	_SWITCH((Ve)(theta))
	double w_KNa  = 0.37/(1+pow(38.7/var_theta, 3.5));
	double I_KNa  = g_KNa * w_KNa * (var_Ve - V_K);
	return I_KNa;
}
/*****************************************************************************************************/
/**********************************		 		end			 		**********************************/
/*****************************************************************************************************/


/*****************************************************************************************************/
/**********************************		 I_A gating functions		**********************************/
/*****************************************************************************************************/
// A-type current inactivation h_A_inf
double Cortical_Column::h_inf_A		(int N) const{
	_SWITCH((Ve))
	double h_inf_A = 1/(1+exp( (var_Ve+80)/6));
	return h_inf_A;
}
/*****************************************************************************************************/
/**********************************		 		end			 		**********************************/
/*****************************************************************************************************/


/*****************************************************************************************************/
/**********************************		 I_KS gating functions		**********************************/
/*****************************************************************************************************/
// potassium rectifying current activation time constant
double Cortical_Column::tau_m_KS	(int N) const{
	_SWITCH((Ve))
	double tau_m_KS = 16/(exp( (var_Ve+55)/30) + exp(-(var_Ve+55)/30));
	return tau_m_KS;
}

// potassium rectifying current activation variable
double Cortical_Column::m_inf_KS	(int N) const{
	_SWITCH((Ve))
	double m_inf_KS = 1/(1+exp(-(var_Ve+34)/6.5));
	return m_inf_KS;
}
/*****************************************************************************************************/
/**********************************		 		end			 		**********************************/
/*****************************************************************************************************/


/*****************************************************************************************************/
/**********************************		 	Natrium pump	 		**********************************/
/*****************************************************************************************************/
double Cortical_Column::Na_pump		(int N) const{
	_SWITCH((theta))
	double var_Na = var_theta;
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
void Cortical_Column::set_RK		(int N, double u_e1, double u_e2, double u_i1, double u_i2) {
	extern const double dt;
	_SWITCH((m_KS)	(h_A)
			(Phi_ee)(Phi_ei)(Phi_ie)(Phi_ii)(Phi_ep)(phi_e)
			(x_ee) 	(x_ei)	(x_ie)	(x_ii)	(x_ep)	(y_e))
	Ve	  	[N] = dt/tau_e * ( psi_ee(N) * (var_Phi_ee + var_Phi_ep	) + psi_ie(N) * var_Phi_ie	- c * (I_L_e(N) + I_A(N) + I_KNa(N)));
	Vi	  	[N] = dt/tau_i * ( psi_ei(N) * (var_Phi_ei				) + psi_ii(N) * var_Phi_ii	- c * (I_L_i(N)));
	m_KS 	[N] = dt*(m_inf_KS(N) - var_m_KS)/tau_m_KS(N);
	h_A 	[N] = dt*(h_inf_A (N) - var_h_A )/tau_h_A;
	theta 	[N] = dt*(lambda* get_Qe(N) - Na_pump(N));
	Phi_ee	[N] = dt*(var_x_ee);
	Phi_ei	[N] = dt*(var_x_ei);
	Phi_ie	[N] = dt*(var_x_ie);
	Phi_ii	[N] = dt*(var_x_ii);
	Phi_ep	[N] = dt*(var_x_ep);
	phi_e 	[N] = dt*(var_y_e);
	x_ee  	[N] = dt*(pow(gamma_e, 2) * (N_ee * get_Qe(N) + noise_xRK(N, u_e1, u_e2)	- var_Phi_ee) - 2 * gamma_e * var_x_ee);
	x_ei  	[N] = dt*(pow(gamma_e, 2) * (N_ei * get_Qe(N) + noise_xRK(N, u_i1, u_i2)	- var_Phi_ei) - 2 * gamma_e * var_x_ei);
	x_ie  	[N] = dt*(pow(gamma_i, 2) * (N_ie * get_Qi(N) 			  			    	- var_Phi_ie) - 2 * gamma_i * var_x_ie);
	x_ii  	[N] = dt*(pow(gamma_i, 2) * (N_ii * get_Qi(N)		 	  			 	  	- var_Phi_ii) - 2 * gamma_i * var_x_ii);
	x_ep  	[N] = dt*(pow(gamma_e, 2) * (N_ep * var_phi_e 								- var_Phi_ep) - 2 * gamma_e * var_x_ep);
	y_e	 	[N] = dt*(pow(nu, 2) 	  * (	    get_Qe(N)							  	- var_phi_e)  - 2 * nu 	  	* var_y_e);
}

// function that ads all the RK terms together
void Cortical_Column::add_RK(double u_e, double u_i) {
	extern const double h;
	Ve	  	[0] += (Ve		[1] + Ve	[2] * 2 + Ve	[3] * 2 + Ve	[4])/6;
	Vi	  	[0] += (Vi		[1] + Vi	[2] * 2 + Vi	[3] * 2 + Vi	[4])/6;
	m_KS	[0] += (m_KS	[1] + m_KS	[2] * 2 + m_KS	[3] * 2 + m_KS	[4])/6;
	h_A		[0] += (h_A		[1] + h_A	[2] * 2 + h_A	[3] * 2 + h_A	[4])/6;
	theta 	[0] += (theta	[1] + theta	[2] * 2 + theta	[3] * 2 + theta	[4])/6;
	Phi_ee	[0] += (Phi_ee	[1] + Phi_ee[2] * 2 + Phi_ee[3] * 2 + Phi_ee[4])/6 + pow(gamma_e, 2) * s * h * u_e;
	Phi_ei	[0] += (Phi_ei	[1] + Phi_ei[2] * 2 + Phi_ei[3] * 2 + Phi_ei[4])/6 + pow(gamma_e, 2) * s * h * u_i;
	Phi_ie	[0] += (Phi_ie	[1] + Phi_ie[2] * 2 + Phi_ie[3] * 2 + Phi_ie[4])/6;
	Phi_ii	[0] += (Phi_ii	[1] + Phi_ii[2] * 2 + Phi_ii[3] * 2 + Phi_ii[4])/6;
	Phi_ep	[0] += (Phi_ep	[1] + Phi_ep[2] * 2 + Phi_ep[3] * 2 + Phi_ep[4])/6;
	phi_e 	[0] += (phi_e	[1] + phi_e	[2] * 2 + phi_e	[3] * 2 + phi_e	[4])/6;
	x_ee  	[0] += (x_ee	[1] + x_ee	[2] * 2 + x_ee	[3] * 2 + x_ee	[4])/6;
	x_ei  	[0] += (x_ei	[1] + x_ei	[2] * 2 + x_ei	[3] * 2 + x_ei	[4])/6;
	x_ie  	[0] += (x_ie	[1] + x_ie	[2] * 2 + x_ie	[3] * 2 + x_ie	[4])/6;
	x_ii  	[0] += (x_ii	[1] + x_ii	[2] * 2 + x_ii	[3] * 2 + x_ii	[4])/6;
	x_ep  	[0] += (x_ep	[1] + x_ep	[2] * 2 + x_ep	[3] * 2 + x_ep	[4])/6;
	y_e   	[0] += (y_e		[1] + y_e	[2] * 2 + y_e	[3] * 2 + y_e	[4])/6;
}
/*****************************************************************************************************/
/**********************************		 		end			 		**********************************/
/*****************************************************************************************************/
