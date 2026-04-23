#pragma once
#include <iostream>
#include <fstream>
#include <cstring>
#include <stdexcept>

class Logger {
private:
    char* lastMessage;
    int messageCount;

    static Logger* instance;

    void freeDynamic();
    void copyDynamic(const Logger& other);

    Logger(); // private constructor

public:
    static Logger* getInstance();

    Logger(const Logger& other) = delete;
    Logger& operator=(const Logger& other) = delete;

    ~Logger();

    void logMessage(const char* msg);
    int getMessageCount() const;
    const char* getLastMessage() const;

    void printAllMessages(std::ostream& os) const;

    void alternativeLog(const char* msg);
};
