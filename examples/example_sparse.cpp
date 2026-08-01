#include <iostream>
#include <Eigen/Sparse>
#include <eigen_print/eigen_print.hpp>
int main() {
std::cout << "=== Eigen Print Library Example - Sparse Matrices ===\n\n";
Eigen::SparseMatrix<double> m(10, 10);
for (int i = 0; i < 10; ++i) {
m.insert(i, i) = static_cast<double>(i + 1);
if (i < 9) {
m.insert(i, i + 1) = static_cast<double>(i + 1) * 0.5;
}
if (i > 0) {
m.insert(i, i - 1) = static_cast<double>(i + 1) * 0.3;
}
}
m.makeCompressed();
std::cout << "Sparse matrix (10x10, tridiagonal):\n";
eigen_print::print(m);
eigen_print::PrintOptions opts;
opts.show_shape = true;
opts.show_dtype = true;
opts.precision = 2;
std::cout << "\nWith shape and dtype info:\n";
eigen_print::print(m, opts);
opts.sparse_as_dense = true;
opts.precision = 1;
opts.show_shape = false;
opts.show_dtype = false;
std::cout << "\nAs dense matrix:\n";
eigen_print::print(m, opts);
Eigen::SparseVector<double> v(10);
v.insert(0) = 1.0;
v.insert(3) = 4.0;
v.insert(5) = 6.0;
v.insert(7) = 8.0;
v.insert(9) = 10.0;
std::cout << "\nSparse vector:\n";
eigen_print::print(v);
Eigen::SparseMatrix<double> big(20, 20);
for (int i = 0; i < 20; ++i) {
for (int j = 0; j < 20; ++j) {
if ((i + j) % 3 == 0) {
big.insert(i, j) = static_cast<double>(i * 20 + j) * 0.1;
}
}
}
big.makeCompressed();
opts.sparse_as_dense = false;
opts.threshold = 30;
std::cout << "\nLarge sparse matrix (20x20, ~133 nnz) with trimming:\n";
eigen_print::print(big, opts);
eigen_print::PrintOptions global_opts;
global_opts.precision = 3;
global_opts.show_shape = true;
global_opts.sparse_as_dense = false;
eigen_print::set_global_options(global_opts);
std::cout << "\nWith global settings (precision=3, show_shape):\n";
eigen_print::print(m);
return 0;
}