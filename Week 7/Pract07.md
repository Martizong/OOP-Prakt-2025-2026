## Копиращ конструктор и оператор =
Заедно с конструктора по подразбиране и деструктора във всеки клас се дефинират и следните член-функции:

- Копиращ конструктор - конструктор, който приема обект от същия клас и създава новият обект като негово копие.
- Оператор= - функция/оператор, който приема обект от същия клас и променя данните на съществуващ обект от същия клас (обектът от който извикваме функцията).

## При липсата на дефиниран/и копиращ конструктор и/или оператор=, компилаторът автоматично създава такива по подразбиране.

## Забележка: Копиращият конструктор създава нов обект, а оператор= модифицира вече съществуващ такъв!

```c++
#include <iostream>

struct Test {
    Test() {
        std::cout << "Default constructor\n";
    }

    Test(const Test& other) {
        std::cout << "Copy constructor\n";
    }

    Test& operator=(const Test& other) {
        std::cout << "operator=\n";
	    return *this;
    }

    ~Test() {
        std::cout << "Destructor\n";
    }
};

void f(Test object) {
    //do Stuff
}

void g(Test& object) {
    //do Stuff
}

int main()
{
    Test t;      //Default constructor;

    Test t2(t);  // Copy constructor
    Test t3(t2); // Copy constructor	
    t2 = t3;     // operator=
    t3 = t;      // operator=

    Test newTest = t; //Copy constructor !!!!!!!

    f(t);   // Copy constructor	
    g(t);   // nothing. We are passing it as a reference. We are not copying it!

    Test* ptr = new Test();  // Default constructor // we create a new object in the dynamic memory. The destructor must be invoked explicitly  (with delete)

    delete ptr; // Destructor	

} //Destructor Destructor Destructor Destructor
```

## Голямата тройка

- Конструктор за копиране
- Оператор =
- Деструктор

## Да разгледаме следната структура:

```c++
struct Test
{	
	A obj1;
	B obj2;
	C obj3;
};
```

Понеже функциите (от голямата тройка) не са дефинирани в структурата, компилаторът ще създаде такива:

```c++
int main()
{
   Test currentObject; //default constructor
    
   Test object2(currentObject); //copy constructor
    
   currentObject = object2; //operator =

} //destructor (x2)
```
Кодът се компилира успешно и функциите имат правилно поведение.

## Проблем при функциите, генерирани от компилатора:

Да разгледаме следния код:

```c++
struct Person
{
   PersonA(const char* name, int age)
   {
   	this->name = new char[strlen(name) + 1];
   	strcpy(this->name, name);
   	this->age = age;
   }
private:

   char* name;
   int age;
};

int main()
{
   Person p1;
   Person p2(p1);
}
```
Горното извикване на копиращия конструктор има неправилно поведение:

<img width="614" height="313" alt="image" src="https://github.com/user-attachments/assets/54a155d9-90de-408e-9eca-032af9618848" />

Това е shallow copy. В p2 са се копирали стойностите на p1, което довежда до споделяне на една и съща динамична памет. В тази ситуация ще трябва да се имплементират експлицитно копиращия конструктор, оператора за присвояване и деструктора, защото генерираните от компилатора не биха работили правилно.

Правилното поведение на копиращия конструктор е следното:

<img width="638" height="316" alt="image" src="https://github.com/user-attachments/assets/d83e5a2c-8af3-41b1-8d1d-0b5af1375670" />

Собствена имплементация на функциите за копиране и деструктора:

```c++
void Person::freeDynamic() {
    delete[] name;
    name = nullptr;
}

void Person::copyDynamic(const Person& other) {
    if (!other.name) {
        name = new char[1];
        name[0] = '\0';
        return;
    }

    name = new char[std::strlen(other.name) + 1];
    std::strcpy(name, other.name);
}


Person::Person(const Person& other) {
    copyDynamic(other);
    age = other.age;
}

Person& Person::operator=(const Person& other) {
    if (this != &other) {
        freeDynamic();
        copyDynamic(other);
        age = other.age;
    }
    return *this;
}

Person::~Person() {
    freeDynamic();
}
```

## Задачи


##Задачи с материал от миналата седмица за упражнение:

### Задача 1  
1. Да се реализира стуктура Song, който описва музикално изпълнение със следните
свойства:
- заглавие (низ до 100 символа)
- изпълнител (низ до 100 символа)
- година на издаване (цяло число)
- дължина на песента (цяло число секунди)
- оригинал (ако изпълнението е “кавър”, указател към оригиналната песен)
2. За структурата Song да се реализират:
- да се защитят нужните член-дании
- подходящи конструктори, селектори и мутатори
- операция за извеждане на информация за песен на стандартния изход
3. Структура Album, който описва албум със следните полета:
- списък от песни с най-много 100 песни
- име на албума (низ до 100 символа)
4. За структурата Album да се реализират
- да се защитят нужните член-дании
- подходящи конструктори, селектори и мутатори
- операция за извеждане на информация за албум на стандартния изход
- операция getLength, която намира дължината на албума в секунди
- операция getArtist, която връща името на изпълнителя на албума, ако всички
песни са на един и същ изпълнител, или “Various Artists”, ако албумът се
състои от песни на повече от един изпълнител
- операция findSong, която връща указател към първата песен в албума с
дадено име, или nullptr, ако такава не е намерена

### Задача 2
Да се създаде клас Alcohol, съдържащ полета за цена и име на алкохола - символен низ, заделен с произволна големина. 
Да се реализират следните функции:

- конструктор по подразбиране
- конструктор с параметри
- сетъри и гетъри за член-данните
- деструктор, грижещ се за динамичната памет
- метод за отпечатване на стандартния изход 
- Бонус: Можете да направите функции за четене и записване в текстови и бинарни файлове.
