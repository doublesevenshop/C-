/*
    这里只是一个简单的例子实现，展示了如何使用分支来实现不同的进度条显示效果。
    在new.cpp中，我们将使用观察者模式来完整的实现这个功能。
*/

#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

/* 清屏函数 */
void clearConsole() {
    cout << "\033[2J\033[1;1H";
}

/* 简单文本进度条 */
void displayProgressBar(int value) {
    cout << "Progress: " << value << " % " << endl;
}

/* 图形化进度条 */
void displayGraphBar(int value) {
    cout << "[";
    for (int i = 0; i < 50; i++) {
        if (i < value / 2) {
            cout << "=";
        } else {
            cout << " ";
        }
    }
    cout << "]" << value << "%" << endl;
}

/* 数字指示器 */
void displayNumericIndicator(int value) {
    cout << "Completed: " << value << " of 100\n";
}

int main() {
    int progress = 0;

    // 模拟进度变化
    for (int i = 0; i <= 100; i += 5) {
        clearConsole();  // 清屏
        progress = i;

        // 判断并显示进度条
        if (progress <= 50) {
            displayProgressBar(progress);
        } else if (progress <= 75) {
            displayGraphBar(progress);
        } else {
            displayNumericIndicator(progress);
        }

        this_thread::sleep_for(chrono::milliseconds(500));
    }

    return 0;
}
