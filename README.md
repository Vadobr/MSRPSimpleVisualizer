
# MSRPSimpleVisualizer
# For developers

## Requirements
- **C++**
- **Qt framework**
- **Visual Studio (recommended for build)**

## Installation & Usage
1. Clone the repository:
   ```sh
   git clone <repository-url>
   cd <project-directory>

2. Open the Visual Studio solution file (.sln).
   
3. Replace the Qt version with the one installed on your computer in the extension settings:
   
   3.1 Extentions  $\textcolor{blue}{→}$  Qt VS Tools _(or similar)_  $\textcolor{blue}{→}$  Qt version
   
   3.2 Project  $\textcolor{blue}{→}$  _\<project name\>_ Properties  $\textcolor{blue}{→}$  Qt Project Settins  $\textcolor{blue}{→}$  Qt Installation
   
5. Build and run the project

# For Users

<h1>Vadym Bondarenko</h1>
<p><strong>Student</strong> of Kharkiv National University of Radio Electronics</p>
<p>(2020 - 2024) - Bachelor's degree, (2024 - 2026) - Master's degree</p>
<p>metavadobr@gmail.com</p>
<h2>Project</h2>
<p>This project was created as a qualification work within the specialty <strong>Computer Engineering</strong>.</p>         
<h2>Description</h2>
<p>The project represents a visualization of a <strong>Markov process</strong> (MP), which is classified based on two criteria: stationarity and discreteness.</p>
<ul>
<li><strong>Markov process</strong> - a process where the probability of transition to another state depends only on the current state.</li>
<li><strong>Stationary MP</strong> - a process where the transition probability remains constant over time.</li>
<li><strong>Discrete MP</strong> - can be divided into specific steps.</li>
</ul>
<p>More details at:</p>
<ul>
<li>Ching, Wai-Ki, and Michael K. Ng. Markov Chains: Models, Algorithms and Applications. Springer, 2006. - 211 р.</li>
</ul>
<h2>Program Capabilities</h2>
<p>The program allows studying the Markov process over a specified time interval with a given accuracy. Due to the nature of the Markov process, it can be analyzed over an infinite time interval, and accuracy in this case is not critical.</p>
<p>The research can be visualized in the following formats:</p>
<ul>
	    <li>Graph</li>
	    <li>Graphics</li>
	    <li>Table</li>
	    <p>With the ability to save results</p>
</ul>
	
<h2>Program Usage Details</h2>
	
<p>When the program starts, the first thing offered to the user is to change the language in the top menu.</p>
<p>Depending on the studied process, select its parameters from the dropdown lists: stationary/non-stationary, petmanent/non-permanent. When switching to petmanent mode, probabilities are replaced with intensities, and the main diagonal is unlocked. When selecting the non-stationary mode, a field for entering a function will appear for each selected cell, but the ability to enter constants remains. It is recommended to paste functions from the clipboard to avoid mistakes.</p>
<p>The matrix expands as the number of states increases. The number of transitions changes automatically as the matrix is filled.</p>
<p>The parameters Research Time and "Number of Steps" determine the accuracy of the conducted studies. Adjust them so that in the "Results" table, the last 2-3 rows completely match, and in the "Graphics" tab, all graphs are smooth and tend to their asymptotes (usually a horizontal line).</p>
<p>You can fill in the matrix using numbers, arrow keys, and the Enter key. The controls are intuitive and require only a keyboard. There is no difference between a comma and a dot. Mistakes will be corrected automatically.</p>
<p>The program does not have "Solve" or "Execute" buttons, so just switch between tabs; the equations are solved automatically.</p>
<p>In the "Graph" tab, you can check if the process resembles the one you are studying. This tab is purely for visualization.</p>
<p>In the "Results" tab, research results are presented in a table format.</p>
<p>In the "Graphics" tab, research results are presented as graphs. This tab is purely for visualization.</p>
<p>Tabs 2, 3, and 4 can be saved in the corresponding formats using the "File" menu.</p>
<p>More information about Markov process research can be found in the <strong>"Computer Systems"</strong> course.</p>
