
import sys
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker
import math
from numpy import *
file = sys.argv[1]


fs = file + ".txt"

f = open(fs, 'r')

x, y = [0], [0]
i = 0

for l in f:
    row = l.split()
    tempx = float(row[0])
    tempy = float(row[1])
    x.append(tempx)
    y.append(tempy)



f.close()

fig, ax1 = plt.subplots(
    nrows=1, ncols=1,
    figsize=(12, 12)
)

t = linspace(0, max(x), max(x))
a = log(t)/log(2)

x.pop(0)
y.pop(0)
ax1.plot(x, y, label = 'Количество вызовов операции')
ax1.plot(t, a, label  = 'log2 N')

ax1.grid(which='major',
         color = 'k')

ax1.minorticks_on()

ax1.grid(which='minor',
         color = 'gray',
         linestyle = ':')

ax1.legend()

ax1.set_xlabel('Количество элементов в дереве')

if(file == "resAdd"):
    ax1.set_ylabel('Количество операций для вставки')
else:
    ax1.set_ylabel('Количество операций для удаления')
fig.set_figwidth(15)
fig.set_figheight(10)

plt.title("Средний случай")
plt.show()