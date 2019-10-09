import numpy as np
import matplotlib
import matplotlib.pyplot as plt
import scipy.signal as signal
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression

if __name__ == "__main__":
    path = './Advertising.csv'
    data = pd.read_csv(path)
    x = data[['AT', 'V', 'AP', 'RH']]
    y = data['PE']
    print(x.head())
    print(y.head())
    print(x.shape, y.shape)

    #随机划分训练集和测试集
    x_train, x_test, y_train, y_test = train_test_split(x, y, test_size=0.2, random_state=1)
    model = LinearRegression()
    model.fit(x_train, y_train)#训练数据
    print(model.coef_, model.intercept_)#斜率与截距
    
    order = y_test.argsort(axis=0)#返回按列排序索引
    y_test = y_test.values[order]#排序好的测试集
    x_test = x_test.values[order, :]
    y_test_pred = model.predict(x_test)
    mse = np.mean((y_test_pred - np.array(y_test)) ** 2)#均方误差
    rmse = np.sqrt(mse)

    from sklearn.metrics import mean_absolute_error
    
    print('MSE = ', mse, end=' ')
    print('MAE = ', mean_absolute_error(y_test, y_test_pred))#平均绝对误差
    print('RMSE = ', rmse)
    print('Training R2 = ', model.score(x_train, y_train))
    print('Test R2 = ', model.score(x_test, y_test))

    error = y_test - y_test_pred
    np.set_printoptions(suppress=True)#不需要科学计数
    print('error = ', error)

    plt.hist(error, bins=40, color='r', alpha=0.5, edgecolor='k')
    plt.show()
    

    matplotlib.rcParams['font.sans-serif'] = ['simHei']
    matplotlib.rcParams['axes.unicode_minus'] = False
    
    plt.figure(facecolor='w',figsize=(8,4))
    t = np.arange(len(x_test))
    plt.plot(t, y_test_pred, 'g-', linewidth=1, label='预测数据')
    
    plt.plot(t, signal.medfilt(y_test_pred,25), 'y-', linewidth=2, label='滤波预测数据')
    plt.plot(t, y_test, 'r-', linewidth=2, label='真实数据')
    plt.legend(loc='upper left')
    plt.title('线性回归预测', fontsize=18)
    plt.grid(b=True, ls=':')
    plt.show()
    
    fig, ax = plt.subplots()
    ax.scatter(y_test, y_test_pred,20)
    ax.plot([y_test.min(), y_test.max()], [y_test.min(), y_test.max()],'k', alpha=0.5,lw=2)
    ax.set_xlabel('Measured')
    ax.set_ylabel('Predicted')
    plt.show()