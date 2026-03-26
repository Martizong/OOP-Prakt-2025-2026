## Класове - идея, видимост

Клас дефинираме по същия начин като структура:

```c++

class Person
{
    char name[50];
    unsigned age;
};
```
## Член-функции - са функции, които работят с член-данните на обекта от дадена структура.

- Функции, които не съществуват глобално.

- Имената им са от вида <ClassName>::<memberFunctionName>

- Извикват се с инстанция/обект на структурата/класа.

- Компилаторът преобразува всяка член-функция на дадена структура/клас в обикновена функция с уникално име и един допълнителен параметър – константен указател към инстанцията/обекта.


```c++
struct Point
{
   int x, y;

   bool IsInFirstQuadrant() const
   {
   	return x >= 0 && y >= 0;
   }
   
};

int main()
{
   Point p1 = {3, 4};
   Point p2 = {-9, 8};
   std::cout << p1.IsInFirstQuadrant() << std::endl;
   std::cout << p2.IsInFirstQuadrant() << std::endl;
}

```

```c++
bool Point::isInFirstQuadrant()
{
	return x >= 0 && y >= 0;
}
```

се превежда в:

```c++
bool Point::isInFirstQuadrant(Point* const this)
{     
	//remember since this is a pointer (const) to Point we use the -> operator instead, which is equivalent to (*this).member;
	return this->x >= 0 && this->y >= 0;
}
//Като забележете, че this е const указател към Point, т.е. не можем да меним this, но можем да променяме обекта, който е сочен от него (четем декларациите на указателите отдясно наляво).
```c++

# Константни член-функции

- Не променят член-данните (състоянието) на структурата/класа.

- Обозначават се чрез записване на ключовата дума const в декларацията и в края на заглавието в дефиницията им.

- Могат да се извикват от константни обекти.

Пример: int get(unsigned int index) const

```c++
struct DynamicArray
{
	int* data;
	size_t used;
	size_t allocated;

	void allocate(size_t size)
	{
		data = new int[size];
		used = 0;
		allocated = size;
	}

	void free()
	{
		delete[] data;
		data = nullptr;
		used = 0;
		allocated = 0;
	}

	void push_back(int el)
	{
		if (used >= allocated)
		{
	    		// resize(allocated * 2);
		}
		data[used++] = el;
	}

	int get(unsigned int index) const
	{
		assert(index < used);
		return data[index];
	}
};

int main()
{
	DynamicArray da;
	da.allocate(8);
	da.push_back(5);
	da.get(0);

```
## Конструктори и деструктор.

Бихме искали инициализирането на обект и освобождаването на динамично заделена памет да се извършват "автоматично", а не ние да извикваме поотделно двете функции (с цел да се избегнат грешки).

Всяка структура/клас може да има n на брой конструктори и само един деструктор.
Това са специални функции, които компилаторът ще извика автоматично вместо нас.

# Жизнен цикъл на обект:

- Създаване на обект в даден scope – заделя се памет и член-данните се инициализират.

- Достига се до края на скоупа(област).

- Обектът и паметта, която е асоциирана с него се разрушава.

# Конструктор:

- Извиква се веднъж - при създаването на обекта.

- Не се оказва експлицитно тип на връщане (връща констатна референция).

- Има същото име като класа.

- Задава стойности на член-данните на class-a (в тялото си или чрез member initializer list)

# Деструктор:

- Извиква се веднъж - при изтриването на обекта.

- Не се оказва експлицитно тип на връщане.

- Има същото име като класа със символа '~' в началото.

# При липсата на дефинирани конструктори или деструктори, компилаторът автоматично създава такива по подразбиране.

```c++
#include <iostream>

struct Test 
{
 Test()
 {
 	std::cout << "Object is created" << std::endl;
 }
 
~Test()
 {
 	std::cout << "Object is destroyed" << std::endl;
 }

 int a, b;
};

int main()
{
   {
   	Test t; // Object is created 
   		{
   			Test t2; // Object is created 
   		} // Object is destroyed (t2)

   } //Object is destroyed (t)
}
```
# Още един пример:

```c++
struct DynamicArray
{
	int* data;
	size_t used;
	size_t allocated;

	DynamicArray() // Default constructor
	{
		data = nullptr;
		used = 0;
		allocated = 0;
	}

	~DynamicArray()
	{
		delete[] data;
		data = nullptr;
		used = 0;
		allocated = 0;
	}

	void allocate(size_t size)
	{
		data = new int[size];
		used = 0;
		allocated = size;
	}
	
	void push_back(int el)
	{
		if (used >= allocated)
		{
	    		// resize(allocated * 2);
		}
		data[used++] = el;
	}

	int get(unsigned int index) const
	{
		assert(index < used);
		return data[index];
	}
};

int main()
{
	DynamicArray da; // DynamicArray::DynamicArray()
} // DynamicArray::~DynamicArray()
```

