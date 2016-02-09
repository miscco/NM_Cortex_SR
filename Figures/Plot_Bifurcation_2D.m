function Plot_Bifurcation_2D()
% Path to helper functions
if(isempty(strfind(path, [pwd,'/Tools'])))
    addpath([pwd,'/Tools']);
end

% Load the data
load('Data/Param_classified')

% Load the data from xppaut
fname_Hopf = 'Data/Hopf-diagram.dat';
fname_Fold = 'Data/Saddle-diagram.dat';

% Create figure
figure()
set(gcf,'units','normalized','outerposition',[0 0 1 1]);
clf, shg

% Plot the data
plotxppaut(fname_Hopf,'Red','-')
plotxppaut(fname_Fold,'Black','-')
xlim([0,8.2])
ylim([0.1,10.5])

% Add the vertical lines
plot([0,8],[6.195,6.195],'--','Color',[0.7,0.7,0.7],'LineWidth',0.5)
plot([0,8],[3.617,3.617],'--','Color',[0.7,0.7,0.7],'LineWidth',0.5)

% Label the axes
xlabel('g_{KNa} [mS/cm^2]')
ylabel('\sigma_{p} [mV]')

% Set the ticks for the axes
set(gca,'YTick',[2 4 6 8 10])
set(gca,'XTick',[0 2 4 6 8])

% Load the color specification from the other figures
load('Data/Colorspec');

h = [];
for i=1:5
    h(i) = plot(g_KNa_stage{i}, sigma_p_stage{i},'Color', Color{i}); %#ok<USENS>
end
legend(h, 'WAKE', 'N1', 'N2', 'N3', 'REM', 'location', 'northoutside', 'orientation','horizontal')
end