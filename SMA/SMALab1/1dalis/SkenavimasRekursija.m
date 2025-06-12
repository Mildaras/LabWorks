function [a, b, i, tikslumas] = SkenavimasRekursija(xmin, xmax, zingsnis, tol, f, iteracijos_sk, draw)
    % Inicializuojame pradinę x reikšmę
    x = xmin;
    
    % Didiname iteracijų skaičių kiekį
    iteracijos_sk = iteracijos_sk + 1;
    
    % Einame per intervalą nuo xmin iki xmax su žingsniu zingsnis
    while x < xmax
        % Patikriname, ar žingsnis zingsnis yra mažesnis nei norimas tikslumas (tol)
        if zingsnis < tol
            % Jei taip, tai intervalas yra pakankamai mažas, galime jį naudoti
            a = xmin; 
            b = xmax; 
            i = iteracijos_sk;
            tikslumas = abs(f(xmax));
            return;
        end
        
        % Patikriname, ar funkcijos ženklai x ir x+zingsnis yra skirtingi
        if (sign(f(x)) ~= sign(f(x + zingsnis)))
            % Jei taip, tai rastas intervalas, kuriame yra šaknis
            % Taip pat, galime nubrežti intervalo galus, jei reikia ir tai pirmoji iteracija
            if (draw == 1 && iteracijos_sk < 7)
                plot(xmin, 0, 'go', 'LineWidth', 2);
                h = findobj(gca, 'Type', 'line');
                h1 = h(1);
                plot(xmax, 0, 'go', 'LineWidth', 2);
                h = findobj(gca, 'Type', 'line');
                h2 = h(1);
                input('Spauskite Enter'), figure(1);
                delete(h1);
                delete(h2);
            end
            
            % Rekursyviai kviečiame funkciją SkenavimasRekursija su mažesniu žingsniu
            [a, b, i, tikslumas] = SkenavimasRekursija(x, x + zingsnis, zingsnis / 10, tol, f, iteracijos_sk, draw);
        end
        
        % Perkeliamas x į kitą žingsnio tašką
        x = x + zingsnis;
    end
end
