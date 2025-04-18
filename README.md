<h1 align="center">C++ Function Benchmark Grapher</h1>

<p align="center">
  Measures execution time of C++ functions over increasing iteration or input sizes and visualizes performance using Python's <code>matplotlib</code>.
</p>

<hr/>

<h2>Overview</h2>

<p>
  This tool benchmarks the time complexity of C++ functions. It uses a C++ timer system to measure execution time across interpolated steps (from <code>1</code> to a user-defined maximum), averaging multiple trials at each step to ensure consistent results.
</p>

<p>
  The benchmark results are stored in CSV format and visualized with Python's <code>matplotlib</code> to generate clean, readable performance graphs.
</p>

<h3>⏱Timer Classes</h3>

<ul>
  <li>
    <strong>AlgorithmTimerIterations</strong> – Used for <em>constant-time</em> functions. Executes the same function repeatedly on a fixed-size input, increasing the number of iterations to measure average time per call.
  </li>
  <li>
    <strong>AlgorithmTimerInput</strong> – Used for functions with <em>scaling input</em>. Increases the size of the input passed to the function at each step to measure how performance scales.
  </li>
</ul>

<h2>Future Improvements</h2>

<ul>
  <li><strong>Automation:</strong> Automate CSV parsing, multi-function benchmarking, and graph generation for large test suites.</li>
  <li><strong>Live Comparison Mode:</strong> Compare multiple functions or data structures on the same graph (e.g., <code>vector</code> vs <code>deque</code>).</li>
  <li><strong>CLI or GUI:</strong> Add a command-line interface or simple GUI for easier use and configuration.</li>
  <li><strong>Encapsulation:</strong> Abstract timer classes and graphing logic further to improve reusability and code quality.</li>
</ul>
