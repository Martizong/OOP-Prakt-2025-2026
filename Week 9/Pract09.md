## Композиция на обекти. Масиви от обекти.

# Композиция – класове като елементи на други класове (влагане на класове).
Един клас може да включва в себе си обекти от други класове като член-данни.

Когато обект от даден клас се дефинира, автоматично се извиква неговият конструктор.

Ако класът съдържа член-данни, в неговия конструктор трябва да се укаже кои конструктори на член-данните да се извикват.

Пример 1:

```c++
class A
{
 .
 .
 .
}
class B
{
	 int n;
	 A obj;
}
```
В тази ситуация се извикват default-ните конструктори на n и obj.

Пример 2

```c++
class A
{
	A(int a, int b)
 .
 .
 .
}
class B
{
	B() : obj(1, 2)
	{}
	
	int n;
	A obj;
}
```
Тук A няма default-ен конструктор. Това означава, че в конструктора на B трябва да се извика експлицитно някой от неговите конструктори.


## Композиция на обекти с динамична памет

Когато имаме композиция и в главния клас има динамично заделяне на памет, то трябва в реализацията на копи-конструктора и оператор= експлицитно 
да се извикват копи-конструкторите и оператора = за всички член-данни (композирани обекти).


```c++
#include <cstddef>
#include <stdexcept>

class B;

class A {
private:
    int* arr;
    size_t size;
    B nestedObject;

    void freeDynamic() {
        delete[] arr;
        arr = nullptr;
    }

    int* copyDynamic(const A& other) {
        if (!other.arr && other.size > 0)
            throw std::invalid_argument("Null source array");

        int* newArr = nullptr;

        try {
            newArr = new int[other.size];
            for (size_t i = 0; i < other.size; i++)
                newArr[i] = other.arr[i];
        }
        catch (...) {
            delete[] newArr;
            throw;
        }

        return newArr;
    }

public:
    A(int n) : size(n) {
        if (n == 0) {
            arr = nullptr;
            return;
        }
        arr = new int[n];
    }

    A(const A& other)
        : nestedObject(other.nestedObject), size(other.size)
    {
        arr = copyDynamic(other);
    }

    A& operator=(const A& other) {
        if (this != &other) {
            A temp(other);       

            freeDynamic();       
            arr = temp.arr;      
            temp.arr = nullptr;  

            nestedObject = other.nestedObject;
            size = other.size;
        }
        return *this;
    }

    ~A() {
        freeDynamic();
    }
};
```

# ВАЖНО: Деструкторите на член-данните НЕ трябва да се извикват експлицитно в деструктора на класа.

# Масиви от обекти

## Статичен масив от обекти

```c++
class A;
int main()
{
	A arr[5]; //5 def. constr.
} //5 destr
```

Създава статичен масив с 5 обекта от тип A. На всеки от тях се е извикал конструктора по подразбиране. Масивът ще се изтрие, когато приключи функцията.

## Статичен масив от указатели към обекти

```c++
class A;
int main()
{
	A* arr[5]; //5 empty pointers.
	
	arr[0] = new A();
	arr[2] = new A();
	
	delete arr[0];
	delete arr[2];
}
```

Създава статичен масив с 5 указателя . Само на 2 от тези указатели присвояваме обекти, които са заделени в динамичната памет. Масивът ще се изтрие, когато приключи функцията.

## Динамичен масив от обекти

```c++
class A;
int main()
{
	A* arr = new A[5]; //5 def constr.
	delete[] arr; //5 destr
} 
```
Създава динамичен масив с 5 обекта от тип A. На всеки от тях се е извикал конструктора по подразбиране. Масивът ще се изтрие (и ще се изтрият обектите), когато се извика delete[] върху него.

## Динамичен масив от указатели към обекти

Пример 1:

```c++
class SomeCollection
{
   A** data;
   //other things
};
```


<img width="463" height="321" alt="image" src="https://github.com/user-attachments/assets/7e72339e-cb60-4e48-be6a-6a8b517c95ff" />

## Какви са ползите:

- Бързо разместване на обектите в колецкията - не се изисква да се копират. Само разместваме указателите
- Не се изисква същестуването на деф. контруктор на A.
- Възможно е да имаме "празна клетка", като се възползваме от възможната nullptr стойност.

Пример 2:

```c++
class A;
int main()
{
	A** arr = new A*[5]; //5 empty pointers.
	
	arr[0] = new A(); //def constr. 
	arr[2] = new A(); //def constr.
	
	delete arr[0]; //destr.
	delete arr[2]; //destr.
	
	delete[] arr;
}
```

Създава динамичен масив с 5 указателя . Само на 2 от тези указатели присвояваме обекти, които са заделени в динамичната памет. Масивът ще се изтрие (и ще се изтрият обектите), когато се извика delete[] върху него.





##  Задачи

