% mex command is given by: 
% mex CXXFLAGS="\$CXXFLAGS -std=gnu++0x -fpermissive" Cortex.cpp Cortical_Column.cpp

function Plots(T)

if nargin == 0
    Input_N3    = [ 8.7;          % sigma_e
                    2.6;        % alpha_Na
                    3;          % tau_Na
                    1.6;        % g_KNa
                    60E-3];     % dphi
                        
                        
    Input_N2    = [ 4.6;        % sigma_e
                    2;          % alpha_Na
                    1.2;        % tau_Na
                    1.33;       % g_KNa
                    60E-3];     % dphi
                     
    % stimulation parameters
    % first number is the mode of stimulation
    % 0 == none
    % 1 == periodic
    % 2 == phase dependend up state
    % 3 == phase dependend down state
    
    var_stim    = [ 0           % mode of stimulation
                    0;          % strength of the stimulus      in Hz (spikes per second)
                    0;       	% duration of the stimulus      in ms
                    0;          % time between stimuli          in s    
                    0];         % time until stimuli after min 	in ms
                
    T           =   30;         % duration of the simulation
end
%[Ve_N2, ~]    = Cortex(T, Input_N2, var_stim);
[Ve_N3, ~]    = Cortex(T, Input_N3, var_stim);

% load the data the model should be fit to

load('Data/EEG_Data_N2');
load('Data/EEG_Data_N3');

ImageFontSize=16;
TitleFontSize=20;
AxisFontName='CMU Serif';

set(gca,'FontName',AxisFontName,'FontSize',ImageFontSize)
% plottig the result with an random T second snipplet from the Data
time = linspace(0,T,T*100);

figure(1)
subplot(211)
plot(time,zscore(Ve_N3)')
title('Model in N3','FontSize',TitleFontSize),  xlabel('time in s','FontSize',ImageFontSize), ylabel('V_{e} in \muV','FontSize',ImageFontSize)
ylim([-5,5]);
subplot(212)
plot(time,Data_N3)
title('EEG trace of N3','FontSize',TitleFontSize),  xlabel('time in s','FontSize',ImageFontSize), ylabel('V_{e} in \muV','FontSize',ImageFontSize)
ylim([-5,5]);
% 
% figure(2)
% subplot(211)
% plot(time,zscore(Ve_N2)')
% ylim([-8,8]);
% title('Model in N2','FontSize',TitleFontSize),  xlabel('time in s','FontSize',ImageFontSize), ylabel('V_{e} in \muV','FontSize',ImageFontSize)
% subplot(212)
% plot(time,Data_N2)
% ylim([-8,8]);
% title('EEG trace of N2','FontSize',TitleFontSize),  xlabel('time in s','FontSize',ImageFontSize), ylabel('V_{e} in \muV','FontSize',ImageFontSize)

load('/home/schellenberger/workspace/C_model/Data/EEG_Data_N3b.mat')
timeaxis=linspace(0,30,3000);
for i=1:8 subplot(211); plot(timeaxis,zscore(Ve_N3)'); ylim([-4,4]); subplot(212); plot(timeaxis, zscore(data((i-1)*3000+1:i*3000))'); ylim([-4,4]);pause; end


end
