## Двоични файлове

- "Разбираеми" за компютъра, "неразбираеми" за нас.

- Използваме функциите:

1.read(char* memoryBlock, size_t size);

2.write(const char* memoryBlock, size_t size);

Обърнете внимание, че функцията приема char*. Ако искаме да запазим променлива от друг вид, ще трябва експлицитно да преобразуваме указателя към тип char* (без значение, че указателят не сочи към елементи от тип char)

- Отваряне на двоичен файл за четене
```c++
#include <iostream>
#include <fstream>

int main()
{
    // ..
    std::ifstream file("myFile.dat", std::ios::binary);
    // ..
}
```

- Отваряне на двоичен файл за писане
```c++
#include <iostream>
#include <fstream>

int main()
{
    // ..
    std::ofstream file("myFile.dat", std::ios::binary);
    // ..
}
```

- Записване на число в двоичен файл
```c++
#include <iostream>
#include <fstream>

int main()
{
    std::ofstream file("myFile.dat", std::ios::binary);
    if (!file.is_open())
    {
        std::cout << "File can't be opened!" << std::endl;
        return -1;
    }

    int num = 1000;
    file.write(reinterpret_cast<const char*>(&num), sizeof(num));

    file.close();
}
```

Как изглежда файлът?

<img width="544" height="277" alt="image" src="https://github.com/user-attachments/assets/77f57f93-f36e-4e0e-a63e-10ed6edb470c" />



# Пример за писане в двоичен файл:

```c++
#include <iostream>
#include <fstream>

int main()
{
   std::ofstream f("file.dat");

   int a = 155555;

   f.write((const char*)&a, sizeof(int));

   f.close();
}
```

# Пример за четене от двоичен файл:

```c++
#include <iostream>
#include <fstream>

int main()
{
  std::ifstream f("file.dat");

  int a;
  f.read((char*)&a, sizeof(int));

  std::cout << a << std::endl;

  f.close();
}
```

# Съдържанието на двоичния файл:

<img width="85" height="36" alt="image" src="https://github.com/user-attachments/assets/9b04fd15-f1d1-45e0-8dfd-e3ecd2c7a24b" />

Байтовете се записват в обратна посока. Най-старшият байт е последен. Следователно запаметеното число е 00025fa3, което е точно шестнайсетичният запис на числото 155555.


# Примери за запазване на структури във файл.

- запазване на структура, която не използва динамична памет

```c++
#include <iostream>
#include <fstream>

struct Test {
	bool b;
	int x;
};

int main()
{
	{
		Test t = { true, 45 };
		std::ofstream file("testObj.bat", std::ios::binary);

		if (!file.is_open()) {
			return -1;
		}

		file.write((const char*)&t, sizeof(t));
	}

	{
		Test t;
		std::ifstream file("testObj.bat", std::ios::binary);

		if (!file.is_open()) {
			return -1;
		}

		file.read((char*)&t, sizeof(t));
		std::cout << t.b << " " << t.x << std::endl;
	}
}

```
  
```c++
#include <iostream>
#include <fstream>
#include <cstring>
#pragma warning (disable: 4996)

struct Student {
	char name[25];
	int fn;
	int age;
};

int main()
{
	{
		Student st;
		strcpy(st.name, "Ivan");
		st.fn = 1234;
		st.age = 33;

		std::ofstream file("student.dat", std::ios::binary);

		if (!file.is_open()) {
			std::cout << "Error while writing to binary file!" << std::endl;
			return -1;
		}

		//since the data is grouped in the struct, we can save it like this.
		file.write((const char*)&st, sizeof(st));
	}

	{
		Student st;
		std::ifstream file("student.dat", std::ios::binary);

		if (!file.is_open()) {
			std::cout << "Error while reading from binary file!" << std::endl;
			return -1;
		}

		file.read((char*)&st, sizeof(st));
		std::cout << st.name << " " << st.fn << " " << st.age << std::endl;
	}
}
```

