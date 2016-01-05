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
 */

/****************************************************************************************************/
/*									Implementation of the ODE solver								*/
/****************************************************************************************************/
#pragma once
#include "Sleep_Regulation.h"
#include "Cortical_Column.h"

/****************************************************************************************************/
/*										Evaluation of SRK4											*/
/****************************************************************************************************/
void ODE(Cortical_Column& Cortex, Sleep_Regulation& SR) {
	/* First calculate every ith RK moment. Has to be in order, 1th moment first */
	for (int i=0; i<4; ++i) {
		SR.set_RK(i);
		Cortex.set_RK(i);
	}

	/* Add all moments */
	SR.add_RK();
	Cortex.add_RK();
}
/****************************************************************************************************/
/*										 		end													*/
/****************************************************************************************************/
