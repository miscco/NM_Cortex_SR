function Plot_Parameter_3D()
% Path to helper functions
if(isempty(strfind(path, [pwd,'/Tools'])))
    addpath([pwd,'/Tools']);
end

% Load the color specification from the other figures
load('Data/Colorspec');

% Load the data
load('Data/Param_classified')

% Create figure
figure()
set(gcf,'units','normalized','outerposition',[0 0 1 1]);
clf

% Plot the data
h = plot3(time_stage{1}, g_KNa_stage{1}, sigma_p_stage{1},...
          time_stage{2}, g_KNa_stage{2}, sigma_p_stage{2},...
          time_stage{3}, g_KNa_stage{3}, sigma_p_stage{3},...
          time_stage{4}, g_KNa_stage{4}, sigma_p_stage{4},...
          time_stage{5}, g_KNa_stage{5}, sigma_p_stage{5});
grid on
set(gca, 'XLim', [0, 24],...
         'XTick', 0:4:24,...
         'XTickLabel', {0, '', 8, '', 16, '', 24},...
         'YLim', [0, 2.5],...
         'YTick', 0:0.5:2.5,...
         'YTickLabel', {0, '', 1, '', 2, ''},...
         'ZLim', [3, 7],...
         'ZTick', 3:1:6);
xlabel('Time [h]')
ylabel('g_{KNa} [mS/cm^2]')
zlabel('\sigma_{p} [mV]')
legend(h, 'WAKE', 'N1', 'N2', 'N3', 'REM', 'location', 'northoutside', 'orientation','horizontal')

for i=1:5
    set(h(i), 'Color', Color{i},'LineWidth', 1.);
end
end