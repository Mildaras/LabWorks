function [R_grub, R_neig, R_teig] = Reziai(n, a)
    % R_grub skaiciavimas
    R_grub = 1 + max(abs(a(2:end)))/a(1);

    % R_teig skaiciavimas
    b = a(2:end);
    B = max(abs(b(b<0)));
    k = n - (n - (find(b<0, 1))); % Nustatome k skaičių: n - (n - pirmas skaičius iš b, kuris yra mažesnis už 0)
    R_teig = 1 + (B/a(1))^(1/k);

    % R_neig skaiciavimas f(-x)
    if mod(n, 2) == 0
        a(end:-2:1) = -a(end:-2:1); % Invertuojame lyginius koeficientus
        b = a(2:end);
        B = max(abs(b(b<0)));
        k = n - (n - (find(b<0, 1)));
        R_neig = 1 + (B/a(1))^(1/k);
        R_neig = -R_neig;
    else % -f(-x)
        a(end:-2:1) = -a(end:-2:1); % Invertuojame lyginius koeficientus
        a = a.*-1; % Invertuojame visus koeficientus
        b = a(2:end);
        B = max(abs(b(b<0)));
        k = n - (n - (find(b<0, 1)));
        R_neig = 1 + (B/a(1))^(1/k);
        R_neig = -R_neig;
    end
end
