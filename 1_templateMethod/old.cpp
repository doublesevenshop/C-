#include <iostream>
#include <memory>
#include <utility>
using namespace std;
// 抽象基类
class Game {
public:
    // 定义算法的骨架
    void play() {
        start();
        playing();
        end();
    }
    virtual ~Game() {}
protected:
    virtual void start() = 0;
    virtual void playing() = 0;
    virtual void end() = 0;
};


// 象棋类
class Chess : public Game {
protected:
    void start() override {
        cout << "Chess start" << endl;
    }
    void playing() override {
        cout << "Chess playing" << endl;
    }
    void end() override {
        cout << "Chess end" << endl;
    }
};

// 扑克类
class Poker : public Game {
protected:
    void start() override {
        cout << "Poker start" << endl;
    }
    void playing() override {
        cout << "Poker playing" << endl;
    }
    void end() override {
        cout << "Poker end" << endl;
    }
};

int main() {
    // 使用智能指针，自动释放资源
    shared_ptr<Game> chess = make_shared<Chess>();
    chess->play();

    shared_ptr<Game> poker = make_shared<Poker>();
    poker->play();

    return 0;
}