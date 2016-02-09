function Plot_Parameter_2D()
% Path to helper functions
if(isempty(strfind(path, [pwd,'/Tools'])))
    addpath([pwd,'/Tools']);
end

% NOTE: The time arrows were postprocessed in tikz

% Load the color specification from the other figures
load('Data/Colorspec');

% Load the data
load('Data/Param_ultradian')

% load the data from xppaut
fname_Hopf = 'Data/Hopf-diagram.dat';

% Create figure
figure();
set(gcf,'units','normalized','outerposition',[0 0 1 1]);
clf

% Create panel
p = panel('no-manage-font');
p.pack(2,2);

% set margins
p.margin = 20;

% Plot the ultradian cycles
p(1,1).select();
h1 = plot(g_KNa_ultradian{1, 1}, sigma_p_ultradian{1, 1},...
          g_KNa_ultradian{1, 2}, sigma_p_ultradian{1, 2},...
          g_KNa_ultradian{1, 3}, sigma_p_ultradian{1, 3},...
          g_KNa_ultradian{1, 4}, sigma_p_ultradian{1, 4});
      
plotxppaut(fname_Hopf,'Red','-');
set(gca, 'XLim', [0, 2.25], 'XTickLabel', [], 'XTick', 0:0.5:2, 'YLim', [3, 7], 'YTick', 3:1:7, 'YTickLabel', {'3', [], '5', [], '7'});
text(0.0,1.0,'First cycle','Units','normalized', 'VerticalAlignment', 'top');
text(0.7,0.225, 'Hopf','Units','normalized', 'VerticalAlignment', 'bottom', 'color', 'red');
ylabel('\sigma_{p} [mV]');

p(1,2).select();
h2 = plot(g_KNa_ultradian{2, 1}, sigma_p_ultradian{2, 1},...
          g_KNa_ultradian{2, 2}, sigma_p_ultradian{2, 2},...
          g_KNa_ultradian{2, 3}, sigma_p_ultradian{2, 3},...
          g_KNa_ultradian{2, 4}, sigma_p_ultradian{2, 4});
      
plotxppaut(fname_Hopf,'Red','-');
set(gca, 'XLim', [0, 2.25], 'XTickLabel', [], 'XTick', 0:0.5:2, 'YLim', [3, 7], 'YTick', 3:1:7, 'YTickLabel', {'3', [], '5', [], '7'}, 'YAxisLocation', 'right');
text(0.0,1.0,'Second cycle','Units','normalized', 'VerticalAlignment', 'top');
text(0.7,0.225, 'Hopf','Units','normalized', 'VerticalAlignment', 'bottom', 'color', 'red');
ylabel('\sigma_{p} [mV]')

p(2,1).select();
h3 = plot(g_KNa_ultradian{3, 1}, sigma_p_ultradian{3, 1},...
          g_KNa_ultradian{3, 2}, sigma_p_ultradian{3, 2},...
          g_KNa_ultradian{3, 3}, sigma_p_ultradian{3, 3},...
          g_KNa_ultradian{3, 4}, sigma_p_ultradian{3, 4});
      
plotxppaut(fname_Hopf,'Red','-');
set(gca, 'XLim', [0, 2.25], 'XTick', 0:0.5:2, 'YLim', [3, 7], 'YTick', 3:1:7, 'YTickLabel', {'3', [], '5', [], '7'})
text(0.0,1.0,'Third cycle','Units','normalized', 'VerticalAlignment', 'top');
text(0.7,0.225, 'Hopf','Units','normalized', 'VerticalAlignment', 'bottom', 'color', 'red');
xlabel('g_{KNa} [mS/cm^2]')
ylabel('\sigma_{p} [mV]')

p(2,2).select();
h4 = plot(g_KNa_ultradian{4, 1}, sigma_p_ultradian{4, 1},...
          g_KNa_ultradian{4, 2}, sigma_p_ultradian{4, 2},...
          g_KNa_ultradian{4, 3}, sigma_p_ultradian{4, 3},...
          g_KNa_ultradian{4, 4}, sigma_p_ultradian{4, 4});
      
plotxppaut(fname_Hopf,'Red','-');
set(gca, 'XLim', [0, 2.25], 'XTick', 0:0.5:2, 'YLim', [3, 7], 'YTick', 3:1:7, 'YTickLabel', {'3', [], '5', [], '7'}, 'YAxisLocation', 'right');
text(0.0,1.0,'Fourth cycle','Units','normalized', 'VerticalAlignment', 'top');
text(0.7,0.225, 'Hopf','Units','normalized', 'VerticalAlignment', 'bottom', 'color', 'red');
xlabel('g_{KNa} [mS/cm^2]')
ylabel('\sigma_{p} [mV]')

% Set the colors depending on the sleep stage
for i=1:4
    set(h1(i), 'Color', Color{i+1},'LineWidth', 1.);
    set(h2(i), 'Color', Color{i+1},'LineWidth', 1.);
    set(h3(i), 'Color', Color{i+1},'LineWidth', 1.);
    set(h4(i), 'Color', Color{i+1},'LineWidth', 1.);    
end

% Add legend for all plots
hl = legend(p(1,1).select(), 'N1', 'N2', 'N3', 'REM', 'location', 'northoutside', 'orientation','horizontal');
newPosition = [0.4 1.1 0.2 0.2];
newUnits = 'normalized';
set(hl,'Position', newPosition,'Units', newUnits);
end