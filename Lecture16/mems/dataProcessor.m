clear
clc

arduinoObj = serialport("COM4",460800);

configureTerminator(arduinoObj,"CR/LF");
flush(arduinoObj);

TestTime = 30;
pause(TestTime);
data = read(arduinoObj, arduinoObj.NumBytesAvailable,"string");
arduinoObj.UserData = struct("Data",[],"Count",1)
%%
data = strsplit(data, "\r\n");
data = data(1:end-1);
data = str2double(data);

writematrix(data, "rawData.csv");
%%
dcOffset = mean(data)
data = data - dcOffset;
data = data/max(abs(data));
plot(data)

F_s = length(data)/TestTime;

sound(data,F_s)