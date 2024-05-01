# Template Method 设计模式的核心设计原则

> 所有设计模式的代码以及文档都放在github中，这是我的github链接，https://github.com/doublesevenshop/Design 欢迎大家收藏下载~

**Template Method** 模式的核心在于定义一个操作中的算法的框架，允许子类在不改变算法结构的情况下，重定义算法的某些特定步骤。这种模式主要用来实现代码的复用及扩展的同时，还可以提供固定的算法架构。

### 核心设计原则

1. **封装不变部分，扩展可变部分**：
   Template Method 模式通过把不变的行为搬移到超类，去除子类中的重复代码来体现封装。可变的行为则保留在子类中实现，提供扩展的可能性。

2. **利用继承推迟决策**：
   通过继承，子类可以选择如何实现算法中的某些步骤，即在超类中定义非具体操作（通过虚函数实现），这样的设计让子类可以自主决定如何实现这些步骤。

3. **提供框架和挂钩（hooks）**：
   Template Method 不仅定义算法的框架，还可以提供挂钩来让子类“挂入”或改变算法的具体内容，而不改变算法的结构。

### 使用情景

Template Method 模式适用于以下情况：

1. **多个类有相似的行为，但具体实现细节有所不同**：
   当不同的实现有着部分相同的步骤时，可以使用 Template Method 模式来提取这些共通的步骤到一个公共父类中，通过抽象方法让子类实现具体的细节。我们可以查看这个例子：

```c++

class HttpRequest {
public:
    virtual ~HttpRequest() {}

    // 模板方法定义了请求的固定流程
    void sendRequest() {
        prepare();         // 准备请求
        send();            // 发送请求
        handleResponse();  // 处理响应
    }

protected:
    virtual void prepare() = 0;        // 准备请求的细节由子类实现
    virtual void send() = 0;           // 发送请求的细节由子类实现
    virtual void handleResponse() = 0; // 处理响应的细节由子类实现
};
```
在这里我们有一个http请求，需要进行准备，发送以及处理响应，但是具体的请求类型有很多不同，因此我们可以在子类中进行实现：
```c++
// 子类实现具体请求类型
class GetRequest : public HttpRequest {
protected:
    void prepare() override {
        std::cout << "Preparing GET request..." << std::endl;
    }

    void send() override {
        std::cout << "Sending GET request..." << std::endl;
    }

    void handleResponse() override {
        std::cout << "Handling response for GET request..." << std::endl;
    }
};

class PostRequest : public HttpRequest {
protected:
    void prepare() override {
        std::cout << "Preparing POST request..." << std::endl;
    }

    void send() override {
        std::cout << "Sending POST request..." << std::endl;
    }

    void handleResponse() override {
        std::cout << "Handling response for POST request..." << std::endl;
    }
};
```

最终我们在main函数中只需要调用sendRqeust即可实现不同类型的请求处理：
```c++
int main() {
    HttpRequest* getRequest = new GetRequest();
    getRequest->sendRequest();  // 执行GET请求流程

    HttpRequest* postRequest = new PostRequest();
    postRequest->sendRequest(); // 执行POST请求流程

    delete getRequest;
    delete postRequest;
    return 0;
}
```

2. **代码复用**：
   当多个类的方法中包含重复的代码时，Template Method 模式是一种将共有代码移动到单一位置，防止代码冗余的策略。
假设我们现在有一个报表，我们需要生成报表，包括获取数据，处理数据，格式化以及打印四个步骤，那么我们可能有许多种不同类型的报表，那么针对具体的报表，我们都可以用统一的处理流程：
```c++
class Report {
public:
    virtual ~Report() {}

    // 模板方法定义了报表生成的流程
    void generate() {
        fetchData();        // 获取数据
        processData();      // 处理数据
        formatReport();     // 格式化报表
        printReport();      // 打印报表
    }

protected:
    virtual void fetchData() = 0;        // 获取数据由子类实现
    virtual void processData() = 0;      // 处理数据由子类实现
    virtual void formatReport() = 0;     // 格式化报表由子类实现
    virtual void printReport() = 0;      // 打印报表由子类实现
};
```
对于具体的不同报表类，我们都可以去进行继承使用：
```c++
// 具体报表类：SalesReport
class SalesReport : public Report {
protected:
    void fetchData() override {
        std::cout << "Fetching sales data..." << std::endl;
    }

    void processData() override {
        std::cout << "Processing sales data..." << std::endl;
    }

    void formatReport() override {
        std::cout << "Formatting sales report..." << std::endl;
    }

    void printReport() override {
        std::cout << "Printing sales report..." << std::endl;
    }
};

// 具体报表类：InventoryReport
class InventoryReport : public Report {
protected:
    void fetchData() override {
        std::cout << "Fetching inventory data..." << std::endl;
    }

    void processData() override {
        std::cout << "Processing inventory data..." << std::endl;
    }

    void formatReport() override {
        std::cout << "Formatting inventory report..." << std::endl;
    }

    void printReport() override {
        std::cout << "Printing inventory report..." << std::endl;
    }
};

int main() {
    Report* salesReport = new SalesReport();
    salesReport->generate(); // 生成销售报表

    Report* inventoryReport = new InventoryReport();
    inventoryReport->generate(); // 生成库存报表

    delete salesReport;
    delete inventoryReport;
    return 0;
}
```
Template Method模式可以将报表生成的公共流程定义在一个父类中，并且在子类实现具体的细节，从而避免代码冗余。


3. **控制子类扩展**：
   你可以在模板方法中不仅定义抽象的操作，也定义具体的操作和顺序，它定义了一个算法的骨架。通过这种方式，可以准确控制子类的扩展。

4. **关键过程的固定算法**：
   在需要固定算法结构，同时允许算法具有一定的灵活性和适应性时，可以使用 Template Method 模式。例如，在游戏中，游戏的启动、进行和结束是固定的，但具体如何启动、进行和结束则可以由具体的游戏来决定。

### 示例中的应用

在代码示例中：
```c++
#include <iostream>
#include <memory>
#include <utility>
using namespace std;
// 抽象基类
class Game {
public:
    // 定义算法的骨架，这一个play的方法是固定不变的
    void play() {
        start();
        playing();
        end();
    }
    virtual ~Game() {}
protected:
    virtual void start() = 0;   // 交给子类实现
    virtual void playing() = 0; // 交给子类实现
    virtual void end() = 0;     // 交给子类实现
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
```
如果象棋或者扑克想添加新的功能该怎么办呢？那么我们就需要一个更加固定的算法框架：

下面是新修改之后的框架：
```c++
#include <iostream>
#include <memory>
#include <utility>

using namespace std;


class Game {
public:
    // 模板方法
    void play() {
         start();
         // 此处为新添加的功能
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

    // 此处为新添加的功能
    virtual bool addNewGameFeature() {
        return false;
    }
    // 此处为新添加的功能
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
```
- **`Game` 类定义了游戏的基本流程**（`play` 方法），这是一个固定的算法骨架。
- **子类 `Chess`, `Poker` 分别实现这些步骤**，根据不同游戏的需要重定义 `start`, `playing`, 和 `end` 方法。
- **新功能的引入**（如在 `Chess` 中的 `newFeature` 方法和 `addNewGameFeature` 钩子）展示了模板方法的扩展性，允许在不改变主流程的情况下插入新的行为。




Template Method模式最关键的一点在于，通过继承实现固定算法的框架，并且允许子类实现特定的步骤，从而实现代码复用，控制子类扩展以及保证算法的稳定性。


