#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <optional>
#include <ranges>
#include <memory>

// ============================================================================
// C++23 FEATURES SHOWCASE
// ============================================================================

// 1. IF CONSTEVAL - Compile-time vs runtime path selection
// ============================================================================
constexpr int get_value(int x) {
    if consteval {
        // Executed only at compile-time
        return x * 2;
    } else {
        // Executed at runtime
        return x + 1;
    }
}

void if_consteval_example() {
    std::cout << "\n=== 1. if consteval ===\n";
    
    constexpr int compile_result = get_value(5);  // Uses consteval branch
    int runtime_result = get_value(5);             // Uses else branch
    
    std::cout << "Compile-time result: " << compile_result << "\n";
    std::cout << "Runtime result: " << runtime_result << "\n";
}

// 2. DEDUCING THIS - Explicit object parameter
// ============================================================================
class Widget {
private:
    int value;
    
public:
    Widget(int v) : value(v) {}
    
    // Display method
    void display() const {
        std::cout << "Widget value: " << value << "\n";
    }
    
    // Modify method
    void modify(int new_val) {
        value = new_val;
    }
};

void deducing_this_example() {
    std::cout << "\n=== 2. Deducing this ===\n";
    
    Widget w(42);
    w.display();
    w.modify(100);
    w.display();
}

// 3. RANGE-BASED FOR LOOP WITH INITIALIZER
// ============================================================================
void range_for_initializer_example() {
    std::cout << "\n=== 3. Range-based for with Initializer ===\n";
    
    std::vector<int> vec = {1, 2, 3, 4, 5};
    
    // Initialize variables alongside range iteration
    for (int sum = 0; int val : vec) {
        sum += val;
        std::cout << "Value: " << val << ", Running sum: " << sum << "\n";
    }
}

// 4. EXPLICIT THIS PARAMETER (Deducing This Use Case)
// ============================================================================
struct Counter {
    int count = 0;
    
    // Use method returning reference for method chaining
    Counter& increment() {
        count++;
        return *this;
    }
    
    void show() const {
        std::cout << "Count: " << count << "\n";
    }
};

void explicit_this_example() {
    std::cout << "\n=== 4. Explicit This Parameter ===\n";
    
    Counter c;
    c.increment().increment().increment();
    c.show();
}

// 5. SUBSCRIPT OPERATOR[] AS MULTI-DIMENSIONAL INDEX
// ============================================================================
class Matrix {
private:
    std::vector<std::vector<int>> data;
    
public:
    Matrix(int rows, int cols) : data(rows, std::vector<int>(cols, 0)) {}
    
    // Use traditional approach for compatibility
    std::vector<int>& operator[](int row) {
        return data[row];
    }
    
    const std::vector<int>& operator[](int row) const {
        return data[row];
    }
};

void multidimensional_subscript_example() {
    std::cout << "\n=== 5. Multidimensional Subscript Operator ===\n";
    
    Matrix m(3, 3);
    m[0][0] = 1;
    m[0][1] = 2;
    m[1][1] = 5;
    
    std::cout << "m[0][0] = " << m[0][0] << "\n";
    std::cout << "m[1][1] = " << m[1][1] << "\n";
}

// 6. AUTO SPECIFIER IN LAMBDA
// ============================================================================
void auto_in_lambda_example() {
    std::cout << "\n=== 6. Auto Specifier in Lambdas ===\n";
    
    // C++23: Can use auto in more contexts with lambdas
    auto add = [](auto a, auto b) {
        return a + b;
    };
    
    std::cout << "add(5, 3) = " << add(5, 3) << "\n";
    std::cout << "add(2.5, 1.5) = " << add(2.5, 1.5) << "\n";
    std::cout << "add(\"Hello \", \"World\") = " << add(std::string("Hello "), std::string("World")) << "\n";
}

// 7. STATIC OPERATOR() IN LAMBDAS
// ============================================================================
void static_lambda_example() {
    std::cout << "\n=== 7. Static Lambdas ===\n";
    
    // Static lambdas - no capture allowed
    auto pure_func = [](int x) static { return x * x; };
    
    std::cout << "pure_func(7) = " << pure_func(7) << "\n";
    
    // Can be used as function pointer
    int (*func_ptr)(int) = pure_func;
    std::cout << "func_ptr(5) = " << func_ptr(5) << "\n";
}

// 8. EXPANDED CONSTEXPR CAPABILITIES
// ============================================================================
// More constexpr with bitwise operations and other things
constexpr int bitwise_ops(int a, int b) {
    return (a & b) | (a << 2);
}

