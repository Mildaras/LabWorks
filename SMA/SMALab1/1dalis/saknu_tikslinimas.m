function saknu_tikslinimas
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
    % ------------------------------------
    % �akn� interval� atskyrimas daugianariui f(x)
    % ------------------------------------
    zingsnis = 0.35; % zingsnio nustatymas
    [SaknuIntervalai_fx]=SkenavimasPastoviu(R_neig, R_teig, zingsnis, f);
    % ------------------------------------
    % REKURSINIS SKENAVIMAS (MA�INANT �INGSN�)
    % ------------------------------------
    % �akn� tikslinimas daugianariui f(x)
    % ------------------------------------
     fprintf( '----------------------------------------------------\n');
     fprintf( '�akn� tikslinimas skenavimo metodu, ma�inant �ingsn�\n');
     fprintf( 'Daugianaris f(x)=-0.67x^4+2.51x^3+2.27x^2-4.02x-2.48\n');
     fprintf( '----------------------------------------------------\n');
     fprintf( 'Stulpeli� reik�m�s:\n');
     fprintf( '1:2 - pradiniai �akn� tikslinimo intervalai\n');
     fprintf( '3 - �aknis\n');
     fprintf( '4 - tikslumas\n');
     fprintf( '5 - atlikt� iteracij� kiekis\n');
     fprintf( '----------------------------------------------------\n');
    Saknys_intervalai_fx = [];
    Tikslumai = [];
    Iteracijos = [];
    tikslumas = 1e-9;
    for i=1:length(SaknuIntervalai_fx)
        x_min = SaknuIntervalai_fx(i,1);
        x_max = SaknuIntervalai_fx(i, 2);
        if i == 1
            draw = 1;
            figure(1); grid on; hold on;
            npoints= 1000; 
            x = x_min:(x_max-x_min)/(npoints - 1):x_max;
            plot(x, f(x), 'r-', 'LineWidth', 2);
        else
            draw = 0;
        end
        if (sign(f(x_min)) ~= sign(f(x_max)))
            iteracijos_sk = 0;
            [a, b, it, t]=SkenavimasRekursija(x_min, x_max, zingsnis, tikslumas, f, iteracijos_sk, draw);
            Saknys_intervalai_fx = [Saknys_intervalai_fx; a b];
            Iteracijos = [Iteracijos; it];
            Tikslumai = [Tikslumai; t];
        end
    end
    close all;
    Saknys_fx = (Saknys_intervalai_fx(:,1) + Saknys_intervalai_fx(:,2))/2;
    Rez_fx = [];
    for i=1:length(Saknys_fx)
        Rez_fx = [Rez_fx; SaknuIntervalai_fx(i,:) Saknys_fx(i) Tikslumai(i) Iteracijos(i)];
    end
     Rez_fx
    % ------------------------------------
    % �akn� tikslinimas funkcijai g(x)
    % ------------------------------------
    zingsnis = 0.2; % zingsnio nustatymas
    g_min = -3;
    g_max = 3;
    [SaknuIntervalai_gx]=SkenavimasPastoviu(g_min, g_max, zingsnis, g);
     fprintf( '----------------------------------------------------\n');
     fprintf( '�akn� tikslinimas skenavimo metodu, ma�inant �ingsn�\n');
     fprintf( 'Funkcija g(x)=e^-^x*sin(x^2)*(x+2)\n');
     fprintf( '----------------------------------------------------\n');
     fprintf( 'Stulpeli� reik�m�s:\n');
     fprintf( '1:2 - pradiniai �akn� tikslinimo intervalai\n');
     fprintf( '3 - �aknis\n');
     fprintf( '4 - tikslumas\n');
     fprintf( '5 - atlikt� iteracij� kiekis\n');
     fprintf( '----------------------------------------------------\n');
    Saknys_intervalai_gx = [];
    Tikslumai = [];
    Iteracijos = [];
    tikslumas = 1e-9;
    for i=1:length(SaknuIntervalai_gx)
        x_min = SaknuIntervalai_gx(i, 1);
        x_max = SaknuIntervalai_gx(i, 2);
        draw = 0;
        if (sign(g(x_min)) ~= sign(g(x_max)))
            iteracijos_sk = 0;
            [a, b, it, t]=SkenavimasRekursija(x_min, x_max, zingsnis, tikslumas, g, iteracijos_sk, draw);
            Saknys_intervalai_gx = [Saknys_intervalai_gx; a b];
            Iteracijos = [Iteracijos; it];
            Tikslumai = [Tikslumai; t];
        end
    end
    Saknys_gx = (Saknys_intervalai_gx(:,1) + Saknys_intervalai_gx(:,2))/2;
    Rez_gx = [];
    for i=1:length(Saknys_gx)
        Rez_gx = [Rez_gx; SaknuIntervalai_gx(i,:) Saknys_gx(i) Tikslumai(i) Iteracijos(i)];
    end
    Rez_gx
    % ------------------------------------
    % Kvazi-Niutono (kirstini�) metodas
    eps = 1e-9;
    % ------------------------------------
    % �akn� tikslinimas daugianariui f(x)
    % ------------------------------------
     fprintf( '----------------------------------------------------\n');
     fprintf( '�akn� tikslinimas Kvazi-Niutono (kirstini�) metodu\n');
     fprintf( 'Daugianaris f(x)=-0.67x^4+2.51x^3+2.27x^2-4.02x-2.48\n');
     fprintf( '----------------------------------------------------\n');
     fprintf( 'Stulpeli� reik�m�s:\n');
     fprintf( '1 - pirmasis pradinis artinys\n');
     fprintf( '2 - antrasis pradinis artinys\n');
     fprintf( '3 - �aknis\n');
     fprintf( '4 - tikslumas\n');
     fprintf( '5 - atlikt� iteracij� kiekis\n');
     fprintf( '----------------------------------------------------\n');
    Tikslumai = [];
    Iteracijos = [];
    Saknys_fx = [];
    Artiniai = []; %pradiniai intervalai
    iteracijos_sk_max = 200;
    figure(1); grid on; hold on;
    % Inicializuojame cikl� per visus sakn� intervalus
