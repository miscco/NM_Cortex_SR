function Data_Sleep_Transition()

% Move to source folder(assuming it contains the figures folder
cd ..;

% Check if the executable exists and compile if needed
if(exist('Cortex_SR.mesa64', 'file')==0)
    mex CXXFLAGS="\$CXXFLAGS -std=c++11 -O3" Cortex_SR_mex.cpp Cortical_Column.cpp Sleep_Regulation.cpp;
end

% Add the path to the simulation routine
addpath(pwd);

% Go back into figures folder
cd Figures;

% Duration of the simulation in Hours and T = seconds
H  = 24;
T  = H*3600;

% Initial parameters for the sleep regulatory network
Param_SR = [5.8043;
            0.0001;
            0.0001;
            0.5086];

% Simulation routine takes a long time        
[Ve, Na, f_W, f_N, f_R, C_E, C_G, C_A, h, g_KNa, sigma_p]  = Cortex_SR_mex(T, Param_SR);  %#ok<*ASGLU>

time = linspace(0, H, T*100); %#ok<NASGU>
clear Param_SR T H;

save('Data/Timeseries_FULL');
end