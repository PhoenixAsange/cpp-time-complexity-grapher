<h1 align="center"> C++ Function Benchmark Grapher</h1>

<p align="center">
  A practical tool to measure execution time of C++ functions over increasing iteration steps and visualize performance with Python's <code>matplotlib</code>.
</p>

<hr/>

<h2>Overview</h2>

<p>
This tool helps benchmark the runtime of C++ functions by executing them multiple times at increasing iteration counts. 
It interpolates between <code>1</code> and a user-defined maximum, recording how execution time scales with input size.
The data is visualized using Python's <code>matplotlib</code> to generate clean performance graphs.
</p>

<h2>Limitations & Future Improvements</h2>

<ul>
  <li>
    <strong>Time Accuracy:</strong> The tool accurately demonstrates time complexity trends (e.g., linear vs. quadratic growth),
    but may not reflect the precise runtime in nanoseconds due to cumulative timing and overhead between steps.
  </li>
  <li>
    <strong>Single Timer Limitation:</strong> Current timing is cumulative from the start of the program. Per-step timing isolation will be added in a future update.
  </li>
  <li>
    <strong>Console and CSV Timing Mismatch:</strong> Timing output to the console and CSV may differ slightly due to multiple calls to the timer.
  </li>
  <li>
    <strong>User Experience:</strong> AlgorithmTimer objects must be manually created to generate csv files and csv files must be inputted by running python program
  </li>
</ul>