```c++
struct DynamicArray
{
	int* data;
	size_t used;
	size_t allocated;

	DynamicArray()
	{
		data = nullptr;
		used = 0;
		allocated = 0;
	}

	DynamicArray(size_t size) // Parameterized constructor
	{
		data = new int[size];
		used = 0;
		allocated = size;
	}

	~DynamicArray()
	{
		delete[] data;
		data = nullptr;
		used = 0;
		allocated = 0;
	}

	void push_back(int el)
	{
		if (used >= allocated)
		{
	    		// resize(allocated * 2);
		}
		data[used++] = el;
	}

	int get(unsigned int index) const
	{
		assert(index < used);
		return data[index];
	}
};

int main()
{
	DynamicArray da(8); // DynamicArray::DynamicArray(8)
} // DynamicArray::~DynamicArray()
```

## Ред на работа на конструктурите и деструктурите

```c++
struct A
{
	int a;

	A()
	{
		std::cout << "A()" << std::endl;
	}
	~A()
	{
		std::cout << "~A()" << std::endl;
	}
};

struct B
{
	int b;

	B()
	{
		std::cout << "B()" << std::endl;
	}
	~B()
	{
		std::cout << "~B()" << std::endl;
	}
};

struct C
{
	A a;
	B b;
	int c;

	C()
	{
		std::cout << "C()" << std::endl;
	}
	~C()
	{
		std::cout << "~C()" << std::endl;
	}
};

int main()
{
	C obj;
}
```

Изход:

<img width="221" height="113" alt="ConstrDestrOrder" src="https://github.com/user-attachments/assets/65971068-3ff2-4bd7-899f-a1b8f98164a4" />


Когато имаме клас X, в който имаме обекти от други класове (A, B) и последните нямат конструктори по подразбиране, задължително в конструктора на X трябва експлицитно да извикаме конструкторите на A и B.


## Капсулация (encapsulation).

Капсулацията (известно още като "скриване на информация") е един от основните принципи в ООП. Тя налага разбиването на един клас на интерфейс и имплементация. Интерфейсът представлява набор от операции, които потребителят може да изпълнява свободно по начин, който не "бърка" в имплементацията. Понякога искаме потребителите да нямат достъп до всички член-данни и методи на даден клас. Това е така, защото тяхната промяна може да доведе до неочаквано поведение на нашата програма. Принципът за капсулация ни помага като позволява да определим кои методи и атрибути може да използват потребителите на нашия клас.

## Модификатор за достъп:

private - 	В текущия клас. Атрибутите, попадащи в обхвата на този модификатор, са вътрешни за съответния клас (не могат да се използват от "външния свят").

protected	- В текущия клас и *наследниците. Като private + съответните атрибути са видими и от наследниците на класа.

public	- За всеки. Атрибутите, попадащи в обхвата на този модификатор, са видими и за "външния свят").

# Първа разлика между структура и клас

- По подразбиране всички член данни и методи на структурата са public-елементи, а тези на класа – private-елементи.

## Селектори и мутатори

Това са публични член-функции, които се използват за достъпване (get) и промяна (set) на член-данни, които са декларирани в private/protected секция на един клас.

# Пример за get-ъри и set-ъри

- Get-ъри – функции, които използваме за достъп до "скрити" данни (попадащи в обхвата на модификатора private (protected)).

- Set-ъри – функции, които използваме за промяна на "скрити" данни. В тях задължително правим валидация на подадените данни (ако такава е необходима)!
  
```c++
#include <iostream>

struct Student 
{
private:
	int grade;
	int age;
public:
	Student(int grade, int age)
	{
		setGrade(grade);
		setAge(age);
	}

	int getGrade() const
	{
		return grade;
	}

	int getAge() const
	{
		return age;
	}

	void setGrade(int grade)
	{
		if(grade >= 2 && grade <= 6) {
			this->grade = grade;
		}
	}

	void setAge(int age) 
	{
		if(age >= 0) {
			this->age = age;
		}
	}
};

```
## Mutable 

- Спецификатора mutable е приложен само в С++. Той позволява на член на обект да предефинира константността. Така mutable член на const обект не е const и може да бъде изменян.

```c++
struct Test
{
private:
   mutable int n;
public:
   void f() const
   {
   	n++;
   }

};

int main()
{
   const Test t;

   t.f();
}

```


## Задачи

# Задача 1

# Задача 2

# Задача 3

# Задача 4

# Задача 5

# Задача 6



