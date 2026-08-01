#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include <eigen_print/eigen_print.hpp>
#include <Eigen/Sparse>
#include "test_utils.hpp"
TEST_CASE("Sparse matrix printing basic", "[sparse]") {
Eigen::SparseMatrix<double> m(3, 3);
m.insert(0, 0) = 1.0;
m.insert(0, 2) = 2.0;
m.insert(1, 1) = 3.0;
m.insert(2, 0) = 4.0;
m.insert(2, 2) = 5.0;
m.makeCompressed();
std::string output = capture_output([&] {
eigen_print::print(m);
});
REQUIRE_THAT(output, Catch::Matchers::ContainsSubstring("tensor(sparse"));
REQUIRE_THAT(output, Catch::Matchers::ContainsSubstring("nnz=5"));
REQUIRE_THAT(output, Catch::Matchers::ContainsSubstring("(0, 0): 1"));
REQUIRE_THAT(output, Catch::Matchers::ContainsSubstring("(2, 2): 5"));
}
TEST_CASE("Sparse matrix printing as dense", "[sparse]") {
Eigen::SparseMatrix<double> m(3, 3);
m.insert(0, 0) = 1.0;
m.insert(1, 1) = 2.0;
m.insert(2, 2) = 3.0;
m.makeCompressed();
eigen_print::PrintOptions opts;
opts.sparse_as_dense = true;
std::string output = capture_output([&] {
eigen_print::print(m, opts);
});
REQUIRE_THAT(output, Catch::Matchers::ContainsSubstring("[[1, 0, 0]"));
REQUIRE_THAT(output, Catch::Matchers::ContainsSubstring("[0, 2, 0]"));
REQUIRE_THAT(output, Catch::Matchers::ContainsSubstring("[0, 0, 3]]"));
}
TEST_CASE("Sparse vector printing basic", "[sparse]") {
Eigen::SparseVector<double> v(5);
v.insert(0) = 1.0;
v.insert(2) = 3.0;
v.insert(4) = 5.0;
std::string output = capture_output([&] {
eigen_print::print(v);
});
REQUIRE_THAT(output, Catch::Matchers::ContainsSubstring("tensor(sparse"));
REQUIRE_THAT(output, Catch::Matchers::ContainsSubstring("nnz=3"));
REQUIRE_THAT(output, Catch::Matchers::ContainsSubstring("(0): 1"));
REQUIRE_THAT(output, Catch::Matchers::ContainsSubstring("(2): 3"));
REQUIRE_THAT(output, Catch::Matchers::ContainsSubstring("(4): 5"));
}
TEST_CASE("Sparse matrix with shape info", "[sparse]") {
Eigen::SparseMatrix<double> m(4, 5);
m.insert(1, 2) = 42.0;
m.makeCompressed();
eigen_print::PrintOptions opts;
opts.show_shape = true;
std::string output = capture_output([&] {
eigen_print::print(m, opts);
});
REQUIRE_THAT(output, Catch::Matchers::ContainsSubstring("tensor(sparse, 4x5"));
}
TEST_CASE("Sparse matrix with large nnz and trimming", "[sparse]") {
Eigen::SparseMatrix<double> m(20, 20);
for (int i = 0; i < 20; ++i) {
for (int j = 0; j < 20; ++j) {
if ((i + j) % 3 == 0) {
m.insert(i, j) = static_cast<double>(i * 20 + j);
}
}
}
m.makeCompressed();
eigen_print::PrintOptions opts;
opts.threshold = 30;
std::string output = capture_output([&] {
eigen_print::print(m, opts);
});
REQUIRE_THAT(output, Catch::Matchers::ContainsSubstring("more entries"));
}
TEST_CASE("Sparse matrix with different types", "[sparse]") {
Eigen::SparseMatrix<int> m(2, 2);
m.insert(0, 0) = 1;
m.insert(1, 1) = 2;
m.makeCompressed();
std::string output = capture_output([&] {
eigen_print::print(m);
});
REQUIRE_THAT(output, Catch::Matchers::ContainsSubstring("(0, 0): 1"));
REQUIRE_THAT(output, Catch::Matchers::ContainsSubstring("(1, 1): 2"));
REQUIRE_FALSE(output.find('.') != std::string::npos);
}