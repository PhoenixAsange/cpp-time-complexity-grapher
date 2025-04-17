import pandas as pd
import matplotlib.pyplot as plt

#Load file
algorithmDocument = input("File name: ")
name = input("Graph label (Default - file name): ") or algorithmDocument

#
df = pd.read_csv(f'./graph-documents/{algorithmDocument}.csv')
df['avg_time'] = df['time'] / df['iterations'] #Calculate average time per iteration


max_time = df['avg_time'].max() #Set time bound

#Calculate time unit
if max_time < 1e3:
    scale_factor = 1
    unit = "ns"
elif max_time < 1e6:
    scale_factor = 1e3
    unit = "µs"
elif max_time < 1e9:
    scale_factor = 1e6
    unit = "ms"
elif max_time < 60e9:
    scale_factor = 1e9
    unit = "s"
else:
    scale_factor = 60e9
    unit = "min"

df['scaled_avg_time'] = df['avg_time'] / scale_factor


plt.figure(figsize=(12, 8))
plt.plot(df['iterations'], df['scaled_avg_time'], marker='o', linestyle='-')

plt.xlabel("Iterations")
plt.ylabel(f"Avg Time per Operation ({unit})")
plt.title(f"{name} Avg Time per Operation")

magic = df['scaled_avg_time'].max() -df['scaled_avg_time'].min()

if df['scaled_avg_time'].max() - df['scaled_avg_time'].min() > magic / 2: #Flattens constant time graphs
    plt.ylim(df['scaled_avg_time'].min() - magic, df['scaled_avg_time'].max() + magic)

plt.ticklabel_format(axis='y', style='plain')
plt.grid(True)
plt.tight_layout()
plt.show()
