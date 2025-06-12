function roots = find_roots(func, df, start, en, step)
    intervals = [];
    x_val = start;
    while x_val < en
        if feval(func, x_val) * feval(func, x_val + step) <= 0
            intervals = [intervals; x_val, x_val + step];
        end
        x_val = x_val + step;
    end

    roots = [];
    for i = 1:size(intervals, 1)
        x0 = (intervals(i, 1) + intervals(i, 2)) / 2;
        root = newton(func, df, x0);
        if ~ismember(root, roots)
            roots = [roots, root];
        end
    end
end
