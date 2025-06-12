import numpy as np
import matplotlib.pyplot as plt

# suranda daugianario reikšmes mažiausių kvadratų metodu
def base(degree, x_array):
    count = len(x_array)
    g_array = np.zeros((count, degree + 1))
    for index in range(0, count):
        for j in range(0, degree + 1):
            g_array[index, j] = x_array[index] ** j
    return g_array

# suranda daugianares funkcijos koeficientus
def coefficients(g_array, y_array):
    tmp1 = (g_array.transpose()).dot(g_array)
    tmp2 = (g_array.transpose()).dot((np.matrix(y_array)).transpose())
    coefficient_array = np.linalg.solve(tmp1, tmp2)
    return coefficient_array

# funkcijos Y atsakymo reikšmės
def answers(c_arr, x):
    y = 0
    for index in range(0, len(c_arr)):
        y = y + c_arr[index] * (x ** index)
    return y

Y = np.array([80295, 78470, 78694, 83002, 84500, 89432, 90323, 90357, 88153, 85204, 84954, 77767, 83551, 81739, 78293, 78909, 75143, 76430, 76781, 78699, 75582])
n = len(Y)

X = np.linspace(3, n, n)
# aproksimuojancios kreivės eilė
deg = 7
draw_points = 100

G = base(deg, X)
c = coefficients(G, Y)

print("Aproksimacijos funkcijos koeficientai:")
print(c.transpose())

draw_x = np.linspace(1, n, draw_points)
draw_y = np.zeros(draw_points)
for i in range(0, draw_points):
    draw_y[i] = answers(c, draw_x[i])


fig = plt.figure()
ax = fig.add_subplot()
ax.plot(X, Y, 'go')
plt.title("1998-2018 met\u0173 Austrijos \u0161iltnamio duj\u0173 emisija")
plt.ylabel("Emisija, kt")
ax.plot(draw_x, draw_y, 'b-', label='Šiltnamio dujų emisijos aproksimacijos kreivė')
plt.legend()
plt.draw()
plt.show()
