f = @(x) 1 ./ (1 + x .^ 2);
% f = @(x) cos(2 * pi * x);
x0 = -10;
x1 = 10;
N = 41;
N_test = 1001;

x = linspace(x0, x1, N);
y = f(x);

x_test = linspace(x0, x1, N_test);
y_test = f(x_test);

% polynomial
degree = 20;
w = polyfit(x, y, degree); 
y_poly = polyval(w, x_test);

% linear piecewise polynomial
y_interp = interp1(x, y, x_test);

% spline
p = csape(x, y, 'second');
y_spline = fnval(p, x_test);

% Fourier interpolation
y_ft = interpft(y, N_test);
dx = (x(2) - x(1)) / N_test * N;
x_test_ft = x0:dx:((N_test - 1) * dx + x0);


hold on
plot(x_test, y_poly)
plot(x_test, y_interp)
plot(x_test, y_spline)
plot(x_test_ft, y_ft)
plot(x_test, y_test)
legend('Polynomial', 'Linear piecewise', 'spline', 'Fourier', 'Ground truth')
% legend('ft', 'gt')

var_poly = [x_test' y_poly'];
var_interp = [x_test' y_interp'];
var_spline = [x_test' y_spline'];
var_ft = [x_test_ft' y_ft'];
var_gt = [x_test' y_test'];
save('poly_Matlab.dat', 'var_poly', '-ascii')
save('interp_Matlab.dat', 'var_interp', '-ascii')
save('spline_Matlab.dat', 'var_spline', '-ascii')
save('ft_Matlab.dat', 'var_ft', '-ascii')
save('gt_Matlab.dat', 'var_gt', '-ascii')


