#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;



namespace printabc{
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
}

namespace printOddEven{
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


};

int main(){
    thread t1(printabc::printA);
    thread t2(printabc::printB);
    thread t3(printabc::printC);

    t1.join();
    t2.join();
    t3.join();

    thread t4(printOddEven::printOdd);
    thread t5(printOddEven::printEven);
    t4.join();
    t5.join();
    return 0;
}