% mex command is given by: 
% mex CXXFLAGS="\$CXXFLAGS -std=gnu++0x -fpermissive" Cortex.cpp Cortical_Column.cpp

function Plots(T, onset, Input)

if nargin == 0

% x=[120 %Nee
%    72  %Nie
%   100  %Nei/ii
%    24  %taue
%   2.7  %tauNa
%  0.63  %gKNa
%   -66  %EL
%    30  %taui
%   -64  %VR
%   8.3  %sigma
%   3.6  %alphaNa];

    % fittet input
    Input_N3    = [ 8.5;          % sigma_e
                    2.7;        % alpha_Na
                    2;          % tau_Na
                    60E-3];     % dphi
                        
                        
    Input_N2    = [ 4.5;        % sigma_e
                    2;          % alpha_Na
                    1.2;        % tau_Na
                    60E-3];     % dphi
                     
    % stimulation parameters
    % first number is the mode of stimulation
    % 0 == none
    % 1 == periodic
    % 2 == phase dependend up state
    % 3 == phase dependend down state
    
    var_stim    = [ 0           % mode of stimulation
                    100.0;      % strength of the stimulus      in Hz (spikes per second)
                    100;       	% duration of the stimulus      in ms
                    8;          % time between stimuli          in s    
                    550];       % time until stimuli after min 	in ms
                
    T           =   30;         % duration of the simulation
end
[Ve_N2, Marker_N2]    = Cortex(T, Input_N2, var_stim);
[Ve_N3, Marker_N3]    = Cortex(T, Input_N3, var_stim);

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
%ylim([-5,5]);
subplot(212)
plot(time,Data_N3(i_N3*100+1:(i_N3+T)*100))
title('EEG trace of N3','FontSize',TitleFontSize),  xlabel('time in s','FontSize',ImageFontSize), ylabel('V_{e} in \muV','FontSize',ImageFontSize)
ylim([-5,5]);




figure(2)
subplot(211)
plot(time,zscore(Ve_N2)')
title('Model in N2','FontSize',TitleFontSize),  xlabel('time in s','FontSize',ImageFontSize), ylabel('V_{e} in \muV','FontSize',ImageFontSize)
subplot(212)
plot(time,Data_N2(i_N2*100+1:(i_N2+T)*100))
title('EEG trace of N2','FontSize',TitleFontSize),  xlabel('time in s','FontSize',ImageFontSize), ylabel('V_{e} in \muV','FontSize',ImageFontSize)

% [Pxx,f] = pwelch(Ve_N2,[], [],[], fs);
% n       = find(f<=60, 1, 'last' );
%  
% figure(7)
% plot(log(f(1:n)),log(Pxx(1:n)))
% title('Powerspectrum with pwelch'), xlabel('frequency in Hz'), ylabel('Power (log)')

%save('Ve.mat', 'Ve')
