import numpy as np
import matplotlib.pyplot as plt


def spline(x_array, y_array):
    print("Metai")
    print(x_array)
    print("Ismestos dujos, kt")
    print(y_array)
    dy_array = akima(x_array, y_array)

    # Patikrinimas ar isvestines yra tikslios
    dy = np.gradient(y_array, x_array)
    for i in range(len(x_array)):
        print(f"x = {x_array[i]}: derivative = {dy[i]}, Akima derivative = {dy_array[i]}")

    plt.scatter(x_array, y_array, color="red")
    count = len(x_array)
    print("Mazgu skaicius N")
    print(count)
    for i in range(count - 1):
        nnn = 100
        xxx = np.linspace(x_array[i], x_array[i + 1], nnn)
        fff = 0
        for j in range(2):
            U, V = hermite(np.array([x_array[i], x_array[i + 1]]), j, xxx)
            fff = fff + U * y_array[i + j] + V * dy_array[i + j]
        plt.plot(xxx, fff, color="black")
    plt.title("1998-2018 metu Austrijos siltnamio duju emisija")
    plt.xlabel("Metai")
    plt.ylabel("Emisija, kt")
    plt.grid()
    plt.show()


# skaiciuoja lagranzo daugianario isvestine pagal x
def d_lagrange(x_array, j, x):
    count = len(x_array)
    dl = np.zeros(x.shape, dtype=np.double)  # dl israiskos skaitiklis
    for i in range(0, count):  # ciklas per atmetamus narius
        if i == j:
            continue
        lds = np.ones(x.shape, dtype=np.double)
        for k in range(0, count):
            if k != j and k != i:
                lds = lds * (x - x_array[k])
        dl = dl + lds
    ldv = np.ones(x.shape, dtype=np.double)  # dl israiskos vardiklis
    for k in range(0, count):
        if k != j:
            ldv = ldv * (x_array[j] - x_array[k])
    dl = dl / ldv
    return dl


# sumuoja visas daugianario koeficientu vertes
def lagrange(x_array, j, x):
    n = len(x_array)
    lagrange_val = np.ones(x.shape, dtype=np.double)
    for k in range(0, n):
        if j != k:
            lagrange_val = lagrange_val * ((x - x_array[k]) / (x_array[j] - x_array[k]))
    return lagrange_val


def f_dy(x, xi, x1, x_, _y, y, y_):
    return (2 * x - xi - x_) / ((x1 - xi) * (x1 - x_)) * _y + (2 * x - x1 - x_) / ((xi - x1) * (xi - x_)) * y + (
            2 * x - x1 - xi) / ((x_ - x1) * (x_ - xi)) * y_


def hermite(X, j, x):
    lagr_val = lagrange(X, j, x)
    lagr_deriv = d_lagrange(X, j, X[j])
    U = (1 - 2 * lagr_deriv * (x - X[j])) * np.square(lagr_val)
    V = (x - X[j]) * np.square(lagr_val)
    return U, V


def akima(x, y):
    dy = []
    n = len(x)
    for i in range(n):
        if i == 0:
            x1 = x[0]
            xi = x[1]
            x_ = x[2]
            _y = y[0]
            _y_ = y[1]
            y_ = y[2]
            dy.append(f_dy(x1, xi, x1, x_, _y, _y_, y_))
        elif i == n - 1:
            x1 = x[n - 3]
            xi = x[n - 2]
            x_ = x[n - 1]
            _y = y[n - 3]
            _y_ = y[n - 2]
            y_ = y[n - 1]
            dy.append(f_dy(x_, xi, x1, x_, _y, _y_, y_))
        else:
            x1 = x[i - 1]
            xi = x[i]
            x_ = x[i + 1]
            _y = y[i - 1]
            _y_ = y[i]
            y_ = y[i + 1]
            dy.append(f_dy(xi, xi, x1, x_, _y, _y_, y_))
    return dy


years = np.array(
    [1998, 1999, 2000, 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009, 2010, 2011, 2012, 2013, 2014, 2015, 2016, 2017, 2018])
emission = np.array([80295, 78470, 78694, 83002, 84500, 89432, 90323, 90357, 88153, 85204, 84954, 77767, 83551, 81739, 78293, 78909, 75143, 76430, 76781, 78699, 75582])

spline(years, emission)