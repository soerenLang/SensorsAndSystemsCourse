close all
clear
clc

data = readtable("..\..\data\train_speed.csv");
data.distance = data.distance/100;

plot(data.time, data.distance, 'o')

A = data.time\data.distance

x = 0:.1:max(data.time);

hold on
plot(x,A*x)
hold off
xlabel("Time [s]")
ylabel("Distance [m]")

