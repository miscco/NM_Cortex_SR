/****************************************************************************************************/
/*								Header for Stimulation protocoll object								*/
/****************************************************************************************************/
#pragma once
#include "Cortical_Column.h"

class Stim {
public:
	// constructor
	Stim(vector<double> var, Cortical_Column& Column)
	: strength	(var[0]), 	ISI ((int)var[1]), 	start ((int)var[2]), 	duration ((int)var[3]),
	  Col		(&Column)
	{}

	void check_stim	(int time) {
		// check whether a stimulation should start
		// the duration of the stimulation is ignored
		if(time==(start + count_stim*ISI)){
			// turn the stimulation on
			mode = 1;
			Col->set_input(strength);

		}

		// check whether a stimulation should end
		if(mode ==1 && count_dur ==duration) {
			// turn off the stimulation
			mode = 0;
			Col->set_input(0.0);

			// add counter for stimulation occurence
			count_stim++ ;

			// reset the stimulation counter
			count_dur = 0;
		}

		// if stimulation is on track its duration
		if(mode==1){
			count_dur++;
		}
	}

private:

	// stimulation strength
	double strength;

	// inter stimulus intervall
	int ISI;

	// onset until stimulation starts
	int start;

	// duiration of the stimulation
	int duration;

	// counter for stimulation events
	int count_stim = 0;

	// counter for stimulation length
	int count_dur  = 0;

	// Simulation on for TRUE and off for FALSE
	bool mode = 0;

	// cortical column
	Cortical_Column* Col;
};
/****************************************************************************************************/
/*										 		end			 										*/
/****************************************************************************************************/
