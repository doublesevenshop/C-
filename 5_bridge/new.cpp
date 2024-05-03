#include <iostream>
#include <string>

using namespace std;

// 消息发送器接口
class MessageSender {
public:
    virtual ~MessageSender() {}
    virtual void send(const string& content) = 0;
};

// 通过电子邮件发送消息
class EmailSender : public MessageSender {
public:
    void send(const string& content) override {
        cout << "Sending email with content: " << content << endl;
    }
};

// 通过短信发送消息
class SmsSender : public MessageSender {
public:
    void send(const string& content) override {
        cout << "Sending SMS with content: " << content << endl;
    }
};

// 抽象消息类
class Message {
protected:
    MessageSender* sender;
public:
    Message(MessageSender* sender) : sender(sender) {}
    virtual ~Message() {}
    virtual void send(const string& content) = 0;
};

// 普通消息
class NormalMessage : public Message {
public:
    NormalMessage(MessageSender* sender) : Message(sender) {}
    void send(const string& content) override {
        cout << "NormalMessage: ";
        sender->send(content);
    }
};

// 紧急消息
class UrgentMessage : public Message {
public:
    UrgentMessage(MessageSender* sender) : Message(sender) {}
    void send(const string& content) override {
        cout << "UrgentMessage: ";
        sender->send(content + " [urgent]");
    }
};

int main() {
    EmailSender email;
    SmsSender sms;

    // 创建一个通过电子邮件发送普通消息的实例
    NormalMessage normalMsg(&email);
    normalMsg.send("Hello, this is a normal message.");

    // 创建一个通过短信发送紧急消息的实例
    UrgentMessage urgentMsg(&sms);
    urgentMsg.send("Please respond ASAP!");

    return 0;
}
