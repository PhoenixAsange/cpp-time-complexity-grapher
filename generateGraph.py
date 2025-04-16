import pandas as pd
from matplotlib import pyplot as plt

#Takes user input to select csv file

algorithmDocument = input("File name (Labels Graph): ")

algorithmData = pd.read_csv(f'./graph-documents/{algorithmDocument}.csv')

algorithmData['avg_time'] = algorithmData['time'] / algorithmData['iterations']

plt.figure(figsize=(10, 6))
plt.plot(algorithmData['iterations'], algorithmData['avg_time'], marker='o', linestyle='-')

plt.xlabel('Iterations')
plt.ylabel('Avg Time per Operation (ns)')
plt.title(f'{algorithmDocument} Avg Runtime vs Iterations')
plt.grid(True)

plt.tight_layout()
plt.show()
