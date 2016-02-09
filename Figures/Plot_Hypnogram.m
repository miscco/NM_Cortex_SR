function Plot_Hypnogram()
% Path to helper functions
if(isempty(strfind(path, [pwd,'/Tools'])))
    addpath([pwd,'/Tools']);
end

% Load the refined hypnogram
load('Data/Hypnogram_Refined')
Hypnogram_refined=Hypnogram;

% present the epochs in terms of hours
time_refined = linspace(0,24,2880);

% Load the color specification from the other figures
load('Data/Colorspec');

% Load the concentrations
load('Data/Timeseries_FULL', 'C_E', 'C_G', 'C_A', 'h', 'time');

% downsample the unnecessary high sampling rate to 0.1Hz
C_E = decimate(C_E, 1000,'fir'); %#ok<*NODEF>
C_G = decimate(C_G, 1000,'fir');
C_A = decimate(C_A, 1000,'fir');
h   = decimate(h, 1000,'fir');
time= decimate(time, 1000,'fir');
Hypnogram= -1*ones(length(C_E),1);  % Wake
Hypnogram(C_E<0.4) = 3;             % NREM
Hypnogram(C_A>0.4) = 1;             % REM


% Create figure
figure()
set(gcf,'units','normalized','outerposition',[0 0 1 1]);
clf

% somehow the legend is removed if not run twice
if nargin ~= 0
    Plot_Hypnogram_refined;
end

% Create panel
p = panel('no-manage-font');
p.pack({1/2, 1/4, 1/4});

% Set margins
p.de.margintop = 5;
p.de.marginbottom = 5;

% Plot data
p(1).select();
h = plot(time, C_E, 'g', time, C_G, 'r', time, C_A, 'b', time, h, 'Y');
set(h(4), 'Color', Color{3}); %#ok<USENS>
set(gca, 'XLim', [0, 24],...
         'XTick', 0:4:24,... 
         'XTickLabel',[]);
legend('C_{E}', 'C_{G}', 'C_{A}', 'h', 'location', 'northoutside', 'orientation','horizontal');
ylabel('Concentration [aU]');

p(2).select();
plot(time, Hypnogram, 'black');
ylim([-0.5, 1.5])
set(gca, 'XLim', [0, 24],...
         'XTick', 0:4:24,... 
         'XTickLabel',[],...
         'YLim', [-2,4],...
         'YTick', [-1,1,3], ...
         'YTickLabel', {'Wake', 'REM', 'NREM'},...
         'YDir','reverse');

p(3).select();
plot(time_refined, Hypnogram_refined, 'black');
ylim([-0.5, 1.5])
xlabel('Time [h]');
set(gca, 'XLim', [0, 24],...
         'XTick', 0:4:24,... 
         'YLim', [-2,4],...
         'YTick', -1:1:3, ...
         'YTickLabel', {'Wake', 'REM', 'N1', 'N2', 'N3'},...
         'YDir','reverse');
end