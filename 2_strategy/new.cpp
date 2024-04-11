#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <memory>

using namespace std;

/* 一种抽象的排序策略 */ 
class SorterStrategy{
public:
    virtual void sort(vector<int>& data) = 0;
    virtual ~SorterStrategy() = default;
};

/* 具体的升序策略 */ 
class ascSort : public SorterStrategy {
public:
    // 对排序进行重载
    void sort(vector<int>& data) override {
        std::sort(data.begin(), data.end());
    }
};

/* 具体的降序策略 */ 
class descSort : public SorterStrategy {
    // 对排序进行重载
    void sort(vector<int>& data) override {
        std::sort(data.rbegin(), data.rend());
    }
};


/* 策略模式，并且使用了智能指针，进行了封装 */ 
class Sorter{
public:
    void setStartegy(shared_ptr<SorterStrategy> strategy) {
        m_strategy = strategy;
    }
    void sort(vector<int>& data) {
        m_strategy->sort(data);
    }
    void print(const vector<int>& data) {
        for(auto& d : data) {
            cout << d << " ";
        }
        cout << endl;
    }
private:
    shared_ptr<SorterStrategy> m_strategy;
};

int main() {
    vector<int> data = {8, 2, 4, 5, 1};
    Sorter sorter;
    sorter.setStartegy(make_shared<ascSort>());
    sorter.sort(data);
    sorter.print(data);

    sorter.setStartegy(make_shared<descSort>());
    sorter.sort(data);
    sorter.print(data);


    return 0;
}