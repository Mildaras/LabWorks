function taylorSeries = Taylor(f, x, x0, N)
    f_syms = f(x);
    fp = subs(f_syms, x, x0);
    df = f_syms;
    
    for i = 1:N
        df = diff(df, x);  % Differentiating
        fp = fp + subs(df, x, x0) * (x - x0)^i / factorial(i);  % Computes the Taylor series
    end
    
    taylorSeries = fp;
end