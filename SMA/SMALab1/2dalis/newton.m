function x_root = newton(f, df, x0, max_iter)
    x_current = x0;
    for iter = 1:max_iter
        % Calculate functional values for the function and its derivative with the current x value
        f_val = feval(f, x_current);
        df_val = feval(df, x_current);

        if df_val == 0
            error("Derivative is zero!");
        end

        dx = -f_val / df_val; % Compute change Δx
        if abs(dx) < 1e-4 % Check if change is small enough
            x_root = x_current;
            return;
        end
        x_current = x_current + dx;
    end

    error(['Newton''s method did not converge after ' num2str(max_iter) ' iterations']);
end