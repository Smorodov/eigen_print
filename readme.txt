
eigen_print
Библиотека для красивого вывода Eigen-объектов (матриц, тензоров, разреженных матриц) в стиле PyTorch/NumPy.
Особенности
• 
✅ PyTorch-подобный вывод с квадратными скобками и многоточием
• 
✅ Автоматическая обрезка больших массивов (как в NumPy/PyTorch)
• 
✅ Поддержка всех типов Eigen: матрицы, тензоры, разреженные матрицы
• 
✅ Различные типы данных: float, double, int, bool, complex
• 
✅ Глобальная конфигурация (как torch.set_printoptions)
• 
✅ Высокая производительность с использованием fmt
• 
✅ Header-only библиотека
• 
✅ C++20 совместимость
Требования
• 
C++20 или выше
• 
Eigen3 (любая версия с поддержкой Tensor)
• 
fmt библиотека
Установка
Через CMake (FetchContent)
cmake
Copy
Download
include(FetchContent)
FetchContent_Declare(
    eigen_print
    GIT_REPOSITORY https://github.com/your-repo/eigen_print.git
    GIT_TAG main
)
FetchContent_MakeAvailable(eigen_print)

target_link_libraries(your_target PRIVATE EigenPrint::eigen_print)
Ручная установка
1. 
Скопируйте папку include/eigen_print в ваш проект
2. 
Подключите заголовочный файл:
cpp
#include <eigen_print/eigen_print.hpp>
Сборка проекта
bash
mkdir build && cd build
cmake ..
make
Быстрый старт
cpp
#include <Eigen/Dense>
#include <eigen_print/eigen_print.hpp>

int main() {
    Eigen::MatrixXd m = Eigen::MatrixXd::Random(100, 100);
    eigen_print::print(m);
    return 0;
}
Вывод:
text
tensor([[-0.9345,  0.9681,  0.7927,  ...,  0.3993, -0.3191,  0.3993],
        [-0.2758, -0.5084,  0.2524,  ...,  0.6344,  0.3930,  0.0016],
        [ 0.7683,  0.9497, -0.1325,  ...,  0.1640,  0.0442, -0.5821],
        ...,
        [ 0.8749, -0.0508, -0.3854,  ...,  0.7756, -0.2179, -0.8909],
        [-0.0754,  0.8714, -0.6206,  ...,  0.7944,  0.4094,  0.8079],
        [ 0.0131, -0.8331, -0.0434,  ..., -0.2927, -0.7328, -0.7367]])
Основные функции
eigen_print::print()
Главная функция для вывода:
cpp
// Для матриц
template<typename Derived>
void print(const Eigen::DenseBase<Derived>& m,
           const PrintOptions& opts = get_global_options());

// Для тензоров
template<typename Derived>
void print(const Eigen::TensorBase<Derived>& t,
           const PrintOptions& opts = get_global_options());

// Для разреженных матриц
template<typename T>
void print(const Eigen::SparseMatrix<T>& m,
           const PrintOptions& opts = get_global_options());

// Для разреженных векторов
template<typename T>
void print(const Eigen::SparseVector<T>& v,
           const PrintOptions& opts = get_global_options());

// Для скаляров
template<typename T>
void print(const T& value,
           const PrintOptions& opts = get_global_options());
eigen_print::println()
То же самое, но добавляет перевод строки в конце:
cpp
eigen_print::println(matrix);
Форматирование вывода
Структура PrintOptions
cpp
struct PrintOptions {
    int precision = 4;              // Количество знаков после запятой
    int edge_items = 3;             // Элементов с каждого края
    int threshold = 7;              // Порог для применения обрезки
    int linewidth = 80;             // Максимальная ширина строки (зарезервировано)
    bool scientific = false;        // Научный формат (экспоненциальный)
    bool show_shape = false;        // Показывать размерность
    bool show_dtype = false;        // Показывать тип данных
    bool show_name = false;         // Показывать имя переменной
    bool sparse_as_dense = false;   // Выводить разреженную как плотную
    std::string prefix = "tensor";  // Префикс перед данными
    std::string name = "";          // Имя переменной (если show_name=true)
};
Примеры использования
cpp
Eigen::MatrixXd m = Eigen::MatrixXd::Random(10, 10);

eigen_print::PrintOptions opts;
opts.precision = 2;
opts.edge_items = 4;
opts.show_shape = true;
opts.show_dtype = true;
opts.prefix = "matrix";

