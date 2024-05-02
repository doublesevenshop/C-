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


// 给卡布奇诺通过继承的方式添加牛奶
class Milk : public Cappuccino {
public:
    string getDescription() const override {
        return Cappuccino::getDescription() + " with Milk";
    }

    double cost() const override {
        return Cappuccino::cost() + 2.0;
    }

    void addMilk() {
        cout << "Add Milk" << endl;
    }
};

// 给卡布奇诺通过继承的方式添加冰块
class Ice : public Cappuccino {
public:
    string getDescription() const override {
        return Cappuccino::getDescription() + " with Ice";
    }

    double cost() const override {
        return Cappuccino::cost() + 1.0;
    }

    void addIce() {
        cout << "Add Ice" << endl;
    }
};

// 给可口可乐通过继承的方式添加冰块
class IceCocaCola : public CocaCola {
public:
    string getDescription() const override {
        return CocaCola::getDescription() + " with Ice";
    }

    double cost() const override {
        return CocaCola::cost() + 1.0;
    }

    void addIce() {
        cout << "Add Ice" << endl;
    }
};

// 给可口可乐通过继承的方式添加柠檬
class LemonCocaCola : public CocaCola {
public:
    string getDescription() const override {
        return CocaCola::getDescription() + " with Lemon";
    }

    double cost() const override {
        return CocaCola::cost() + 2.0;
    }

    void addLemon() {
        cout << "Add Lemon" << endl;
    }
};


int main() {
    /*首先，我们来一杯卡布奇诺*/ 
    unique_ptr<IBeverage> cappuccino = make_unique<Cappuccino>();
    // 然后，我们给卡布奇诺加牛奶
    unique_ptr<Milk> milk = make_unique<Milk>();
    cout << milk->getDescription() << " : " << milk->cost() << endl;
    milk->addMilk();
    // 接着，我们给卡布奇诺加冰块
    unique_ptr<Ice> ice = make_unique<Ice>();
    cout << ice->getDescription() << " : " << ice->cost() << endl;
    ice->addIce();


    /* 再来一杯可口可乐 */ 
    unique_ptr<CocaCola> cocaCola = make_unique<CocaCola>();
    // 然后，我们给可口可乐加冰块
    unique_ptr<IceCocaCola> iceCocaCola = make_unique<IceCocaCola>();
    cout << iceCocaCola->getDescription() << " : " << iceCocaCola->cost() << endl;
    iceCocaCola->addIce();
    // 最后，我们给可口可乐加柠檬
    unique_ptr<LemonCocaCola> lemonCocaCola = make_unique<LemonCocaCola>();
    cout << lemonCocaCola->getDescription() << " : " << lemonCocaCola->cost() << endl;
    lemonCocaCola->addLemon();

    return 0;
}