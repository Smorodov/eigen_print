#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include <eigen_print/eigen_print.hpp>
#include <Eigen/Dense>
#include "test_utils.hpp"
TEST_CASE("Matrix printing basic functionality", "[matrix]") {
Eigen::Matrix3d m;
m << 1, 2, 3,
4, 5, 6,
7, 8, 9;
std::string output = capture_output([&] {
eigen_print::print(m);
});
REQUIRE_THAT(output, Catch::Matchers::ContainsSubstring("tensor"));
REQUIRE_THAT(output, Catch::Matchers::ContainsSubstring("[1, 2, 3]"));
REQUIRE_THAT(output, Catch::Matchers::ContainsSubstring("[4, 5, 6]"));
REQUIRE_THAT(output, Catch::Matchers::ContainsSubstring("[7, 8, 9]"));
}
TEST_CASE("Matrix printing with custom options", "[matrix]") {
Eigen::MatrixXd m(10, 10);
for (int i = 0; i < 10; ++i) {
for (int j = 0; j < 10; ++j) {
m(i, j) = static_cast<double>(i * 10 + j);
}
}
eigen_print::PrintOptions opts;
opts.precision = 6;
opts.edge_items = 2;
opts.show_shape = true;
std::string output = capture_output([&] {
eigen_print::print(m, opts);
});
REQUIRE_THAT(output, Catch::Matchers::ContainsSubstring("tensor(10x10)"));
}
TEST_CASE("Matrix printing with trimming", "[matrix]") {
Eigen::MatrixXd m(100, 100);
for (int i = 0; i < 100; ++i) {
for (int j = 0; j < 100; ++j) {
m(i, j) = static_cast<double>(i * 100 + j);
}
}
std::string output = capture_output([&] {
eigen_print::print(m);
});
REQUIRE_THAT(output, Catch::Matchers::ContainsSubstring("..."));
}
TEST_CASE("Matrix printing with scientific notation", "[matrix]") {
Eigen::MatrixXd m(2, 2);
m << 1e-10, 2e-5,
3e-4, 4e-3;
eigen_print::PrintOptions opts;
opts.scientific = true;
opts.precision = 2;
std::string output = capture_output([&] {
eigen_print::print(m, opts);
});
REQUIRE_THAT(output, Catch::Matchers::ContainsSubstring("e"));
}
TEST_CASE("Matrix printing with different types", "[matrix]") {
Eigen::Matrix<int, 3, 3> m_int;
m_int << 1, 2, 3,
4, 5, 6,
7, 8, 9;
std::string output = capture_output([&] {
eigen_print::print(m_int);
});
REQUIRE_THAT(output, Catch::Matchers::ContainsSubstring("[1, 2, 3]"));
REQUIRE_FALSE(output.find('.') != std::string::npos);
}
TEST_CASE("Matrix printing with complex numbers", "[matrix]") {
Eigen::Matrix<std::complex<double>, 2, 2> m;
m << std::complex<double>(1.0, 2.0), std::complex<double>(3.0, -4.0),
std::complex<double>(-5.0, 6.0), std::complex<double>(7.0, 8.0);
std::string output = capture_output([&] {
eigen_print::print(m);
});
REQUIRE_THAT(output, Catch::Matchers::ContainsSubstring("(1.0000+2.0000j)"));
REQUIRE_THAT(output, Catch::Matchers::ContainsSubstring("(3.0000-4.0000j)"));
}
TEST_CASE("Matrix printing with bool type", "[matrix]") {
Eigen::Matrix<bool, 2, 2> m;
m << true, false,
false, true;
std::string output = capture_output([&] {
eigen_print::print(m);
});
REQUIRE_THAT(output, Catch::Matchers::ContainsSubstring("true"));
REQUIRE_THAT(output, Catch::Matchers::ContainsSubstring("false"));
}
TEST_CASE("Global options work correctly", "[matrix]") {
Eigen::Matrix3d m = Eigen::Matrix3d::Identity();
eigen_print::PrintOptions default_opts = eigen_print::get_global_options();
eigen_print::PrintOptions new_opts;
new_opts.precision = 2;
new_opts.edge_items = 1;
eigen_print::set_global_options(new_opts);
std::string output = capture_output([&] {
eigen_print::print(m);
});
eigen_print::set_global_options(default_opts);
REQUIRE_THAT(output, Catch::Matchers::ContainsSubstring("1, 0"));
}