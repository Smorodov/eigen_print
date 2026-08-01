#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include <eigen_print/eigen_print.hpp>
#include <Eigen/Dense>
#include "test_utils.hpp"
TEST_CASE("Scalar printing works", "[print]") {
std::string output = capture_output([&] {
eigen_print::print(42);
eigen_print::print(3.14159);
eigen_print::print(true);
});
REQUIRE_THAT(output, Catch::Matchers::ContainsSubstring("42"));
REQUIRE_THAT(output, Catch::Matchers::ContainsSubstring("3.1416"));
REQUIRE_THAT(output, Catch::Matchers::ContainsSubstring("true"));
}
TEST_CASE("Print with custom precision", "[print]") {
double value = 1.23456789;
eigen_print::PrintOptions opts;
opts.precision = 2;
std::string output = capture_output([&] {
eigen_print::print(value, opts);
});
REQUIRE_THAT(output, Catch::Matchers::ContainsSubstring("1.23"));
}
TEST_CASE("Print with scientific notation", "[print]") {
double value = 1.234e-5;
eigen_print::PrintOptions opts;
opts.scientific = true;
opts.precision = 3;
std::string output = capture_output([&] {
eigen_print::print(value, opts);
});
REQUIRE_THAT(output, Catch::Matchers::ContainsSubstring("e"));
}
TEST_CASE("Print NaN and inf values", "[print]") {
double nan_val = std::numeric_limits<double>::quiet_NaN();
double inf_val = std::numeric_limits<double>::infinity();
double neg_inf_val = -std::numeric_limits<double>::infinity();
std::string output = capture_output([&] {
eigen_print::print(nan_val);
eigen_print::print(inf_val);
eigen_print::print(neg_inf_val);
});
REQUIRE_THAT(output, Catch::Matchers::ContainsSubstring("nan"));
REQUIRE_THAT(output, Catch::Matchers::ContainsSubstring("inf"));
REQUIRE_THAT(output, Catch::Matchers::ContainsSubstring("-inf"));
}
TEST_CASE("Printing with name and shape", "[print]") {
Eigen::Matrix3d m = Eigen::Matrix3d::Identity();
eigen_print::PrintOptions opts;
opts.show_name = true;
opts.show_shape = true;
opts.name = "I";
std::string output = capture_output([&] {
eigen_print::print(m, opts);
});
REQUIRE_THAT(output, Catch::Matchers::ContainsSubstring("tensor(3x3)"));
REQUIRE_THAT(output, Catch::Matchers::ContainsSubstring("I ="));
}
TEST_CASE("Printing with prefix", "[print]") {
Eigen::Matrix2d m;
m << 1, 2, 3, 4;
eigen_print::PrintOptions opts;
opts.prefix = "matrix";
std::string output = capture_output([&] {
eigen_print::print(m, opts);
});
REQUIRE_THAT(output, Catch::Matchers::ContainsSubstring("matrix"));
}