eigen_print::print(m, opts);
Вывод:
text
matrix(10x10), dtype=d([[-0.93, 0.69, 0.54, 0.59..., -0.23, 0.35, 0.67, 0.66],
                        [-0.28, -0.5, -0.54, -0.24..., -0.3, -0.68, 0.6, -0.25],
                        ...])
Типы данных
Поддерживаются следующие типы:
• 
float, double — числа с плавающей точкой
• 
int, long — целые числа
• 
bool — логический тип (true/false)
• 
std::complex<float>, std::complex<double> — комплексные числа
Форматирование типов
cpp
// Целые числа
Eigen::Matrix<int, 3, 3> m_int;
eigen_print::print(m_int);
// tensor([[1, 2, 3], [4, 5, 6], [7, 8, 9]])

// Числа с плавающей точкой
Eigen::Matrix<double, 3, 3> m_double;
eigen_print::print(m_double);
// tensor([[1.0000, 2.0000, 3.0000], ...])

// Логический тип
Eigen::Matrix<bool, 2, 2> m_bool;
eigen_print::print(m_bool);
// tensor([[true, false], [false, true]])

// Комплексные числа
Eigen::Matrix<std::complex<double>, 2, 2> m_complex;
eigen_print::print(m_complex);
// tensor([[(1.0000+2.0000j), (3.0000-4.0000j)], ...])
Матрицы и векторы
Базовый вывод
cpp
#include <Eigen/Dense>
#include <eigen_print/eigen_print.hpp>

Eigen::Matrix3d m;
m << 1, 2, 3,
     4, 5, 6,
     7, 8, 9;

eigen_print::print(m);
Вывод:
text
tensor([[1, 2, 3],
        [4, 5, 6],
        [7, 8, 9]])
Обрезка больших матриц
cpp
Eigen::MatrixXd big = Eigen::MatrixXd::Random(100, 100);
eigen_print::print(big);
Вывод (автоматическая обрезка):
text
tensor([[-0.9345,  0.9681,  0.7927,  ...,  0.3993, -0.3191,  0.3993],
        [-0.2758, -0.5084,  0.2524,  ...,  0.6344,  0.3930,  0.0016],
        [ 0.7683,  0.9497, -0.1325,  ...,  0.1640,  0.0442, -0.5821],
        ...,
        [ 0.8749, -0.0508, -0.3854,  ...,  0.7756, -0.2179, -0.8909],
        [-0.0754,  0.8714, -0.6206,  ...,  0.7944,  0.4094,  0.8079],
        [ 0.0131, -0.8331, -0.0434,  ..., -0.2927, -0.7328, -0.7367]])
Настройка обрезки
cpp
eigen_print::PrintOptions opts;
opts.edge_items = 4;   // Показывать по 4 элемента с каждого края
opts.threshold = 10;   // Обрезать если размер > 10

eigen_print::print(big, opts);
Научный формат
cpp
Eigen::MatrixXd m(2, 2);
m << 1e-10, 2e-5,
     3e-4, 4e-3;

eigen_print::PrintOptions opts;
opts.scientific = true;
opts.precision = 2;

eigen_print::print(m, opts);
Вывод:
text
tensor([[1.00e-10, 2.00e-05],
        [3.00e-04, 4.00e-03]])
Тензоры
Подключение:
cpp
#include <unsupported/Eigen/CXX11/Tensor>
#include <eigen_print/eigen_print.hpp>
1D Тензор (вектор)
cpp
Eigen::Tensor<float, 1> t(10);
for (int i = 0; i < 10; ++i) {
    t(i) = static_cast<float>(i) * 0.5f;
}
eigen_print::print(t);
Вывод:
text
tensor([0, 0.5, 1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5])
2D Тензор (матрица)
cpp
Eigen::Tensor<float, 2> t(3, 4);
for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 4; ++j) {
        t(i, j) = static_cast<float>(i * 4 + j);
    }
}
eigen_print::print(t);
Вывод:
text
tensor([[0, 1, 2, 3],
        [4, 5, 6, 7],
        [8, 9, 10, 11]])
3D Тензор
cpp
Eigen::Tensor<float, 3> t(2, 3, 4);
// ... заполнение ...
eigen_print::print(t);
Вывод:
text
tensor([[[0, 1, 2, 3],
         [4, 5, 6, 7],
         [8, 9, 10, 11]],
        [[12, 13, 14, 15],
         [16, 17, 18, 19],
         [20, 21, 22, 23]]])
