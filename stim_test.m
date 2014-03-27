% mex command is given by: 
% mex CXXFLAGS="\$CXXFLAGS -std=gnu++0x -fpermissive" Cortex.cpp Cortical_Column.cpp

function stim_test

if nargin == 0
    % fittet input
    Input_N3    = [ 28;         % tau_e
                    -63;        % theta_e
                    8;          % sigma_e
                    2.6;        % alpha_Na
                    1.3;          % tau_Na
                    1.33        % g_KNa
                    0E-3];      % dphi
                        
                        
    Input_N2    = [ 30;         % tau_e
                    -58.5;      % theta_e
                    4.25;       % sigma_e
                    2;          % alpha_Na
                    1.3;        % tau_Na
                    1.33;       % g_KNa
                    0E-3];      % dphi
                        
    var_stim    = [ 0;		% strength of the stimulus 	in Hz (spikes per second)
                    10;		% time between stimuli 		in s    
                    1;          % time until first stimuli 	in s
                    50];       	% duration of the stimulus 	in ms
    T           =   5;		% duration of the simulation
end

L           = T*100;
timeaxis    = linspace(-1,T-1,L);

figure(1)
clf
hold on
for i=1:20 
    var_stim(1)= i*20;
    [Ve]    = Cortex(T, Input_N3, var_stim);
    plot(timeaxis,Ve)
    ylim([-80,-40]);
    title('pyramidal membrane voltage'),  xlabel('time in s'), ylabel('V_{e} in \muV')
end
hold off
end
