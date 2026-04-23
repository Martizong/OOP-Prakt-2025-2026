#include "Logger.h"

Logger* Logger::instance = nullptr;

void Logger::freeDynamic() {
    delete[] lastMessage;
    lastMessage = nullptr;
}

void Logger::copyDynamic(const Logger& other) {
    if (!other.lastMessage)
        throw std::invalid_argument("Source lastMessage is null");

    char* newMsg = new char[strlen(other.lastMessage) + 1];
    strcpy(newMsg, other.lastMessage);

    freeDynamic();
    lastMessage = newMsg;
}

Logger::Logger() : lastMessage(nullptr), messageCount(0) {}

Logger* Logger::getInstance() {
    if (!instance)
        instance = new Logger();
    return instance;
}

Logger::~Logger() {
    freeDynamic();
}

void Logger::logMessage(const char* msg) {
    if (!msg)
        throw std::invalid_argument("Cannot log null message");

    std::ofstream file("log.txt", std::ios::app);
    if (!file)
        throw std::runtime_error("Failed to open log.txt");

    file << msg << "\n";

    freeDynamic();
    lastMessage = new char[strlen(msg) + 1];
    strcpy(lastMessage, msg);

    messageCount++;
}

int Logger::getMessageCount() const {
    return messageCount;
}

const char* Logger::getLastMessage() const {
    if (!lastMessage)
        throw std::runtime_error("No messages logged yet");
    return lastMessage;
}

void Logger::printAllMessages(std::ostream& os) const {
    std::ifstream file("log.txt");
    if (!file)
        throw std::runtime_error("Failed to open log.txt");

    std::string line;
    while (std::getline(file, line))
        os << line << "\n";
}

void Logger::alternativeLog(const char* msg) {
    if (!msg)
        throw std::invalid_argument("Cannot log null message");

    std::ofstream file("log.txt", std::ios::app);
    if (!file)
        throw std::runtime_error("Failed to open log.txt");

    file << "[ALT] " << msg << "\n";

    freeDynamic();
    lastMessage = new char[strlen(msg) + 1];
    strcpy(lastMessage, msg);

    messageCount++;
}
