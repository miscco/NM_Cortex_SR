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
                        
    var_stim    = [ 0;		% strength of the stimulus 	in Hz (spikes per second)
                    10;		% time between stimuli 		in s    
                    1;          % time until first stimuli 	in s
                    50];       	% duration of the stimulus 	in ms
    T           =   5;		% duration of the simulation
end

L           = T*100;
fs          = L/T;
timeaxis    = linspace(-1,T-1,L);
ImageFontSize=16;
TitleFontSize=20;
AxisFontName='CMU Serif';

figure(1)
clf
hold on
for i=1:40 
    var_stim(1)= i*25;
    [Ve]    = Cortex(T, Con, var_stim);
    plot(timeaxis,Ve)
    ylim([-70,-40]);
    title('pyramidal membrane voltage','FontSize',TitleFontSize),  xlabel('time in s','FontSize',ImageFontSize), ylabel('V_{e} in \muV','FontSize',ImageFontSize)
end
hold off
end
