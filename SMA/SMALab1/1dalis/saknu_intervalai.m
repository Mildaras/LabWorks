function saknu_intervalai
    clc, close all, clear all;
    format long;
    % ------------------------------------
    % Daugianaris f(x)
    f = @(x)(-0.67*x.^4) + 2.51*x.^3+2.27*x.^2-4.02*x-2.48;
    %f = @(x)(0.67*x.^4) - 2.51*x.^3-2.27*x.^2+4.02*x+2.48;
    f_name = '-0.67x^4+2.51x^3+2.27x^2-4.02x-2.48';
    % ------------------------------------
    % Funkcija g(x)
    g = @(x)exp(-1*x.^2).*sin(x.^2).*(x+2);
    g_name = 'e^-^x*sin(x^2)*(x+2)';
    % ------------------------------------
    a = [0.67 -2.51 -2.27 4.02 2.48];
    n = numel(a);
    [R_grub, R_neig, R_teig]=Reziai(n, a);
    colors = ['g', 'r', 'b', 'k', 'y', 'c'];
    % ------------------------------------
    % ðaknø intervalø atskyrimas daugianariui f(x)
    zingsnis = 0.35; % Þingsnio nustatymas
    [SaknuIntervalai_fx]=SkenavimasPastoviu(R_neig, R_teig, zingsnis, f);
    SaknuIntervalai_fx
    % daugianario f(x) ir jo ðaknø intervalø atvaizdavimas
    figure(1); hold on; grid on;
    tikslus_intervalas = R_neig:0.1:R_teig;
    plot([R_neig R_teig], [0 0], 'bp', 'LineWidth', 2);
    plot(tikslus_intervalas, f(tikslus_intervalas), 'k-', 'LineWidth', 2);
    for i = 1:length(SaknuIntervalai_fx)
        plot(SaknuIntervalai_fx(i, 1), 0*SaknuIntervalai_fx(i, 1), 'o', 'MarkerFaceColor', colors(i), 'MarkerSize', 5);
        plot(SaknuIntervalai_fx(i, 2), 0*SaknuIntervalai_fx(i, 2), 'o', 'MarkerFaceColor', colors(i), 'MarkerSize', 5);
    end
    title(['f(x)=', f_name, ' Ðaknø atskyrimo intervalai. Þingsnis: ', num2str(zingsnis)]);
    legend('f(x) ðaknø intervalo rëþiai', 'Daugianaris f(x)');
    axis([R_neig R_teig -25 50]);
    % ------------------------------------
    % ðaknø intervalø atskyrimas funkcijai g(x)
    zingsnis = 0.2; % Þingsnio nustatymas
    g_min = -3;
    g_max = 3;
    g_intervalas = g_min:0.1:g_max;
    [SaknuIntervalai_gx]=SkenavimasPastoviu(g_min, g_max, zingsnis, g);
    SaknuIntervalai_gx
    figure(2); hold on; grid on;
    plot([g_min g_max], [0 0], 'rp', 'LineWidth', 2);
    plot(g_intervalas, g(g_intervalas), 'k-', 'LineWidth', 2);
    for i = 1:length(SaknuIntervalai_gx)
        plot(SaknuIntervalai_gx(i, 1), 0*SaknuIntervalai_gx(i, 1), 'o', 'MarkerFaceColor', colors(i), 'MarkerSize', 5);
        plot(SaknuIntervalai_gx(i, 2), 0*SaknuIntervalai_gx(i, 2), 'o', 'MarkerFaceColor', colors(i), 'MarkerSize', 5);
    end
    title(['g(x)=', g_name, ' Ðaknø atskyrimo intervalai. Þingsnis: ', num2str(zingsnis)]);
    legend('funkcijos g(x) intervalo rëþiai', 'Funkcija g(x)');
    axis([g_min g_max -6 2]);
end
