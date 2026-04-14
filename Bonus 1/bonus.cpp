#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;


const int MAX_LEN = 128;
const int MAX_USERS = 100;


void safeCopy(char* dest, const char* src) {
    strncpy(dest, src, MAX_LEN - 1);
    dest[MAX_LEN - 1] = '\0';
}


struct User {
    char name[MAX_LEN];
    char email[MAX_LEN];
    char password[MAX_LEN];
};


void saveUserText(ofstream& out, const User& u) {
    out << u.name << '\n'
        << u.email << '\n'
        << u.password << '\n';
}

void loadUserText(ifstream& in, User& u) {
    in.getline(u.name, MAX_LEN);
    in.getline(u.email, MAX_LEN);
    in.getline(u.password, MAX_LEN);
}


struct System {
    User users[MAX_USERS];
    int userCount;
};


void saveSystem(const char* filename, const System& sys) {
    ofstream out(filename);
    if (!out) {
        cout << "Error: cannot open users file for writing\n";
        return;
    }

    out << sys.userCount << '\n';
    for (int i = 0; i < sys.userCount; i++)
        saveUserText(out, sys.users[i]);
}


void loadSystem(const char* filename, System& sys) {
    ifstream in(filename);
    if (!in) {
        sys.userCount = 0;
        return;
    }

    int count;
    if (!(in >> count)) {
        sys.userCount = 0;
        return;
    }

    if (count < 0 || count > MAX_USERS) {
        sys.userCount = 0;
        return;
    }

    sys.userCount = count;
    in.ignore();

    for (int i = 0; i < sys.userCount; i++)
        loadUserText(in, sys.users[i]);
}



bool emailExists(const System& sys, const char* email) {
    for (int i = 0; i < sys.userCount; i++)
        if (strcmp(sys.users[i].email, email) == 0)
            return true;
    return false;
}

bool registerUser(System& sys, const char* name, const char* email, const char* password) {
    if (sys.userCount >= MAX_USERS) return false;
    if (emailExists(sys, email)) return false;

    safeCopy(sys.users[sys.userCount].name, name);
    safeCopy(sys.users[sys.userCount].email, email);
    safeCopy(sys.users[sys.userCount].password, password);

    sys.userCount++;
    return true;
}

bool loginUser(const System& sys, const char* email, const char* password) {
    for (int i = 0; i < sys.userCount; i++)
        if (strcmp(sys.users[i].email, email) == 0 &&
            strcmp(sys.users[i].password, password) == 0)
            return true;
    return false;
}


struct Stats {
    int registrations;
    int successfulLogins;
    int failedLogins;
};

void loadStats(const char* filename, Stats& s) {
    ifstream in(filename);
    if (!in) {
        s.registrations = 0;
        s.successfulLogins = 0;
        s.failedLogins = 0;
        return;
    }

    in >> s.registrations >> s.successfulLogins >> s.failedLogins;
}

void saveStats(const char* filename, const Stats& s) {
    ofstream out(filename);
    if (!out) return;

    out << s.registrations << "\n"
        << s.successfulLogins << "\n"
        << s.failedLogins << "\n";
}



void saveLastSession(const char* filename, const char* email) {
    ofstream out(filename);
    if (!out) return;
    out << email;
}

void showLastSession(const char* filename) {
    ifstream in(filename);
    if (!in) return;

    char email[MAX_LEN];
    in.getline(email, MAX_LEN);

    if (strlen(email) > 0)
        cout << "Last logged user: " << email << "\n";
}



int main() {
    System sys;
    Stats stats;

    sys.userCount = 0;
    stats.registrations = 0;
    stats.successfulLogins = 0;
    stats.failedLogins = 0;

    char usersFile[256];
    char statsFile[256];
    char sessionFile[256];

    cout << "Enter users file name:\n> ";
    cin.getline(usersFile, 256);

    cout << "Enter stats file name:\n> ";
    cin.getline(statsFile, 256);

    cout << "Enter last session file name:\n> ";
    cin.getline(sessionFile, 256);

    loadSystem(usersFile, sys);
    loadStats(statsFile, stats);
    showLastSession(sessionFile);

    while (true) {
        cout << "Enter command:\n> ";

        string cmd;
        cin >> cmd;

        if (cmd == "register") {
            cin.ignore();
            char name[MAX_LEN], email[MAX_LEN], password[MAX_LEN];

            cout << "Enter name:\n> ";
            cin.getline(name, MAX_LEN);

            cout << "Enter email:\n> ";
            cin.getline(email, MAX_LEN);

            cout << "Enter password:\n> ";
            cin.getline(password, MAX_LEN);

            if (registerUser(sys, name, email, password)) {
                cout << "Registration successful\n";
                stats.registrations++;
            } else {
                cout << "Registration failed (email exists or system full)\n";
            }
        }

        else if (cmd == "login") {
            cin.ignore();
            char email[MAX_LEN], password[MAX_LEN];

            cout << "Enter email:\n> ";
            cin.getline(email, MAX_LEN);

            cout << "Enter password:\n> ";
            cin.getline(password, MAX_LEN);

            if (loginUser(sys, email, password)) {
                cout << "Login successful\n";
                stats.successfulLogins++;
                saveLastSession(sessionFile, email);
            } else {
                cout << "Login failed\n";
                stats.failedLogins++;
            }
        }

        else if (cmd == "exit") {
            saveSystem(usersFile, sys);
            saveStats(statsFile, stats);
            cout << "Exiting...\n";
            break;
        }

        else {
            cout << "Unknown command\n";
        }
    }

    return 0;
}
