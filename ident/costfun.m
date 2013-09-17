function D=costfun(fun,x,Y,costname)
Y1=fun(x);
D=xdist(Y,Y1(:,1),costname);
end