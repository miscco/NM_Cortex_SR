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
plot(time,zscore(Ve'))
title('pyramidal membrane voltage','FontSize',TitleFontSize),  xlabel('time in s','FontSize',ImageFontSize), ylabel('V_{e} in \muV','FontSize',ImageFontSize)
subplot(212)
plot(time,Data(i*100+1:(i+T)*100))
title('EEG trace','FontSize',TitleFontSize),  xlabel('time in s','FontSize',ImageFontSize), ylabel('V_{e} in \muV','FontSize',ImageFontSize)
% 
% subplot(212), plot(timeaxis, noise)
% title('noise','FontSize',TitleFontSize), xlabel('time in
% s','FontSize',ImageFontSize), ylabel('Noise input in ms^{-1}','FontSize',ImageFontSize), xlim =([0,T]);
% 
% figure(2)
% set(gca,'FontName',AxisFontName,'FontSize',ImageFontSize,'XTick',[0:0.5:4])
% subplot(511), plot(timeaxis, I_KNa)
% title('I_{NaP} current','FontSize',TitleFontSize), xlabel('time in s','FontSize',ImageFontSize), ylabel('I_{NaP} in \muA','FontSize',ImageFontSize), axis tight
% 
% subplot(512), plot(timeaxis, I_A)
% title('I_{A} current','FontSize',TitleFontSize), xlabel('time in s','FontSize',ImageFontSize), ylabel('I_{A} in \muA','FontSize',ImageFontSize), axis tight
% 
% subplot(513), plot(timeaxis, I_AR)
% title('I_{AR} current','FontSize',TitleFontSize), xlabel('time in s','FontSize',ImageFontSize), ylabel('I_{AR} in \muA','FontSize',ImageFontSize), axis tight
% 
% subplot(514), plot(timeaxis, I_KS)
% title('I_{KS} current','FontSize',TitleFontSize), xlabel('time in s','FontSize',ImageFontSize), ylabel('I_{KS} in \muA','FontSize',ImageFontSize), axis tight
% 
% subplot(515), plot(timeaxis, I_KNa)
% title('I_{KNa} current','FontSize',TitleFontSize), xlabel('time in s','FontSize',ImageFontSize), ylabel('I_{KNa} in \muA','FontSize',ImageFontSize), axis tight
% 
% figure(3)
% set(gca,'FontName',AxisFontName,'FontSize',ImageFontSize,'XTick',[0:0.5:4])
% subplot(511), plot(timeaxis, I_KS + I_KNa)
% title('I_{KS} + I_{KNa}','FontSize',TitleFontSize), xlabel('time in s','FontSize',ImageFontSize), ylabel('In \muA','FontSize',ImageFontSize), axis tight
% 
% subplot(512), plot(timeaxis, I_KNa)
% title('I_{A} + I_{KNa}','FontSize',TitleFontSize), xlabel('time in s','FontSize',ImageFontSize), ylabel('In \muA','FontSize',ImageFontSize), axis tight
% 
% subplot(513), plot(timeaxis, I_AR + I_KNa)
% title('I_{AR} + I_{KNa}','FontSize',TitleFontSize), xlabel('time in s','FontSize',ImageFontSize), ylabel('In \muA','FontSize',ImageFontSize), axis tight
% 
% subplot(514), plot(timeaxis, I_A + I_KS + I_KNa)
% title('I_{A} + I_{KS} + I_{KNa}','FontSize',TitleFontSize), xlabel('time in s','FontSize',ImageFontSize), ylabel('In \muA','FontSize',ImageFontSize), axis tight
% 
% subplot(515), plot(timeaxis, I_AR + I_KS + I_KNa)
% title('I_{AR} + I_{KS} + I_{KNa}','FontSize',TitleFontSize), xlabel('time in s','FontSize',ImageFontSize), ylabel('In \muA','FontSize',ImageFontSize), axis tight

%exportfig(gcf, 'C_K_complex.png', 'Format', 'png', 'width', 12.8, 'Color', 'rgb')
%  
% [Pxx,f] = pwelch(Ve-mean(Ve),[], [],[], fs);
% n       = find(f<=60, 1, 'last' );
%  
% figure(7)
% plot(log(f(1:n)),log(Pxx(1:n)))
% title('Powerspectrum with pwelch'), xlabel('frequency in Hz'), ylabel('Power (log)')

%save('Ve.mat', 'Ve')