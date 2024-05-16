import numpy as np
import matplotlib.pyplot as plt

# 設置參數
num_samples = 50  # 樣本數量
num_features = 2  # 特徵數量
num_classes = 2  # 類別數量


# 生成隨機的特徵資料
X = np.random.rand(num_samples, num_features)
    
# 隨機生成每個樣本的多標籤
y = np.random.randint(2, size=(num_samples))
print(y)
# 繪製散點圖
plt.figure(figsize=(8, 6))
class_indices = np.where(y[:] == 0)[0]
plt.scatter(X[class_indices, 0], X[class_indices, 1], label=f'Type')
class_indices = np.where(y[:] == 1)[0]
plt.scatter(X[class_indices, 0], X[class_indices, 1], label=f'Type')
plt.title('Label0')
plt.xlabel('Feature 1')
plt.ylabel('Feature 2')
plt.grid(True)
# 存儲圖片
plt.savefig('synthetic_data_plot0.png')

# 繪製散點圖
y = np.random.randint(2, size=(num_samples, num_classes))
plt.figure(figsize=(8, 6))
class_indices = np.where(y[:] == 0)[0]
plt.scatter(X[class_indices, 0], X[class_indices, 1], label=f'Type')
class_indices = np.where(y[:] == 1)[0]
plt.scatter(X[class_indices, 0], X[class_indices, 1], label=f'Type')
plt.title('Label1')
plt.xlabel('Feature 1')
plt.ylabel('Feature 2')
plt.grid(True)
# 存儲圖片
plt.savefig('synthetic_data_plot1.png')

# 繪製散點圖
y = np.random.randint(2, size=(num_samples, num_classes))
plt.figure(figsize=(8, 6))
class_indices = np.where(y[:] == 0)[0]
plt.scatter(X[class_indices, 0], X[class_indices, 1], label=f'Type')
class_indices = np.where(y[:] == 1)[0]
plt.scatter(X[class_indices, 0], X[class_indices, 1], label=f'Type')
plt.title('Label2')
plt.xlabel('Feature 1')
plt.ylabel('Feature 2')
plt.grid(True)
# 存儲圖片
plt.savefig('synthetic_data_plot2.png')

# 繪製散點圖
y = np.random.randint(2, size=(num_samples, num_classes))
plt.figure(figsize=(8, 6))
class_indices = np.where(y[:] == 0)[0]
plt.scatter(X[class_indices, 0], X[class_indices, 1], label=f'Type')
class_indices = np.where(y[:] == 1)[0]
plt.scatter(X[class_indices, 0], X[class_indices, 1], label=f'Type')
plt.title('Label3')
plt.xlabel('Feature 1')
plt.ylabel('Feature 2')
plt.grid(True)
# 存儲圖片
plt.savefig('synthetic_data_plot3.png')