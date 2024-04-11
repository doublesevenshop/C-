#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Sorter{
public:
    virtual void sort(vector<int>& data, const string& type) {

        // 在这个地方用到了分支语句，这个地方就是策略模式的应用场景
        if(type == "ascending") {
            std::sort(data.begin(), data.end());
        } else if(type == "descending") {
            std::sort(data.rbegin(), data.rend());
        } else {
            cout << "Invalid type" << endl;
        }
    }
    void print(const vector<int>& data) {
        for(auto& d : data) {
            cout << d << " ";
        }
        cout << endl;
    }
};


int main() {
    vector<int> data = {8, 2, 4, 5, 1};
    Sorter sorter;
    sorter.sort(data, "ascending");
    sorter.print(data);
    sorter.sort(data, "descending");
    sorter.print(data);


    return 0;
}