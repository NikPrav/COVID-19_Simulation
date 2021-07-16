# Accompanying python program to plot the values
# Run the C program, after that, run this program
import matplotlib.pyplot as plt
import numpy as np
# Reads the data from the file
f = open("data.txt","r");

x = f.readline()
day = 0
inf = 0
rec = 0
sus = 0

while x != 'stop': # till the end,
	# print(x)
	no = x.split(' ') # splitting each line at a space,
	day = np.append(day,int(no[0]))
	sus = np.append(sus,int(no[1]))
	inf = np.append(inf,int(no[2]))
	rec = np.append(rec,int(no[3]))
	x = f.readline()

f.close()
# and finally, plots the curves
plt.plot(day,sus,label = "Suspected")
plt.plot(day,inf,label = "Infected")
plt.plot(day,rec,label = "recovered")
plt.legend();
plt.show();
