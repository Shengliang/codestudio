#include <iostream>
#include <optional>
#include <variant>
#include <string_view>
#include <tuple>
#include <vector>
#include <functional>

// ============================================================================
// C++17 FEATURES SHOWCASE - IMPROVED VERSION
// ============================================================================

// 1. STRUCTURED BINDINGS
// ============================================================================
void structured_bindings_example() {
    std::cout << "\n=== 1. Structured Bindings ===\n";
    
    // Unpacking pairs - useful for key-value data
    std::pair<int, std::string> user_data = {123, "Alice"};
    auto [user_id, username] = user_data;
    std::cout << "User " << user_id << ": " << username << "\n";
    
    // Unpacking tuples - useful for multiple return values
    auto rgb_color = std::make_tuple(255, 128, 64);
    auto [red, green, blue] = rgb_color;
    std::cout << "RGB Color: (" << red << ", " << green << ", " << blue << ")\n";
    
    // Unpacking arrays - useful for coordinate data
    int coordinates[3] = {10, 20, 30};
    auto [x, y, z] = coordinates;
    std::cout << "Coordinates: (" << x << ", " << y << ", " << z << ")\n";
}

// 2. IF/SWITCH WITH INITIALIZERS
// ============================================================================
int process_user_input(int input) {
    // Initialize variable in if condition - better scoping
    if (int threshold = 100; input > threshold) {
        std::cout << "Input " << input << " exceeds threshold " << threshold << "\n";
        return 1;
    } else {
        std::cout << "Input " << input << " is within acceptable range\n";
        return 0;
    }
}

void if_initializer_example() {
    std::cout << "\n=== 2. If with Initializer ===\n";
    process_user_input(150);
    process_user_input(50);
}

// Switch with initializer - determining operation based on input
std::string interpret_grade(int score) {
    switch (int grade_threshold = score / 10; grade_threshold) {
        case 10:
        case 9:   // 90-99
            return "A (Excellent)";
        case 8:   // 80-89
            return "B (Good)";
        case 7:   // 70-79
            return "C (Satisfactory)";
        case 6:   // 60-69
            return "D (Passing)";
        default:  // Below 60
            return "F (Failing)";
    }
}

void switch_initializer_example() {
    std::cout << "\n=== 2b. Switch with Initializer ===\n";
    std::cout << "Score 95: " << interpret_grade(95) << "\n";
    std::cout << "Score 75: " << interpret_grade(75) << "\n";
    std::cout << "Score 55: " << interpret_grade(55) << "\n";
}

// 3. CONSTEXPR IF (Compile-time conditionals)
// ============================================================================
template<typename T>
void print_type_info(T value) {
    if constexpr (std::is_integral_v<T>) {
        std::cout << "Integral type with value: " << value << "\n";
    } else if constexpr (std::is_floating_point_v<T>) {
        std::cout << "Floating point type with value: " << value << "\n";
    } else if constexpr (std::is_same_v<T, std::string>) {
        std::cout << "String type with value: " << value << "\n";
    } else {
        std::cout << "Other type\n";
    }
}

void constexpr_if_example() {
    std::cout << "\n=== 3. Constexpr If ===\n";
    print_type_info(42);
    print_type_info(3.14);
    print_type_info(std::string("C++17"));
}

// 4. FOLD EXPRESSIONS
// ============================================================================
// Sum of all arguments
template<typename... Args>
auto sum_all(Args... args) {
    return (... + args);
}

// Product of all arguments
template<typename... Args>
auto multiply_all(Args... args) {
    return (args * ...);
}

// Check if all values are positive (practical use case)
template<typename... Args>
bool all_positive(Args... args) {
    return (... && (args > 0));
}

