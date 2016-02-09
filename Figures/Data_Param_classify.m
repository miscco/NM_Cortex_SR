function Data_Param_classify()
load('Data/Timeseries_FULL', 'C_E', 'C_A', 'g_KNa', 'sigma_p', 'time');
load('Data/Hypnogram_Refined.mat')

% Upsample Hypnogram
Hypnogram = repmat(Hypnogram', 3000, 1);
Hypnogram = reshape(Hypnogram, 8640000, 1);

% Get the indices for the sleep stages
wake = logical(Hypnogram ==-1);
REM  = logical(Hypnogram == 0);
N1   = logical(Hypnogram == 1);
N2   = logical(Hypnogram == 2);
N3   = logical(Hypnogram == 3);

% Insert NaNs after epochs
Transitions = find(diff(Hypnogram));
g_KNa(Transitions)   = NaN;
sigma_p(Transitions) = NaN;
time(Transitions)    = NaN;

% Find the end of the rem phases
id_REM = find(diff(REM));
id_REM = id_REM(2:2:end);
id_ultradian = [find(diff(wake), 1, 'first')+1;
                id_REM]; 
            
% There might be some N1 after REm so search for the last change in sleep stage
id_ultradian(end) = find(diff(Hypnogram)~=0, 1, 'last');

% Sleep stage class containers. The ultradian cycles are during sleep so
% there is no wakefulness
g_KNa_stage       = cell(5,1);            
g_KNa_ultradian   = cell(4,4);
sigma_p_stage     = cell(5,1);
sigma_p_ultradian = cell(4,4);     

% Cut the data out
g_KNa_stage{1} = g_KNa(wake);sigma_p_stage{1} = sigma_p(wake);
g_KNa_stage{2} = g_KNa(N1);  sigma_p_stage{2} = sigma_p(N1);
g_KNa_stage{3} = g_KNa(N2);  sigma_p_stage{3} = sigma_p(N2);
g_KNa_stage{4} = g_KNa(N3);  sigma_p_stage{4} = sigma_p(N3);
g_KNa_stage{5} = g_KNa(REM); sigma_p_stage{5} = sigma_p(REM);

time_stage{1} = time(wake);
time_stage{2} = time(N1);
time_stage{3} = time(N2);
time_stage{4} = time(N3);
time_stage{5} = time(REM);
   
for i=1:4
    ultradian = false(size(g_KNa))';
    ultradian(id_ultradian(i)+1:id_ultradian(i+1)) = true;
    g_KNa_ultradian{i,1} = g_KNa(N1 & ultradian);  sigma_p_ultradian{i,1} = sigma_p(N1& ultradian);
    g_KNa_ultradian{i,2} = g_KNa(N2 & ultradian);  sigma_p_ultradian{i,2} = sigma_p(N2& ultradian);
    g_KNa_ultradian{i,3} = g_KNa(N3 & ultradian);  sigma_p_ultradian{i,3} = sigma_p(N3& ultradian);  
    g_KNa_ultradian{i,4} = g_KNa(REM & ultradian); sigma_p_ultradian{i,4} = sigma_p(REM& ultradian);   
end

% Some stages might not be there every ultradian cycle, NaN them.
for i=1:numel(g_KNa_ultradian)
    if isempty(g_KNa_ultradian{i})
        g_KNa_ultradian{i} = NaN;
        sigma_p_ultradian{i} = NaN;
    end
end

% Save the data
save('Data/Param_classified', 'g_KNa_stage', 'sigma_p_stage', 'time_stage');
save('Data/Param_ultradian', 'g_KNa_ultradian', 'sigma_p_ultradian');
end