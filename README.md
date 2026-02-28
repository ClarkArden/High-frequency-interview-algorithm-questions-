# High-frequency interview algorithm questions 

## 1. 合并有序链表
#### 题目描述：
讲两个有序链表合并为一个新的有序链表
```C++
输入：1->2->4 , 1->3->4
输出：1->1->2->3->4->4
```
#### 算法思路:
1. 将链表1和链表2进行比较，谁小就放在dummy节点后面
2. 若链表1比较完，将链表2后面的所有节点放在主链表后
3. 若链表2比较完，将链表1后面的所有节点放在主链表后

```C++
struct ListNode{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

ListNode* mergeTwoLists(ListNode *list1, ListNode *list2){
    ListNode *dummy =new ListNode(-1), *p = dummy;
    
    ListNode *p1 = list1, *p2 = list2;
    while(p1 != nullptr && p2 != nullptr){
        if(p1->val < p2->val){
            p->next = p1;
            p1 = p1->next;
        }else{
            p->next = p2;
            p2 = p2->next;
        }
        p = p->next;
    }
    if(p1 == nullptr){
        p->next = p2;
    }
    if(p2 == nullptr){
        p->next = p1;
    }

    return dummy->next;
}

```

## 2. 反转链表
#### 题目描述：
定义一个函数，输入一个链表的头节点，反转该链表并输出反转后链表的头节点。
```C++
输入: 1->2->3->4->5->nullptr 
输出: 5->4->3->2->1->nullptr
```
#### 算法思路：
定义三个节点，prev, cur, nxt
依次交换nxt，cur，prev
反转后返回prev
```C++
struct ListNode{
    int val;
    ListNode *next;
    ListNode(int x): val(x), next(nullptr) {}
};
ListNode* revert(ListNode *node){
    ListNode *prev , *cur, *nxt; 
    prev = nullptr;
    cur = node;
    nxt = node;

    while(cur){
        nxt = cur->next;
        cur->next = prev;
        prev = nxt;
        nxt = cur;
    }
    return prev;
}
```

## 3. 单例模式
#### 题目描述：
实现饿汉单例模式和懒汉单例模式
#### 算法思路：
1. 构造函数私有化 -> 防止从类外调用构造函数，保证在任何情况下只生成一个实例。
2. 在类中定义一个静态指针，指向本类的变量的静态变量指针。
3. 提供一个全局的静态方法getInstance（全局访问点）-> 便于提供从类外部获取类的唯一实例方法


###### 饿汉单例模式代码：
```C++
//饿汉单例模式在类加载的时候就立即初始化，并且创建单例对象，
//不管有没有使用到，先创建好了再说。在线程创建之前就实例化了，所以不会出现线程安全的问题
class Single{
private:
    static Single* p;
    Single (){};

public:
    static Single* getInstance();
};
Single* Single::p = new Single();               // 饿汉模式类加载的时候就已经创建了对象
Single* Single::getInstance(){return p;}
```

###### 懒汉单例模式代码：
```C++
//懒汉单列模式，顾名思义，比较“懒”， 用的时候才去检查有没有实例， 如果有则直接返回，没有则创建。
class Single{
private:
    static Single* p;
    Single (){};
public:
    static Single* getInstance(){                       // 懒汉模式在使用的时候才创建该对象
        if(p == nullptr){
            std::lock_guard<std::mutex> lock(m);
            if(p == nullptr){
                return new Single();
            }
        }
        return p;
    };
};
Single* Single::p = nullptr;                //懒汉模式类加载的时候没有创建该类
```