- запазване на структура, която използва динамична памет

```c++
#include <iostream>
#include <fstream>
#pragma warning (disable: 4996)

struct Student {
	char* name;
	int fn;
	int gradesCount;
	double averageGrade;
};

Student createStudent(const char* name, int fn, int gradesCount, double avGrade) {
	Student obj;

	size_t nameLen = strlen(name);

	obj.name = new char[nameLen + 1];
	strcpy(obj.name, name);

	obj.fn = fn;
	obj.gradesCount = gradesCount;
	obj.averageGrade = avGrade;

	return obj;
}

void saveStudentToFile(ofstream& f, const Student& st) {
	size_t nameLen = strlen(st.name);

	f.write((const char*)&nameLen, sizeof(nameLen));  //first we write the size of the name!
	f.write(st.name, nameLen);

	f.write((const char*)&st.fn, sizeof(st.fn));
	f.write((const char*)&st.gradesCount, sizeof(st.gradesCount));
	f.write((const char*)&st.averageGrade, sizeof(st.averageGrade));

}

Student readStudentFromFile(ifstream& f) {
	Student res;

	size_t nameLen;

	f.read((char*)&nameLen, sizeof(nameLen)); //first we read the size of the name!

	res.name = new char[nameLen + 1];
	f.read(res.name, nameLen);
	res.name[nameLen] = '\0';

	f.read((char*)&res.fn, sizeof(res.fn));
	f.read((char*)&res.gradesCount, sizeof(res.gradesCount));
	f.read((char*)&res.averageGrade, sizeof(res.averageGrade));

	return res;
}

void freeStudent(Student& s) {
	delete[] s.name;
	s.averageGrade = s.fn = s.gradesCount = 0;
}

void print(const Student& st) {
	std::cout << st.name << " " << st.fn << " " << st.gradesCount << " " << st.averageGrade << std::endl;
}

int main()
{
	{
		Student s1 = createStudent("Ivan", 1234, 2, 4);
		Student s2 = createStudent("Petur", 5555, 5, 5.5);

		std::ofstream f1("uni.dat", std::ios::binary);

		if (!f1.is_open()) {
			cout << "Error" << endl;
			return -1;
		}

		saveStudentToFile(f1, s1);
		saveStudentToFile(f1, s2);

		freeStudent(s1);
		freeStudent(s2);
	}

	{
		std::ifstream f2("uni.dat", std::ios::binary);

		if (!f2.is_open()) {
			cout << "Error" << endl;
			return -1;
		}
		
		Student s1 = readStudentFromFile(f2);
		Student s2 = readStudentFromFile(f2);

		print(s1);
		print(s2);

		freeStudent(s1);
		freeStudent(s2);
	}
}
```

# Пример за запазване на масив от структури във файл.

- запазване на масив от обекти, които не използват динамична памет

```c++
#include <iostream>
#include <fstream>
#include <cstring>
#pragma warning (disable: 4996)

struct Student {
	char name[30];
	int age;
	int fn;
};

void initStudent(Student& st, const char* name, int age, int fn) {
	strcpy(st.name, name);
	st.age = age;
	st.fn = fn;
}

void saveToFile(const Student* students, size_t count, ofstream& file) {
	file.write((const char*)students, count * sizeof(Student));
}

int main()
{
	Student* arr = new Student[4];
	initStudent(arr[0], "ivan", 44, 1234);
	initStudent(arr[1], "petur", 12, 765);
	initStudent(arr[2], "alex", 15, 44);
	initStudent(arr[3], "katerina", 19, 12134);

	std::ofstream file("students.dat", std::ios::binary);

	if (!file.is_open()) {
		std::cout << "Error while opening the file!" << std::endl;
		delete[] arr; //!
		return -1;
	}

	saveToFile(arr, 4, file);

	delete[] arr;
}

```

- четене на масив от обекти, които не използват динамична памет


