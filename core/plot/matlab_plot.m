load('../data/Output.dat');
load('../data/data.dat');

hold on
plot(data(:, 1), data(:, 2), '*r')
plot(Output(:, 1), Output(:, 2), '.b')

legend('Data points provided', 'Approximated data')

xlabel('x')
ylabel('y')