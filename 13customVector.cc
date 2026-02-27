#include <iostream>
#include <cstdlib>   // for malloc, free
#include <new>       // for placement new
#include <utility>   // for std::move

template <typename T>
class MyVector {
private:
    T* data_;         // 指向底层裸内存的指针
    size_t size_;     // 实际已构造的元素个数
    size_t capacity_; // 分配的内存能容纳的元素总数

public:
    // 1. 默认构造
    MyVector() : data_(nullptr), size_(0), capacity_(0) {}

    // 2. 析构函数 (核心变化 1)
    ~MyVector() {
        if (data_) {
            // 必须先显式调用每个已构造对象的析构函数
            for (size_t i = 0; i < size_; ++i) {
                data_[i].~T(); 
            }
            // 然后释放裸内存
            free(data_);
        }
    }

    // 3. 拷贝构造
    MyVector(const MyVector& other) : size_(other.size_), capacity_(other.capacity_) {
        data_ = static_cast<T*>(malloc(capacity_ * sizeof(T)));
        for (size_t i = 0; i < size_; ++i) {
            // 使用 placement new 在已分配的内存上调用拷贝构造
            new (&data_[i]) T(other.data_[i]); 
        }
    }

    // 4. 拷贝赋值
    MyVector& operator=(const MyVector& other) {
        if (this != &other) {
            // 销毁当前对象并释放内存
            for (size_t i = 0; i < size_; ++i) {
                data_[i].~T();
            }
            free(data_);

            size_ = other.size_;
            capacity_ = other.capacity_;
            data_ = static_cast<T*>(malloc(capacity_ * sizeof(T)));
            for (size_t i = 0; i < size_; ++i) {
                new (&data_[i]) T(other.data_[i]);
            }
        }
        return *this;
    }

    // 5. 移动构造
    MyVector(MyVector&& other) noexcept 
        : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    // 6. 移动赋值
    MyVector& operator=(MyVector&& other) noexcept {
        if (this != &other) {
            for (size_t i = 0; i < size_; ++i) data_[i].~T();
            free(data_);

            data_ = other.data_;
            size_ = other.size_;
            capacity_ = other.capacity_;

            other.data_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
        }
        return *this;
    }

    // 7. 扩容逻辑 (核心变化 2)
    void reserve(size_t new_capacity) {
        if (new_capacity <= capacity_) return;

        // 1. 分配新的裸内存
        T* new_data = static_cast<T*>(malloc(new_capacity * sizeof(T)));

        // 2. 将旧元素移动/拷贝到新内存中
        for (size_t i = 0; i < size_; ++i) {
            // 使用 placement new 和移动构造函数
            new (&new_data[i]) T(std::move(data_[i]));
            // 3. 显式销毁旧内存中的对象
            data_[i].~T(); 
        }

        // 4. 释放旧内存
        free(data_);
        
        data_ = new_data;
        capacity_ = new_capacity;
    }

    // 8. 尾部插入 (核心变化 3)
    void push_back(const T& value) {
        if (size_ == capacity_) {
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        // 在未初始化的内存上，原地构造对象
        new (&data_[size_]) T(value);
        size_++;
    }

    void push_back(T&& value) {
        if (size_ == capacity_) {
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        // 原地移动构造对象
        new (&data_[size_]) T(std::move(value));
        size_++;
    }

    // 9. 尾部删除 (核心变化 4)
    void pop_back() {
        if (size_ > 0) {
            size_--;
            // 必须显式调用析构函数，销毁对象，但内存不退还
            data_[size_].~T(); 
        }
    }

    // 10. 元素访问
    T& operator[](size_t index) { return data_[index]; }
    const T& operator[](size_t index) const { return data_[index]; }

    size_t size() const { return size_; }
    size_t capacity() const { return capacity_; }
    bool empty() const { return size_ == 0; }
};