for i = 1:length(SaknuIntervalai_fx)
    % I�traukiame pradin� ir galutin� intervalo rib�
    x0 = SaknuIntervalai_fx(i, 1);
    x01 = SaknuIntervalai_fx(i, 2);
    
    % Nustatome ta�k� skai�i� npoints intervalo viduje
    npoints = 1000;
    
    % Sugeneruojame masyv� x, kuriame saugosime ta�kus nuo x0 iki x01
    x = x0:(x01 - x0) / (npoints - 1):x01;
    
    % Nustatome grafiko ribas
    axis([(x0 - 0.01) (x01 + 0.01) -2.5 8.5]);
    
    % Pridedame intervalo ribas prie Artiniai masyvo
    Artiniai = [Artiniai; x0 x01];
    
    % Apskai�iuojame funkcijos reik�mes prad�ioje ir pabaigoje intervalo
    fxn = f(x0);
    fxn1 = f(x01);
    
    % Inicializuojame kintamuosius, kurie saugos iteracijos metu kei�ian�ias reik�mes
    xn = x0;
    xn_plot = x0;
    xn1_plot = x01;
    fxn_plot = f(x0);
    fxn1_plot = f(x01);
    
    % Apskai�iuojame pirm�j� i�vestin� dfxn
    dfxn = (fxn1 - fxn) / (x01 - x0);
    
    % Nustatome pradin� tikslum�
    tikslumas = 1;
    
    % Inicializuojame iteracij� skai�iavimui naudojam� kintam�j�
    iteracijos_sk = 0;
    
    % Pradedame iteracij� proces�
    while tikslumas > eps
        iteracijos_sk = iteracijos_sk + 1;
        
        % Patikriname, ar nevir�ytas maksimalus leistinas iteracij� skai�ius
        if (iteracijos_sk > iteracijos_sk_max)
            fprintf('Virsytas leistinas iteraciju skaicius');
            break;
        end
        
        % Apskai�iuojame nauj� x reik�m�
        xn1 = xn - fxn / dfxn;
        
        % Brai�ome grafik�, jei tai pirmoji iteracija ir iteracij� skai�ius ma�esnis nei 7
        if (i == 1 && iteracijos_sk < 7)
            plot(x, f(x), 'r-');
            plot([x0 x01], [0 0], 'b-');
            plot(x0, 0, 'mp');
            h = findobj(gca, 'Type', 'line');
            h1 = h(1);
            plot([xn_plot, xn_plot, xn1_plot, xn1_plot], [0, fxn_plot, fxn1_plot, 0], 'k-');
            plot([xn, xn, xn1], [0, fxn, 0], 'k-');
            delete(h1);
            plot(xn1, 0, 'mp');
            h = findobj(gca, 'Type', 'line');
            h1 = h(1);
            input('Paspauskite Enter'), figure(1);
        end
        
        % Apskai�iuojame nauj� funkcijos reik�m� ir i�vestin�
        fxn1 = f(xn1);
        dfxn = (fxn1 - fxn) / (xn1 - xn);
        
        % Atnaujiname x reik�m� ir funkcijos reik�m�
        xn = xn1;
        fxn = f(xn);
        
        % Skai�iuojame tikslum�
        tikslumas = abs(fxn);
    end
    
    % Pridedame iteracij� skai�i�, tikslum� ir gaut� �akn� � atitinkamus masyvus
    Iteracijos = [Iteracijos; iteracijos_sk];
    Tikslumai = [Tikslumai; tikslumas];
    Saknys_fx = [Saknys_fx; xn];
end

    % U�darome visus atidarytus grafikus
close all;

% Sukuriame tu��i� Rez_fx masyv�
Rez_fx = [];

