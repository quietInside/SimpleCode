import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

path = './test_data.txt'
pdData = pd.read_csv(path, header=None, names=['Data 1', 'Data 2', 'Admitted'])
print(pdData.head())
print(pdData.shape)

positive = pdData[pdData['Admitted'] == 1]
negative = pdData[pdData['Admitted'] == 0]

fig, ax = plt.subplots(figsize=(5,5))
ax.scatter(positive['Data 1'], positive['Data 2'], s=30, c='b', label='Admitted')
ax.scatter(negative['Data 1'], negative['Data 2'], s=30, c='r', label='Not Admitted')
ax.legend()
ax.set_xlabel('Data 1')
ax.set_ylabel('Data 2')

def sigmoid(z):
    return 1 / (1 + np.exp(-z))

nums = np.arange(-10, 10, step=0.1) #sigmod函数图
fig, ax = plt.subplots(figsize=(6,2))
ax.plot(nums, sigmoid(nums), 'r')
ax.grid()

def model(X, theta):
    return sigmoid(np.dot(X, theta.T))

pdData.insert(0, 'Ones', 1)#第一列插入1
orig_data = pdData.values#表格化为矩阵
cols = orig_data.shape[1]#有4列
X = orig_data[:,0:cols-1]#前三列
y = orig_data[:,cols-1:cols]#最后一列0/1
theta = np.zeros([1, 3])

def cost(X, y, theta): #损失函数
    left = np.multiply(-y, np.log(model(X, theta)))
    right = np.multiply(1 - y, np.log(1 - model(X, theta)))
    return np.sum(left - right) / (len(X))

def gradient(X, y, theta): #梯度计算
    grad = np.zeros(theta.shape)
    error = (model(X, theta)- y).ravel()
    for j in range(len(theta.ravel())): #for each parmeter 3
        term = np.multiply(error, X[:,j])
        grad[0,j] = np.sum(term) / len(X)
    
    return grad

import numpy.random
#随机打乱数据
def shuffleData(data):
    np.random.shuffle(data)
    cols = data.shape[1]
    X = data[:, 0:cols-1]
    y = data[:, cols-1:]
    return X, y

def descent(data, theta, batchSize, thresh, alpha):
    #梯度下降求解
    i = 0 # 迭代次数
    k = 0 # batch
    X, y = shuffleData(data)
    grad = np.zeros(theta.shape) # 计算的梯度
    costs = [cost(X, y, theta)] # 损失值

    
    while True:
        grad = gradient(X[k:k+batchSize], y[k:k+batchSize], theta)
        k += batchSize #取batch数量个数据
        if k >= len(X): 
            k = 0 
            X, y = shuffleData(data) #重新洗牌
        theta = theta - alpha*grad # 参数更新
        costs.append(cost(X, y, theta)) # 计算新的损失
        i += 1 

        if (i > thresh) : break #根据迭代次数停止
    
    return theta, costs

n=len(X)
theta, costs=descent(orig_data, theta, n, thresh=20000, alpha=0.002)
print(theta)

fig, ax = plt.subplots(figsize=(10,4))
ax.plot(np.arange(len(costs)), costs, 'r')
ax.set_xlabel('Iterations')
ax.set_ylabel('Cost')
ax.set_title('Cost')

fig, ax = plt.subplots(figsize=(5,5))
ax.scatter(positive['Data 1'], positive['Data 2'], s=30, c='b', label='Admitted')
ax.scatter(negative['Data 1'], negative['Data 2'], s=30, c='r', label='Not Admitted')
x = np.arange(-3, 3, 0.1)
y = (-theta[0, 0] - theta[0, 1] * x) / theta[0, 2]
ax.plot(x, y)
ax.legend()
ax.set_xlabel('Data 1')
ax.set_ylabel('Data 2')
