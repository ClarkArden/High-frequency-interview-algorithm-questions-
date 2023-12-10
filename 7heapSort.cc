#include <iostream>
#include <vector>
using namespace std;

void heapfy(vector<int> &a, int start, int end){
    // 建立父节点和子节点索引
    int father = start;
    int son = 2 * father + 1;
    while(son <= end){              // 子节点在指定范围内才做比较
        if(son + 1 <= end &&  a[son] < a[son+1]){  // 先比较两个子节点，选择最大的
            son++;
        }
        if(a[father] > a[son]){      // 如果父节点大于子节点代表调整完毕，直接跳出函数
            return;
        }else{                          // 否则交换父子内容再继续子节点和孙节点比较
            swap(a[father], a[son]);
            father = son;
            son = 2 * father + 1;
        }
    }
}

void heapSort(vector<int> &a){
    int len = a.size();                                   // 初始化，构建最大堆，i从最后一个父节点开始调整
    for(int i = len / 2 -1 ; i >= 0; i--){
        heapfy(a, i, len-1);
    }                                                     // 固定最大值到数组最后，然后再调整堆，使其满足堆的属性
    for(int i = len -1; i >= 0; i--){
        swap(a[0], a[i]);
        heapfy(a, 0, i-1);
    }
}

int main(){
    vector<int> vec = {2,7,2,9,1,3,5,4,6,7};
    heapSort(vec);
    for(auto val: vec){
        cout<<val<<" ";
    }
    cout<<endl;
}