function Data_Hypnogram()
% Filename
fn = 'Hypnogram_Refined.mat';

% This routine manually classifies the epochs to a certain sleep stadium;
Num_Epochs = 24*60*2;

% Number of samples per epoch
Num_samples = 30*100;

% Time axis of an epoch
time = linspace(0,30,Num_samples);

% Load or create hypnogram
if(exist(['Data/', fn], 'file') ~=0)
    load(['Data/', fn])
else    
    Hypnogram = -1*ones(Num_Epochs,1);
end

% Load the data
if(exist('Vp', 'var') ==0)
    load('Data/Timeseries_FULL', 'Vp');
end

% sleep scoring through the epochs
% Wake: -1
% REM   0
% N1    1
% N2    2
% N3    3

% As most of the epochs are wake anyway, just skip them
Start_Sleep = 2610;
End_Sleep   = 2620;

figure(1)
for i=Start_Sleep:End_Sleep
   plot(time, Vp((i-1)*Num_samples+1:i*Num_samples));
   ylim([-80,-40]);
   Hypnogram(i) = input(['Score the sleep stadium of Epoch: ', num2str(i), '!']);
   % save every 20 steps
   if mod(1,20)==0
       save(['Data/',fn], 'Hypnogram');
   end
end
save(['Data/',fn], 'Hypnogram');
end