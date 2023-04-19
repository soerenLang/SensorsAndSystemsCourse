clear
close all
clc

arduinoObj = serialport("COM4",115200);

configureTerminator(arduinoObj,"CR/LF");
flush(arduinoObj);

TestTime = 180;
pause(TestTime);
data = read(arduinoObj, arduinoObj.NumBytesAvailable,"string");
arduinoObj.UserData = struct("Data",[],"Count",1)

%%
data = strsplit(data, "C\r\n");
data = data(1:end-1);
data = str2double(data);

writematrix(data, "rawData_part5.csv");

%%
%close Figure
figure(1)
t = linspace(0, TestTime, length(data));
plot(t,data)
hold on
plot(t,max(data)-ones(1,length(data))*(max(data)-min(data))*.66, 'Color','black', 'LineStyle','--')
hold off
title("Temperature change from boiling to cold")
xlabel("Time [s]")
ylabel("Temperature [C]")
grid on

%%
figure(2)
t = linspace(0, TestTime, length(data));
switchPoint = 146;
plot(t(switchPoint-10:switchPoint +10),data(switchPoint-10:switchPoint+10))

title("Temperature change from boiling to cold")
xlabel("Time [s]")
ylabel("Temperature [C]")
grid on