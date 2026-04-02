#include <iostream>
#include <cstring>

#pragma warning(disable:4996)

struct Event {
private:
    char* name;

public:
    Event() {
        name = new char[1];
        name[0] = '\0';
    }

    Event(const char* text) {
        if (!text || strlen(text) == 0) {
            name = new char[1];
            name[0] = '\0';
        } else {
            name = new char[strlen(text) + 1];
            strcpy(name, text);
        }
    }

    ~Event() {
        delete[] name;
    }

    const char* getName() const {
        return name;
    }

    void setName(const char* text) {
        delete[] name;

        if (!text || strlen(text) == 0) {
            name = new char[1];
            name[0] = '\0';
            return;
        }

        name = new char[strlen(text) + 1];
        strcpy(name, text);
    }

    void print() const {
        std::cout << name;
    }
};

struct EventLog {
private:
    Event* events;
    int size;
    int capacity;

    void resize() {
        capacity *= 2;
        Event* newArr = new Event[capacity];

        for (int i = 0; i < size; i++) {
            newArr[i].setName(events[i].getName());
        }

        delete[] events;
        events = newArr;
    }

public:
    EventLog() {
        size = 0;
        capacity = 8;
        events = new Event[capacity];
    }

    ~EventLog() {
        delete[] events;
    }

    int getSize() const {
        return size;
    }

    int getCapacity() const {
        return capacity;
    }

    void addEvent(const char* text) {
        if (!text || strlen(text) == 0) {
            std::cout << "Invalid event!\n";
            return;
        }

        if (size == capacity) {
            resize();
        }

        events[size].setName(text);
        size++;
    }

    void print() const {
        if (size == 0) {
            std::cout << "No events.\n";
            return;
        }

        for (int i = 0; i < size; i++) {
            std::cout << i + 1 << ". ";
            events[i].print();
            std::cout << std::endl;
        }
    }
};

int main() {
    EventLog log;

    log.addEvent("Start");
    log.addEvent("Login");
    log.addEvent("Error");
    log.addEvent("Exit");

    log.print();

    std::cout << "Size: " << log.getSize() << std::endl;
    std::cout << "Capacity: " << log.getCapacity() << std::endl;

    return 0;
}