Обрезка тензоров
Обрезка применяется ко всем размерностям независимо:
cpp
Eigen::Tensor<float, 4> t(8, 8, 8, 8);
// ... заполнение ...
eigen_print::print(t);
Вывод:
text
tensor([[[[0, 1, 2, ..., 5, 6, 7],
          [1, 2, 3, ..., 6, 7, 8],
          ...,
          [6, 7, 8, ..., 11, 12, 13],
          [7, 8, 9, ..., 12, 13, 14]],
         ...]])
Вывод размеров тензора
cpp
eigen_print::PrintOptions opts;
opts.show_shape = true;
eigen_print::print(t, opts);
Вывод:
text
tensor(8x8x8x8) [[[[0, 1, 2, ..., 5, 6, 7], ...]]]
Разреженные матрицы
Базовый вывод
cpp
#include <Eigen/Sparse>
#include <eigen_print/eigen_print.hpp>

Eigen::SparseMatrix<double> m(3, 3);
m.insert(0, 0) = 1.0;
m.insert(0, 2) = 2.0;
m.insert(1, 1) = 3.0;
m.insert(2, 0) = 4.0;
m.insert(2, 2) = 5.0;
m.makeCompressed();

eigen_print::print(m);
Вывод:
text
tensor(sparse, nnz=5)
(0, 0): 1
(0, 2): 2
(1, 1): 3
(2, 0): 4
(2, 2): 5
Вывод как плотная матрица
cpp
eigen_print::PrintOptions opts;
opts.sparse_as_dense = true;
eigen_print::print(m, opts);
Вывод:
text
tensor([[1, 0, 2],
        [0, 3, 0],
        [4, 0, 5]])
Разреженные векторы
cpp
Eigen::SparseVector<double> v(5);
v.insert(0) = 1.0;
v.insert(2) = 3.0;
v.insert(4) = 5.0;

eigen_print::print(v);
Вывод:
text
tensor(sparse, nnz=3)
(0): 1
(2): 3
(4): 5
Глобальные настройки
Установка глобальных опций
cpp
// Установка глобальных опций (аналог torch.set_printoptions)
eigen_print::set_global_options({
    .precision = 6,
    .edge_items = 4,
    .threshold = 10,
    .linewidth = 100,
    .scientific = false,
    .show_shape = true,
    .show_dtype = true
});
Получение текущих опций
cpp
eigen_print::PrintOptions opts = eigen_print::get_global_options();
std::cout << "Precision: " << opts.precision << std::endl;
Пример с глобальными опциями
cpp
// Устанавливаем глобальные настройки
eigen_print::set_global_options({
    .precision = 2,
    .edge_items = 2,
    .show_shape = true
});

// Теперь все вызовы используют эти настройки
Eigen::MatrixXd m = Eigen::MatrixXd::Random(100, 100);
eigen_print::print(m);  // Использует глобальные настройки
Полный справочник API
Пространство имён
cpp
namespace eigen_print {
    // Функции вывода
    template<typename Derived>
    void print(const Eigen::DenseBase<Derived>& m,
               const PrintOptions& opts = get_global_options());

    template<typename Derived>
    void print(const Eigen::TensorBase<Derived>& t,
               const PrintOptions& opts = get_global_options());

    template<typename T>
    void print(const Eigen::SparseMatrix<T>& m,
               const PrintOptions& opts = get_global_options());

    template<typename T>
    void print(const Eigen::SparseVector<T>& v,
               const PrintOptions& opts = get_global_options());

    template<typename T>
    void print(const T& value,
               const PrintOptions& opts = get_global_options());

    template<typename Derived>
    void println(const Derived& m,
                 const PrintOptions& opts = get_global_options());

    // Глобальные настройки
    PrintOptions& get_global_options();
    void set_global_options(const PrintOptions& opts);
}
Структура PrintOptions
cpp
struct PrintOptions {
    int precision = 4;              // Количество знаков после запятой
    int edge_items = 3;             // Элементов с каждого края
    int threshold = 7;              // Порог для применения обрезки
    int linewidth = 80;             // Максимальная ширина строки
    bool scientific = false;        // Научный формат
    bool show_shape = false;        // Показывать размерность
    bool show_dtype = false;        // Показывать тип данных
    bool show_name = false;         // Показывать имя переменной
    bool sparse_as_dense = false;   // Разреженную как плотную
    std::string prefix = "tensor";  // Префикс
    std::string name = "";          // Имя переменной
};
Примеры
Пример 1: Матрицы
cpp
#include <iostream>
#include <Eigen/Dense>
#include <eigen_print/eigen_print.hpp>

