#include <iostream>
#include <concepts>
#include <ranges>
#include <vector>
#include <string>
#include <compare>
#include <thread>
#include <chrono>
#include <source_location>
#include <span>
#include <array>

// ============================================================================
// C++20 FEATURES SHOWCASE
// ============================================================================

// 1. CONCEPTS - Type constraints
// ============================================================================
// Define a concept for integral types
template<typename T>
concept Integral = std::is_integral_v<T>;

// Define a concept for types with specific operations
template<typename T>
concept Addable = requires(T a, T b) {
    { a + b } -> std::convertible_to<T>;
};

// Use concept in function
template<Integral T>
T add_integers(T a, T b) {
    return a + b;
}

// Use multiple concepts
template<Addable T>
T add_values(T a, T b) {
    return a + b;
}

void concepts_example() {
    std::cout << "\n=== 1. Concepts ===\n";
    std::cout << "Add integers: " << add_integers(5, 3) << "\n";
    std::cout << "Add values: " << add_values(2.5, 1.5) << "\n";
    // add_integers(2.5, 1.5);  // Compile error - concept not satisfied
}

// 2. REQUIRES CLAUSE
// ============================================================================
template<typename T>
requires std::is_floating_point_v<T>
void print_float(T value) {
    std::cout << "Float value: " << value << "\n";
}

// Complex requires clause
template<typename T>
requires requires(T t) {
    { t.size() } -> std::convertible_to<size_t>;
    { t[0] };
}
void print_container_info(T& container) {
    std::cout << "Container size: " << container.size() << "\n";
}

void requires_clause_example() {
    std::cout << "\n=== 2. Requires Clause ===\n";
    print_float(3.14);
    std::vector<int> vec = {1, 2, 3};
    print_container_info(vec);
}

// 3. DESIGNATED INITIALIZERS
// ============================================================================
struct Point {
    int x;
    int y;
    std::string label;
};

struct Person {
    std::string name;
    int age;
    std::string email;
};

void designated_initializers_example() {
    std::cout << "\n=== 3. Designated Initializers ===\n";
    
    // Initialize by member name
    Point p = {.x = 10, .y = 20, .label = "origin"};
    std::cout << "Point: (" << p.x << ", " << p.y << ") - " << p.label << "\n";
    
    Person person = {.name = "Alice", .age = 30, .email = "alice@example.com"};
    std::cout << "Person: " << person.name << ", age " << person.age << "\n";
}

// 4. THREE-WAY COMPARISON OPERATOR (SPACESHIP OPERATOR)
// ============================================================================
struct Rectangle {
    double width;
    double height;
    
    // Spaceship operator: returns std::strong_ordering
    auto operator<=>(const Rectangle& other) const {
        auto area_cmp = (width * height) <=> (other.width * other.height);
        if (area_cmp != 0) return area_cmp;
        return width <=> other.width;
    }
    
    bool operator==(const Rectangle& other) const = default;
};

void spaceship_operator_example() {
    std::cout << "\n=== 4. Spaceship Operator (<=>)===\n";
    
    Rectangle r1{5.0, 4.0};  // area = 20
    Rectangle r2{4.0, 4.0};  // area = 16
    Rectangle r3{5.0, 4.0};  // area = 20
    
    if (r1 > r2) {
        std::cout << "r1 is larger than r2\n";
    }
    if (r1 == r3) {
        std::cout << "r1 equals r3\n";
    }
    if (r1 <=> r2 > 0) {
        std::cout << "r1 <=> r2 returns positive (r1 > r2)\n";
    }
}

// 5. RANGES LIBRARY
// ============================================================================
void ranges_example() {
    std::cout << "\n=== 5. Ranges Library ===\n";
    
    std::vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // Using ranges - filter even numbers
    auto even_nums = nums 
        | std::views::filter([](int n) { return n % 2 == 0; })
        | std::views::transform([](int n) { return n * n; });
    
    std::cout << "Even numbers squared: ";
    for (int n : even_nums) {
        std::cout << n << " ";
    }
    std::cout << "\n";
    
    // Using range-based algorithms with transform_view
    auto squared_view = nums | std::views::transform([](int n) { return n * n; });
    
    std::cout << "All numbers squared: ";
    for (int n : squared_view) {
        std::cout << n << " ";
    }
    std::cout << "\n";
}