## 4. 抽象工厂模式
#### 题目描述：
实现一个抽象工厂模式
#### 算法思路：
1. 实现抽象产品接口类
2. 实现具体产品类
3. 实现抽象工厂接口类
4. 实现具体工厂类
5. 工厂可以生产不同的类别的产品，同时有关联的产品在同一工厂中生产
```C++
class ProductA{
public:
    virtual void show() = 0;
    virtual ~ProductA(){} ;
};

class BrandAproductA : public ProductA {
public:
    void show() {
        cout<<"BrandAproductA show"<<endl;
    }
    ~BrandAproductA() {
        cout<<"BrandAproductA destroy"<<endl;
    }
};

class BrandBproductA : public ProductA {
public:
    void show(){
        cout<<"BrandBproductA show"<<endl;
    }
    ~BrandBproductA() {
        cout<<"BrandBproductA destroy"<<endl;
    }
};

class BrandCproductA : public ProductA {
public:
    void show() {
        cout<<"BrandCproductA show"<<endl;
    }
    ~BrandCproductA() {
        cout<<"BrandCproductA destroy"<<endl;
    }
};

class ProductB{
public:
    virtual void show() = 0; 
    virtual ~ProductB(){};
};

class BrandAproductB: public ProductB{
public:
    void show(){
        cout<<"BrandAproductB show"<<endl;
    }
    ~BrandAproductB() {
        cout<<"BrandAproductB destory"<<endl;
    }
};

class BrandBproductB: public ProductB{
public:
    void show(){
        cout<< "BrandBproductB show"<<endl;
    }
    ~BrandBproductB(){
        cout <<"BrandBproductB destory"<<endl;
    }
};

//工厂可以创建不同的产品，同时有关联的产品在同一工厂创建
class Factory{
public:
    virtual ProductA* createProductA() = 0;
    virtual ProductB* createProductB() = 0;
};

class BrandAFactory: public Factory{
public:
    ProductA* createProductA(){
        return new BrandAproductA();
    }
    ProductB* createProductB(){
        return new BrandAproductB();
    }
};

class BrandBFactory: public Factory{
public:
    ProductA* createProductA(){
        return new BrandBproductA();
    }
    ProductB *createProductB(){
        return new BrandBproductB();
    }
};

class BrandCFactory: public Factory{
public:
    ProductA* createProductA(){
        return new  BrandCproductA();
    }
    ProductB* createProductB(){
        return nullptr;
    }
};

void ClientCode(){
    std::unique_ptr<Factory> brandAfty = std::make_unique<BrandAFactory>();
    std::unique_ptr<Factory> brandBfty = std::make_unique<BrandBFactory>();
    std::unique_ptr<Factory> brandCfty = std::make_unique<BrandCFactory>();

    std::unique_ptr<ProductA> brandAPrctA(brandAfty->createProductA());
    std::unique_ptr<ProductA> brandBPrctA(brandBfty->createProductA());
    std::unique_ptr<ProductA> brandCPrctA(brandCfty->createProductA());

    std::unique_ptr<ProductB> brandAPrctB(brandAfty->createProductB());
    std::unique_ptr<ProductB> brandBPrctB(brandBfty->createProductB());

    brandAPrctA->show();
    brandBPrctA->show();
    brandCPrctA->show();

    brandAPrctB->show();
    brandBPrctB->show();

}
```
## 5. 快速排序
#### 题目描述：
实现快速排序
#### 算法思路：
1. 整体来看快速排序可以看成二叉树的前序遍历
2. 选一个元素作为pivot，然后将所有小于pivot位置的数，放在pivot的左边所有大于pivot位置的数，放在pivot的右边
3. 通过pivot将数组一分为二，递归调用
```C++
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


```
## 6. 归并排序
#### 题目描述：
实现归并排序
#### 算法思路：
1. 整体来看可以将归并排序看成二叉树的后序遍历
2. 将数组对半划分 ，递归调用归并排序函数将数组划分成只有一个元素的数组
3. 将左边有序的数组和右边有序的数组合并成一个有序的数组
```C++
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

```
## 7. 堆排序
#### 题目描述
实现堆排序。
#### 算法思路
堆是一颗完全二叉树，对于从下标从0开始的二叉树，对于任何一个i节点，
父节点索引为：(i - 1) / 2
左孩子索引为：2 * i + 1
右孩子索引为：2 * i + 2

1.首先将待排序的数组构造成一个大根堆，此时，整个数组的最大值就是堆结构的顶端

2.将顶端的数与末尾的数交换，此时，末尾的数为最大值，剩余待排序数组个数为n-1

3.将剩余的n-1个数再构造成大根堆，再将顶端数与n-1位置的数交换，如此反复执行，便能得到有序数组

