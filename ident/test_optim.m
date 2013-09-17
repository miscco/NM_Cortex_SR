% *** reference ***
addpath('~/workspace/C_model')

    Con                     = [  100;		% N_ee
                                      60;			% N_ei
                                      90;			% N_ie
                                      90]; 			% N_ii
    Adaption             = [ 2;              % alpha_Na
                                     0.09];        % R_pump
                                 
   Noise_inp             = [ 20E-3;     % mean
                                      20E-3];   % sd
                                  
    % Full input vector                              
	Input                   = [ Con;
                                     Adaption;
                                     Noise_inp]';

Y=Cortex(Input);
plot(Y(:,1)),shg

costname='W';
fun=@(x)costfun(@Cortex,x,Y(:,1),costname);

lb=[0;
       0;
       0;
       0;
       0;
       0];
ub=[10;
        10;
        10;
        10;
        10;
        10];


options = gaoptimset('UseParallel','always',...
    'Display','iter',...
    'PlotFcns',{@gaplotbestf},...
    'CrossoverFcn',@crossoverscattered,...
    'SelectionFcn',@selectionstochunif,...
    'MutationFcn',@mutationadaptfeasible,...
    'PopulationSize',40,...
    'Generations',100,...
    'InitialPopulation',[],...
    'TolFun',0,...
    'FitnessLimit',0);

[x,fval,exitflag,output,population] = ga(fun,...
    numel(ub),[],[],[],[],lb,ub,[],options);

%%
psopt = psoptimset('Display','iter',...
    'UseParallel','always',...
    'Cache','on',...
    'CacheTol',0.1,...
    'PollingOrder','Random',...
    'MeshContraction',0.5,...
    'MeshExpansion',2,...    
    'MaxFunEvals',500);

y = patternsearch(fun,x,[],[],[],[],lb,ub,[],psopt);