#include <iostream>
#include <unsupported/Eigen/CXX11/Tensor>
#include <eigen_print/eigen_print.hpp>
int main() {
std::cout << "=== Eigen Print Library Example - Tensors ===\n\n";
Eigen::Tensor<float, 1> t1(10);
for (int i = 0; i < 10; ++i) {
t1(i) = static_cast<float>(i) * 0.5f;
}
std::cout << "1D Tensor (10 elements):\n";
eigen_print::print(t1);
Eigen::Tensor<float, 2> t2(5, 6);
for (int i = 0; i < 5; ++i) {
for (int j = 0; j < 6; ++j) {
t2(i, j) = static_cast<float>(i * 10 + j);
}
}
std::cout << "\n2D Tensor (5x6):\n";
eigen_print::print(t2);
Eigen::Tensor<float, 3> t3(3, 4, 5);
int counter = 0;
for (int i = 0; i < 3; ++i) {
for (int j = 0; j < 4; ++j) {
for (int k = 0; k < 5; ++k) {
t3(i, j, k) = static_cast<float>(counter++);
}
}
}
std::cout << "\n3D Tensor (3x4x5):\n";
eigen_print::print(t3);
eigen_print::PrintOptions opts;
opts.precision = 1;
opts.edge_items = 2;
opts.show_shape = true;
opts.show_dtype = true;
opts.prefix = "tensor";
std::cout << "\nWith custom options (precision=1, edge_items=2, show_shape, show_dtype):\n";
eigen_print::print(t3, opts);
Eigen::Tensor<float, 4> t4(8, 8, 8, 8);
for (int i = 0; i < 8; ++i) {
for (int j = 0; j < 8; ++j) {
for (int k = 0; k < 8; ++k) {
for (int l = 0; l < 8; ++l) {
t4(i, j, k, l) = static_cast<float>(i + j + k + l);
}
}
}
}
std::cout << "\n4D Tensor (8x8x8x8) with automatic trimming:\n";
eigen_print::print(t4);
Eigen::Tensor<std::complex<double>, 1> t_complex(5);
for (int i = 0; i < 5; ++i) {
t_complex(i) = std::complex<double>(static_cast<double>(i), static_cast<double>(i * 2));
}
std::cout << "\nComplex tensor:\n";
eigen_print::print(t_complex);
Eigen::Tensor<bool, 2> t_bool(3, 3);
for (int i = 0; i < 3; ++i) {
for (int j = 0; j < 3; ++j) {
t_bool(i, j) = (i == j);
}
}
std::cout << "\nBool tensor (identity):\n";
eigen_print::print(t_bool);
eigen_print::PrintOptions global_opts;
global_opts.precision = 1;
global_opts.edge_items = 2;
global_opts.show_shape = true;
eigen_print::set_global_options(global_opts);
Eigen::Tensor<float, 2> t_small(4, 4);
for (int i = 0; i < 4; ++i) {
for (int j = 0; j < 4; ++j) {
t_small(i, j) = static_cast<float>(i * 4 + j);
}
}
std::cout << "\nWith global settings (precision=1, edge_items=2):\n";
eigen_print::print(t_small);
return 0;
}