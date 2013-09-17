function D=emdist(Y,Y1,n)
Y=num2cell(Y,1);
Y1=num2cell(Y1,1);

[P,J]   = histn(Y{:},n,0);
[Q,J1]  = histn(Y1{:},n,0);

if any(isnan(J1))
    J1=J;
end

J=combs(num2cell(J,1));
J1=combs(num2cell(J1,1));
 

P=P(:);
Q=Q(:);
Z=any([P,Q],2);
P=P(Z,:);
Q=Q(Z,:);
J=J(Z,:);
J1=J1(Z,:);

D       = pdist2(J,J1,'cityblock');

thresh  = max(D(:))/2;
D       = min(D,repmat(thresh,size(D)));

D       = emd_hat_gd_metric_mex(P(:),Q(:),D,-1);

D       = abs(D);