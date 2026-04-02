#include <iostream>
#include <cstring>

#pragma warning(disable:4996)

class Secret {
private:
    char task[1024];
    char password[50];
    int loginFails;

    bool checkPassword(const char* pwd) {
        if (!pwd) {
            loginFails++;
            return false;
        }

        if (strcmp(password, pwd) == 0) {
            return true;
        }

        loginFails++;
        return false;
    }

public:
    Secret() {
        task[0] = '\0';
        password[0] = '\0';
        loginFails = 0;
    }

    Secret(const char* t, const char* p) {
        if (t && strlen(t) < 1024) strcpy(task, t);
        else task[0] = '\0';

        if (p && strlen(p) < 50) strcpy(password, p);
        else password[0] = '\0';

        loginFails = 0;
    }

    const char* getTask(const char* pwd) {
        if (checkPassword(pwd)) {
            return task;
        }
        return "Access denied";
    }

    void setPassword(const char* newPassword, const char* oldPassword) {
        if (!newPassword || !oldPassword) return;
        if (strlen(newPassword) >= 50) return;

        if (checkPassword(oldPassword)) {
            strcpy(password, newPassword);
        }
    }

    void setTask(const char* newTask, const char* pwd) {
        if (!newTask || !pwd) return;
        if (strlen(newTask) >= 1024) return;

        if (checkPassword(pwd)) {
            strcpy(task, newTask);
        }
    }

    int getLoginFails() const {
        return loginFails;
    }
};

int main() {
    Secret s("Very secret task", "1234");

    std::cout << s.getTask("wrong") << std::endl;
    std::cout << s.getTask("1234") << std::endl;

    s.setPassword("abcd", "1234");
    s.setTask("New secret task", "abcd");

    std::cout << s.getTask("abcd") << std::endl;

    std::cout << "Fails: " << s.getLoginFails() << std::endl;

    return 0;
}
