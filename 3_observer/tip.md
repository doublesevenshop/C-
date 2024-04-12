# Observer观察者模式
## 动机
在软件构建的过程中，我们需要为某些对象建立一种通知依赖关系，一个对象的状态发生改变，所有依赖对象都能够得到通知。但是如果依赖过于紧密，则软件不能很好地抵御变化。

面向对象可以将这种依赖关系弱化，并且使其更加稳定，从而实现软件体系结构的松耦合。

例如在一个任务处理中，我们希望加一个进度条来查看处理进度，可以查看如下案例：
```c++
class A{
public:
    void split() {
        // 读取

        // 分批处理
        for(int i = 0; i < num; i++) {
            // ...
        
            // 在这个地方加入进度条处理
            if(m_processBar != nullptr) {
                // 开始显示进度
            }
        }
    }
private:
    ProcessBar* m_processBar;
};
```

我们发现上述代码是在for循环中去添加进度显示，大致看的时候是没什么问题的，但是这个实现是有哪些问题呢？

**违背了依赖倒置原则**，我们发现A会产生编译时依赖ProcessBar，而这个进度条是一个实现细节，我们无法保证ProcessBar一直都是一个进度条的实现，它可能是百分比/图形化/非图形化等等各种显示，它会导致我们产生实现细节的困扰。

解决方案就是我们不依赖它本身，而是依赖它的抽象基类，但是如果没有基类怎么办？——自行抽象

我们发现进度条实际上是一条通知，通知当前进度

```c++
// 一个抽象的通知机制，只是一个接口，不含具体实现
class IProgress{
public:
    virtual void Notice() = 0;
    virtual ~IProgress(){}

};

class A{
public:
    void split() {
        // 读取

        // 分批处理
        for(int i = 0; i < num; i++) {
            // ...
        
            // 在这个地方加入进度条处理
            if(m_iprogress != nullptr) {
                m_iprogress->Notice(); // 进行通知，与实际处理无关
            }
        }
    }
private:
    IProgress* m_iprogress;
};
```

这样我们就通过一个抽象接口来解决通知问题，实际上还可以再优化一些
```c++
// 一个抽象的通知机制，只是一个接口，不含具体实现
class IProgress{
public:
    virtual void Notice() = 0;
    virtual ~IProgress(){}

};

class A{
public:
    void split() {
        // 读取

        // 分批处理
        for(int i = 0; i < num; i++) {
            
            // 开始处理

            // 通知机制
            onProgress();
        }
    }
protected:
    void onProgress() {
        // 在这个地方加入进度条处理
        if(m_iprogress != nullptr) {
            m_iprogress->Notice(); // 进行通知，与实际处理无关
        }
    }
private:
    IProgress* m_iprogress;
};
```

我们现在已经支持了一个观察者，那么当有多个观察者我们该怎么办呢？我们希望所有的对象都是松耦合。

我们接着修改:

```c++
// 一个抽象的通知机制，只是一个接口，不含具体实现
class IProgress{
public:
    virtual void Notice() = 0;
    virtual ~IProgress(){}

};

class A{
public:
    void split() {
        // 读取

        // 分批处理
        for(int i = 0; i < num; i++) {
            
            // 开始处理

            // 通知机制
            onProgress();
        }
    }
    // 增加一个插入和删除观察者模式的接口
    void addIProgress(IProgress* iprogress) {
        m_iprogressVector.push_back(iprogress);
    }

protected:
    void onProgress() {
        // 在这里改成迭代器去寻找，针对每一个具体的通知机制去执行
        auto iterator = m_progressVector.begin();
        while(iterator != m_progressVector.end()) {
            iterator->Notice();
        }
    }
private:
    // 修改这个地方
    // IProgress* m_iprogress;
    list<IProgress*> m_iprogressVector; // 支持多个观察者
};
```
上述没有写内存管理，还需要进行智能指针来进行内存管理

定义对象间的一种一对多的依赖关系，当一个对象的状态发生改变时，所有依赖它的对象都得到通知并且自动更新。

观察者模式是基于事件的UI框架中非常常用的一个模式，也是MVC模式的重要组成部分