int main() {
    Eigen::Matrix3d small;
    small << 1.0, 2.0, 3.0,
             4.0, 5.0, 6.0,
             7.0, 8.0, 9.0;

    std::cout << "Small matrix:\n";
    eigen_print::print(small);

    Eigen::MatrixXd big = Eigen::MatrixXd::Random(100, 100);
    std::cout << "\nLarge matrix:\n";
    eigen_print::print(big);

    Eigen::MatrixXd sci(2, 2);
    sci << 1e-10, 2e-5,
           3e-4, 4e-3;

    eigen_print::PrintOptions opts;
    opts.scientific = true;
    opts.precision = 2;

    std::cout << "\nScientific notation:\n";
    eigen_print::print(sci, opts);

    return 0;
}
Пример 2: Тензоры
cpp
#include <iostream>
#include <unsupported/Eigen/CXX11/Tensor>
#include <eigen_print/eigen_print.hpp>

int main() {
    Eigen::Tensor<float, 2> t(5, 6);
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 6; ++j) {
            t(i, j) = static_cast<float>(i * 10 + j);
        }
    }

    eigen_print::PrintOptions opts;
    opts.show_shape = true;
    opts.show_dtype = true;
    opts.precision = 1;

    eigen_print::print(t, opts);

    return 0;
}
Пример 3: Разреженные матрицы
cpp
#include <iostream>
#include <Eigen/Sparse>
#include <eigen_print/eigen_print.hpp>

int main() {
    Eigen::SparseMatrix<double> m(5, 5);
    for (int i = 0; i < 5; ++i) {
        m.insert(i, i) = static_cast<double>(i + 1);
        if (i < 4) {
            m.insert(i, i + 1) = static_cast<double>(i + 1) * 0.5;
        }
    }
    m.makeCompressed();

    eigen_print::print(m);

    eigen_print::PrintOptions opts;
    opts.sparse_as_dense = true;
    opts.precision = 1;

    eigen_print::print(m, opts);

    return 0;
}
Пример 4: Глобальные настройки
cpp
#include <iostream>
#include <Eigen/Dense>
#include <eigen_print/eigen_print.hpp>

int main() {
    Eigen::MatrixXd m = Eigen::MatrixXd::Random(100, 100);

    eigen_print::set_global_options({
        .precision = 2,
        .edge_items = 4,
        .show_shape = true,
        .show_dtype = true
    });

    eigen_print::print(m);

    eigen_print::print(m, {
        .precision = 6,
        .edge_items = 2
    });

    eigen_print::set_global_options(eigen_print::PrintOptions{});

    return 0;
}
Пример 5: Комплексные числа и bool
cpp
#include <iostream>
#include <Eigen/Dense>
#include <eigen_print/eigen_print.hpp>

int main() {
    Eigen::Matrix<std::complex<double>, 2, 2> m_complex;
    m_complex << std::complex<double>(1.0, 2.0),
                 std::complex<double>(3.0, -4.0),
                 std::complex<double>(-5.0, 6.0),
                 std::complex<double>(7.0, 8.0);

    eigen_print::print(m_complex);

    Eigen::Matrix<bool, 3, 3> m_bool;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            m_bool(i, j) = (i == j);
        }
    }

    eigen_print::print(m_bool);

    return 0;
}
Советы и рекомендации
Для отладки
cpp
// Быстрый вывод с размерами
eigen_print::print(matrix, {.show_shape = true});

// Или глобально
eigen_print::set_global_options({.show_shape = true, .precision = 4});
Для больших данных
cpp
// Увеличить edge_items чтобы видеть больше данных
eigen_print::print(big_matrix, {.edge_items = 5});

// Или отключить обрезку
eigen_print::print(big_matrix, {.threshold = 0});
Для научных вычислений
cpp
// Научный формат с высокой точностью
eigen_print::print(matrix, {
    .scientific = true,
    .precision = 8
});
Лицензия
MIT License
Вклад в развитие
Библиотека открыта для улучшений. Предложения и pull requests приветствуются!
 