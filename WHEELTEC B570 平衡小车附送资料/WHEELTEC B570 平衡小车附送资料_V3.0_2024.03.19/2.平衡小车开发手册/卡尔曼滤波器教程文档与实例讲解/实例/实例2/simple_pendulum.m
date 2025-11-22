clc
clear
close all
g = 9.8; % 重力加速度(m·s^-2)
l = 0.2; % 轻杆的长度(m)
A = [0 1; -g/l 0];
B = [0; 0];
C = [1 0];
D = 0;
Q = diag([1e-4 1e-4]); % 过程噪声
R = 1e-2; % 测量噪声
Ts = 0.02; % 采样间隔
t_min = 0;
t_max = 4.26;
t = t_min:Ts:t_max;
sys = ss(A,B,C,D); % 状态空间表达式
sysd = c2d(sys,Ts); % 离散化
theta = zeros(2,length(t));
theta(1,:) = pi*cos(7*t)/18; % 角度真实值
theta(2,:) = -(7*pi*sin(7*t))/18; % 角速度真实值
theta_measure = C*theta + normrnd(0,sqrt(R),1,size(theta,2)); % 角度测量值
x0 = [0; 0];
p0 = diag([1 1]);
theta_estimate = KF(sysd.A,sysd.C,theta_measure,Q,R,t,x0,p0); % 卡尔曼滤波
for i = 1:length(t)
    subplot(1,2,1)
    x = l*cos(theta(1,i) - pi/2); % 摆球的横坐标（真实值）
    y = l*sin(theta(1,i) - pi/2); % 摆球的纵坐标（真实值）
    x_measure = l*cos(theta_measure(i) - pi/2); % 摆球的横坐标（测量值）
    y_measure = l*sin(theta_measure(i) - pi/2); % 摆球的纵坐标（测量值）
    x_estimate = l*cos(theta_estimate(1,i) - pi/2); % 摆球的横坐标（估计值）
    y_estimate = l*sin(theta_estimate(1,i) - pi/2); % 摆球的纵坐标（估计值）
    plot([0 x],[0 y],'bo',x_measure,y_measure,'go', ...
    x_estimate,y_estimate,'ro','LineWidth',2)
    line([0,x],[0,y],'Color','b','LineWidth',1)
    xlim([-l/2 l/2]);
    ylim([-2*l 0]);
    subplot(1,2,2)
    plot(t(1:i),theta(1,1:i),'b',t(1:i),theta_measure(1:i),'g',...
    t(1:i),theta_estimate(1,1:i),'r','LineWidth',1)
    xlim([t_min t_max]);
    ylim([4*min(theta(1,:)) 4*max(theta(1,:))]);
    legend('角度（真实值）','角度（测量值）','角度（后验估计）')
    grid on
    make_gif('simple_pendulum.gif',i)
    pause(0.1);
end
% 绘制图像
figure
subplot(2,1,1)
plot(t,theta(1,:),'b','LineWidth',1)
hold on
plot(t,theta_estimate(1,:),'r','LineWidth',1)
xlim([t_min t_max]);
ylim([4*min(theta(1,:)) 4*max(theta(1,:))]);
legend('角度（真实值）','角度（后验估计）')
grid on
subplot(2,1,2)
plot(t,theta(2,:),'b','LineWidth',1)
hold on
plot(t,theta_estimate(2,:),'r','LineWidth',1)
xlim([t_min t_max]);
ylim([4*min(theta(2,:)) 4*max(theta(2,:))]);
legend('角速度（真实值）','角速度（后验估计）')
grid on
