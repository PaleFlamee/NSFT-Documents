% 计算解析解（线性化后的方程）
clc
clear
close all
syms theta(t)
g = 9.8; % 重力加速度(m·s^-2)
l = 0.2; % 轻杆的长度(m)
eqn = diff(theta,t,2) == -(g/l)*theta(t);
dtheta = diff(theta,t);
cond = [theta(0) == pi/18 dtheta(0) == 0];
theta(t) = dsolve(eqn,cond); % 角度
dtheta(t) = diff(theta); % 角速度
