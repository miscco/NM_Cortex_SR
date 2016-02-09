function Plot_Timeseries_Full()
% Path to helper functions
if(isempty(strfind(path, [pwd,'/Tools'])))
    addpath([pwd,'/Tools']);
end

% Load the data
load('Data/Timeseries_FULL', 'time', 'Vp')

% Individual sleep epochs
load('Data/Sleep_Epochs')

% Create figure
figure(1)
set(gcf,'units','normalized','outerposition',[0 0 1 1]);
clf

% Plot the data
plot(time, Vp, '-black')
set(gca, 'XLim', [0, 24],...
         'XTick', 0:4:24,... 
         'XTickLabel',0:4:24,...
         'YLim', [-90, -30],...
         'YTick', -90:30:-30,...
         'YTickLabel', -90:30:-30);
ylabel('V_{p} [mV]');
xlabel('Time [h]');

% Mark the epoch times in the large time series
Lines = [Epoch_WAKE.time_epoch, Epoch_N1.time_epoch, Epoch_N2.time_epoch, Epoch_N3.time_epoch, Epoch_REM.time_epoch;
         Epoch_WAKE.time_epoch, Epoch_N1.time_epoch, Epoch_N2.time_epoch, Epoch_N3.time_epoch, Epoch_REM.time_epoch;];
h = line(Lines, get(gca, 'YLim'));
legend(h, 'WAKE', 'N1', 'N2', 'N3', 'REM', 'location', 'northoutside', 'orientation','horizontal')
end