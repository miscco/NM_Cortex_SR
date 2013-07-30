if ( exist('~/Documents/MATLAB/SW_power/','dir')~=7)
    addpath('~/Documents/MATLAB/SW_power/');
end

Con         = [60;                % N_ee
                    60;                % N_ei
                    90;                % N_ie
                    90;                % N_ii
                    40];            % N_ep (long range)

T              = 30;               % duration of the simulation
onset       = 20;                 % time until data is saved
    
var_stim   = [0;                 % strength of the stimulus
                     1050E1;       % time until stimulus         in 0.1 ms
                      50E1;          % duration of the stimulus in 0.1 ms
                      1;                % number of stimuli
                      10];               % minimal time between stimulations
    
[Ve] = TC(Con, T, onset, var_stim);

% reducing the sampling rate to 100 Hz
data        = decimate(Ve, 100);
fs          = 100;

% filter of the data with respect to the full spectrum
% lowpass first
fpass       = 30;            % begin of the passband in Hz  4Hz für SW-average, 30 Hz for spectrum
fstop       = 30.4;          % begin of the stopband in Hz
data_filter = lowpass(data, fpass, fstop, fs);

% highpass second
fpass       = 0.2;          % begin of the passband in Hz
fstop       = 0.16;         % begin of the stopband in Hz
data_filter = highpass(data_filter, fpass, fstop, fs);

%'finding the SW
A=200; B=1000; C=-2; D=140;
[y,~,~]=SWMMM(data_filter',[],fs,A,B,C,D);
events=y(:,1);
pre=-1000;                  % time before a slow oszillation
post=4250;                  % time after  a slow oszillation
numel(events)
% cutting off events, that are to close to the edges of the data
events(events>(numel(data_filter)-post/10-10))= [];   
events(events<abs(pre)/10)= [];

Y=eta(data', events,[pre,post],fs,true);
Y= mean(Y,1);
timeaxis = linspace(0,T,max(size(data)));

figure(1)
subplot(211), plot(timeaxis(3000:6000),data_filter(3000:6000))
title('membrane potential of exitatory  population'),         xlabel('time in s'), ylabel('V_{e} in mV'), axis tight
subplot(212), plot(pre:10:post,Y);
title('Slow wave triggered average'); xlabel('time in ms'); ylabel('mV');