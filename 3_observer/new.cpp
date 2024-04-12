#include <iostream>
#include <list>
#include <memory>
#include <chrono>
#include <thread>

using namespace std;

/* 清屏函数 */
void clearConsole() {
    cout << "\033[2J\033[1;1H";
}

/* 观察者抽象接口定义 */
class IObserver {
public:
    virtual ~IObserver() {}
    // 更新方法，由Subject调用，来通知观察者进度变化
    virtual void update(int value) = 0;
};

/* 主题接口定义 */
class ISubject {
public:
    virtual ~ISubject() {}
    // 添加观察者
    virtual void attach(shared_ptr<IObserver> observer) = 0;
    // 移除观察者
    virtual void detach(shared_ptr<IObserver> observer) = 0;
    // 通知观察者
    virtual void notify() = 0;
};


/* 进度条主体实现 */
class ProgressSubject : public ISubject {
private:
    list<shared_ptr<IObserver>> observers;      // 观察者列表
    int progress;                               // 进度

public:
    ProgressSubject() : progress(0) {}

    // 设置进度
    void setProgress(int value) {
        progress = value;
        notify();
    }

    // 添加观察者
    void attach(shared_ptr<IObserver> observer) override {
        observers.push_back(shared_ptr<IObserver>(observer));
    }
    // 移除观察者
    void detach(shared_ptr<IObserver> observer) override {
        observers.remove(observer);
    }

    void notify() override {
        for(auto& observer : observers) {
            observer->update(progress);
        }
    }
};

/* 简单文本进度条 */
class progressBar : public IObserver {
public:
    void update(int value) override {
        cout << "Progress: " << value << " % " << endl;
    }
};

/* 图形化进度条 */
class graphBar : public IObserver {
public:
    void update(int value) override {
        cout << "[";
        for(int i = 0; i < 50; i++) {
            if(i < value / 2) {
                cout << "=";
            } else {
                cout << " ";
            }
        }
        cout << "]" << value << "%" << endl;
    }
};

/* 数字指示器 */
class numbericIndicator : public IObserver {
public:
    void update(int value) override {
        cout << "Completed: " << value <<  " of 100\n";
    }
};



int main() {
    shared_ptr<ProgressSubject> subject = make_shared<ProgressSubject>();
    shared_ptr<IObserver> pb = make_shared<progressBar>();
    shared_ptr<IObserver> gb = make_shared<graphBar>();
    shared_ptr<IObserver> ni = make_shared<numbericIndicator>();

    subject->attach(pb);
    subject->attach(gb);
    subject->attach(ni);

    // 模拟进度变化
    for(int i = 0; i <= 100; i += 5) {
        clearConsole();     // 清屏
        subject->setProgress(i);
        std::this_thread::sleep_for(chrono::milliseconds(500));
    }

    // 移除一个观察者
    subject->detach(gb);

    // 再次更新进度
    for(int i = 0; i <= 100; i += 5) {
        clearConsole();     // 清屏
        subject->setProgress(i);
        std::this_thread::sleep_for(chrono::milliseconds(300));
    }
    return 0;

}