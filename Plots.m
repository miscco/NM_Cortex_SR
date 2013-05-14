% mex command is given by: 
% mex CXXFLAGS="\$CXXFLAGS -std=gnu++0x -fpermissive" SteynRoss.cpp Cortical_Colum.cpp

function Plots(T, onset, Con)

if nargin == 0
    Con     = [40;             % N_ee
                    40;             % N_ei
                    80;             % N_ie
                    80;             % N_ii
                    40];            % N_ep (long range)
           
    T          = 100;              % duration of the simulation
    onset   = 20;               % time until data is saved
end

[Ve, Vi, Na, I_KS, I_A, I_KNa]    = Cortex(Con, T, onset);

L           = max(size(Ve));
fs          = L/T;
timeaxis    = linspace(0,T,L);

ImageFontSize=16;
TitleFontSize=20;
AxisFontName='CMU Serif';

figure(1)
set(gca,'FontName',AxisFontName,'FontSize',ImageFontSize,'XTick',[0:0.5:4])
subplot(211), plot(timeaxis,Ve)
title('membrane potential of exitatory  population','FontSize',TitleFontSize),         
xlabel('time in s','FontSize',ImageFontSize), ylabel('V_{e} in mV','FontSize',ImageFontSize), axis tight

subplot(212), plot(timeaxis,Na)
title('membrane potential of inhibitory  population','FontSize',TitleFontSize),         
xlabel('time in s','FontSize',ImageFontSize), ylabel('V_{i} in mV','FontSize',ImageFontSize), axis tight


%exportfig(gcf, 'C_KNa_short.png', 'Format', 'png', 'width', 12.8, 'Color', 'rgb')
 
% fs      = L/T;
% [Pxx,f] = pwelch(Ve-mean(Ve),[], [], [], fs);
% n       = find(f<=60, 1, 'last' );
%  
% figure(7)
% plot(f(1:n),log(Pxx(1:n)))
% title('Powerspectrum with pwelch'), xlabel('frequency in Hz'), ylabel('Power (log)')

%save('Ve.mat', 'Ve')