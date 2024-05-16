import numpy as np
import matplotlib.pyplot as plt
from sklearn.datasets import make_blobs
import pandas as pd

# 生成2維合成數據
X, y = make_blobs(n_samples=1000, centers=5, n_features=2, random_state=42)

# 將數據轉換為 pandas DataFrame
data = pd.DataFrame(X, columns=['Feature 1', 'Feature 2'])
data['Label'] = y

# 畫出散點圖並保存
plt.figure(figsize=(8, 6))
plt.scatter(X[:, 0], X[:, 1], c=y, cmap='viridis')
plt.title('Synthetic 2D Classification Data')
plt.xlabel('Feature 1')
plt.ylabel('Feature 2')
plt.savefig('synthetic_data.png', dpi=300, bbox_inches='tight')

# 保存數據到 CSV 文件
data.to_csv('synthetic_data.csv', index=False)