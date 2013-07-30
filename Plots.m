% mex command is given by: 
% mex CXXFLAGS="\$CXXFLAGS -std=gnu++0x -fpermissive" SteynRoss.cpp Cortical_Colum.cpp

function Plots(T, onset, Con)

if nargin == 0
    Con        = [80;			% N_ee
                  60;			% N_ei
                  90;			% N_ie
                  90]; 			% N_ii

    T          = 60;			% duration of the simulation
    onset      = 20;			% time until data is saved
    
    var_stim   = [0;			% strength of the stimulus
                  1050E1;		% time until stimulus         in 0.1 ms
                  50E1;			% duration of the stimulus in 0.1 ms
                  1;			% number of stimuli
                  10];			% minimal time between stimulations
end

[Ve]    = Cortex(Con, T, onset, var_stim);

L           = max(size(Ve));
fs          = L/T;
timeaxis    = linspace(0,T,L);

ImageFontSize=16;
TitleFontSize=20;
AxisFontName='CMU Serif';

figure(2)
set(gca,'FontName',AxisFontName,'FontSize',ImageFontSize)
subplot(111), plot(timeaxis, Ve)
title('pyramidal membrane voltage','FontSize',TitleFontSize),  xlabel('time in s','FontSize',ImageFontSize), ylabel('Vi_{e} in \muV','FontSize',ImageFontSize)
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

%exportfig(gcf, 'C_KNa_short.png', 'Format', 'png', 'width', 12.8, 'Color', 'rgb')
%  
% [Pxx,f] = pwelch(Ve-mean(Ve),[], [],[], fs);
% n       = find(f<=60, 1, 'last' );
%  
% figure(7)
% plot(log(f(1:n)),log(Pxx(1:n)))
% title('Powerspectrum with pwelch'), xlabel('frequency in Hz'), ylabel('Power (log)')

%save('Ve.mat', 'Ve')