// 6. STD::SPAN - Non-owning array view
// ============================================================================
void process_array(std::span<const int> data) {
    std::cout << "Span size: " << data.size() << "\n";
    std::cout << "Elements: ";
    for (int val : data) {
        std::cout << val << " ";
    }
    std::cout << "\n";
}

void span_example() {
    std::cout << "\n=== 6. std::span ===\n";
    
    // From vector
    std::vector<int> vec = {1, 2, 3, 4, 5};
    process_array(vec);
    
    // From array
    int arr[] = {10, 20, 30};
    process_array(arr);
    
    // Subspan
    std::span<const int> sub = std::span(vec).subspan(1, 3);
    std::cout << "Subspan (1, 3): ";
    for (int val : sub) {
        std::cout << val << " ";
    }
    std::cout << "\n";
}

// 7. STD::JTHREAD - Joinable thread
// ============================================================================
void thread_worker(int id) {
    std::cout << "Thread " << id << " started\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "Thread " << id << " finished\n";
}

void jthread_example() {
    std::cout << "\n=== 7. std::jthread (Joinable Thread) ===\n";
    
    {
        // jthread automatically joins in destructor
        std::jthread t1(thread_worker, 1);
        std::jthread t2(thread_worker, 2);
        std::cout << "Main thread continues...\n";
        // Threads automatically join when going out of scope
    }
    std::cout << "All threads finished\n";
}

// 8. CONSTEXPR IMPROVEMENTS
// ============================================================================
// constexpr std::string (C++20)
constexpr std::string make_string() {
    return "Hello from constexpr";
}

// constexpr std::vector (C++20)
constexpr int sum_constexpr(std::span<const int> nums) {
    int sum = 0;
    for (int n : nums) {
        sum += n;
    }
    return sum;
}

void constexpr_improvements_example() {
    std::cout << "\n=== 8. Constexpr Improvements ===\n";
    
    constexpr int arr[] = {1, 2, 3, 4, 5};
    constexpr int result = sum_constexpr(arr);
    std::cout << "Constexpr sum: " << result << "\n";
    
    auto str = make_string();
    std::cout << "Constexpr string: " << str << "\n";
}

// 9. STD::SOURCE_LOCATION - Get caller information
// ============================================================================
void log_message(const std::string& msg, 
                 const std::source_location& loc = std::source_location::current()) {
    std::cout << "[" << loc.file_name() << ":" << loc.line() 
              << "] " << msg << "\n";
}

void source_location_example() {
    std::cout << "\n=== 9. std::source_location ===\n";
    log_message("This is a log message");
}

// 10. AGGREGATE INITIALIZATION WITH PRIVATE MEMBERS
// ============================================================================
struct Aggregate {
    int x;
    int y;
    int z = 10;  // Default member initializer
};

void aggregate_example() {
    std::cout << "\n=== 10. Aggregate Initialization ===\n";
    
    Aggregate agg{.x = 5, .y = 15};
    std::cout << "Aggregate initialized: x=" << agg.x << ", y=" << agg.y << "\n";
}

// 11. CHAR8_T - UTF-8 character type
// ============================================================================
void char8t_example() {
    std::cout << "\n=== 11. char8_t (UTF-8) ===\n";
    
    // Explicit UTF-8 literal
    const char8_t* utf8_str = u8"Hello UTF-8";
    std::cout << "UTF-8 support available (char8_t type exists)\n";
}

// 12. CONTAINS METHOD FOR ASSOCIATIVE CONTAINERS
// ============================================================================
void contains_example() {
    std::cout << "\n=== 12. Container.contains() ===\n";
    
    std::vector<int> vec = {1, 2, 3, 4, 5};
    
    // Check if element exists using std::find from ranges
    if (std::ranges::find(vec, 3) != vec.end()) {
        std::cout << "Vector contains 3\n";
    }
}

// Main function
int main() {
    std::cout << "=== C++20 FEATURES SHOWCASE ===";
    
    concepts_example();
    requires_clause_example();
    designated_initializers_example();
    spaceship_operator_example();
    ranges_example();
    span_example();
    jthread_example();
    constexpr_improvements_example();
    source_location_example();
    aggregate_example();
    char8t_example();
    contains_example();
    
    std::cout << "\n=== End of C++20 Features ===\n";
    
    return 0;
}
