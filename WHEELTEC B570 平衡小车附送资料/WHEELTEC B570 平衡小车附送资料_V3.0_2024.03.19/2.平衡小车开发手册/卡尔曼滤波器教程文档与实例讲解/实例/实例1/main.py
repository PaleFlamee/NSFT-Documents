import numpy as np
import matplotlib.pyplot as plt

n = 100  # 迭代次数
x = 0.01234  # 真实值
Q = 1e-10
R = 1e-3 ** 2
x_hat = np.zeros(n)
p = np.zeros(n)
x_hat_minus = np.zeros(n)
p_minus = np.zeros(n)
K = np.zeros(n)
y = np.random.normal(x, 1e-3, size=n)

#  初始化
x_hat[0] = 0.0
p[0] = 1.0

#  卡尔曼滤波
for k in range(1, n):
    #  预测部分
    x_hat_minus[k] = x_hat[k - 1]
    p_minus[k] = p[k - 1] + Q
    #  校正部分
    K[k] = p_minus[k] / (p_minus[k] + R)
    x_hat[k] = x_hat_minus[k] + K[k] * (y[k] - x_hat_minus[k])
    p[k] = (1 - K[k]) * p_minus[k]

#  绘制图像
plt.rcParams['figure.figsize'] = (7, 4)
plt.figure()
plt.plot(y, 'r+', label='noisy measurements')
plt.plot(x_hat, 'g-', label='a posteri estimate')
plt.axhline(x, color='b', label='truth value')
plt.legend()
plt.xlabel('Iteration')
plt.ylabel('Length')
plt.show()
