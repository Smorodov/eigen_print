#pragma once
#include <string>
namespace eigen_print {
struct PrintOptions {
int precision = 4;
int edge_items = 3;
int threshold = 7;
int linewidth = 80;
bool scientific = false;
bool show_shape = false;
bool show_dtype = false;
bool show_name = false;
bool sparse_as_dense = false;
std::string prefix = "tensor";
std::string name = "";
};
inline PrintOptions& get_global_options() {
static PrintOptions opts;
return opts;
}
inline void set_global_options(const PrintOptions& opts) {
get_global_options() = opts;
}
}