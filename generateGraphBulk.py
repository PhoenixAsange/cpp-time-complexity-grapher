import os
import pandas as pd
import matplotlib.pyplot as plt

script_dir = os.path.dirname(os.path.abspath(__file__))
docs_dir = os.path.join(script_dir, "graph-documents")
graphs_dir = os.path.join(script_dir, "graphs")
os.makedirs(graphs_dir, exist_ok=True)

constantTime = input("Are these Constant Time Algorithms? (T/true if yes): ") or "true"
dataMode = input("Input or Iteration? (Input): ") or "input"

xColumn = "iterations"
xLabel = "Input size" if dataMode.lower() == "input" else "Iterations"

for file in os.listdir(docs_dir):
    if not file.endswith(".csv"):
        continue

    name = file[:-4]
    df = pd.read_csv(os.path.join(docs_dir, file))

    if dataMode.lower() == "input":
        df['plottable_time'] = df['time']
    else:
        df['plottable_time'] = df['time'] / df['iterations']

    maxTime = df['plottable_time'].max()
    if maxTime < 1e3:
        scaleFactor, unit = 1, "ns"
    elif maxTime < 1e6:
        scaleFactor, unit = 1e3, "µs"
    elif maxTime < 1e9:
        scaleFactor, unit = 1e6, "ms"
    elif maxTime < 60e9:
        scaleFactor, unit = 1e9, "s"
    else:
        scaleFactor, unit = 60e9, "min"

    df['scaled_time'] = df['plottable_time'] / scaleFactor

    plt.figure(figsize=(12, 8))
    plt.plot(df[xColumn], df['scaled_time'], marker='o', linestyle='-')
    plt.xlabel(f"{xLabel} (n)")
    ylabel = "Avg Time per Operation" if dataMode.lower() != "input" else "Total Time"
    plt.ylabel(f"{ylabel} ({unit})")
    plt.title(f"{name} {ylabel}")

    if str(constantTime).lower() in ["t", "true"]:
        graphScale = df['scaled_time'].max() - df['scaled_time'].min()
        plt.ylim(
            df['scaled_time'].min() - graphScale * 1.5,
            df['scaled_time'].max() + graphScale * 1.5
        )

    plt.ticklabel_format(style='plain', useOffset=False, axis='both')
    plt.grid(True)
    plt.tight_layout()
    plt.savefig(os.path.join(graphs_dir, f"{name}.png"))
    plt.close()

print("All graphs saved to ./graphs/")