% Einame per visus rastus �akn� artinius
for i = 1:length(Saknys_fx)
    % Pridedame artini�, �aknies, tikslumo ir iteracij� skai�iaus informacij� � Rez_fx masyv�
    Rez_fx = [Rez_fx; Artiniai(i, :) Saknys_fx(i) Tikslumai(i) Iteracijos(i)];
end

% I�spausdiname Rez_fx masyv�
Rez_fx

% ------------------------------------
% �akn� tikslinimas funkcijai g(x)
% ------------------------------------
fprintf('----------------------------------------------------\n');
fprintf('�akn� tikslinimas Kvazi-Niutono (kirstini�) metodu\n');
fprintf('Funkcija g(x)=sin(x)ln(x)-(x/6)\n');
fprintf('----------------------------------------------------\n');
fprintf('Stulpeli� reik�m�s:\n');
fprintf('1 - pirmasis pradinis artinys\n');
fprintf('2 - antrasis pradinis artinys\n');
fprintf('3 - �aknis\n');
fprintf('4 - tikslumas\n');
fprintf('5 - atlikt� iteracij� kiekis\n');
fprintf('----------------------------------------------------\n');

% I�valome kintamuosius, kurie bus naudojami funkcijai g(x)
Tikslumai = [];
Iteracijos = [];
Saknys_gx = [];
Artiniai = [];

% Nustatome maksimal� leistin� iteracij� skai�i�
iteracijos_sk_max = 200;

% Einame per visus intervalus funkcijai g(x)
for i = 1:length(SaknuIntervalai_gx)
    % Nustatome pradin� artin� x0 ir x01
    x0 = SaknuIntervalai_gx(i, 1) - 0.2;
    x01 = SaknuIntervalai_gx(i, 1) - 0.1;
    
    % Pridedame artini� ribas � Artiniai masyv�
    Artiniai = [Artiniai; x0 x01];
    
    % Apskai�iuojame funkcijos reik�mes prad�ioje ir pabaigoje intervalo
    fxn = g(x0);
    fxn1 = g(x01);
    
    % Apskai�iuojame pirm�j� i�vestin� dfxn
    dfxn = (fxn1 - fxn) / (x01 - x0);
    
    % Inicializuojame kintamuosius funkcijos g(x) iteracijoms
    xn = x0;
    tikslumas = 1;
    iteracijos_sk = 0;
    
    % Pradedame iteracij� proces�
    while tikslumas > eps
        iteracijos_sk = iteracijos_sk + 1;
        
        % Patikriname, ar nevir�ytas maksimalus leistinas iteracij� skai�ius
        if (iteracijos_sk > iteracijos_sk_max)
            fprintf('Virsytas leistinas iteraciju skaicius');
            break;
        end
        
        % Apskai�iuojame nauj� artin� xn1
        xn1 = xn - fxn / dfxn;
        
        % Apskai�iuojame funkcijos reik�m� naujame ta�ke
        fxn1 = g(xn1);
        
        % Apskai�iuojame nauj� i�vestin� dfxn
        dfxn = (fxn1 - fxn) / (xn1 - xn);
        
        % Atnaujiname artin� xn
        xn = xn1;
        
        % Atnaujiname funkcijos reik�m� fxn
        fxn = g(xn);
        
        % Apskai�iuojame tikslum�
        tikslumas = abs(fxn);
    end
    
    % Pridedame iteracij� skai�i�, tikslum� ir gaut� �akn� � atitinkamus masyvus
    Iteracijos = [Iteracijos; iteracijos_sk];
    Tikslumai = [Tikslumai; tikslumas];
    Saknys_gx = [Saknys_gx; xn];
end

% Sukuriame tu��i� Rez_gx masyv�
Rez_gx = [];

% Einame per visus rastus �akn� artinius funkcijai g(x)
for i = 1:length(Saknys_gx)
    % Pridedame artini�, �aknies, tikslumo ir iteracij� skai�iaus informacij� � Rez_gx masyv�
    Rez_gx = [Rez_gx; Artiniai(i, :) Saknys_gx(i) Tikslumai(i) Iteracijos(i)];
end

% I�spausdiname Rez_gx masyv�
Rez_gx

    % Matlab funkcijos
    % Daugianaris f(x)
     fprintf( '----------------------------------------------------\n');
     fprintf( 'MATLAB funkcijos\n');
     fprintf( '----------------------------------------------------\n');
     fprintf( 'Daugianaris f(x)\n');
     fprintf( '----------------------------------------------------\n');
    a = [0.67 -2.51 -2.27 4.02 2.48];
    saknys_roots = roots(a)
    for i=1:length(SaknuIntervalai_fx)
        fzero(f, SaknuIntervalai_fx(i, 1))
    end
    % Matlab funkcijos
    % Funkcija g(x)
     fprintf( '----------------------------------------------------\n');
     fprintf( 'Funkcija g(x)\n');
     fprintf( '----------------------------------------------------\n');
    for i=1:length(SaknuIntervalai_gx)
        fzero(g, SaknuIntervalai_gx(i, 1))
    end
end