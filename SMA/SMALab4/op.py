import numpy as np
import matplotlib.pyplot as plt
import random
from multiprocessing import Pool
import time

def Target(args):
    X, Y, dist = args
    n = len(X)
    full_distance = 0

    for i in range(n):
        for j in range(i + 1, n):
            computation_distance = np.exp(-0.3 * ((X[i] - X[j]) ** 2 + (Y[i] - Y[j]) ** 2))
            compuation_price = ((X[i] ** 4 + Y[i] ** 4) / 1000) + ((np.sin(X[i]) + np.cos(X[i])) / 5) + 0.4
            full_distance += computation_distance + compuation_price

    full_distance = full_distance + np.average(X) ** 2 + np.average(Y) ** 2
    return full_distance

def NumericalGradient(args):
    X, Y, dist, h = args
    n = len(X)
    xx = np.array(X)
    yy = np.array(Y)
    Gx = np.zeros(n)
    Gy = np.zeros(n)

    for i in range(n):
        xx[i] = xx[i] + h
        Gx[i] = (Target((xx, Y, dist)) - Target((X, Y, dist))) / h
        xx[i] = X[i]

        yy[i] = yy[i] + h
        Gy[i] = (Target((X, yy, dist)) - Target((X, Y, dist))) / h
        yy[i] = Y[i]

    aa = np.linalg.norm(np.hstack((Gx, Gy)))
    Gx0 = Gx / aa
    Gy0 = Gy / aa

    return Gx0, Gy0

def compute_partial_gradient(i, args):
    X, Y, dist, h = args
    xx = np.array(X)
    yy = np.array(Y)

    xx[i] = xx[i] + h
    Gx_i = (Target((xx, Y, dist)) - Target((X, Y, dist))) / h
    xx[i] = X[i]

    yy[i] = yy[i] + h
    Gy_i = (Target((X, yy, dist)) - Target((X, Y, dist))) / h
    yy[i] = Y[i]

    return Gx_i, Gy_i

def optimize(args, processes=10):
    X, Y, dist, step, h, fff = args
    pool = Pool(processes=processes)

    for iii in range(itmax):
        results = pool.starmap(compute_partial_gradient, [(i, (X, Y, dist, h)) for i in range(n)])
        Gx0, Gy0 = zip(*results)
        Gx0 = np.sum(Gx0, axis=0)
        Gy0 = np.sum(Gy0, axis=0)
        X = X - step * Gx0
        Y = Y - step * Gy0
        fff1 = Target((X, Y, dist))

        if fff1 > fff:
            X = X + step * Gx0
            Y = Y + step * Gy0
            step = step / 3
            #print('step=', step)
        else:
            fff = fff1

        if step < 1e-16:
            print('optimizavimas baigtas fff=', fff, "iteracijų skaičius=", iii)
            break

    pool.close()
    pool.join()
    return X, Y, fff

def experiment(processes):
    start_time = time.time()

    # Call your optimization function with the specified number of processes
    optimized_result = optimize((X, Y, dist, step, h, fff), processes=processes)

    end_time = time.time()
    elapsed_time = end_time - start_time

    return elapsed_time

if __name__ == '__main__':
    start_time = time.time()  # Initialize the start time

    plt.ion()  # Enable interactive mode

    n = 5
    X = np.zeros(n)
    Y = np.zeros(n)

    for i in range(n): X[i] = random.uniform(-10., 10.)
    for i in range(n): Y[i] = random.uniform(-10., 10.)

    plt.subplot(2, 1, 1)  # Create subplot for optimization result
    plt.plot(X, Y, 'rp')
    plt.grid()
    plt.axis('equal')

    m = 5
    X = np.zeros(m)
    Y = np.zeros(m)

    for i in range(m): X[i] = random.uniform(-20., 20.)
    for i in range(m): Y[i] = random.uniform(-20., 20.)

    itmax = 200000
    step = 0.2
    h = 0.00001
    dist = 3
    fff = Target((X, Y, dist))

    # Run the optimization
    optimized_result = optimize((X, Y, dist, step, h, fff), processes=1)

    plt.subplot(2, 1, 2)  # Create subplot for performance vs processes
    # Define the number of processes to experiment with
    process_counts = [8, 10, 12, 14, 18, 24]

    # Store execution times for each process count
    execution_times = []

    for processes in process_counts:
        elapsed_time = experiment(processes)
        execution_times.append(elapsed_time)
        print(elapsed_time)

    # Plot the results
    plt.subplot(2, 1, 2)
    plt.plot(process_counts, execution_times, marker='o')
    plt.xlabel('Number of Processes')
    plt.ylabel('Execution Time (seconds)')
    plt.title('Performance vs Number of Processes, Iterations = 200000')

    plt.tight_layout()  # Adjust layout to prevent overlap
    plt.show()

    plt.ioff()  # Turn off interactive mode

    end_time = time.time()
    total_elapsed_time = end_time - start_time
    print(f"Total execution time: {total_elapsed_time} seconds")