```C++
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


```
## 8. LRU缓存
#### 题目描述：
请你设计并实现一个满足  LRU (最近最少使用) 缓存 约束的数据结构。
实现 LRUCache 类：
1. LRUCache(int capacity) 以 正整数 作为容量 capacity 初始化 LRU 缓存
2. int get(int key) 如果关键字 key 存在于缓存中，则返回关键字的值，否则返回 -1 。
3. void put(int key, int value) 如果关键字 key 已经存在，则变更其数据值 value ；如果不存在，则向缓存中插入该组 key-value 。如果插入操作导致关键字数量超过 capacity ，则应该 逐出 最久未使用的关键字。
#### 算法思路：
1. 使用双向链表list和和hash表unordered_map实现
2. put的流程
![](./asset/put.jpg)
```C++
class LRU{
private:
    list<pair<int,int>> cache;
    unordered_map<int, list<pair<int,int>>::iterator> map;
    int cap;

public:
    LRU(int capacity): cap(capacity){}
    int get(int key){
        if(map.find(key) == map.end()) return -1;       // 若没有key值，则返回-1；
        auto key_value = *map[key];                     //若有key则把cacche中的key移到最前面
        cache.erase(map[key]);
        cache.push_front(key_value);
        map[key] = cache.begin();                      //同时改变map中key的引用
        return key_value.second;
    }

    void put(int key, int value){
        if(map.find(key) != map.end()){
            auto key_value = *map[key];                 //如果存在key，则将cache中key对应的value改掉，然后移到最前面
            key_value.second = value;
            cache.erase(map[key]);
            cache.push_front(key_value);
            map[key] = cache.begin();                   //同时修改map中key的引用
            return;
        }
        if(cache.size() == cap){                        //如果容量满，则删除最久未使用的
            auto key_ = cache.back().first;             
            cache.pop_back();
            map.erase(key_);
        }
        cache.push_front({key, value});                //添加新的key 和 value
        map[key] = cache.begin();
    }
};

```

## 9. 重排链表
#### 题目描述：
给定一个单链表 L：L0→L1→…→Ln-1→Ln ， 将其重新排列后变为： L0→Ln→L1→Ln-1→L2→Ln-2→…
```C++
示例 1:
输入链表 1->2->3->4    输出排列 1->4->2->3.
示例 2:
输入链表 1->2->3->4->5, 输出排列 1->5->2->4->3.
```

#### 算法思路：
1. 将链表对半分开
2. 将第二个链表反转
3. 然后将两个链表依次插入
```C++
struct ListNode{
    int val;
    ListNode *next;
    ListNode(int x):val(x),next(nullptr) {}
};

ListNode* revert(ListNode *list){
    ListNode *prev, *cur, *nxt;
    prev = nullptr;
    cur = list;
    nxt = list;
    while(cur){
        nxt = cur->next;
        cur->next = prev;
        prev = cur;
        cur = nxt;
    }
    return prev;
}

void reorderedList(ListNode *list){
    ListNode *slow = list, *fast = list;
    while(fast->next && fast->next->next){
        slow = slow->next;
        fast = fast->next->next;
    }
    ListNode *p2 = slow->next, *p1 = list;
    ListNode *dummy = new ListNode(-1), *p = dummy;
    slow->next = nullptr;                                   //断链
    p2 = revert(p2);
    while(p1){
        p->next = p1;
        p1 = p1->next;
        p = p->next;
        p->next = p2;
        if(p2){
            p2 = p2->next;
            p = p->next;
        }
    }
    list = dummy->next;
};
```

## 10. 奇偶链表
#### 题目描述：
给定一个单链表，把所有的奇数节点和偶数节点分别排在一起。请注意，这里的奇数节点和偶数节点指的是节点编号的奇偶性，而不是节点的值的奇偶性。
```C++
示例 1:
输入: 1->2->3->4->5->NULL
输出: 1->3->5->2->4->NULL
示例 2:
输入: 2->1->3->5->6->4->7->NULL 
输出: 2->3->6->7->1->5->4->NULL
 
```

#### 算法思路：
![算法步骤](/asset/1.png)

```C++
struct ListNode{
    int val;
    ListNode *next;
    ListNode(int x):val(x),next(nullptr) {}
};

ListNode *oddEvenList(ListNode *head){
    if(head == nullptr) return nullptr;

    ListNode *evenHead = head->next;
    ListNode *odd = head;
    ListNode *even = evenHead;

    while(even && even->next){
        odd->next = even->next;
        odd = odd->next;
        even->next = odd->next;
        even = even->next;
    }

    odd->next = evenHead;
    return head;
}

```

## 11. 多线程轮流依次打印
#### 题目描述：
1. 依次轮流打印abc
2. 依次打印奇数偶数
#### 算法思路：
使用锁，条件变量

