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

/******************************************************************************/
/*                  Main file for compilation and runtime tests				  */
/******************************************************************************/
#include <iostream>
#include <chrono>

#include "Cortical_Column.h"
#include "Sleep_Regulation.h"
#include "ODE.h"

/******************************************************************************/
/*                          Fixed simulation settings						  */
/******************************************************************************/
typedef std::chrono::high_resolution_clock::time_point timer;
extern const int T      = 30;		/* Time until data is stored in  s		  */
extern const int res 	= 1E4;		/* Number of iteration steps per s		  */
extern const double dt 	= 1E3/res;	/* Duration of a time step in ms		  */
extern const double h	= sqrt(dt); /* Square root of dt for SRK iteration	  */

/******************************************************************************/
/*                              Main simulation routine						  */
/******************************************************************************/
int main(void) {
    /* Initializing the populations */
    Cortical_Column Cortex = Cortical_Column();
    Sleep_Regulation SR = Sleep_Regulation();

    /* Connect cortex with sleep regulatory network */
    Cortex.connect_SR(SR);

    /* Take the time of the simulation */
    timer start,end;

    /* Simulation */
    start = std::chrono::high_resolution_clock::now();
    for (int t=0; t< T*res; ++t) {
        ODE(Cortex, SR);
    }
    end = std::chrono::high_resolution_clock::now();

    /* Time consumed by the simulation */
    double dif = 1E-3*std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count();
    std::cout << "simulation done!\n";
    std::cout << "took " << dif << " seconds" << "\n";
    std::cout << "end\n";
}
