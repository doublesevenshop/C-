#include <iostream>
#include <string>
#include <memory>

using namespace std;

// 基本的饮品抽象类
class IBeverage {
public:
    virtual string getDescription() const = 0; // 描述
    virtual double cost() const = 0; // 价格
    virtual ~IBeverage() {}
};

// 具体的饮品类： 卡布奇诺
class Cappuccino : public IBeverage {
public:
    string getDescription() const override {
        return "Cappuccino";
    }

    double cost() const override {
        return 10.0;
    }
};

// 具体的饮品类： 可口可乐
class CocaCola : public IBeverage {
public:
    string getDescription() const override {
        return "CocaCola";
    }

    double cost() const override {
        return 5.0;
    }
};

// 装饰者基类
class BeverageDecorator : public IBeverage {
    // 把公共的方法放在基类中，避免在每个具体装饰者中重复实现
    // 既有继承又有组合
protected:
    shared_ptr<IBeverage> beverage; // 持有一个饮品对象的指针
public:
    BeverageDecorator(shared_ptr<IBeverage> b) : beverage(b) {}
    string getDescription() const override {
        return beverage->getDescription();
    }
    double cost() const override {
        return beverage->cost();
    }
    virtual ~BeverageDecorator() {}
    virtual void addSomething() = 0;
};

// 具体的装饰者类： 牛奶
class Milk : public BeverageDecorator {
public:
    Milk(shared_ptr<IBeverage> b) : BeverageDecorator(b) {}
    string getDescription() const override {
        return beverage->getDescription() + " with Milk";
    }
    double cost() const override {
        return beverage->cost() + 2.0;
    }
    virtual void addSomething() {
        cout << "Add Milk" << endl;
    }
};

// 具体的装饰者类： 冰块
class Ice : public BeverageDecorator {
public:
    Ice(shared_ptr<IBeverage> b) : BeverageDecorator(b) {}
    string getDescription() const override {
        return beverage->getDescription() + " with Ice";
    }
    double cost() const override {
        return beverage->cost() + 1.0;
    }
    virtual void addSomething() {
        cout << "Add Ice" << endl;
    }
};


// 具体的装饰者类： 柠檬
class Lemon : public BeverageDecorator {
public:
    Lemon(shared_ptr<IBeverage> b) : BeverageDecorator(b) {}
    string getDescription() const override {
        return beverage->getDescription() + " with Lemon";
    }
    double cost() const override {
        return beverage->cost() + 3.0;
    }
    virtual void addSomething() {
        cout << "Add Lemon" << endl;
    }
};

int main() {
    /*首先，我们来一杯卡布奇诺*/ 
    shared_ptr<IBeverage> cappuccino = make_shared<Cappuccino>();
    // 为卡布奇诺加一些牛奶
    cappuccino = make_shared<Milk>(cappuccino);
    dynamic_cast<Milk*>(cappuccino.get())->addSomething();
    cout << cappuccino->getDescription() << " : " << cappuccino->cost() << endl;
    
    // 为卡布奇诺加一些冰块
    cappuccino = make_shared<Ice>(cappuccino);
    dynamic_cast<Ice*>(cappuccino.get())->addSomething();
    cout << cappuccino->getDescription() << " : " << cappuccino->cost() << endl;


    /* 再来一杯可口可乐 */
    cout << "======================" << endl;
    shared_ptr<IBeverage> cocaCola = make_shared<CocaCola>();
    // 为可口可乐加一些冰块
    cocaCola = make_shared<Ice>(cocaCola);
    dynamic_cast<Ice*>(cocaCola.get())->addSomething();
    cout << cocaCola->getDescription() << " : " << cocaCola->cost() << endl;

    // 为可口可乐加一些柠檬
    cocaCola = make_shared<Lemon>(cocaCola);
    dynamic_cast<Lemon*>(cocaCola.get())->addSomething();
    cout << cocaCola->getDescription() << " : " << cocaCola->cost() << endl;

    return 0;
}