void fold_expressions_example() {
    std::cout << "\n=== 4. Fold Expressions ===\n";
    std::cout << "Sum(1,2,3,4,5): " << sum_all(1, 2, 3, 4, 5) << "\n";
    std::cout << "Product(2,3,4): " << multiply_all(2, 3, 4) << "\n";
    std::cout << "All positive(1,2,3): " << (all_positive(1, 2, 3) ? "true" : "false") << "\n";
    std::cout << "All positive(1,-2,3): " << (all_positive(1, -2, 3) ? "true" : "false") << "\n";
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
        std::cout << "10 / 2 = " << result.value() << "\n";
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
    
    // A variant can hold different types (type-safe union)
    std::variant<int, std::string, double> response;
    
    response = 42;
    std::cout << "Response (int): " << std::get<int>(response) << "\n";
    
    response = std::string("Success");
    std::cout << "Response (string): " << std::get<std::string>(response) << "\n";
    
    response = 3.14159;
    std::cout << "Response (double): " << std::get<double>(response) << "\n";
    
    // Visitor pattern for type-safe access
    auto print_response = [](auto&& val) {
        std::cout << "Current value: " << val << "\n";
    };
    std::visit(print_response, response);
}

// 7. STD::STRING_VIEW
// ============================================================================
void string_view_example() {
    std::cout << "\n=== 7. std::string_view ===\n";
    
    std::string message = "Hello, C++17!";
    std::string_view view = message;  // Non-owning view
    
    std::cout << "Full view: " << view << "\n";
    std::cout << "Substring view: " << view.substr(0, 5) << "\n";
    std::cout << "View size: " << view.size() << "\n";
}

// 8. DEDUCTION GUIDES (Class Template Argument Deduction - CTAD)
// ============================================================================
template<typename T>
struct Container {
    T value;
    int count;
    
    Container(T v, int c) : value(v), count(c) {}
    
    void display() const {
        std::cout << "Value: " << value << ", Count: " << count << "\n";
    }
};

// Deduction guide
template<typename T>
Container(T, int) -> Container<T>;

void ctad_example() {
    std::cout << "\n=== 8. Class Template Argument Deduction ===\n";
    
    // No need to specify template arguments - deduced automatically
    Container c1{42, 5};
    c1.display();
    
    Container c2{3.14, 10};
    c2.display();
    
    Container c3{std::string("Hello"), 3};
    c3.display();
}

// 9. STRUCTURED BINDING WITH CONTAINERS
// ============================================================================
void container_bindings() {
    std::cout << "\n=== 9. Structured Bindings with Containers ===\n";
    
    // Dictionary-like structure with structured bindings
    std::vector<std::pair<int, std::string>> items = {
        {1, "apple"},
        {2, "banana"},
        {3, "cherry"}
    };
    
    for (auto [id, name] : items) {
        std::cout << "ID " << id << ": " << name << "\n";
    }
}

// 10. BYTE TYPE
// ============================================================================
void byte_example() {
    std::cout << "\n=== 10. std::byte ===\n";
    
    std::byte b1{0xFF};
    std::byte b2{0x0F};
    
    std::cout << "Byte type for binary data manipulation\n";
    std::cout << "b1 and b2 are distinct byte types (not chars)\n";
}

// 11. NESTED NAMESPACES
// ============================================================================
namespace App::Module::SubModule {
    void show_info() {
        std::cout << "\n=== 11. Nested Namespaces ===\n";
        std::cout << "In nested namespace: App::Module::SubModule\n";
        std::cout << "No need for separate namespace declarations\n";
    }
}

// 12. INLINE VARIABLES
// ============================================================================
namespace config {
    inline int max_users = 100;  // Can be defined in header files safely
    inline double version = 1.0;
}

// Main function
int main() {
    std::cout << "=== C++17 FEATURES SHOWCASE ===\n";
    
    // Run examples
    structured_bindings_example();
    if_initializer_example();
    switch_initializer_example();
    
    constexpr_if_example();
    
    fold_expressions_example();
    
    optional_example();
    variant_example();
    string_view_example();
    ctad_example();
    container_bindings();
    byte_example();
    
    App::Module::SubModule::show_info();
    
    std::cout << "\n=== 12. Inline Variables ===\n";
    std::cout << "Max users: " << config::max_users << "\n";
    std::cout << "Version: " << config::version << "\n";
    
    std::cout << "\n=== End of C++17 Features ===\n";
    
    return 0;
}
