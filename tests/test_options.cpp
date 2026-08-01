#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include <eigen_print/eigen_print.hpp>
#include "test_utils.hpp"
TEST_CASE("Global options default values", "[options]") {
eigen_print::PrintOptions opts = eigen_print::get_global_options();
REQUIRE(opts.precision == 4);
REQUIRE(opts.edge_items == 3);
REQUIRE(opts.threshold == 7);
REQUIRE(opts.linewidth == 80);
REQUIRE(opts.scientific == false);
REQUIRE(opts.show_shape == false);
REQUIRE(opts.show_dtype == false);
REQUIRE(opts.show_name == false);
REQUIRE(opts.sparse_as_dense == false);
REQUIRE(opts.prefix == "tensor");
REQUIRE(opts.name == "");
}
TEST_CASE("Global options can be set and retrieved", "[options]") {
eigen_print::PrintOptions original = eigen_print::get_global_options();
eigen_print::PrintOptions new_opts;
new_opts.precision = 6;
new_opts.edge_items = 5;
new_opts.threshold = 10;
new_opts.linewidth = 100;
new_opts.scientific = true;
new_opts.show_shape = true;
new_opts.show_dtype = true;
new_opts.show_name = true;
new_opts.sparse_as_dense = true;
new_opts.prefix = "array";
new_opts.name = "my_tensor";
eigen_print::set_global_options(new_opts);
eigen_print::PrintOptions retrieved = eigen_print::get_global_options();
REQUIRE(retrieved.precision == 6);
REQUIRE(retrieved.edge_items == 5);
REQUIRE(retrieved.threshold == 10);
REQUIRE(retrieved.linewidth == 100);
REQUIRE(retrieved.scientific == true);
REQUIRE(retrieved.show_shape == true);
REQUIRE(retrieved.show_dtype == true);
REQUIRE(retrieved.show_name == true);
REQUIRE(retrieved.sparse_as_dense == true);
REQUIRE(retrieved.prefix == "array");
REQUIRE(retrieved.name == "my_tensor");
eigen_print::set_global_options(original);
}
TEST_CASE("Options can be passed by value to print", "[options]") {
Eigen::Matrix3d m = Eigen::Matrix3d::Identity();
eigen_print::PrintOptions opts;
opts.precision = 2;
opts.prefix = "custom";
std::string output = capture_output([&] {
eigen_print::print(m, opts);
});
REQUIRE_THAT(output, Catch::Matchers::ContainsSubstring("custom"));
REQUIRE_THAT(output, Catch::Matchers::ContainsSubstring("1, 0"));
}