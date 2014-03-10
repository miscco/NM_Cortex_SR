% mex command is given by: 
% mex CXXFLAGS="\$CXXFLAGS -std=gnu++0x -fpermissive" Cortex.cpp Cortical_Column.cpp

function Plots(T, onset, Input)

if nargin == 0
    % fittet input
    Input_N3    = [ 2.6;        % alpha_Na
                    3;          % tau_Na
                    1.33	% g_KNa
                    -63;        % theta_e
                    8;          % sigma_e
                    30E-3];     % dphi
                        
                        
    Input_N2    = [ 2;          % alpha_Na
                    1;          % tau_Na
                    1.33;	% g_KNa
                    -58.5;      % theta_e
                    4.25;       % sigma_e
                    30E-3];     % dphi
                        
    var_stim    = [ 0;          % strength of the stimulus 	in Hz (spikes per second)
                    0;          % time between stimuli 		in s    
                    0;          % time until first stimuli 	in s
                    0];        	% duration of the stimulus 	in ms
    T           =   30;		% duration of the simulation
end

[Ve_N2]    = Cortex(T, Input_N2, var_stim);
[Ve_N3]    = Cortex(T, Input_N3, var_stim);

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
subplot(211)
plot(time,zscore(Ve_N3)')
title('Model in N3','FontSize',TitleFontSize),  xlabel('time in s','FontSize',ImageFontSize), ylabel('V_{e} in \muV','FontSize',ImageFontSize)
ylim([-5,5]);
subplot(212)
plot(time,Data_N3(i_N3*100+1:(i_N3+T)*100))
title('EEG trace of N3','FontSize',TitleFontSize),  xlabel('time in s','FontSize',ImageFontSize), ylabel('V_{e} in \muV','FontSize',ImageFontSize)
ylim([-5,5]);
%exportfig(gcf, 'Cortex_N3.png', 'Format', 'png', 'width', 28, 'Color', 'rgb')



figure(2)
subplot(211)
plot(time,zscore(Ve_N2)')
title('Model in N2','FontSize',TitleFontSize),  xlabel('time in s','FontSize',ImageFontSize), ylabel('V_{e} in \muV','FontSize',ImageFontSize)
subplot(212)
plot(time,Data_N2(i_N2*100+1:(i_N2+T)*100))
title('EEG trace of N2','FontSize',TitleFontSize),  xlabel('time in s','FontSize',ImageFontSize), ylabel('V_{e} in \muV','FontSize',ImageFontSize)
%exportfig(gcf, 'Cortex_N2.png', 'Format', 'png', 'width', 28, 'Color', 'rgb')

% [Pxx,f] = pwelch(Ve_N2,[], [],[], fs);
% n       = find(f<=60, 1, 'last' );
%  
% figure(7)
% plot(log(f(1:n)),log(Pxx(1:n)))
% title('Powerspectrum with pwelch'), xlabel('frequency in Hz'), ylabel('Power (log)')

%save('Ve.mat', 'Ve')
