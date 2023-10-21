#include <vector>
#include <iostream>

using namespace std;

void merge(vector<int> &nums, int lo, int mid, int hi){
    vector<int> temp(nums.size());
    for(int i= lo; i<=hi; i++){
        temp[i] = nums[i];
    }

    int i = lo, j = mid + 1;
    for(int p = lo; p<=hi; p++) {
        if(i == mid + 1){
            nums[p] = temp[j++];
        }else if(j == hi + 1){
            nums[p] = temp[i++];
        }else if(temp[i] < temp[j]){
            nums[p] = temp[i++];
        }else{
            nums[p] = temp[j++];
        }
    }
}

void MergeSort(vector<int> &nums, int left, int right){
    if(left == right) return;

    int mid = (left + right) / 2;
    MergeSort(nums, left, mid );
    MergeSort(nums, mid + 1, right);
    merge(nums, left, mid, right);

}

int main(){
    vector<int> nums = {3, 4, 1, 5, 12, 4, 0, 9, 6};
    MergeSort(nums, 0, nums.size()-1);

    for(auto i: nums){
        cout << i << " " <<endl;
    }
    return 0;
}