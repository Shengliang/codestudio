#include <iostream>
#include <vector>
#include <algorithm>

int search(const std::vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (nums[mid] == target) {
            return mid;
        }

        // Determine which half is sorted
        if (nums[left] <= nums[mid]) { // Left half is sorted
            if (target >= nums[left] && target < nums[mid]) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        } else { // Right half is sorted
            if (target > nums[mid] && target <= nums[right]) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
    }
    return -1; // Target not found
}

int main() {
    std::vector<int> nums1 = {4, 5, 6, 7, 0, 1, 2};
    int target1 = 0;
    std::cout << "Target " << target1 << " found at index: " << search(nums1, target1) << std::endl;

    std::vector<int> nums2 = {4, 5, 6, 7, 0, 1, 2};
    int target2 = 3;
    std::cout << "Target " << target2 << " found at index: " << search(nums2, target2) << std::endl;

    std::vector<int> nums3 = {1};
    int target3 = 0;
    std::cout << "Target " << target3 << " found at index: " << search(nums3, target3) << std::endl;
    
    std::vector<int> nums4 = {1};
    int target4 = 1;
    std::cout << "Target " << target4 << " found at index: " << search(nums4, target4) << std::endl;

    std::vector<int> nums5 = {3, 1};
    int target5 = 1;
    std::cout << "Target " << target5 << " found at index: " << search(nums5, target5) << std::endl;

    return 0;
}