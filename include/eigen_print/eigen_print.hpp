#pragma once
#include <iostream>
#include <string>
#include <type_traits>
#include <vector>
#include <array>
#include <cmath>
#include <algorithm>
#include <limits>
#include <fmt/format.h>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <unsupported/Eigen/CXX11/Tensor>
#include "options.hpp"
namespace eigen_print {
namespace detail {
template<typename T>
struct is_sparse : std::false_type {};
template<typename T>
struct is_sparse<Eigen::SparseMatrix<T>> : std::true_type {};
template<typename T>
struct is_sparse<Eigen::SparseVector<T>> : std::true_type {};
template<typename T>
struct is_tensor : std::false_type {};
template<typename T, int Rank>
struct is_tensor<Eigen::Tensor<T, Rank>> : std::true_type {};
template<typename T>
struct is_scalar {
static constexpr bool value = std::is_arithmetic_v<T> ||
std::is_same_v<T, std::complex<float>> ||
std::is_same_v<T, std::complex<double>>;
};
template<typename T>
std::string format_number(T value, int precision, bool scientific) {
if constexpr (std::is_same_v<T, float> || std::is_same_v<T, double>) {
if (std::isnan(value)) return "nan";
if (std::isinf(value)) return value > 0 ? "inf" : "-inf";
if (scientific) {
return fmt::format("{:.{}e}", value, precision);
} else {
std::string result = fmt::format("{:.{}f}", value, precision);
size_t pos = result.find('.');
if (pos != std::string::npos) {
while (result.size() > pos + 1 && result.back() == '0') {
result.pop_back();
}
if (result.back() == '.') {
result.pop_back();
}
}
return result;
}
} else if constexpr (std::is_integral_v<T> && !std::is_same_v<T, bool>) {
return fmt::format("{}", value);
} else if constexpr (std::is_same_v<T, bool>) {
return value ? "true" : "false";
} else if constexpr (std::is_same_v<T, std::complex<float>> ||
std::is_same_v<T, std::complex<double>>) {
std::string real_str, imag_str;
if (scientific) {
real_str = fmt::format("{:.{}e}", value.real(), precision);
imag_str = fmt::format("{:.{}e}", std::abs(value.imag()), precision);
} else {
real_str = fmt::format("{:.{}f}", value.real(), precision);
imag_str = fmt::format("{:.{}f}", std::abs(value.imag()), precision);
}
if (value.imag() >= 0) {
return fmt::format("({}+{}j)", real_str, imag_str);
} else {
return fmt::format("({}-{}j)", real_str, imag_str);
}
} else {
return fmt::format("{}", value);
}
}
inline std::string indent(int level, int spaces_per_level = 2) {
return std::string(level * spaces_per_level, ' ');
}
inline bool should_trim(int size, int threshold) {
return threshold > 0 && size > threshold;
}
inline int get_display_count(int size, int edge_items, int threshold) {
if (!should_trim(size, threshold)) {
return size;
}
return std::min(edge_items * 2, size);
}
}
template<typename Derived>
void print_matrix(const Eigen::DenseBase<Derived>& m,
const PrintOptions& opts = get_global_options()) {
int rows = m.rows();
int cols = m.cols();
bool trim_rows = detail::should_trim(rows, opts.threshold);
bool trim_cols = detail::should_trim(cols, opts.threshold);
int row_edge = trim_rows ? opts.edge_items : rows;
int col_edge = trim_cols ? opts.edge_items : cols;
std::cout << opts.prefix;
if (opts.show_shape) {
std::cout << "(" << rows << "x" << cols << ")";
}
if (opts.show_dtype) {
std::cout << ", dtype=" << typeid(typename Derived::Scalar).name();
}
if (opts.show_name && !opts.name.empty()) {
std::cout << " " << opts.name << " =";
}
std::cout << "([";
for (int i = 0; i < rows; ++i) {
if (i > 0) {
std::cout << " ";
}
bool show_row = (i < row_edge || i >= rows - row_edge);
if (!show_row) {
if (i == row_edge) {
std::cout << "[..., ";
i = rows - row_edge - 1;
}
continue;
}
std::cout << "[";
for (int j = 0; j < cols; ++j) {
bool show_col = (j < col_edge || j >= cols - col_edge);
if (!show_col) {
if (j == col_edge) {
std::cout << "..., ";
j = cols - col_edge - 1;
}
continue;
}
std::cout << detail::format_number(m(i, j), opts.precision, opts.scientific);
if (j < cols - 1 && !(j == col_edge - 1 && trim_cols)) {
std::cout << ", ";
}
}
std::cout << "]";
if (i < rows - 1 && !(i == row_edge - 1 && trim_rows)) {
std::cout << ",";
}
if (i < rows - 1) {
std::cout << "\n";
}
}
std::cout << "]])" << std::endl;
}
template<typename Derived>
void print_tensor_rec(const Derived& t,
const PrintOptions& opts,
std::array<int, Derived::NumDimensions>& indices,
int depth) {
const int Rank = Derived::NumDimensions;
if (depth == Rank - 1) {
int size = t.dimension(depth);
bool trim = detail::should_trim(size, opts.threshold);
int edge = trim ? opts.edge_items : size;
std::cout << "[";
for (int i = 0; i < size; ++i) {
bool show = (i < edge || i >= size - edge);
if (!show) {
if (i == edge) {
std::cout << "..., ";
i = size - edge - 1;
}
continue;
}
indices[depth] = i;
std::cout << detail::format_number(t.coeff(indices), opts.precision, opts.scientific);
if (i < size - 1 && !(i == edge - 1 && trim)) {
std::cout << ", ";
}
}
std::cout << "]";
} else {
int size = t.dimension(depth);
bool trim = detail::should_trim(size, opts.threshold);
int edge = trim ? opts.edge_items : size;
std::cout << "[";
for (int i = 0; i < size; ++i) {
bool show = (i < edge || i >= size - edge);
if (!show) {
if (i == edge) {
std::cout << "...";
if (depth < Rank - 2) {
std::cout << ",";
}
std::cout << "\n" << detail::indent(depth + 1);
i = size - edge - 1;
}
continue;
}
if (i > 0) {
std::cout << ",";
if (depth < Rank - 2) {
std::cout << "\n" << detail::indent(depth + 1);
} else {
std::cout << " ";
}
}
indices[depth] = i;
print_tensor_rec<Derived>(t, opts, indices, depth + 1);
}
std::cout << "]";
}
}
template<typename Derived>
void print_tensor(const Derived& t,
const PrintOptions& opts = get_global_options()) {
const int Rank = Derived::NumDimensions;
std::cout << opts.prefix;
if (opts.show_shape) {
std::cout << "(";
for (int i = 0; i < Rank; ++i) {
if (i > 0) std::cout << "x";
std::cout << t.dimension(i);
}
std::cout << ")";
}
if (opts.show_dtype) {
std::cout << ", dtype=" << typeid(typename Derived::Scalar).name();
}
if (opts.show_name && !opts.name.empty()) {
std::cout << " " << opts.name << " =";
}
std::cout << " ";
std::array<int, Rank> indices;
indices.fill(0);
print_tensor_rec<Derived>(t, opts, indices, 0);
std::cout << std::endl;
}
template<typename T>
void print_sparse(const Eigen::SparseMatrix<T>& m,
const PrintOptions& opts = get_global_options()) {
if (opts.sparse_as_dense) {
Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> dense = m;
print_matrix(dense, opts);
return;
}
std::cout << opts.prefix << "(sparse";
if (opts.show_shape) {
std::cout << ", " << m.rows() << "x" << m.cols();
}
std::cout << ", nnz=" << m.nonZeros() << ")";
if (opts.show_dtype) {
std::cout << ", dtype=" << typeid(T).name();
}
if (opts.show_name && !opts.name.empty()) {
std::cout << " " << opts.name << " =";
}
std::cout << "\n";
int count = 0;
for (int k = 0; k < m.outerSize(); ++k) {
for (typename Eigen::SparseMatrix<T>::InnerIterator it(m, k); it; ++it) {
std::cout << "(" << it.row() << ", " << it.col() << "): "
<< detail::format_number(it.value(), opts.precision, opts.scientific) << "\n";
count++;
if (count >= 100 && opts.threshold > 0 && m.nonZeros() > opts.threshold) {
std::cout << "... (" << (m.nonZeros() - count) << " more entries)\n";
return;
}
}
}
}
template<typename T>
void print_sparse(const Eigen::SparseVector<T>& v,
const PrintOptions& opts = get_global_options()) {
if (opts.sparse_as_dense) {
Eigen::Matrix<T, Eigen::Dynamic, 1> dense(v.size());
dense.setZero();
for (typename Eigen::SparseVector<T>::InnerIterator it(v); it; ++it) {
dense(it.index()) = it.value();
}
print_matrix(dense, opts);
return;
}
std::cout << opts.prefix << "(sparse";
if (opts.show_shape) {
std::cout << ", " << v.size() << "x1";
}
std::cout << ", nnz=" << v.nonZeros() << ")";
if (opts.show_dtype) {
std::cout << ", dtype=" << typeid(T).name();
}
if (opts.show_name && !opts.name.empty()) {
std::cout << " " << opts.name << " =";
}
std::cout << "\n";
int count = 0;
for (typename Eigen::SparseVector<T>::InnerIterator it(v); it; ++it) {
std::cout << "(" << it.index() << "): "
<< detail::format_number(it.value(), opts.precision, opts.scientific) << "\n";
count++;
if (count >= 100 && opts.threshold > 0 && v.nonZeros() > opts.threshold) {
std::cout << "... (" << (v.nonZeros() - count) << " more entries)\n";
return;
}
}
}
template<typename Derived>
void print(const Eigen::DenseBase<Derived>& m,
const PrintOptions& opts = get_global_options()) {
print_matrix(m, opts);
}
template<typename Derived>
void print(const Eigen::TensorBase<Derived>& t,
const PrintOptions& opts = get_global_options()) {
print_tensor(t.derived(), opts);
}
template<typename T>
void print(const Eigen::SparseMatrix<T>& m,
const PrintOptions& opts = get_global_options()) {
print_sparse(m, opts);
}
template<typename T>
void print(const Eigen::SparseVector<T>& v,
const PrintOptions& opts = get_global_options()) {
print_sparse(v, opts);
}
template<typename T, typename std::enable_if<detail::is_scalar<T>::value, int>::type = 0>
void print(const T& value, const PrintOptions& opts = get_global_options()) {
std::cout << detail::format_number(value, opts.precision, opts.scientific) << std::endl;
}
template<typename Derived>
void println(const Derived& m, const PrintOptions& opts = get_global_options()) {
print(m, opts);
}
}