```c++
#include <iostream>
#include <fstream>
#include <cstring>

struct Student {
	char name[30];
	int age;
	int fn;
};

size_t getFileSize(ifstream& f) {
	size_t currentPos = f.tellg();
	f.seekg(0, std::ios::end);
	size_t size = f.tellg();

	f.seekg(currentPos);
	return size;
}

void readFromFile(Student*& ptr, size_t& studentsCount, ifstream& f) {
	size_t sizeOfFile = getFileSize(f);
	studentsCount = sizeOfFile / sizeof(Student);
	ptr = new Student[studentsCount];
	f.read((char*)ptr, sizeOfFile);
}

int main()
{
	Student* arr;
	size_t count;
	std::ifstream file("students.dat", std::ios::binary);

	if (!file.is_open()) {
		std::cout << "Error while opening the file!" << std::endl;
		return -1;
	}

	readFromFile(arr, count, file);

	for (int i = 0; i < count; i++) {
		std::cout << "Name: " << arr[i].name << ", age: " << arr[i].age << ", fn: " << arr[i].fn << std::endl;
	}

	delete[] arr;
}
```
# Режими за работа с файлове


 ```c++
ifstream str("file.txt", <режим на работа>).
```

Режимът на работа е цяло число. Ако искаме да зададем повече от един ги изреждаме с двоично или('|').

<img width="1149" height="415" alt="Screenshot (1466)" src="https://github.com/user-attachments/assets/c3e2b972-51d8-4d34-9c30-f887910f9da7" />

  
```c++
ofstream file("file.txt", ios::out | ios::app).
```


# Флагове на състоянията на потока

<img width="798" height="261" alt="Screenshot (1467)" src="https://github.com/user-attachments/assets/cda5d731-c812-4bcb-a6ba-a56ca87a5ea2" />


# Позициониране във файл

- tellg() - Връща позицията на текущия символ в потока за четене
 
- tellp() - Връща позицията на текущия символ в потока за писане

- seekg(offset, direction) - Премества get-указателят на позцития на потока за четене.

- seekg(streampos idx) - Премества get-указателят на позция idx на потока за четене.

- seekp(offset, direction) - Премества put-указателят на позцития на потока за писане.

- seekp(streampos idx) - Премества put-указателят на позция idx на потока за писане.

-offset : целочислена стойност. Отместването от direction.

-direction : Може да заема следите стойностти:

1. ios::beg - началото на файла.
2. ios::cur - текущата позиция във файла.
3. ios::end - края на файла.

# ignore();

- ignore() е функция на входния поток (например cin или ifstream), която пропуска определен брой символи, без да ги обработва. Тя не трие нищо от файла – просто казва на програмата да не обръща внимание на тези символи при четене.

- Какво прави:

Прескача зададен брой байтове/символи.

Често се използва за пропускане на разделители, ненужни символи или остатъци от предишно четене.

При текстови файлове: Пропуска символи като интервали, нови редове, запетаи и др.

При двоични файлове:  Пропуска точно определен брой байтове, което е полезно, когато искаш да преминеш към следващ запис или поле.

# flush() 
- при работа с двоични файлове се използва, за да избута незаписаните данни от буфера(временна памет, която събира информацията, за да се запише по-ефективно на по-големи порции) към самия файл веднага, вместо да чака буферът да се напълни или файлът да се затвори.
  
- Това е важно, защото при двоични файлове се работи с сурови байтове и всяко забавяне или непълен запис може да доведе до повредени данни.


## Задачи

# Задача 1
Дефинирайте функцията 'writeToFile', която приема като аргумент името на файл ('fileName'). Функцията трябва да прочете цяло число ('count') от стандартния вход и след това 'count' на брой цели числа, въведени от потребителя. След като прочете данните, функцията трябва да запише броя на числата ('count') и самите числа в двоичен формат във файл с име 'fileName'.

