function Stimulation
    Input_N3    = [ 6.5;          % sigma_e
                    2;          % alpha_Na
                    1;          % tau_Na
                    2;        % g_KNa
                    0E-3];      % dphi
                        
                        
    Input_N2    = [ 4.6;        % sigma_e
                    2;          % alpha_Na
                    1;          % tau_Na
                    1.33;       % g_KNa
                    0E-3];      % dphi
            
% stimulation parameters
% first number is the mode of stimulation
% 0 == none
% 1 == periodic
% 2 == phase dependend up state
% 3 == phase dependend down state
var_stim    = [ 1           % mode of stimulation
                100.0;      % strength of the stimulus      in Hz (spikes per second)
                100;       	% duration of the stimulus      in ms
                8;          % time between stimuli          in s    
                550];       % time until stimuli after min 	in ms    
            
% Number of runs for stimulation, as well as color set            
N = 15;
ColorSet = colormap(jet(N));

% time of the stimulation
T           = 4;
t_stim_N2   = linspace(-1,T-1,T*100);
t_stim_N3   = linspace(3,T+3,T*100);

% generate a stimulus reference
Stimulus	=@(t) 2*(heaviside(t) - heaviside(t-0.05)) + 2*(heaviside(t-4) - heaviside(t-4.05))-40;

% create figure handle
figure(1)
clf,shg
hold on

for i=1:N 
    var_stim(2)= i*10;
    [Ve_N2, ~]    = Cortex(T, Input_N2, var_stim);
    [Ve_N3, ~]    = Cortex(T, Input_N3, var_stim);
    plot(t_stim_N2,Ve_N2, 'Color', ColorSet(i,:));
    plot(t_stim_N3,Ve_N3, 'Color', ColorSet(i,:));
end

% create the labels
set(gca,'YTick',[-80,-70,-60,-50,-40,-30]);
set(gca,'XTick',[-1, 0, 1, 2, 4, 5, 6, 7]);
set(gca,'XTickLabel',[-1, 0, 1, 2, 0, 1, 2, 3]);
ylim([-80,-30]);    
xlabel('Time [s]');
ylabel('$V_{e}$ [mV]')

% plot the stimulus reference
plot(t_stim_N2, Stimulus(t_stim_N2),'Color',[0.7,0.7,0.7],'LineWidth',1)
plot(t_stim_N3, Stimulus(t_stim_N3),'Color',[0.7,0.7,0.7],'LineWidth',1)

% plot the separating line
plot([3,3],[-80,-30],'-','Color','Black','LineWidth',0.5)

% label the stimulus and the KC peaks
text(-0.9,-31.5,'(a)')
text( 3.1,-31.5,'(b)')
text(-0.5,-35,'Stimulus')
text(0.0,-45,'P200')
text(0.4,-77.5,'N550')
text(1.1,-42.5,'P900')
hold off
end