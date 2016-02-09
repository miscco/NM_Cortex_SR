function Create_Figures()
% Path to helper functions
if(isempty(strfind(path, [pwd,'/Tools'])))
    addpath([pwd,'/Tools']);
end


% The 2D Bifurcation diagram from Weigenand2014 with trace from sleep
% plotxppaut requires figure(1)
Plot_Bifurcation_2D();

% Refined Hypnogram 
Plot_Hypnogram();

% A 3D representation of the bifurcation parameter evolution 
Plot_Parameter_3D();

% The individual ultradian cycles 
Plot_Parameter_2D();

% Time series of whole day
Plot_Timeseries_Full();

% Time series of selected epochs
Plot_Timeseries_Epochs_vertical();

% Transition between NREM-REM and REM-NREM
Plot_Timeseries_Transition();
end