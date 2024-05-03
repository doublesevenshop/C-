#include <iostream>
#include <string>

using namespace std;

// 抽象消息类
class Message {
public:
    virtual ~Message() {}
    virtual void send(const string& content) = 0;
};

// 普通消息通过电子邮件发送
class NormalEmailMessage : public Message {
public:
    void send(const string& content) override {
        cout << "Sending normal email with content: " << content << endl;
    }
};

// 紧急消息通过短信发送
class UrgentSmsMessage : public Message {
public:
    void send(const string& content) override {
        cout << "Sending urgent SMS with content: " << content << " [urgent]" << endl;
    }
};
// 还可以扩展紧急消息通过电子邮件发送，普通消息通过短信发送等，可以自行添加


int main() {
    // 使用具体消息类型实例发送消息
    NormalEmailMessage normalMsg;
    normalMsg.send("Hello, this is a normal message.");

    UrgentSmsMessage urgentMsg;
    urgentMsg.send("Please respond ASAP!");

    return 0;
}
