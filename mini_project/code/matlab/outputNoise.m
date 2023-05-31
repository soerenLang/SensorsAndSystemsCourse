close all
clc
clear
addpath("udp_functions\")

data = read_json("..\..\data\run2.json");
figure(3)
cutoff = 740;
plot_mag = data.mag(28:150);
t = 0:1/10:(length(plot_mag)-1)/10;
plot(t,plot_mag)
hold on
plot([0, t(end)], [cutoff, cutoff])
hold off

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
mv_avg_elem = zeros(1,1);
for i = 1:length(bool_mag)
    temp = [zeros(round(fs*s_elem),1); bool_mag];
    vel(i) = sum(temp(i:i+fs*s_elem))/(fs*s_elem)*a;
    mv_avg_elem = [mv_avg_elem(2:end); vel(i)];
    vel_out(i) = mean(mv_avg_elem);
end
figure(8)
plot(t,vel_out)
vel_cov = cov(vel_out);
xlabel("Time [s]")
ylabel("Velocity [m/s]")
exportgraphics(gca, "velocitytest.pdf")

t = 0:1/10:(length(data.acc.x)-1)/10;
figure(6)
plot(t, data.acc.x)
acc_x_cov = cov(data.acc.x)

figure(7)
plot(t, data.acc.y)
acc_y_cov = cov(data.acc.y)

