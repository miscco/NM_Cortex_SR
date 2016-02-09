function Plot_Timeseries_Transition()
% Path to helper functions
if(isempty(strfind(path, [pwd,'/Tools'])))
    addpath([pwd,'/Tools']);
end

% Load the data
load('Data/Sleep_Epochs', 'Epoch_NREM_REM', 'Epoch_REM_NREM');

% Create figure
figure()
set(gcf,'units','normalized','outerposition',[0 0 1 1]);
clf;

% Create panel
p = panel('no-manage-font');
p.pack(2);
% set margins
p.de.margintop = 15;
p.de.marginbottom = 15;

% Plot the data
p(1).select();
plot(Epoch_NREM_REM.time, Epoch_NREM_REM.Vp, '-black')
set(gca, 'XLim', [0, 90],...
         'XTick', 0:15:90,... 
         'XTickLabel',[],...
         'YLim', [-80, -40],...
         'YTick',-80:20:-40,...
         'YTickLabel',-80:20:-40);
title('NREM-REM');
ylabel('V_{p} [mV]');

p(2).select();
plot(Epoch_REM_NREM.time, Epoch_REM_NREM.Vp, '-black')
set(gca, 'XLim', [0, 90],...
         'XTick', 0:15:90,... 
         'XTickLabel',0:15:90,...
         'YLim', [-80, -40],...
         'YTick',-80:20:-40,...
         'YTickLabel',-80:20:-40);
title('REM-NREM');
xlabel('Time [s]');
ylabel('V_{p} [mV]');
end