#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include <eigen_print/eigen_print.hpp>
#include <unsupported/Eigen/CXX11/Tensor>
#include "test_utils.hpp"
TEST_CASE("Tensor 1D printing", "[tensor]") {
Eigen::Tensor<float, 1> t(5);
for (int i = 0; i < 5; ++i) {
t(i) = static_cast<float>(i * 2);
}
std::string output = capture_output([&] {
eigen_print::print(t);
});
REQUIRE_THAT(output, Catch::Matchers::ContainsSubstring("tensor"));
REQUIRE_THAT(output, Catch::Matchers::ContainsSubstring("[0, 2, 4, 6, 8]"));
}
TEST_CASE("Tensor 2D printing", "[tensor]") {
Eigen::Tensor<float, 2> t(3, 3);
for (int i = 0; i < 3; ++i) {
for (int j = 0; j < 3; ++j) {
t(i, j) = static_cast<float>(i * 3 + j);
}
}
std::string output = capture_output([&] {
eigen_print::print(t);
});
REQUIRE_THAT(output, Catch::Matchers::ContainsSubstring("[[0, 1, 2]"));
REQUIRE_THAT(output, Catch::Matchers::ContainsSubstring("[3, 4, 5]"));
REQUIRE_THAT(output, Catch::Matchers::ContainsSubstring("[6, 7, 8]]"));
}
TEST_CASE("Tensor 3D printing", "[tensor]") {
Eigen::Tensor<float, 3> t(2, 2, 2);
int counter = 0;
for (int i = 0; i < 2; ++i) {
for (int j = 0; j < 2; ++j) {
for (int k = 0; k < 2; ++k) {
t(i, j, k) = static_cast<float>(counter++);
}
}
}
std::string output = capture_output([&] {
eigen_print::print(t);
});
REQUIRE_THAT(output, Catch::Matchers::ContainsSubstring("[[[0, 1]"));
REQUIRE_THAT(output, Catch::Matchers::ContainsSubstring("[2, 3]]"));
REQUIRE_THAT(output, Catch::Matchers::ContainsSubstring("[[4, 5]"));
REQUIRE_THAT(output, Catch::Matchers::ContainsSubstring("[6, 7]]"));
}
TEST_CASE("Tensor with shape and dtype", "[tensor]") {
Eigen::Tensor<float, 2> t(2, 3);
for (int i = 0; i < 2; ++i) {
for (int j = 0; j < 3; ++j) {
t(i, j) = static_cast<float>(i * 3 + j);
}
}
eigen_print::PrintOptions opts;
opts.show_shape = true;
opts.show_dtype = true;
std::string output = capture_output([&] {
eigen_print::print(t, opts);
});
REQUIRE_THAT(output, Catch::Matchers::ContainsSubstring("(2x3)"));
REQUIRE_THAT(output, Catch::Matchers::ContainsSubstring("dtype"));
}
TEST_CASE("Tensor with custom precision", "[tensor]") {
Eigen::Tensor<float, 1> t(3);
t(0) = 1.23456789f;
t(1) = 2.3456789f;
t(2) = 3.456789f;
eigen_print::PrintOptions opts;
opts.precision = 2;
std::string output = capture_output([&] {
eigen_print::print(t, opts);
});
REQUIRE_THAT(output, Catch::Matchers::ContainsSubstring("[1.23, 2.35, 3.46]"));
}
TEST_CASE("Tensor with scientific notation", "[tensor]") {
Eigen::Tensor<float, 1> t(3);
t(0) = 1e-5f;
t(1) = 2e-4f;
t(2) = 3e-3f;
eigen_print::PrintOptions opts;
opts.scientific = true;
opts.precision = 2;
std::string output = capture_output([&] {
eigen_print::print(t, opts);
});
REQUIRE_THAT(output, Catch::Matchers::ContainsSubstring("e"));
}
TEST_CASE("Tensor with bool type", "[tensor]") {
Eigen::Tensor<bool, 2> t(2, 2);
t(0, 0) = true;
t(0, 1) = false;
t(1, 0) = false;
t(1, 1) = true;
std::string output = capture_output([&] {
eigen_print::print(t);
});
REQUIRE_THAT(output, Catch::Matchers::ContainsSubstring("true"));
REQUIRE_THAT(output, Catch::Matchers::ContainsSubstring("false"));
}
TEST_CASE("Tensor with complex numbers", "[tensor]") {
Eigen::Tensor<std::complex<double>, 1> t(2);
t(0) = std::complex<double>(1.0, 2.0);
t(1) = std::complex<double>(3.0, -4.0);
std::string output = capture_output([&] {
eigen_print::print(t);
});
REQUIRE_THAT(output, Catch::Matchers::ContainsSubstring("(1.0000+2.0000j)"));
REQUIRE_THAT(output, Catch::Matchers::ContainsSubstring("(3.0000-4.0000j)"));
}
TEST_CASE("Tensor with trimming", "[tensor]") {
Eigen::Tensor<float, 1> t(20);
for (int i = 0; i < 20; ++i) {
t(i) = static_cast<float>(i);
}
eigen_print::PrintOptions opts;
opts.threshold = 5;
opts.edge_items = 2;
std::string output = capture_output([&] {
eigen_print::print(t, opts);
});
REQUIRE_THAT(output, Catch::Matchers::ContainsSubstring("0, 1..., 18, 19"));
}
TEST_CASE("Global options work for tensors", "[tensor]") {
Eigen::Tensor<float, 2> t(3, 3);
for (int i = 0; i < 3; ++i) {
for (int j = 0; j < 3; ++j) {
t(i, j) = static_cast<float>(i * 3 + j);
}
}
eigen_print::PrintOptions default_opts = eigen_print::get_global_options();
eigen_print::PrintOptions new_opts;
new_opts.precision = 1;
new_opts.edge_items = 1;
new_opts.show_shape = true;
eigen_print::set_global_options(new_opts);
std::string output = capture_output([&] {
eigen_print::print(t);
});
eigen_print::set_global_options(default_opts);
REQUIRE_THAT(output, Catch::Matchers::ContainsSubstring("(3x3)"));
REQUIRE_THAT(output, Catch::Matchers::ContainsSubstring("0, 1"));
}