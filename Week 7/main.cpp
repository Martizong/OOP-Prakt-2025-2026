#include "Person.h"

int main() {
    Person p1("Ivan", 20);
    Person p2(p1);
    Person p3;

    p3 = p1;

    std::cout << p2.getName() << " " << p2.getAge() << std::endl;
    std::cout << p3.getName() << " " << p3.getAge() << std::endl;

    return 0;
}
