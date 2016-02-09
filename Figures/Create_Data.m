function Create_Data()

% Create data folder
if(exist('Data', 'dir')==0)
    mkdir('Data');
end

% Get the EEG data for the different initial parameters
Data_Sleep_Transition(1); % Takes a long time (1h)

% Extract epochs data. Time points have to be set *MANUALLY*
Data_Sleep_Epochs(1);

% Score the time series *MANUALLY*
Data_Hypnogram_Timeseries();
Data_Hypnogram_Timescales();

% Segmentize the data wrt to sleep scoring
Data_Param_classify();
end