#include <iostream>
#include <optional>
#include <variant>
#include <string_view>
#include <tuple>
#include <vector>
#include <functional>

// ============================================================================
// C++17 FEATURES SHOWCASE
// ============================================================================

// 1. STRUCTURED BINDINGS
// ============================================================================
void structured_bindings_example() {
    std::cout << "\n=== 1. Structured Bindings ===\n";
    
    // Unpacking pairs
    std::pair<int, std::string> p = {42, "hello"};
    auto [num, str] = p;
    std::cout << "num: " << num << ", str: " << str << "\n";
    
    // Unpacking tuples
    auto [a, b, c] = std::make_tuple(1, 2.5, "world");
    std::cout << "a: " << a << ", b: " << b << ", c: " << c << "\n";
    
    // Unpacking arrays
    int arr[3] = {10, 20, 30};
    auto [x, y, z] = arr;
    std::cout << "array: " << x << ", " << y << ", " << z << "\n";
}

// 2. IF/SWITCH WITH INITIALIZERS
// ============================================================================
void if_initializer_example() {
    std::cout << "\n=== 2. If/Switch with Initializers ===\n";
    
    // Initialize variable in if condition
    if (int value = 42; value > 40) {
        std::cout << "Value " << value << " is greater than 40\n";
    }
    
    // Switch with initializer
    switch (int x = 2; x) {
        case 1:
            std::cout << "One\n";
            break;
        case 2:
            std::cout << "Two\n";
            break;
        default:
            std::cout << "Other\n";
    }
}

// 3. CONSTEXPR IF (Compile-time conditionals)
// ============================================================================
template<typename T>
void constexpr_if_example(T value) {
    if constexpr (std::is_integral_v<T>) {
        std::cout << "Integral type: " << value << "\n";
    } else if constexpr (std::is_floating_point_v<T>) {
        std::cout << "Floating point type: " << value << "\n";
    } else {
        std::cout << "Other type\n";
    }
}

// 4. FOLD EXPRESSIONS
// ============================================================================
// Sum of all arguments (left fold)
template<typename... Args>
auto sum_all(Args... args) {
    return (... + args);  // Left fold: ((((0 + a) + b) + c) + ...)
}

// Product of all arguments (right fold)
template<typename... Args>
auto multiply_all(Args... args) {
    return (args * ...);  // Right fold: (a * (b * (c * ...)))
}

// 5. STD::OPTIONAL
// ============================================================================
std::optional<int> divide(int a, int b) {
    if (b == 0) {
        return std::nullopt;  // Return "nothing"
    }
    return a / b;
}

void optional_example() {
    std::cout << "\n=== 5. std::optional ===\n";
    
    auto result = divide(10, 2);
    if (result.has_value()) {
        std::cout << "Result: " << result.value() << "\n";
    }
    
    auto error = divide(10, 0);
    if (!error) {
        std::cout << "Division by zero detected\n";
    }
}

// 6. STD::VARIANT
// ============================================================================
void variant_example() {
    std::cout << "\n=== 6. std::variant ===\n";
    
    std::variant<int, std::string, double> var;
    
    var = 42;
    std::cout << "int: " << std::get<int>(var) << "\n";
    
    var = std::string("hello");
    std::cout << "string: " << std::get<std::string>(var) << "\n";
    
    var = 3.14;
    std::cout << "double: " << std::get<double>(var) << "\n";
    
    // Visitor pattern
    auto visitor = [](auto&& arg) {
        std::cout << "Visited: " << arg << "\n";
    };
    std::visit(visitor, var);
}

// 7. STD::STRING_VIEW
// ============================================================================
void string_view_example() {
    std::cout << "\n=== 7. std::string_view ===\n";
    
    std::string str = "Hello, World!";
    std::string_view view = str;  // Non-owning view
    
    std::cout << "Full view: " << view << "\n";
    std::cout << "Substring view: " << view.substr(0, 5) << "\n";
    std::cout << "Size: " << view.size() << "\n";
}

// 8. DEDUCTION GUIDES (Class Template Argument Deduction - CTAD)
// ============================================================================
template<typename T>
struct Pair {
    T first;
    T second;
    Pair(T a, T b) : first(a), second(b) {}
};

// Deduction guide to allow different types
template<typename T, typename U>
Pair(T, U) -> Pair<std::common_type_t<T, U>>;

void ctad_example() {
    std::cout << "\n=== 8. Class Template Argument Deduction ===\n";
    
    // No need to specify template arguments explicitly
    Pair p1{1, 2};
    std::cout << "Pair: " << p1.first << ", " << p1.second << "\n";
}

// 9. STRUCTURED BINDING WITH ARRAYS IN CONTAINERS
// ============================================================================
void container_bindings() {
    std::cout << "\n=== 9. Structured Bindings with Containers ===\n";
    
    std::vector<std::pair<int, std::string>> items = {
        {1, "one"},
        {2, "two"},
        {3, "three"}
    };
    
    for (auto [num, str] : items) {
        std::cout << num << " -> " << str << "\n";
    }
}

// 10. BYTE TYPE
// ============================================================================
void byte_example() {
    std::cout << "\n=== 10. std::byte ===\n";
    
    std::byte b1{0xFF};
    std::byte b2{0x0F};
    
    std::cout << "Byte operations supported\n";
    // std::byte is a distinct type for byte manipulation
}

// 11. NESTED NAMESPACES
// ============================================================================
namespace A::B::C {
    void nested_func() {
        std::cout << "\n=== 11. Nested Namespaces ===\n";
        std::cout << "In nested namespace A::B::C\n";
    }
}

// 12. INLINE VARIABLES
// ============================================================================
namespace globals {
    inline int global_var = 42;  // Can be defined in header files safely
}

// Main function
int main() {
    std::cout << "=== C++17 FEATURES SHOWCASE ===";
    
    // Run examples
    structured_bindings_example();
    if_initializer_example();
    
    std::cout << "\n=== 3. Constexpr If ===\n";
    constexpr_if_example(42);
    constexpr_if_example(3.14);
    
    std::cout << "\n=== 4. Fold Expressions ===\n";
    std::cout << "Sum(1,2,3,4,5): " << sum_all(1, 2, 3, 4, 5) << "\n";
    std::cout << "Product(2,3,4): " << multiply_all(2, 3, 4) << "\n";
    
    optional_example();
    variant_example();
    string_view_example();
    ctad_example();
    container_bindings();
    byte_example();
    
    A::B::C::nested_func();
    
    std::cout << "\n=== 12. Inline Variables ===\n";
    std::cout << "Global var: " << globals::global_var << "\n";
    
    std::cout << "\n=== End of C++17 Features ===\n";
    
    return 0;
}
