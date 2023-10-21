#include <iostream>
#include <string>
#include <memory>

using namespace std;

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

int main() {
    ClientCode();
    return 0;
}