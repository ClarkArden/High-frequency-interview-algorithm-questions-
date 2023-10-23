#include <queue>
#include <vector>
#include <algorithm>
#include <iostream>


using namespace std;

namespace sort_ns{

bool cmp1(int a, int b){
    return a < b;      //升序
}

bool cmp2(int a, int b){
    return a > b;           //降序
}

void customsort(){
    int count = 0;
    vector<int> nums;
    while(count< 5){
        nums.emplace_back(rand() % 10);
        count++;
    }
    sort(nums.begin(), nums.end(), cmp1);
    for(int num:nums){
        cout<<num<<" ";
    }
    cout<<endl;

    sort(nums.begin(), nums.end(), cmp2);
    for(int num:nums){
        cout<<num<<" ";
    }
    cout<<endl;
}
}

namespace pq_ns{

struct cmp{
    bool operator()(const pair<int, int> &a, const pair<int, int> &b){
    
        if(a.first == b.first) return a.second < b.second;   //降序
        else return a.first > b.first;     // 升序
    }
};
void custompq(){
    priority_queue<pair<int,int>, vector<pair<int,int>>, cmp> pq;
    int count = 0;
    while(count<5){
        pq.push({rand()%10, rand()%10});
        count++;
    }

    while(!pq.empty()){
        auto k_v = pq.top();;
        pq.pop();
        cout<< "("<<k_v.first<<","<<k_v.second<<")"<<endl;
    }
}
}
void topK(){
    priority_queue<int, vector<int>, less<int>> big_pq;  // 大顶堆，默认, 降序
    priority_queue<int, vector<int>, greater<int>> small_pq; // 小顶堆，升序

    int count = 0;
    int k =2;
    while(count < 5){
        int num = rand() % 10;
        cout<< num << " ";
        big_pq.push(num);         //大顶堆求第k小的元素
        small_pq.push(num);        //小顶堆求第k大的元素
        if(big_pq.size() > k){
            big_pq.pop(); 
        }
        if(small_pq.size() > k){
            small_pq.pop(); 
        }
        count++;
    }
    cout<<endl;
    std::cout<< "第"<<k<<"大的元素为:" << small_pq.top() << endl;
    std::cout<< "第"<<k<<"小的元素为:" << big_pq.top() << endl;

}
int main(){
    topK();
    sort_ns::customsort();
    pq_ns::custompq();
    return 0;   
}