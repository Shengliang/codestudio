#include <iostream>
#include <vector>
#include <algorithm> // For std::max, std::lower_bound, std::distance
#include <functional> // For std::greater

// Function to find the peak index in a mountain array
int findPeakIndex(const std::vector<int>& arr) {
    int left = 0;
    int right = arr.size() - 1;

    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] < arr[mid + 1]) {
            // We are on the ascending part, peak is to the right
            left = mid + 1;
        } else {
            // We are on the descending part or at the peak
            // Peak could be mid or to the left
            right = mid;
        }
    }
    return left; // 'left' will be the peak index
}

// Function to perform binary search in an ascending sorted array using std::lower_bound
int binarySearchAscending(const std::vector<int>& arr, int target, int left, int right) {
    auto it = std::lower_bound(arr.begin() + left, arr.begin() + right + 1, target);
    if (it != arr.begin() + right + 1 && *it == target) {
        return std::distance(arr.begin(), it);
    }
    return -1; // Target not found
}

// Function to perform binary search in a descending sorted array using std::lower_bound with a custom comparator
int binarySearchDescending(const std::vector<int>& arr, int target, int left, int right) {
    // std::lower_bound finds the first element not less than value.
    // For a descending array, "not less than" means equal or greater than the target.
    // We need to find the first element that is <= target.
    // Using std::greater<int>() reverses the comparison, so it effectively finds
    // the first element x such that !(x > target), i.e., x <= target.
    auto it = std::lower_bound(arr.begin() + left, arr.begin() + right + 1, target, std::greater<int>());
    if (it != arr.begin() + right + 1 && *it == target) {
        return std::distance(arr.begin(), it);
    }
    return -1; // Target not found
}

// Main function to find target in a mountain array
int findTargetInMountainArray(const std::vector<int>& arr, int target) {
    if (arr.empty()) {
        return -1;
    }

    int peakIndex = findPeakIndex(arr);

    // Search in the left (ascending) part including the peak
    int result = binarySearchAscending(arr, target, 0, peakIndex);
    if (result != -1) {
        return result;
    }

    // Search in the right (descending) part
    return binarySearchDescending(arr, target, peakIndex + 1, arr.size() - 1);
}


int main() {
    std::vector<int> mountainArr = {1, 3, 5, 8, 7, 4, 2};
    int target = 4; // Example target

    int index = findTargetInMountainArray(mountainArr, target);

    if (index != -1) {
        std::cout << "Target " << target << " found at index " << index << std::endl;
    } else {
        std::cout << "Target " << target << " not found in the array." << std::endl;
    }

    // Test cases
    std::vector<int> mountainArr2 = {0, 1, 2, 4, 2, 1};
    int target2 = 3;
    int index2 = findTargetInMountainArray(mountainArr2, target2);
    if (index2 != -1) {
        std::cout << "Target " << target2 << " found at index " << index2 << std::endl;
    } else {
        std::cout << "Target " << target2 << " not found in the array." << std::endl;
    }

    std::vector<int> mountainArr3 = {1, 2, 3, 4, 5, 3, 1};
    int target3 = 5;
    int index3 = findTargetInMountainArray(mountainArr3, target3);
    if (index3 != -1) {
        std::cout << "Target " << target3 << " found at index " << index3 << std::endl;
    } else {
        std::cout << "Target " << target3 << " not found in the array." << std::endl;
    }

    std::vector<int> mountainArr4 = {1, 2, 3, 4, 5}; // Technically a mountain array (peak at end)
    int target4 = 1;
    int index4 = findTargetInMountainArray(mountainArr4, target4);
    if (index4 != -1) {
        std::cout << "Target " << target4 << " found at index " << index4 << std::endl;
    } else {
        std::cout << "Target " << target4 << " not found in the array." << std::endl;
    }

    std::vector<int> mountainArr5 = {5, 4, 3, 2, 1}; // Technically a mountain array (peak at beginning)
    int target5 = 3;
    int index5 = findTargetInMountainArray(mountainArr5, target5);
    if (index5 != -1) {
        std::cout << "Target " << target5 << " found at index " << index5 << std::endl;
    } else {
        std::cout << "Target " << target5 << " not found in the array." << std::endl;
    }

    return 0;
}