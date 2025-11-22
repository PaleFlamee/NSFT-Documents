% 卡尔曼滤波
function output = KF(A,B,C,u,y,Q,R,t,x0,p0)
N = length(t);
x_hat = zeros(2,N);
x_hat_minus = zeros(2,N);
% 初始化
x_hat(:,1) = x0;
p = p0;
for k = 1:N-1
    % 预测部分
    x_hat_minus(:,k+1) = A*x_hat(:,k) + B*u(:,k);
    p_minus = A*p*A' + Q;
    % 校正部分
    K = (p_minus*C') / (C*p_minus*C' + R);
    x_hat(:,k+1) = x_hat_minus(:,k+1) + K*(y(k+1) - C*x_hat_minus(:,k+1));
    p = (eye(2) - K*C)*p_minus;
end
output = x_hat;
end
