#include "Logger.h"

int main() {
    Logger* log = Logger::getInstance();

    log->logMessage("Program started");
    log->logMessage("Loading modules...");
    log->alternativeLog("Alternative logging test");

    std::cout << "Last message: " << log->getLastMessage() << "\n";
    std::cout << "Total messages: " << log->getMessageCount() << "\n\n";

    std::cout << "=== All messages ===\n";
    log->printAllMessages(std::cout);

    return 0;
}

