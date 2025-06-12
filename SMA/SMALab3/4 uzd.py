import numpy as np
import matplotlib.pyplot as plt
from matplotlib import gridspec

def Haar_scaling(x, j, k, a, b):
    eps = 1e-9
    xtld = (x - a) / (b - a)
    xx = 2**j * xtld - k
    h = 2**(j/2) * (np.sign(xx + eps) - np.sign(xx - 1 - eps)) / (2 * (b - a))
    return h

def Haar_wavelet(x, j, k, a, b):
    eps = 1e-9
    xtld = (x - a) / (b - a)
    xx = 2**j * xtld - k
    h = 2**(j/2) * (np.sign(xx + eps) - 2 * np.sign(xx - 0.5) + np.sign(xx - 1 - eps)) / (2 * (b - a))
    return h

def Haar_wavelet_approximation(SX, SY, n, m):
    a = min(SX)
    b = max(SX)
    nnn = 2**n
    smooth = (b - a) * SY * 2**(-n/2)

    details = {}
    for i in range(1, m + 1):
        smooth1 = (smooth[::2] + smooth[1::2]) / np.sqrt(2)
        details[i] = (smooth[::2] - smooth[1::2]) / np.sqrt(2)
        print(f'\n details {i} : ', details[i])
        smooth = smooth1

    print(f'\n smooth {i} : ', smooth)
    return smooth, details

def main():
    plt.close('all')

    n = 10
    nnn = 2**n
    fhx = open(r'austriax.txt', 'r')
    fhy = open(r'austriay.txt', 'r')
    plt.figure(1)
    plt.axis('equal')
    plt.grid(True)

    SX = np.array(fhx.read().split(), dtype=float)
    SY = np.array(fhy.read().split(), dtype=float)

    t = np.zeros_like(SX)
    t[1:] = np.cumsum(np.linalg.norm(np.column_stack((SX[1:], SY[1:])) - np.column_stack((SX[:-1], SY[:-1])), axis=1))

    a, b = min(t), max(t)
    t1 = np.linspace(a, b, nnn)
    tsx = np.interp(t1, t, SX)
    tsy = np.interp(t1, t, SY)
    SX, SY, t = tsx, tsy, t1

    plt.plot(SX, SY, 'k.')
    plt.title(f'duota funkcija, tasku skaicius 2^{n}')
    xmin, xmax = min(SX), max(SX)
    ymin, ymax = min(SY), max(SY)

    m = 10
    smoothx, detailsx = Haar_wavelet_approximation(t, SX, n, m)
    smoothy, detailsy = Haar_wavelet_approximation(t, SY, n, m)

    print("smoothx:", smoothx)
    print("smoothy:", smoothy)

    hx = np.zeros(nnn)
    hy = np.zeros(nnn)

    for k in range(2**(n-m)):
        hx += smoothx[k] * Haar_scaling(t, n-m, k, a, b)
        hy += smoothy[k] * Haar_scaling(t, n-m, k, a, b)

    plt.figure(2)
 
    


    plt.figure(2)
    plt.axis('equal')
    plt.axis([xmin, xmax, ymin, ymax])
    plt.grid(True)
    plt.plot(hx, hy, '.', linewidth=2)
    plt.title(f'lygyje {0} suglodinta funkcija')
    leg = [f'suglodinta funkcija, detalumo lygmuo {n-m}']


    for i in range(m):
        h1x = np.zeros(nnn)
        h1y = np.zeros(nnn)

        for k in range(2**(n-m+i)):
            h1x += detailsx[m-i][k] * Haar_wavelet(t, n-m+i, k, a, b)
            h1y += detailsy[m-i][k] * Haar_wavelet(t, n-m+i, k, a, b)


        hx += h1x
        hy += h1y

        plt.figure(i + 3, figsize=(10, 10))

        plt.subplot(2, 1, 1)  # First subplot
        plt.axis('equal')
        plt.axis([xmin, xmax, ymin, ymax])
        plt.grid(True)
        plt.plot(hx, hy, linewidth=2)
        plt.title(f'lygyje {i+1} suglodinta funkcija')
        
        plt.subplot(2, 1, 2)  # Second subplot
        plt.axis('equal')
        plt.axis([xmin, xmax, ymin, ymax])
        plt.grid(True)
        plt.plot(h1x + 14, h1y + 47, 'r-', linewidth=2)
        plt.title(f'{i+1} lygio detales')
        
        leg.append(f'lygmens {n-m+i} detales')




    plt.show()

if __name__ == "__main__":
    main()
