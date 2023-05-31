close all
clear
%%
angle = 0:.01:2*3/4*pi;
straigth = 0:.01:.29;
track = [straigth, cos(angle - pi/2)*.2 + .29; zeros(size(straigth)), sin(angle - pi/2)*.2 + .2];
distance = [straigth, .29 + .01  + linspace(0,3/4*.4*pi, length(angle))];
plot(track(1,:), track(2,:))
axis equal



%%
A = [0 0 0; 1 0 0; 0 1 0];
B = [1;0;0];
C = [1 0 0; 0 1 0];
ts = .1;
sys = ss(A,B,C,0);
sys = c2d(sys,ts);

Q = diag([1,0,0]);
R = diag([0.0011, 6.5941e-04]);

P_pred = eye(3,3);
P_est = eye(3,3);

x_est = zeros(3,1); x_est(3) = .18;
x_pred = x_est;

addpath udp_functions\

arduino_udp =  UdpClass('udp_functions/UdpSettings.json','udp_functions/SensorIDToNames.json', 'use_twin',false);

data = struct;
data.flag = [];
data.acc.x = [];
data.acc.y = [];
data.acc.z = [];
data.mag = [];
data.vel.y = [];
data.kalman.x = [];
while true
    
    %Recieve udp-stream and format
    recieved = arduino_udp.receive();
    data.acc.x(end+1) = recieved.acc_x;
    data.acc.y(end+1) = recieved.acc_y;
    data.acc.z(end+1) = recieved.acc_z;
    data.mag(end+1) = recieved.mag_mes;
    data.vel.y(end+1) = recieved.vel_x;
    
    %Kalman filter
    %Measurement update
    y_pred = sys.C*x_pred;
    y_error = [data.acc.y(end); data.vel.y(end)] - y_pred;
    u = 0;

    Kalman_gain = P_pred*sys.C'*inv(sys.C*P_pred*sys.C' + R);
    x_est = x_pred + Kalman_gain*y_error;
    
    P_est = (eye(3,3)-Kalman_gain*sys.C)*P_pred*(eye(3,3)-Kalman_gain*sys.C)' + Kalman_gain*R*Kalman_gain';

    %Time update
    x_pred = sys.A*x_est + sys.B*u;
    data.kalman.x(:,end+1) = x_est;
    P_pred = sys.A*P_est*sys.A' + Q;

    %Plot 
    figure(2)
    plot(track(1,:), track(2,:), 'Color','black')
    %Find point in plot closest to current position
    [d, ix] = min (abs(distance -x_est(3)));
    
    hold on
    plot(track(1,ix), track(2,ix), 'o', 'Color','red')
    hold off
end