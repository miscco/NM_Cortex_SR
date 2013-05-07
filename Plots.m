% mex command is given by: 
% mex CXXFLAGS="\$CXXFLAGS -std=gnu++0x -fpermissive" SteynRoss.cpp Cortical_Colum.cpp

function Plots(T, onset, Con)

if nargin == 0
    Con     = [40;             % N_ee
               40;             % N_ei
               80;             % N_ie
               80;             % N_ii
               40];            % N_ep (long range)
           
    T       = 300;              % duration of the simulation
    onset   = 10;               % time until data is saved
end

[Ve, theta, I_KNa, noise]    = Cortex(Con, T, onset);

L           = max(size(Ve));
fs          = L/T;
timeaxis    = linspace(0,T,L);
noise = noise(onset*fs+1:end);

figure(1)
subplot(311), plot(timeaxis,Ve)
title('membrane potential of exitatory  population'),         xlabel('time in s'), ylabel('V_{e} in mV'), axis tight
subplot(312), plot(timeaxis,theta)
title('membrane potential of inhibitory population'),         xlabel('time in s'), ylabel('V_{i} in mV'), axis tight
subplot(313), plot(timeaxis, I_KNa)
title('I_KNa current'),         xlabel('time in s'), ylabel('V_{i} in mV'), axis tight
%exportfig(gcf, 'TC_full.png', 'Format', 'png', 'height', 11, 'Color', 'rgb', 'FontMode', 'fixed', 'FontSize', 22)
% 
% fs      = L/T;
% [Pxx,f] = pwelch(Ve-mean(Ve),[], [], [], fs);
% n       = find(f<=60, 1, 'last' );
%  
% figure(7)
% plot(f(1:n),log(Pxx(1:n)))
% title('Powerspectrum with pwelch'), xlabel('frequency in Hz'), ylabel('Power (log)')

%save('Ve.mat', 'Ve')