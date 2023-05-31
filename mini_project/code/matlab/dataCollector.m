clc
clear
close all

addpath udp_functions\

arduino_udp =  UdpClass('udp_functions/UdpSettings.json','udp_functions/SensorIDToNames.json', 'use_twin',false);

data = struct;
data.flag = [];
data.acc.x = [];
data.acc.y = [];
data.acc.z = [];
data.mag = [];
while true
    
    recieved = arduino_udp.receive();
    data.acc.x(end+1) = recieved.acc_x;
    data.acc.y(end+1) = recieved.acc_y;
    data.acc.z(end+1) = recieved.acc_z;
    data.mag(end+1) = recieved.mag_mes;
    
    tic
    %plot(data.acc.x)
    hold on
    %plot(data.acc.y)
    %plot(data.acc.z)
    plot(data.mag/100, 'Color','black')
    hold off
    drawnow
    disp(recieved) 
    toc
end

%%
toprint = jsonencode(data, PrettyPrint = true);

fileID = fopen("..\..\data\run2.json", 'w');
fprintf(fileID, toprint);
fclose(fileID);
%%
data = read_json("..\..\data\run2.json")
%%
figure(3)
cutoff = 740;
plot_mag = data.mag(28:150);
t = 0:1/10:(length(plot_mag)-1)/10
plot(t,plot_mag)
hold on
plot([0, t(end)], [cutoff, cutoff])
hold off


figure(4)
fft_mag = fft(plot_mag);
f = 10*(0:length(fft_mag)/2)/length(fft_mag);
plot(f,abs(fft_mag(1:length(fft_mag)/2+1)))


bool_mag = zeros(size(plot_mag));

for i = 2:length(bool_mag)
    if plot_mag(i-1) > cutoff && plot_mag(i) < cutoff
        bool_mag(i) = 1;
    end
end

figure(5)
plot(t,bool_mag)

fs = 10;
s_elem = 1;
num_elem = fs*s_elem;
a = 0.08*num_elem/(4.1*s_elem)
vel = zeros(size(plot_mag));
vel_out = zeros(size(plot_mag));
mv_avg_elem = zeros(3,1);
for i = 1:length(bool_mag)
    temp = [zeros(round(fs*s_elem),1); bool_mag];
    vel(i) = sum(temp(i:i+fs*s_elem))/(fs*s_elem)*a;
    mv_avg_elem = [mv_avg_elem(2:end); vel(i)];
    vel_out(i) = mean(mv_avg_elem);
end
figure(8)
plot(t,vel_out)


t = 0:1/10:(length(data.acc.x)-1)/10;
figure(6)
plot(t, data.acc.x)

figure(7)
plot(t, data.acc.y)


