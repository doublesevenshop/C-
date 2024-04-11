#include <iostream>
#include <memory>
#include <utility>

using namespace std;


class Game {
public:
    // 模板方法
    void play() {
        start();
        if(addNewGameFeature()) {
            newFeature();
        }
        playing();
        end();

    }

    virtual ~Game() = default;

protected:
    virtual void start() = 0;
    virtual void end() = 0;
    virtual void playing() = 0;
    virtual bool addNewGameFeature() {
        return false;
    }
    virtual void newFeature() {
        cout << "new feature" << endl;
    }

};


// 象棋类
class Chess : public Game {
protected:
    void start() override {
        std::cout << "Chess Game Started." << std::endl;
    }

    void playing() override {
        std::cout << "Playing Chess Game." << std::endl;
    }

    void end() override {
        std::cout << "Chess Game Finished." << std::endl;
    }

    bool addNewGameFeature() override {
        return true; // 特定情况下我们可能想加入新功能
    }

    void newFeature() override {
        std::cout << "New Chess Strategy Tips." << std::endl;
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
    unique_ptr<Game> chess = make_unique<Chess>();
    chess->play();

    unique_ptr<Game> soccer = make_unique<Poker>();
    soccer->play();

    return 0;
}