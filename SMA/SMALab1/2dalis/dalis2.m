function dalis2
clc;
close all;
clear all;
format long;

syms x;
fh = 5*cos(x)-sin(2*x)+2;
% Find the derivative of fh(x)
fh_der = diff(fh, x);

% Find all roots for fh(x)
a = -6;
b = 3;
x0_val = (a + b) / 2;
%roots_hx = find_roots(fh, fh_der, a, b);
roots_hx = find_roots(@(x_val) subs(fh, x, x_val), @(x_val) subs(fh_der, x, x_val), a, b);

disp(['h(x) roots: ' num2str(roots_hx)]);

% Find all roots for the Taylor expansion
N = 1;
while true
    f_N = Taylor(fh, x, x0_val, N);
    f_N_der = diff(f_N, x);
    roots_f_N = find_roots(f_N, f_N_der, a, b);

    % Compare roots of f_N with roots of h(x) with a given accuracy
    roots_match = true;
    for root_f_N = roots_f_N
        is_match_for_this_root = false;
        for root_hx = roots_hx
            if abs(root_f_N - root_hx) < 1e-4
                is_match_for_this_root = true;
                break;
            end
        end
        if ~is_match_for_this_root
            roots_match = false;
            break;
        end
    end
    if roots_match
        break;
    end
    N = N + 1;
end
disp(['To reach all roots with the Taylor series, ' num2str(N) ' terms are needed']);
disp(['Taylor series roots with N=' num2str(N) ': ' num2str(roots_f_N)]);

% First task
f_3 = Taylor(fh, x, x0_val, 3);
f_4 = Taylor(fh, x, x0_val, 4);
f_5 = Taylor(fh, x, x0_val, 5);

xxx = linspace(a, b, 200);
hx_values = subs(fh, x, xxx);
f3_values = subs(f_3, x, xxx);
f4_values = subs(f_4, x, xxx);
f5_values = subs(f_5, x, xxx);

figure;
ylim([-500, 500]);
plot([a, b], [0, 0], 'k--');
hold on;
plot(xxx, hx_values, 'Color', [1, 0.5, 0]);
plot(xxx, f3_values, 'b--');
plot(xxx, f4_values, 'g--');
plot(xxx, f5_values, 'r--');
xlabel('x');
ylabel('y');
plot(roots_hx, zeros(size(roots_hx)), 'mp');
legend('h(x)', 'TE, N=3', 'TE, N=4', 'TE, N=5');
grid on;
title('g(x) and TE Intermediate Graphs');
hold off;
end
