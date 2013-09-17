function D=Wdist(Y,Y1)
% handle diverged ODE solutions
%--------------------------------------------------------------------------
Y1(isnan(Y1))=inf;

% normalized data
%--------------------------------------------------------------------------
Z=zscore([Y(:),Y1(:)]);

% create phase space representation
% % --------------------------------------------------------------------------
temp=diff(Z(:,1));
Y=[Z(2:end,1),temp];
temp=diff(Z(:,2));
Y1=[Z(2:end,2),temp];
 
% Y=embed(Z(:,1),2,200);
% Y1=embed(Z(:,2),2,200);


% calculate distances (separately)
%--------------------------------------------------------------------------
D = [];
D = [D,divergence_wkv(Y',Y1')];
% D = [D,emdist(Y,Y1,10)];
% D = [D,ccdist(Z)];

% combine distances
%--------------------------------------------------------------------------
% D=geomean(D);
end

function D=h2dist(Y,Y1)
Y=hist2(Y(:,1),Y(:,2),100,0);
Y1=hist2(Y1(:,1),Y1(:,2),100,0);
D=(sum(sqrt(abs(Y(:)-Y1(:)))))^2;
end

function D=ccdist(Y)
c=lpc2cc(Y);
D=sqrt(sum(diff(c,1,2).^2));
D=abs(D);
end

function c=lpc2cc(x)
p       = 20;
a       = lpc(x,p)';

c(p,size(a,2)) = 0;
c(2,:)  = - a(2,:);
for m = 2:p
    k=1:(m-1);
    s=bsxfun(@times, c(m-k+1,:).*a(k+1,:), -(m-k)');
    c(m+1,:) = - a(m+1,:) + sum(s,1)/m;    
end
end