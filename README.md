# codestudio

A comprehensive collection of C++ feature demonstrations across multiple C++ standards (C++17, C++20, C++23, and C++26).

## File Overview

### C++ Feature Showcases

#### `cpp17_features.cpp`
Comprehensive showcase of C++17 features including:
- **Structured Bindings** - Unpack tuples, pairs, and arrays into individual variables
- **If/Switch with Initializers** - Initialize variables directly in conditions
- **Constexpr If** - Compile-time conditional compilation for type-specific code
- **Fold Expressions** - Variadic template operations with binary operators
- **std::optional** - Safe way to represent optional values without null pointers
- **std::variant** - Type-safe union replacing void pointers
- **std::string_view** - Non-owning string references for zero-copy operations
- **Class Template Argument Deduction (CTAD)** - Automatically deduce template types
- **Structured Bindings with Containers** - Loop over elements with unpacking
- **std::byte** - Distinct type for binary data manipulation
- **Nested Namespaces** - `namespace A::B::C` syntax simplification
- **Inline Variables** - Variables safely definable in header files

**Compile:** `g++ -std=c++17 -o cpp17_features cpp17_features.cpp`

#### `cpp20_features.cpp`
Comprehensive showcase of C++20 features including:
- **Concepts** - Type constraints and template requirements
- **Requires Clause** - Complex type checking at compile-time
- **Designated Initializers** - Initialize struct members by name
- **Spaceship Operator (<=>)** - Three-way comparison in one operator
- **Ranges Library** - Composable view pipelines and range-based algorithms
- **std::span** - Non-owning array views (replacing raw pointers)
- **std::jthread** - Thread that automatically joins on destruction
- **Constexpr Improvements** - `constexpr` for strings and vectors
- **std::source_location** - Get file/line info at runtime for debugging
- **Aggregate Initialization** - Improved struct initialization
- **char8_t** - Dedicated UTF-8 character type
- **Container.find()** - Check membership with ranges library

**Compile:** `g++ -std=c++20 -o cpp20_features cpp20_features.cpp`

#### `cpp23_features.cpp`
Showcase of C++23 features including:
- **if consteval** - Compile-time vs runtime branch selection
- **Deducing this** - Explicit object parameter for advanced member functions
- **Range-based for with Initializer** - Initialize variables alongside iteration
- **Explicit This Parameter** - Method chaining with self-reference
- **Multidimensional Subscript Operator** - Better matrix/grid indexing
- **Auto in Lambdas** - Generic lambda parameters with auto
- **Static Lambdas** - No-capture lambdas convertible to function pointers
- **Expanded Constexpr** - More compile-time computation capabilities
- **std::source_location** - File/line information at runtime
- **Improved Structured Bindings** - With references and more flexibility
- **Size Type Improvements** - Better container size handling
- **Template Improvements** - Better concept integration

**Compile:** `g++ -std=c++23 -o cpp23_features cpp23_features.cpp`

#### `cpp26_features.cpp`
Showcase of proposed C++26 features (still in development):
- **Contracts** - Preconditions, postconditions, and runtime assertions
- **Pattern Matching** - More elegant conditional logic with `inspect`
- **Reflection (std::meta)** - Runtime type information capabilities
- **Expected<T, E>** - Type-safe error handling without exceptions
- **Enhanced Constexpr** - More compile-time computation capabilities
- **User-Defined Literals** - Better custom literal suffix support
- **Improved Memory Management** - Enhanced lifetime safety guarantees
- **Advanced Ranges** - Additional range adapters and algorithms
- **Lifetime Safety** - Bounds-checked container access
- **Template Metaprogramming** - Better compile-time programming features
- **Coroutines** - Enhanced coroutine utilities (under development)
- **Attributes** - Expanded attribute support for static analysis

**Compile:** `g++ -std=c++23 -o cpp26_features cpp26_features.cpp` (C++26 features compiled with C++23 as closest available)

**Note:** C++26 is still in development. Features shown are proposals and may change before finalization.

### Other Files

- `build_bst.cpp` - Binary Search Tree building implementation
- `validate_bst.cpp` - Binary Search Tree validation
- `find_target_in_mountain_array.cpp` - Array search algorithm
- `find_target_in_rotated_sorted_array.cpp` - Rotated array search algorithm
- `code.cpp` - Additional code examples

## How to Use

1. Choose a C++ standard version you want to explore
2. Compile using the appropriate flag:
   - C++17: `-std=c++17`
   - C++20: `-std=c++20`
   - C++23: `-std=c++23`
3. Run the compiled executable to see feature demonstrations

## Requirements

- GCC or Clang compiler with C++17 or later support
- Linux/Unix environment (or WSL on Windows)

## License

This project is open source and available for learning and educational purposes.
