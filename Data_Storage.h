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
/*									Functions for data storage										*/
/****************************************************************************************************/
#pragma once
#include "Cortical_Column.h"
#include "Sleep_Regulation.h"

/****************************************************************************************************/
/*											Save data												*/
/****************************************************************************************************/
inline void get_data(int counter, Cortical_Column& Col, Sleep_Regulation& SR, vector<double*> pData) {
    pData[0][counter] = Col.Vp		[0];
	pData[1][counter] = Col.Vi		[0];
	pData[2][counter] = SR.f_W		[0];
	pData[3][counter] = SR.f_N		[0];
	pData[4][counter] = SR.f_R		[0];
	pData[5][counter] = SR.C_E		[0];
	pData[6][counter] = SR.C_G		[0];
	pData[7][counter] = SR.C_A		[0];
	pData[8][counter] = SR.h		[0];
	pData[9][counter] = Col.g_KNa	[0];
    pData[10][counter]= Col.sigma_p	[0];

}
/****************************************************************************************************/
/*										 		end													*/
/****************************************************************************************************/
