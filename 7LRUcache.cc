#include <iostream>
#include <list>
#include <unordered_map>
#include <memory>

using namespace std;

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

int main(){
    shared_ptr<LRU> cache = make_shared<LRU>(2);
    cache->put(1, 1);
    cache->put(2, 2);
    cout << cache->get(1) << endl;       // 返回  1
    cache->put(3, 3);                   // 该操作会使得密钥 2 作废
    cout << cache->get(2) << endl;       // 返回 -1 (未找到)
    cache->put(4, 4);                    // 该操作会使得密钥 1 作废
    cout << cache->get(1) << endl;       // 返回 -1 (未找到)
    cout << cache->get(3) << endl;       // 返回  3
    cout << cache->get(4) << endl;       // 返回  4

    return 0;
}