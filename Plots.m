% mex command is given by: 
% mex CXXFLAGS="\$CXXFLAGS -std=gnu++0x -fpermissive" Cortex.cpp Cortical_Column.cpp

function Plots(T, onset, Input)

addpath('~/Documents/MATLAB/TC_model/Data');                            % Data folder

% load the data the model should be fit to
load('S13_2');
Data=zscore(double(data30(6,(391*100):(630*100))))';


if nargin == 0
    Input                = [102.8;		% N_ee
                            72.3;			% N_ei
                            100.5;		% N_ie
                            100.5; 		% N_ii
                            3.6322;        % alpha_Na
                            2.718;		% tau_Na
                            0.6347;			% g_KNa
                            24.36;		% tau_e
                            29.75; 		% tau_i
                            -64.5536;        % theta_e
                            8.3553];      % sigma_e
    T          = 30;			% duration of the simulation
    onset    = 10;			% time until data is saved
end



[Ve]    = Cortex(Input,T,onset);

L           = max(size(Ve));
fs          = L/T;
timeaxis    = linspace(0,T,L);

ImageFontSize=16;
TitleFontSize=20;
AxisFontName='CMU Serif';

figure(1)
set(gca,'FontName',AxisFontName,'FontSize',ImageFontSize)
% plottig the result with an random T second snipplet from the Data
time = linspace(0,T,T*100);
i    = randi([0,239-T],1);
figure(1)
subplot(211)
plot(time,Ve')
title('pyramidal membrane voltage','FontSize',TitleFontSize),  xlabel('time in s','FontSize',ImageFontSize), ylabel('V_{e} in \muV','FontSize',ImageFontSize)
subplot(212)
plot(time,Data(i*100+1:(i+T)*100))
title('EEG trace','FontSize',TitleFontSize),  xlabel('time in s','FontSize',ImageFontSize), ylabel('V_{e} in \muV','FontSize',ImageFontSize)

%exportfig(gcf, 'C_K_complex.png', 'Format', 'png', 'width', 12.8, 'Color', 'rgb')
%  
% [Pxx,f] = pwelch(Ve-mean(Ve),[], [],[], fs);
% n       = find(f<=60, 1, 'last' );
%  
% figure(7)
% plot(log(f(1:n)),log(Pxx(1:n)))
% title('Powerspectrum with pwelch'), xlabel('frequency in Hz'), ylabel('Power (log)')

%save('Ve.mat', 'Ve')