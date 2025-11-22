clc
clear
close all
%
% 读取MPU6050三轴加速度的动态测量数据
Data = readtable("DataScope-OutPut.xlsx","VariableNamingRule","preserve");
Data = table2cell(Data(1:9,2:end));
Data = cell2mat(Data);
%
% 通过DMP获得的角度数据
roll_DMP  = Data(1,:)/180*pi;
pitch_DMP = Data(2,:)/180*pi;
yaw_DMP   = Data(3,:)/180*pi;
%
% 角速度数据
gyro_X = Data(4,:);
gyro_Y = Data(5,:);
gyro_Z = Data(6,:);
%
% 加速度数据
acce_X = Data(7,:);
acce_Y = Data(8,:);
acce_Z = Data(9,:);
%
% 加速度与角度之间的换算
roll_estimate = atan2(-acce_Y,acce_Z);
%
% 采样间隔
Ts = 0.05;
%
% 采样时间
t_min = 0;
t_max = Ts*(size(Data,2)-1);
t = t_min:Ts:t_max;
%
% A矩阵
A = [1 -Ts; 0 1];
%
% B矩阵
B = [Ts; 0];
%
% C矩阵
C = [1 0];
%
% D矩阵
D = 0;
%
% 离散状态空间表达式
sys = ss(A,B,C,D,Ts);
%
% 过程噪声
Q = diag([1e-10 1e-10]);
%
% 测量噪声
R = 1e-4;
%
% 初始状态
x0 = [0; 0];
p0 = diag([1 1]);
%
% 卡尔曼滤波
u = gyro_X;
y = roll_estimate;
x_hat = KF(sys.A,sys.B,sys.C,u,y,Q,R,t,x0,p0);
%
% 绘制图像
plot(t,roll_DMP,'b','LineWidth',1)
hold on
plot(t,x_hat(1,:),'r','LineWidth',1)
grid on
xlim([t_min t_max]);
legend('角度(DMP)','角度(Kalman Filter)')
