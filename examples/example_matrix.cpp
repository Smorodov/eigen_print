#include <iostream>
#include <Eigen/Dense>
#include <eigen_print/eigen_print.hpp>
int main() {
std::cout << "=== Eigen Print Library Example - Matrices ===\n\n";
Eigen::Matrix3d small;
small << 1.0, 2.0, 3.0,
4.0, 5.0, 6.0,
7.0, 8.0, 9.0;
std::cout << "Small matrix (3x3):\n";
eigen_print::print(small);
Eigen::MatrixXd big(100, 100);
for (int i = 0; i < 100; ++i) {
for (int j = 0; j < 100; ++j) {
big(i, j) = static_cast<double>(i * 100 + j);
}
}
std::cout << "\nLarge matrix (100x100) with automatic trimming:\n";
eigen_print::print(big);
eigen_print::PrintOptions opts;
opts.precision = 2;
opts.edge_items = 4;
opts.show_shape = true;
opts.show_dtype = true;
opts.prefix = "matrix";
std::cout << "\nWith custom options (precision=2, edge_items=4, show_shape, show_dtype):\n";
eigen_print::print(big, opts);
Eigen::MatrixXd scientific(2, 2);
scientific << 1e-10, 2e-5,
3e-4, 4e-3;
opts.scientific = true;
opts.precision = 3;
opts.show_shape = false;
opts.show_dtype = false;
opts.prefix = "tensor";
std::cout << "\nScientific notation:\n";
eigen_print::print(scientific, opts);
Eigen::MatrixXd m = Eigen::MatrixXd::Identity(4, 4);
opts.show_name = true;
opts.name = "I";
opts.precision = 1;
opts.scientific = false;
std::cout << "\nNamed output:\n";
eigen_print::print(m, opts);
eigen_print::PrintOptions global_opts;
global_opts.precision = 2;
global_opts.edge_items = 2;
global_opts.show_shape = true;
eigen_print::set_global_options(global_opts);
std::cout << "\nWith global settings (precision=2, edge_items=2):\n";
eigen_print::print(big);
return 0;
}