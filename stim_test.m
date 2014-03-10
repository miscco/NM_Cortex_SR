Con        	= [100;			% N_ee
                   60;			% N_ei
                   90;			% N_ie
                   90]; 		% N_ii

    T          	= 5;			% duration of the simulation
    
    var_stim    = [ 0;          	% strength of the stimulus 	in Hz (spikes per second)
                    0;          	% time between stimuli 		in s    
                    0;          	% time until first stimuli 	in s
                    0];        		% duration of the stimulus 	in ms

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
    var_stim(1)= i*0.25E-1;
    [Ve, Na]    = Cortex(T, Con, var_stim);
    subplot(211)
    plot(timeaxis,Ve)
    ylim([-70,-40]);
    title('pyramidal membrane voltage','FontSize',TitleFontSize),  xlabel('time in s','FontSize',ImageFontSize), ylabel('V_{e} in \muV','FontSize',ImageFontSize)
    hold on
    subplot(212)
    plot(timeaxis,0.037./(1+(38.7./Na).^3.5))
    title('pyramidal membrane voltage','FontSize',TitleFontSize),  xlabel('time in s','FontSize',ImageFontSize), ylabel('V_{e} in \muV','FontSize',ImageFontSize)
    hold on
end
exportfig(gcf, 'Response.png', 'Format', 'png', 'width', 12.8, 'Color', 'rgb')
