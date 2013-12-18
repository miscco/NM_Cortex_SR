% mex command is given by: 
% mex CXXFLAGS="\$CXXFLAGS -std=gnu++0x -fpermissive" Cortex.cpp Cortical_Column.cpp

function Plots(T, onset, Input)

if nargin == 0
    % fittet input
    Input_N3    = [ 102;         % N_ee
                    72;			% N_ei
                    100;		% N_ie
                    100; 		% N_ii
                    3.6322;     % alpha_Na
                    2.7;		% tau_Na
                    0.6347;		% g_KNa
                    25;         % tau_e
                    30; 		% tau_i
                    -64.5536;   % theta_e
                    8.3553];	% sigma_e
                        
    Input_N2    = [ 120;	% N_ee
                    60;			% N_ei
                    90;         % N_ie
                    90;         % N_ii
                    2.;         % alpha_Na
                    1;          % tau_Na
                    1.33;		% g_KNa
                    30;         % tau_e
                    30; 		% tau_i
                    -58.5;      % theta_e
                    4];         % sigma_e
                        
    var_stim    = [ 0;          % strength of the stimulus in Hz (spikes per second)
                    0;          % time between   stimuli in s    
                    0;          % time until first stimuli in s
                    0];        % duration of the stimulus in ms
    T           =   30;			% duration of the simulation
    onset       =   10;			% time until data is saved
end

[Ve_N2]    = Cortex(T, onset, Input_N2, var_stim);
[Ve_N3]    = Cortex(T, onset, Input_N3, var_stim);

% load the data the model should be fit to
addpath('~/Documents/MATLAB/TC_model/Data');        % Data folder
load('N2data');
Data_N2=zscore(data)';
load('S13_2', 'data30');
Data_N3=zscore(double(data30(6,(391*100):(630*100))))';

ImageFontSize=16;
TitleFontSize=20;
AxisFontName='CMU Serif';

set(gca,'FontName',AxisFontName,'FontSize',ImageFontSize)
% plottig the result with an random T second snipplet from the Data
time = linspace(0,T,T*100);
i_N2    = randi([0,150-T],1);
i_N3    = randi([0,239-T],1);

figure(1)
subplot(221)
plot(time,zscore(Ve_N2)')
title('Model in N2','FontSize',TitleFontSize),  xlabel('time in s','FontSize',ImageFontSize), ylabel('V_{e} in \muV','FontSize',ImageFontSize)
subplot(222)
plot(time,zscore(Ve_N3)')
title('Model in N3','FontSize',TitleFontSize),  xlabel('time in s','FontSize',ImageFontSize), ylabel('V_{e} in \muV','FontSize',ImageFontSize)
subplot(223)
plot(time,Data_N2(i_N2*100+1:(i_N2+T)*100))
title('EEG trace of N2','FontSize',TitleFontSize),  xlabel('time in s','FontSize',ImageFontSize), ylabel('V_{e} in \muV','FontSize',ImageFontSize)
subplot(224)
plot(time,Data_N3(i_N3*100+1:(i_N3+T)*100))
title('EEG trace of N3','FontSize',TitleFontSize),  xlabel('time in s','FontSize',ImageFontSize), ylabel('V_{e} in \muV','FontSize',ImageFontSize)
%exportfig(gcf, 'C_K_complex.png', 'Format', 'png', 'width', 12.8, 'Color', 'rgb')
%  
% [Pxx,f] = pwelch(Ve-mean(Ve),[], [],[], fs);
% n       = find(f<=60, 1, 'last' );
%  
% figure(7)
% plot(log(f(1:n)),log(Pxx(1:n)))
% title('Powerspectrum with pwelch'), xlabel('frequency in Hz'), ylabel('Power (log)')

%save('Ve.mat', 'Ve')
