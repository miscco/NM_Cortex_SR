#NM_Cortex_SR

This repository contains the reference implementation of the model proposed in Schellenberger Costa et al. 2016, available 
here http://link.springer.com/article/10.1007%2Fs10827-016-0602-z

For convenience we utilize MATLAB for data processing and plotting. Therefore the simulation comes with an additional source-file 
Cortex_SR_mex.cpp that can be compiled within MATLAB to utilize their C++-mex interface. The easiest way to reproduce the figures 
in the paper is to simply run the Create_Data() function within MATLAB, assuming the mex interface is setup. Afterwards simply run the Create_Figures() function to generate the different figures. 

Please note that due to the stochastic nature of the simulation the time series will differ.

