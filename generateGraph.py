import pandas as pd
import matplotlib.pyplot as plt
import os

# Create the directory if it doesn't exist
os.makedirs('./graphs', exist_ok=True)

# Load file
algorithmDocument = input("File name: ")
constantTime = input("Constant Time Algorithm (T): ") or "true"
dataMode = input("Input or Iteration? (Input): ") or "input"

xColumn = "iterations"  # Always use this column
xLabel = "Input size" if dataMode.lower() == "input" else "Iterations"
name = algorithmDocument

# Read CSV
df = pd.read_csv(f'./graph-documents/{algorithmDocument}.csv')

# Compute appropriate time value
if dataMode.lower() == "input":
    # Show total time (e.g., to reflect O(n), O(n^2), etc.)
    df['plottable_time'] = df['time']
else:
    # Show average time per operation
    df['plottable_time'] = df['time'] / df['iterations']

# Determine time unit scaling
maxTime = df['plottable_time'].max()
if maxTime < 1e3:
    scaleFactor = 1
    unit = "ns"
elif maxTime < 1e6:
    scaleFactor = 1e3
    unit = "µs"
elif maxTime < 1e9:
    scaleFactor = 1e6
    unit = "ms"
elif maxTime < 60e9:
    scaleFactor = 1e9
    unit = "s"
else:
    scaleFactor = 60e9
    unit = "min"

# Scale the time values
df['scaled_time'] = df['plottable_time'] / scaleFactor

# Plot
plt.figure(figsize=(12, 8))
plt.plot(df[xColumn], df['scaled_time'], marker='o', linestyle='-')

plt.xlabel(f"{xLabel} (n)")
ylabel = "Avg Time per Operation" if dataMode.lower() != "input" else "Total Time"
plt.ylabel(f"{ylabel} ({unit})")
plt.title(f"{name} {ylabel}")

# Adjust y-limits if graph is constant time
graphScale = df['scaled_time'].max() - df['scaled_time'].min()
scaleMultiplier = 1.5
if str(constantTime).lower() in ["t", "true"]:
    plt.ylim(
        df['scaled_time'].min() - (graphScale * scaleMultiplier),
        df['scaled_time'].max() + (graphScale * scaleMultiplier)
    )

plt.ticklabel_format(style='plain', useOffset=False, axis='both')  # No scientific notation
plt.grid(True)
plt.tight_layout()
plt.savefig(f'./graphs/{name}.png')
plt.show()
