#include <iostream>
#include <memory>
#include <stack>
#include <limits>
#include <concepts>
#include <string> // Added for std::string test

// C++20 Concept to ensure value type is ordered and supports comparison
template<typename T>
concept Ordered = requires(T a, T b) {
    { a < b } -> std::convertible_to<bool>;
    { a > b } -> std::convertible_to<bool>;
    { a <= b } -> std::convertible_to<bool>; // Explicitly require operator<=
};

template<typename T>
struct TreeNode {
    T val;
    // Using std::unique_ptr for automatic memory management (RAII)
    // No manual delete needed. Prevents memory leaks.
    std::unique_ptr<TreeNode<T>> left;
    std::unique_ptr<TreeNode<T>> right;

    TreeNode(const T& x) : val(x), left(nullptr), right(nullptr) {}
};

template<Ordered T> // Apply the Ordered concept to the Solution class template parameter
class Solution {
public:
    // Validate if the tree is a Binary Search Tree
    // Uses raw pointer for traversal to avoid ownership transfer issues
    bool isValidBST(const std::unique_ptr<TreeNode<T>>& root) {
        std::stack<TreeNode<T>*> stack;
        TreeNode<T>* curr = root.get();
        TreeNode<T>* prev = nullptr;
        
        while (curr != nullptr || !stack.empty()) {
            while (curr != nullptr) {
                stack.push(curr);
                curr = curr->left.get();
            }
            
            curr = stack.top();
            stack.pop();
            
            // Validation logic: In-order traversal must be strictly increasing
            if (prev != nullptr && curr->val <= prev->val) {
                return false;
            }
            
            prev = curr;
            curr = curr->right.get();
        }
        return true;
    }
};

int main() {
    // --- Test with int ---
    // Modern C++: Use std::make_unique to prevent memory leaks automatically
    auto root_int_valid = std::make_unique<TreeNode<int>>(2);
    root_int_valid->left = std::make_unique<TreeNode<int>>(1);
    root_int_valid->right = std::make_unique<TreeNode<int>>(3);

    Solution<int> s_int;
    bool result_int_valid = s_int.isValidBST(root_int_valid);
    
    // C++23 std::print would be nice here, falling back to iostream
    std::cout << "Is Valid BST (int - valid): " << (result_int_valid ? "Yes" : "No") << std::endl;

    auto root_int_invalid = std::make_unique<TreeNode<int>>(5);
    root_int_invalid->left = std::make_unique<TreeNode<int>>(1);
    root_int_invalid->right = std::make_unique<TreeNode<int>>(4);
    root_int_invalid->right->left = std::make_unique<TreeNode<int>>(3);
    root_int_invalid->right->right = std::make_unique<TreeNode<int>>(6); // Invalid: 4 has right child 6

    bool result_int_invalid = s_int.isValidBST(root_int_invalid);
    std::cout << "Is Valid BST (int - invalid): " << (result_int_invalid ? "Yes" : "No") << std::endl;

    // --- Test with std::string ---
    // Valid string BST
    auto root_string_valid = std::make_unique<TreeNode<std::string>>("banana");
    root_string_valid->left = std::make_unique<TreeNode<std::string>>("apple");
    root_string_valid->right = std::make_unique<TreeNode<std::string>>("orange");

    Solution<std::string> s_string;
    bool result_string_valid = s_string.isValidBST(root_string_valid);
    std::cout << "Is Valid BST (string - valid): " << (result_string_valid ? "Yes" : "No") << std::endl;

    // Invalid string BST
    auto root_string_invalid = std::make_unique<TreeNode<std::string>>("grape");
    root_string_invalid->left = std::make_unique<TreeNode<std::string>>("kiwi"); // Invalid: "kiwi" > "grape"
    root_string_invalid->right = std::make_unique<TreeNode<std::string>>("apple"); // Invalid: "apple" < "grape"

    bool result_string_invalid = s_string.isValidBST(root_string_invalid);
    std::cout << "Is Valid BST (string - invalid): " << (result_string_invalid ? "Yes" : "No") << std::endl;
    
    // root is automatically destroyed here. No leak.
    return 0;
}