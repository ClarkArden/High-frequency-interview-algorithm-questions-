#include <vector>
#include <iostream>

using namespace std;

void swap(vector<int> &nums, int i, int j) {
    int temp = nums[i];
    nums[i] = nums[j];
    nums[j] = temp;
}
int partition(vector<int> &nums, int left, int right) {
    int i = left, j = right;
    while(i<j){
        while(i<j && nums[j] >= nums[left]) j--;
        while(i<j && nums[i] <= nums[left]) i++;
        swap(nums, i, j);
    }
    swap(nums, left, i);
    return i;

}

void QuickSort(vector<int> &nums, int lo, int hi){
    if(lo > hi) return;

    int pivot = partition(nums, lo, hi);

    QuickSort(nums, lo, pivot -1);
    QuickSort(nums, pivot + 1, hi);
}

int main(){
    vector<int> nums = {3, 4, 1, 5, 12, 4, 0, 9, 6};
    QuickSort(nums, 0, nums.size()-1);

    for(auto i: nums){
        cout << i << " " <<endl;
    }
    return 0;
}