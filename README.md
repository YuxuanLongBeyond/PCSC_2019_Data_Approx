## PCSC_2019_Data_Approx  
C++ implementation of basic data fitting algorithms, which involve four methods:  
1. Polynomial fitting  
2. Linear piecewise polynomial fitting  
3. Cubic spline  
4. Fourier interpolation  

# Configuration File
The input parameters are defined in the configuration file in the folder *config*. An example config.txt is already included by default. New configuration file can be created, where its name can be passed to the main function as the first argument. If no argment is provided, the default configuration (in config.txt) will be used. If the codes have been compiled as "project", an example command for running the code can be:
`<./project YourNewConfigFile.txt>`  
The following instructions are all about the specific parameter setup in configuration file.  

# Data Aquisition  
The user has two options to the access of the input data. If *use_file* = 0 (by default),  the program will generate data by writing a new file. Otherwise, the user has to provide his/her own data file (not recommended). In both cases, *use_file_name* is the file name. By default, *use_file_name* = data.dat.  
In this project, **all** the data files contain two columns, which correspond to x and y values.

# Input Data Generation
If *use_file* = 0, there are several parameters to be specified:  
1. *function_type*, which indicates the choice of function to be used for data generation. It should be of integer type: 1 for trigonometric function; 2 for Runge function (by default); 3 for polynomial function.
2. *x_input_min* and *x_input_max*, which control the range of the input x.  
3. *num_input_points*, which indicates the number of input data points to be used for interpolation.  
4. *node_type*, which indicates the nodes distribution. It should be of integer type: 1 for uniform distribution; 2 for Chebyshev Gaussian Lobatto (CGL) nodes.

# Fitting Methods
To use one specific method, assign the method name to the parameter **approximation_method**.  
For polynomial fitting, we set *approximation_method* = polynomial. In the configuration file, this method has two relevant parameters:  
1. *polynomial_degree*, which controls the degree of the polynomial.
2. *polynomial_lambda*, small non-negative number to be added on the diagonal when solving the linear system. By default, it is zero.  
For spline interpolation, set *approximation_method* = spline.  
For linear piecewise interpolation, set *approximation_method* = interp1.  
For Fourier interpolation, set *approximation_method* = dct.    

# Test Data Generation
The test to compare the true data with the approximation is compulsory in each run. To generate true data, we can set:
1. *x_test_min* and *x_test_max*, which control the range of the test points $x_test$.
2. *num_test_points*, the number of test points.
The test output will be stored in the file name *out_file_name*, which can be Output.dat by
default.  

# Plot
To plot the results directly in C++, set *use_gnuplot* = 1, but make sure that Gnuplot has been installed.  
Alternatively, run matlab_plot.m in folder plot will plot the results from default data files.  

# Debug Mode
Open debug mode if we set *use_debug_mode* = 1. In debug mode, it will compute the deviation between data approximated by our implementation and Matlab built-in function. 
In this mode, the parameter *MATLAB_generated_file_name* should be set, as the name of the output data file generated from Matlab built-in function.

# Root Structure
config---contains configuration files and configuration class.
data---contains data files and Matlab script (for reference data generation in debug mode).
doc---stores the documentation from Doxygen.
plot---contains plot methods by Gnuplot and Matlab
src---contains source files for the implementation of the main algorithms
test---contains data IO handling (include data generation) and test suite.