##### 轮流打印abc代码
```C++
mutex m;
int max_count= 3;
condition_variable cv;
int flag = 0;
int number = 0;

void printA(){
    while(number < max_count){
        unique_lock<mutex> lock(m);
        cv.wait(lock, []{return flag==0;});             //如果条件为true就往下运行，否者线程等待
        cout << "thread1: a"<< endl;
        number++;
        flag = 1;
        cv.notify_all();
    }
}
void printB(){
    while(number < max_count){
        unique_lock<mutex> lock(m);
        cv.wait(lock, []{return flag==1;});
        cout<< "thread2: b"<< endl;
        number++;
        flag = 2;
        cv.notify_all();
    }
}
void printC(){
    while(number < max_count){
        unique_lock<mutex> lock(m);
        cv.wait(lock, []{return flag==2;});
        cout<< "thread3: c"<<endl;
        number++;
        flag = 0;
        cv.notify_all();
    }
}
```
##### 轮流打印奇数偶数代码
```C++
mutex m;
int max_count = 10;
condition_variable cv;
int number = 0;

void printOdd(){
    while(number < max_count){
        unique_lock<mutex> lock(m);
        cv.wait(lock, []{return number%2==1;});     //如果条件为真则往下执行
        cout << std::this_thread::get_id() << ": "<< number <<endl;
        number++;
        cv.notify_one();
    }
}

void printEven(){
    while(number < max_count){
        unique_lock<mutex> lock(m);
        cv.wait(lock, []{return number%2==0;});   //如果条件为真则继续往下执行
        cout << std::this_thread::get_id() << ": "<<number <<endl;
        number++;
        cv.notify_one();
    }
}

```

##12 topK问题
#### 题目描述
得到第K大的元素，或第K小的元素
#### 算法思路
1. 维护一个大顶堆或者小顶堆
2. 对于大顶堆（降序），每次压入元素后当队列的size大于K，则删除堆顶最大的元素，这样最后堆顶就是第K小的元素。
3. 对于小顶堆（升序），每次压入元素后当队列的size大于K，则删除堆顶最小的元素，这样最后堆顶就是第K大的元素。
4. 默认是大顶对
   
##### 大小顶堆的代码实现
```C++
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
```

####  关于容器自定义排序问题
#####  对于sort函数排序
1. 定义一个比较函数，返回为一个bool值
2. 对于sort函数来说，"<"符号意味着升序，">"符号意味着降序
##### sort自定义顺序代码
```C++
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
```
#### 关于priority_queue自定义排序问题
1. 使用重载()运算符。
2. 和sort中相反， "<"符号意味着降序，">"符号意味着升序。

##### 优先权队列关于自定义排序的代码
```C++
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
```

## 13自定义vector
### 总结

**移动构造**和**移动赋值**是 C++11 引入的两个重要概念，它们与拷贝版本类似，但核心区别在于**资源的所有权转移**而非复制。让我详细解释：

### 1. 基本定义

### 移动构造函数 (Move Constructor)
- **定义**：用同类型的**右值对象**来**初始化**一个新对象，并转移资源所有权。
- **语法**：`T(T&& other)`
- **调用时机**：新对象创建时，且源对象是右值（临时对象或 `std::move` 转换的对象）。

### 移动赋值函数 (Move Assignment Operator)
- **定义**：将一个**右值对象**的资源转移给一个**已存在**的对象。
- **语法**：`T& operator=(T&& other)`
- **调用时机**：两个对象都已存在，将右值对象的资源转移给左值对象。



## 关键区别点

| 特性 | 构造 | 赋值 |
|------|----------|----------|
| **操作对象** | 创建**新对象** | 修改**已存在对象** |
| **调用前状态** | 新对象还未存在 | 目标对象已存在，可能有资源 |
| **是否需要释放旧资源** | 不需要（新对象无旧数据） | 需要（先释放原有资源） |
| **源对象状态** | 被置于"空"状态 | 被置于"空"状态 |
| **自赋值检查** | 不需要 | 需要 |


### 性能优势
- **移动构造/赋值**：通常只是指针交换，O(1) 复杂度
- **拷贝构造/赋值**：可能需要深拷贝，O(n) 复杂度

### 异常安全
- 移动操作通常声明为 `noexcept`，以便标准库容器能安全使用（如 `vector` 重新分配时）

### 源对象状态
- 移动后的源对象处于"有效但未指定"的状态
- 通常置为 `nullptr` 或空状态，保证析构安全
- 不应再使用源对象，除非重新赋值

## 总结

