#include <iostream>
#include <memory>
#include <vector>
#include <concepts>
#include <limits>

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

template<Ordered T>
class Solution {
public:
    // Convert Pre-order Array to BST
    std::unique_ptr<TreeNode<T>> sortedArrayToBST(const std::vector<T>& nums) {
        if (nums.empty()) return nullptr;
        int index = 0;
        return build(nums, index, std::numeric_limits<T>::lowest(), std::numeric_limits<T>::max());
    }
    
    std::unique_ptr<TreeNode<T>> build(const std::vector<T>& nums, int& index, T lower_bound, T upper_bound) {
        // Base case: reached end of array or all elements have been processed
        if (index >= static_cast<int>(nums.size())) {
            return nullptr;
        }
        
        T val = nums[static_cast<size_t>(index)];
        
        // Check if the current value is within the valid BST range
        if (val <= lower_bound || val >= upper_bound) {
            return nullptr;
        }
        
        // Consume this element as we're using it for the current node
        index++;
        
        auto node = std::make_unique<TreeNode<T>>(val);
        
        // Left subtree: values must be less than current value
        node->left = build(nums, index, lower_bound, val);
        // Right subtree: values must be greater than current value
        node->right = build(nums, index, val, upper_bound);
        
        return node;
    }
    
    // Helper to print tree (Pre-order)
    void printTree(const std::unique_ptr<TreeNode<T>>& node) {
        if (!node) return;
        std::cout << node->val << " ";
        printTree(node->left);
        printTree(node->right);
    }
};

int main() {
    // Pre-order array: [10, 5, 1, 7, 15, 12, 20]
    // This represents a valid BST pre-order traversal
    std::vector<int> nums = {10, 5, 1, 7, 15, 12, 20};
    Solution<int> s;
    auto root = s.sortedArrayToBST(nums);
    
    std::cout << "BST Created (Pre-order): ";
    s.printTree(root);
    std::cout << std::endl;
    
    // root is automatically destroyed here. No leak.
    return 0;
}