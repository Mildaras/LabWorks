import numpy as np
import matplotlib.pyplot as plt

def LF(x):
    return np.log(x) / (np.sin(2 * x) + 1.5) + x / 5

def base(x, n):
    return np.power(x, n)


def chebyshevRange(count, start, end):
    xRange = []
    for i in range(1, count + 1):
        temp = (start + end) / 2 + (end - start) / 2 * np.cos((2 * i - 1) * np.pi / (2 * count))
        xRange.append(temp)

    return xRange

def InterpolationEvenlyXY():
    #n = 12
    n = 11 
    rangeStart = 2  
    rangeEnd = 10

    xRange = np.linspace(rangeStart, rangeEnd, n)
    yRange = [LF(x) for x in xRange]

    xP = np.linspace(rangeStart, rangeEnd, 1000)
    yP = LF(xP)

    # Sukuriama Vandermonde matricą
    N = len(xRange)
    A = np.zeros((N, N), dtype=float)
    for i in range(N):
        A[:, i] = base(xRange, i)

    # Gaunami koeficientai
    coeff = np.linalg.solve(A, yRange)
    print("Koeficientai:", coeff)  # Spausdinami koeficientus konsoleje

    # Įvertiname     interpoliuojantį daugianarį
    xxx = np.linspace(xRange[0], xRange[-1], 1000)
    yyy = np.zeros(xxx.size, dtype=float)
    for i in range(N):
        yyy += base(xxx, i) * coeff[i]

    # Skaičiuoja netiktis
    loss = np.abs(yyy - LF(xxx))

    plt.figure(figsize=(10, 6))

    plt.plot(xP, yP, 'g', label='Duota funkcija')
    plt.plot(xRange, yRange, 'bo', label='Interpolacijos taškai')
    plt.plot(xxx, yyy, 'b-', label='Interpoliuota funkcija')
    plt.plot(xxx, loss, 'r--', label='Netiktis')
    plt.legend()
    plt.title('Interpoliacija su taškais, kurie yra tolgiai pasiskirste')
    plt.xlabel('x')
    plt.ylabel('y')
    plt.grid(True)

    plt.show()

def ChebushevRangeInterpolation():
    #pradiniai duomenys
    #15 
    n = 11
    rangeStart = 2  
    rangeEnd = 10

  
    xRange = chebyshevRange(n, rangeStart, rangeEnd)
    yRange = [LF(x) for x in xRange]

    
    xP = np.linspace(rangeStart, rangeEnd, 1000)
    yP = LF(xP)

    # Vandermonde matrix
    N = len(xRange)
    A = np.zeros((N, N), dtype=float)
    for i in range(N):
        A[:, i] = base(xRange, i)

    # koeficientu sprendimas
    coeff = np.linalg.solve(A, yRange)
    print("Koeficientai:", coeff)

    
    xxx = np.linspace(xRange[0], xRange[-1], 1000)
    yyy = np.zeros(xxx.size, dtype=float)
    for i in range(N):
        yyy += base(xxx, i) * coeff[i]

    # netiktis
    loss = np.abs(yyy - LF(xxx))

    plt.figure(figsize=(10, 6))

    plt.plot(xP, yP, 'g', label='Duota funkcija')
    plt.plot(xRange, yRange, 'bo', label='Interpolacijos taškai')
    plt.plot(xxx, yyy, 'b-', label='Interpoliuota funkcija')
    plt.plot(xxx, loss, 'r--', label='Netiktis')
    plt.legend()
    plt.title('Interpoliacija su Čiobyševo mazgais')
    plt.xlabel('x')
    plt.ylabel('y')
    plt.grid(True)

    plt.show()

# Funckijų vykdymas

InterpolationEvenlyXY()
ChebushevRangeInterpolation()