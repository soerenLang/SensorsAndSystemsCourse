clear
close all
clc

arduinoObj = serialport("COM4",115200);

configureTerminator(arduinoObj,"CR/LF");
flush(arduinoObj);

TestTime = 30;
pause(TestTime);
data = read(arduinoObj, arduinoObj.NumBytesAvailable,"string");
arduinoObj.UserData = struct("Data",[],"Count",1)

%%
data = strsplit(data, "C\r\n");
data = data(1:end-1);
data = str2double(data);

writematrix(data, "rawData.csv");

%%
%close Figure
figure(1)
plot(data)
title("Temperature at water kettle")
xlabel("Sample []")
ylabel("Temperature [C]")
grid on