| 操作 | 拷贝语义 | 移动语义 |
|------|----------|----------|
| **构造** | `T(const T&)` 深拷贝 | `T(T&&)` 偷资源 |
| **赋值** | `T& operator=(const T&)` 深拷贝 | `T& operator=(T&&)` 偷资源 + 释放旧资源 |
| **资源处理** | 复制资源 | 转移所有权 |
| **性能** | 可能较慢 | 通常很快 |

## 移动和拷贝的区别
**移动**和**拷贝**的核心区别在于：**拷贝是复制资源，移动是转移所有权**。

## 1. 核心概念对比

| 特性 | 拷贝 (Copy) | 移动 (Move) |
|------|------------|-------------|
| **本质** | 复制一份新资源 | 偷走已有资源 |
| **源对象状态** | 保持不变 | 被置为空/无效状态 |
| **性能** | 可能较慢（深拷贝） | 很快（指针交换） |
| **内存使用** | 两份独立资源 | 同一份资源，所有权转移 |
| **异常安全** | 通常强保证 | 通常 noexcept |

## 2. 直观类比

### 拷贝就像：
- **复印文件**：你有了一份文件，复印后你和你朋友各有一份，内容相同但独立。
- **借书并手抄一本**：你有了这本书的完整副本，原书不受影响。

### 移动就像：
- **转交文件**：你把唯一的一份文件交给朋友，你手上不再拥有它。
- **借书并直接转借**：书还是那本书，只是所有者变了。

## 3. 代码示例对比

```cpp
class String {
private:
    char* data;
    size_t size;
    
public:
    // 拷贝构造：深复制
    String(const String& other) {
        size = other.size;
        data = new char[size + 1];
        memcpy(data, other.data, size + 1);
        cout << "拷贝：复制了 " << size << " 字节\n";
    }
    
    // 移动构造：偷资源
    String(String&& other) noexcept {
        size = other.size;
        data = other.data;        // 偷走指针
        other.data = nullptr;     // 源对象放弃所有权
        other.size = 0;
        cout << "移动：偷走了资源\n";
    }
    
    // 析构函数
    ~String() {
        delete[] data;
    }
};
```

## 4. 使用场景对比

```cpp
int main() {
    String s1("Hello");
    
    // 拷贝场景
    String s2 = s1;              // s1 保持不变，s2 是独立副本
    cout << "s1 仍可用: " << s1 << "\n";  // 正常
    
    // 移动场景
    String s3 = std::move(s1);    // s1 的资源被转移给 s3
    // cout << s1;                 // 危险！s1 已为空
    
    // 函数返回值
    String createString() {
        String temp("World");
        return temp;              // 自动移动（而不是拷贝）
    }
    
    String s4 = createString();   // 移动构造
    
    return 0;
}
```

## 5. 为什么需要移动？

### 性能提升
```cpp
// 传统方式（拷贝）
vector<string> v1 = getLargeVector();
vector<string> v2 = v1;           // O(n) 深拷贝，慢！

// C++11方式（移动）
vector<string> v2 = std::move(v1); // O(1) 指针交换，极快！
// v1 不再拥有元素
```

### 处理只能移动的资源
有些资源只能移动，不能拷贝：
```cpp
unique_ptr<int> p1(new int(42));
// unique_ptr<int> p2 = p1;        // 错误！不能拷贝 unique_ptr
unique_ptr<int> p3 = std::move(p1); // 正确！移动所有权
// p1 现在为空
```

## 6. 自动移动的场景

C++ 会在某些情况下自动使用移动而不是拷贝：

```cpp
vector<int> createVector() {
    vector<int> v(1000000);
    // 处理 v...
    return v;        // 自动移动（而不是拷贝）
}

void process(vector<int> v) {
    // 处理 v...
}

int main() {
    vector<int> data(1000000);
    process(std::move(data));  // 显式移动（避免拷贝）
    // data 现在为空
}
```

## 7. 对比总结

| 方面 | 拷贝 | 移动 |
|------|------|------|
| **资源处理** | 分配新内存 + 复制数据 | 转移指针所有权 |
| **时间复杂度** | O(n) | O(1) |
| **源对象** | 完整可用 | 空状态（不能再使用） |
| **异常安全** | 通常可保证强异常安全 | 通常 noexcept |
| **适用对象** | 所有对象 | 右值或显式 std::move 的对象 |
| **典型使用** | 需要独立副本时 | 临时对象、转移所有权时 |

## 最佳实践
- **需要独立副本**时用拷贝
- **不再需要原对象**时用移动
- **对于只能移动的对象**（如 `unique_ptr`），必须用移动
- **大对象**优先考虑移动而不是拷贝