# Задача 2
Дефинирайте функцията 'readFromFile', която приема като аргумент името на файл ('fileName'). Функцията трябва да отвори указания файл в двоичен режим за четене. След това функцията трябва да прочете първоначално записания брой на числата ('count') от файла. След като прочете 'count', функцията трябва да създаде масив от цели числа с големина, равна на 'count', и да прочете всички числа от файла в този масив. Функцията връща създания масив

# Задача 3
Да се дефинира структура Customer, която съдържа информация за клиента: име уникален идентификатор и възраст. Да се реализира функция, която чете и записва информацията за клиента в двоичен файл.

Да се дефинира структура Order, която съдържа информация за поръчката: цена, ДДС и клиент. Да се реализира функция writeOrderToFile, която записва информацията за поръчката в двоичен файл. Да се реализира функция writeOrdersToFile, която записва масив от поръчки в двоичен файл. 
Да се напише функция readOrdersFromFile, която чете поръчките от двоичен файл.
# Задача 4
а) Направете структура Student с име, фак. номер и имейл адрес,брой взети изпити, брой невзети изпити и средно аритметично от положените изпити през изминалия семестър.

б) Напишете програма, която oтвaря поток за записване в бинарен файл, използвайки данните на предварително дефинирани променливи от тип Student, след което напишете функция,която прочита данните от бинарния файл и сортира студентите по успех и връща масив с факултетните номера, където първи е студентът с най-нисък успех.

в) Изведете информацията от върнатия масив в конзолата.


# Задача 5
а)Създайте структурите описващи Животно/Animal и Зоопарк/Zoo. Структурата Person/Човек - име на човека и отдела, в който работи в зоопарка. Структурата Animal/Животно трябва да съдържа име на животното и вид на животното(влечуго, бозайник, хищник).

б)Структурата Zoo/Зоопарк трябва да съдържа персонал(масив от Person/Хора), който се грижи за видовете животни и също така масив от животни. Напишете функция, която прочита n на брой животни от стандартния вход. 
Животните се запазват в двоичен файл. Напишете функция, която прочита персонал от стандартния вход. Персонала се запазват в двоичен файл. Със запазениете данни на животните и персонала, да се създаде зоопарк.
Напишете функция, която запазва данните на зоопарка в нов файл.
Напишете функция, която чете данните на зоопарка от новия файл и принтира данните в конзолата.


# Задача 6

След като Данаил успешно завърши първи курс на ФМИ, той беше готов да започне работа.
Но понеже работодателите, търсещи неговите невероятни умения, бяха повече от очакваното,
той реши да изтрие имейла си и да направи собствена система, чрез която да получава покани за работа.

Създайте структура, описваща обява за работа. Структурата трябва да съдържа:

- Име на фирмата. То трябва да е с максимална дължина от 25 символа.

- Брой на програмистите, с които той ще работи в екип.

- Брой на дните платен отпуск през годината.

- Сума, която ще му бъде изплатена след успешно завършване на проекта (от тип long long).

Създайте функция, която прочита n на брой заявки от стандартния вход. Заявките се запазват в двоичен файл, като ако във файла вече има информация,тя не се изтрива.

Създайте функция void filterOffers(const char* filePath, long long minSalary), която приема адрес на файл, от който четем заявките и минимална заплата.
Извежда на стандартния изход всички обяви за работа, които предлагат поне толкова пари, колкото са подадени като аргумент.

Създайте функция, bool existOffer(const char* filePath, const char* name), която проверява дали дадена фирма е пратила покана за работа.

- Бонус №1: Създайте void perfectOffer(const char* filePath, int maxCoworkers, int minVacancyDays, int minSalary), която извежда във файл всички обяви, които отговарят точно на изискванията на Данаил.

- Бонус №2: Създайте система, която работи чрез следните заявки:

a <оферта> - добавя оферта за работа

i - показва всички оферти

s <име на фирма> - връща дали фирмата съществува

f <число> - извежда всички обяви, за които заплатата е по - висока от числото

q - изход от системата


