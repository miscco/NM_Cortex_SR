% mex command is given by: 
% mex CXXFLAGS="\$CXXFLAGS -std=gnu++0x -fpermissive" SteynRoss.cpp Cortical_Colum.cpp

function Plots(T, onset, Con)

if nargin == 0
    Con        = [100;			% N_ee
                  60;			% N_ei
                  90;			% N_ie
                  90]; 			% N_ii

    T          = 30;			% duration of the simulation
    onset      = 60;			% time until data is saved
    
    var_stim   = [1E-3;			% strength of the stimulus
                  1050E1;		% time until stimulus         in 0.1 ms
                  50E1;			% duration of the stimulus in 0.1 ms
                  1;			% number of stimuli
                  10];			% minimal time between stimulations
end

[Ve, ~]    = Cortex(T, onset, Con, var_stim);

L           = max(size(Ve));
fs          = L/T;
timeaxis    = linspace(0,T,L);

ImageFontSize=16;
TitleFontSize=20;
AxisFontName='CMU Serif';

%figure(2)
set(gca,'FontName',AxisFontName,'FontSize',ImageFontSize)
subplot(111), plot(timeaxis, Ve)
title('pyramidal membrane voltage','FontSize',TitleFontSize),  xlabel('time in s','FontSize',ImageFontSize), ylabel('Vi_{e} in \muV','FontSize',ImageFontSize)
%  
% [Pxx,f] = pwelch(Ve-mean(Ve),[], [],[], fs);
% n       = find(f<=60, 1, 'last' );
%  
% figure(7)
% plot(log(f(1:n)),log(Pxx(1:n)))
% title('Powerspectrum with pwelch'), xlabel('frequency in Hz'), ylabel('Power (log)')

%save('Ve.mat', 'Ve')