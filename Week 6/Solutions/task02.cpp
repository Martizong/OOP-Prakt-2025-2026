#include <iostream>
#include <cstring>

#pragma warning(disable:4996)

struct BankAccount {
private:
    char owner[50];
    char iban[35];
    double balance;
    double savings;
    bool isLocked;

public:
    BankAccount() {
        owner[0] = '\0';
        iban[0] = '\0';
        balance = 0;
        savings = 0;
        isLocked = true;
    }

    void setOwner(const char* newOwner) {
        if (!newOwner || strlen(newOwner) >= 50) return;
        strcpy(owner, newOwner);
    }

    void setIBAN(const char* newIBAN) {
        if (!newIBAN || strlen(newIBAN) >= 35) return;
        strcpy(iban, newIBAN);
    }

    const char* getIBAN() const {
        return iban;
    }

    bool isAccountLocked() const {
        return isLocked;
    }

    double getTotalMoney() const {
        return balance + savings;
    }

    void deposit(double amount) {
        if (amount <= 0) return;
        balance += amount;
    }

    void withdraw(double amount) {
        if (isLocked || amount <= 0 || amount > balance) return;
        balance -= amount;
    }

    void addToSavings(double amount) {
        if (amount <= 0 || amount > balance) return;
        balance -= amount;
        savings += amount;
    }

    void withdrawFromSavings(double amount) {
        if (amount <= 0 || amount > savings) return;
        savings -= amount;
        balance += amount;
    }

    void lock() {
        isLocked = true;
    }

    void unlock() {
        isLocked = false;
    }

    void close() {
        owner[0] = '\0';
        iban[0] = '\0';
        balance = 0;
        savings = 0;
        isLocked = true;
    }

    void print() const {
        std::cout << owner << " | " << iban
                  << " | Balance: " << balance
                  << " | Savings: " << savings
                  << " | Locked: " << (isLocked ? "Yes" : "No")
                  << std::endl;
    }
};

struct Bank {
private:
    char name[20];
    BankAccount accounts[1000];
    int size;

    int findIndex(const char* iban) const {
        if (!iban) return -1;

        for (int i = 0; i < size; i++) {
            if (strcmp(accounts[i].getIBAN(), iban) == 0)
                return i;
        }
        return -1;
    }

public:
    Bank() {
        name[0] = '\0';
        size = 0;
    }

    void setName(const char* newName) {
        if (!newName || strlen(newName) >= 20) return;
        strcpy(name, newName);
    }

    void addAccount(const BankAccount& acc) {
        if (size >= 1000) return;
        if (strlen(acc.getIBAN()) == 0) return;
        if (findIndex(acc.getIBAN()) != -1) return;

        accounts[size] = acc;
        size++;
    }

    void removeAccount(const char* iban) {
        int index = findIndex(iban);
        if (index == -1) return;

        for (int i = index; i < size - 1; i++) {
            accounts[i] = accounts[i + 1];
        }

        accounts[size - 1].close();
        size--;
    }

    double getTotalMoney() const {
        double sum = 0;
        for (int i = 0; i < size; i++) {
            sum += accounts[i].getTotalMoney();
        }
        return sum;
    }

    void transfer(const char* fromIBAN, const char* toIBAN, double amount) {
        if (amount <= 0) return;

        int fromIndex = findIndex(fromIBAN);
        int toIndex = findIndex(toIBAN);

        if (fromIndex == -1 || toIndex == -1) return;
        if (accounts[fromIndex].isAccountLocked()) return;

        double before = accounts[fromIndex].getTotalMoney();
        accounts[fromIndex].withdraw(amount);

        if (accounts[fromIndex].getTotalMoney() == before) return;

        accounts[toIndex].deposit(amount);
    }

    void lockAccount(const char* iban) {
        int index = findIndex(iban);
        if (index == -1) return;
        accounts[index].lock();
    }

    void unlockAccount(const char* iban) {
        int index = findIndex(iban);
        if (index == -1) return;
        accounts[index].unlock();
    }

    void print() const {
        for (int i = 0; i < size; i++) {
            accounts[i].print();
        }
    }
};

int main() {
    Bank bank;
    bank.setName("MyBank");

    BankAccount a1;
    a1.setOwner("Ivan");
    a1.setIBAN("BG111");
    a1.unlock();
    a1.deposit(1000);

    BankAccount a2;
    a2.setOwner("Petar");
    a2.setIBAN("BG222");
    a2.unlock();
    a2.deposit(500);

    bank.addAccount(a1);
    bank.addAccount(a2);

    bank.transfer("BG111", "BG222", 200);

    bank.print();

    std::cout << "Total money: " << bank.getTotalMoney() << std::endl;

    return 0;
}
