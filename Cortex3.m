function Y=Cortex3(x,I)

T=15e3;

% javaaddpath('d:/Dropbox\Dokumente/Projects/ThaCo.jar')
% javaaddpath('d:/Dropbox\Dokumente/Projects/commons-math3-3.2.jar')

% ****** Full thalamo - cortical model ******
p=thaco.Cortex();
%  ******* initialize ALL model parameters *******
dt=.5; 
% ********* Inputs **********
time=0:(T+2e3);

% I=0e-2*ones(size(time));

p.sigma=2e-3;

if isempty(I)
    I=time*0;
end

% Connectivities 
%--------------------------------------------------------------------------
p.gPYPY=102.8;
p.gINPY=72.5;
p.gPYIN=100.5;
p.gININ=100.5;
p.gPYTC=1;  %da geht auch der externe Input durch
p.gINTC=1;  %da geht auch der externe Input durch

% Time constants for exhibitory and inhibitory neurons in ms
%--------------------------------------------------------------------------
p.py.C=24.4;
p.in.C=29.8;

% Maximum firing rate in ms^-1
%--------------------------------------------------------------------------
p.py.fR=30e-3;
p.in.fR=60e-3;

% Sigmoid threshold values in mV
%--------------------------------------------------------------------------
p.py.VR=-64.6;
p.in.VR=-58.5;

% Standard deviation for threshold in mV
%--------------------------------------------------------------------------
cf=pi/sqrt(3);

p.py.bR=8.3/cf;
p.in.bR=6/cf;

% parameters of the firing adaption
%--------------------------------------------------------------------------
p.py.alphaNa=3.6;
p.py.Rpump=0.09;
p.py.Naeq=9.5;
p.py.tfatigue=2.7;

% synaptic time constants 
%--------------------------------------------------------------------------
p.sIPY.gamma=58e-3; 
p.sEPY.gamma=70e-3; 
p.sIIN.gamma=58e-3; 
p.sEIN.gamma=70e-3; 
p.sDelayTC.gamma=60e-3;


% conductances
%--------------------------------------------------------------------------
% Leak current
p.py.gL=1;
p.in.gL=1;

% KNa current
p.py.gfatigue=0.6;


% reversal potentials
%--------------------------------------------------------------------------
% synaptic inputs in mV
p.py.Eexc=0;
p.in.Eexc=0;
p.py.Einh=-70;
p.in.Einh=-70;

% leak current
p.py.EL=-66.2;
p.in.EL=-64;
p.py.EKL=-95; 

% I_KNa current
p.py.EKNa=-100;

% ******************************
p.T=T; p.dt=dt; p.I=I; p.time=time;
% ****** run it ******
p.run(); 

Y=decimate(p.Y(:,8),20);
trans=2e2;
Y=Y(trans:end);

% Y=zscore(Y);