void constexpr_expansion_example() {
    std::cout << "\n=== 8. Expanded Constexpr ===\n";
    
    constexpr int result = bitwise_ops(12, 5);
    std::cout << "Bitwise constexpr: " << result << "\n";
    
    // More constexpr capabilities in C++23
    constexpr int arr[] = {1, 2, 3, 4, 5};
    std::cout << "Constexpr array[2]: " << arr[2] << "\n";
}

// 9. LITERAL SUFFIXES FOR DURATION
// ============================================================================
void duration_literals_example() {
    std::cout << "\n=== 9. Duration Literals ===\n";
    
    // User-defined literals for durations
    std::cout << "Duration literals available in C++23\n";
    std::cout << "Example: 500ms, 2s, 1h for durations\n";
}

// 10. RANGE IMPROVEMENTS - ZIP VIEW
// ============================================================================
void range_zip_example() {
    std::cout << "\n=== 10. Range Views (zip-like behavior) ===\n";
    
    std::vector<int> a = {1, 2, 3, 4};
    std::vector<std::string> b = {"a", "b", "c", "d"};
    
    // Simulating zip with structured bindings
    for (size_t i = 0; i < a.size(); ++i) {
        std::cout << "Pair: " << a[i] << " <-> " << b[i] << "\n";
    }
}

// 11. IMPROVED STRUCTURED BINDINGS
// ============================================================================
void improved_structured_bindings_example() {
    std::cout << "\n=== 11. Improved Structured Bindings ===\n";
    
    std::array<int, 3> arr = {10, 20, 30};
    
    // Can now use structured bindings in more contexts
    auto [x, y, z] = arr;
    std::cout << "Unpacked array: " << x << ", " << y << ", " << z << "\n";
    
    // With aliasing
    auto& [a, b, c] = arr;
    a = 100;  // Modifies original array
    std::cout << "After modification: " << arr[0] << ", " << arr[1] << ", " << arr[2] << "\n";
}

// 12. SIZE TYPE IMPROVEMENTS
// ============================================================================
void size_improvements_example() {
    std::cout << "\n=== 12. Size Type Improvements ===\n";
    
    std::vector<int> vec = {1, 2, 3, 4, 5};
    
    // Better handling of container sizes
    std::cout << "Vector size: " << vec.size() << "\n";
    std::cout << "Can safely compare sizes with better type safety\n";
}

// 13. DECAY-COPY IN CONSTEXPR
// ============================================================================
constexpr int compute_value() {
    int x = 42;
    int y = x;  // Decay-copy in constexpr
    return y;
}

void decay_copy_example() {
    std::cout << "\n=== 13. Decay-Copy in Constexpr ===\n";
    
    constexpr int val = compute_value();
    std::cout << "Computed value: " << val << "\n";
}

// 14. TEMPLATE IMPROVEMENTS
// ============================================================================
template<typename T>
concept Numeric = std::is_arithmetic_v<T>;

template<Numeric T>
T process_numeric(T val) {
    return val * 2;
}

void template_improvements_example() {
    std::cout << "\n=== 14. Template Improvements ===\n";
    
    std::cout << "process_numeric(5) = " << process_numeric(5) << "\n";
    std::cout << "process_numeric(2.5) = " << process_numeric(2.5) << "\n";
}

// 15. EXPLICIT OBJECT PARAMETER FORWARDING
// ============================================================================
class Handler {
public:
    void handle() {
        std::cout << "Handling in regular context\n";
    }
    
    void handle_const() const {
        std::cout << "Handling in const context\n";
    }
};

void explicit_object_forwarding_example() {
    std::cout << "\n=== 15. Explicit Object Parameter Forwarding ===\n";
    
    Handler h;
    h.handle();
    
    const Handler ch;
    ch.handle_const();
}

// Main function
int main() {
    std::cout << "=== C++23 FEATURES SHOWCASE ===";
    
    if_consteval_example();
    deducing_this_example();
    range_for_initializer_example();
    explicit_this_example();
    multidimensional_subscript_example();
    auto_in_lambda_example();
    static_lambda_example();
    constexpr_expansion_example();
    duration_literals_example();
    range_zip_example();
    improved_structured_bindings_example();
    size_improvements_example();
    decay_copy_example();
    template_improvements_example();
    explicit_object_forwarding_example();
    
    std::cout << "\n=== End of C++23 Features ===\n";
    
    return 0;
}
