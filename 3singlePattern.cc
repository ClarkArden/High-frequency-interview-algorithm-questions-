#include <iostream>
#include <vector>
#include <mutex>

using namespace std;

//单例模式使用方法
// 1. 构造函数私有化 -> 防止从类外调用构造函数，保证在任何情况下只生成一个实例。
// 2. 在类中定义一个静态指针，指向本类的变量的静态变量指针。
// 3. 提供一个全局的静态方法getInstance（全局访问点）-> 便于提供从类外部获取类的唯一实例方法

namespace Hungry {
    
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
}

namespace Lazy {
    std::mutex m;

    //懒汉单列模式，顾名思义，比较“懒”， 用的时候才去检查有没有实例， 如果有则直接返回，没有则创建。
    class Single{
    private:
        static Single* p;
        Single (){};
    public:
        static Single* getInstance(){                       // 懒汉模式在使用的时候才创建该对象
            if(p == nullptr){
                std::lock_guard<std::mutex> lock(m);
                if(p == nullptr){                           //why:会出现多个线程在等待获取当前的锁,                            
                    return new Single();                    //当其中的一个线程释放掉锁后,又会重新new 一个对象.就会出现不同的对象
                }
            }
            return p;
        };
    };
    Single* Single::p = nullptr;                //懒汉模式类加载的时候没有创建该类
}

void ClientCode(){
    Hungry::Single* p1 = Hungry::Single::getInstance();
    Hungry::Single* p2 = Hungry::Single::getInstance();

    if(p1 == p2){
        std::cout<<"hungry pattern same"<<std::endl;
    }

    Lazy::Single* p3 = Lazy::Single::getInstance();
    Lazy::Single* p4 =  Lazy::Single::getInstance();

    if(p3 == p4){
        std::cout<<"lazy pattern same"<<std::endl;
    }
}

void main(){
    ClientCode();
}