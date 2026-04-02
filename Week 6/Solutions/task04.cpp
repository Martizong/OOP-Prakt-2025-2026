#include <iostream>
#include <cstring>

#pragma warning(disable:4996)

struct Message {
private:
    char content[1000];
    char sender[50];
    char receiver[50];
    bool isRead;

public:
    Message() {
        content[0] = '\0';
        sender[0] = '\0';
        receiver[0] = '\0';
        isRead = false;
    }

    void setMessage(const char* text, const char* from, const char* to) {
        if (!text || !from || !to) return;
        if (strlen(text) >= 1000) return;
        if (strlen(from) >= 50) return;
        if (strlen(to) >= 50) return;

        strcpy(content, text);
        strcpy(sender, from);
        strcpy(receiver, to);
        isRead = false;
    }

    void markAsRead() {
        isRead = true;
    }

    const char* getContent() const { return content; }
    const char* getSender() const { return sender; }
    const char* getReceiver() const { return receiver; }
    bool getIsRead() const { return isRead; }
};

struct User {
private:
    char username[50];
    char email[50];
    char password[50];

    Message sent[100];
    Message received[100];

    int sentCount;
    int receivedCount;

public:
    User() {
        username[0] = '\0';
        email[0] = '\0';
        password[0] = '\0';
        sentCount = 0;
        receivedCount = 0;
    }

    void setUser(const char* u, const char* e, const char* p) {
        if (!u || !e || !p) return;
        if (strlen(u) >= 50 || strlen(e) >= 50 || strlen(p) >= 50) return;

        strcpy(username, u);
        strcpy(email, e);
        strcpy(password, p);
    }

    const char* getUsername() const { return username; }
    const char* getEmail() const { return email; }
    const char* getPassword() const { return password; }

    void sendMessage(User& receiver, const char* text) {
        if (!text || strlen(text) >= 1000) return;
        if (sentCount >= 100 || receiver.receivedCount >= 100) return;
        if (strcmp(username, receiver.username) == 0) return;

        Message m;
        m.setMessage(text, username, receiver.username);

        sent[sentCount++] = m;
        receiver.received[receiver.receivedCount++] = m;
    }

    void printInbox() const {
        std::cout << "Inbox of " << username << ":\n";
        for (int i = 0; i < receivedCount; i++) {
            std::cout << received[i].getSender()
                      << ": " << received[i].getContent()
                      << " | Read: " << (received[i].getIsRead() ? "Yes" : "No")
                      << std::endl;
        }
    }
};

struct SocialMedia {
private:
    char name[50];
    User users[100];
    int usersCount;

    int findUserByEmail(const char* email) const {
        if (!email) return -1;

        for (int i = 0; i < usersCount; i++) {
            if (strcmp(users[i].getEmail(), email) == 0)
                return i;
        }
        return -1;
    }

public:
    SocialMedia() {
        name[0] = '\0';
        usersCount = 0;
    }

    void setName(const char* n) {
        if (!n || strlen(n) >= 50) return;
        strcpy(name, n);
    }

    void registerUser(const User& u) {
        if (usersCount >= 100) return;
        if (findUserByEmail(u.getEmail()) != -1) return;

        users[usersCount++] = u;
    }

    bool login(const char* email, const char* pass) const {
        if (!email || !pass) return false;

        for (int i = 0; i < usersCount; i++) {
            if (strcmp(users[i].getEmail(), email) == 0 &&
                strcmp(users[i].getPassword(), pass) == 0) {
                return true;
            }
        }
        return false;
    }

    void sendMessage(const char* senderEmail,
                     const char* receiverEmail,
                     const char* text) {

        if (!senderEmail || !receiverEmail || !text) return;

        int s = findUserByEmail(senderEmail);
        int r = findUserByEmail(receiverEmail);

        if (s == -1 || r == -1) return;

        users[s].sendMessage(users[r], text);
    }

    void printAll() const {
        for (int i = 0; i < usersCount; i++) {
            users[i].printInbox();
            std::cout << std::endl;
        }
    }
};

int main() {
    SocialMedia sm;
    sm.setName("MyApp");

    User u1, u2;

    u1.setUser("Ivan", "ivan@mail.com", "123");
    u2.setUser("Petar", "petar@mail.com", "456");

    sm.registerUser(u1);
    sm.registerUser(u2);

    if (sm.login("ivan@mail.com", "123")) {
        sm.sendMessage("ivan@mail.com", "petar@mail.com", "Hello!");
    }

    sm.printAll();

    return 0;
}
