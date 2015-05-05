% mex command is given by: 
% mex CXXFLAGS="\$CXXFLAGS -std=c++11" Cortex.cpp Cortical_Column.cpp

function Plots(T)

if nargin == 0
    Input_N3    = [ 6.2;        % sigma_e
                    2;          % g_KNa
                 %2;         % alpha_Na
                 %1;         % tau_Na
                    20E-1];	% dphi
                        
                        
    Input_N2    = [ 4.6;        % sigma_e
                    1.33;       % g_KNa
                 %2;         % alpha_Na
                 %1;         % tau_Na
                    20E-1];	% dphi
                     
    % stimulation parameters
    % first number is the mode of stimulation
    % 0 == none
    % 1 == semi-periodic
    % 2 == phase dependend
    
    var_stim    = [ 0;           % mode of stimulation
                    0;          % strength of the stimulus              in Hz (spikes per second)
                    0;       	% duration of the stimulus              in ms
                    0;          % time between stimulation events       in s  (ISI)
                    0;          % range of ISI                          in s  [ISI-range,ISI+range]  
                    0;          % Number of stimuli per event
                    0;          % time between stimuli within a event   in ms         
                    0];         % time until stimuli after minimum      in ms
                
    T           =   30;         % duration of the simulation
end
[Ve_N2, Na_N2, ~]    = Cortex(T, Input_N2, var_stim);
[Ve_N3, Na_N3, ~]    = Cortex(T, Input_N3, var_stim);

% load the data the model should be fit to

load('Data/EEG_Data_N2');
load('Data/EEG_Data_N3');

% plottig the result with an random T second snipplet from the Data
time = linspace(0,T,T*100);

% figure(1)
% subplot(211)
% plot(time,zscore(Ve_N3)')
% title('Model in N3'),  xlabel('time in s'), ylabel('V_{e} in \muV')
% %ylim([-5,5]);
% subplot(212)
% plot(time,Data_N3)
% title('EEG trace of N3'),  xlabel('time in s'), ylabel('V_{e} in \muV')
% %ylim([-5,5]);

figure(2)
subplot(211)
plot(time,(Ve_N2)')
title('Model in N2'),  xlabel('time in s'), ylabel('V_{e} in \muV')
subplot(212)
% plot(time,Data_N2)
% ylim([-8,8]);
% title('EEG trace of N2'),  xlabel('time in s'), ylabel('V_{e} in \muV')

plot(Ve_N2, Na_N2)
xlabel('V_{e}')
ylabel('Na')