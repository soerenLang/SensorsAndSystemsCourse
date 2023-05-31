clear
clc
close all

data = readtable('..\..\data\udp_transmission_time.csv');
plot(data.time, 'o');
xlabel("Sample []");
ylabel("Transmission time [ms]");
ylim([0,2]);
title("UDP transmission time")