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

-запазване на масив от обекти, които не използват динамична памет

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

## ignore();

- ignore() е функция на входния поток (например cin или ifstream), която пропуска определен брой символи, без да ги обработва. Тя не трие нищо от файла – просто казва на програмата да не обръща внимание на тези символи при четене.

- Какво прави:

Прескача зададен брой байтове/символи.

Често се използва за пропускане на разделители, ненужни символи или остатъци от предишно четене.

При текстови файлове: Пропуска символи като интервали, нови редове, запетаи и др.

При двоични файлове:  Пропуска точно определен брой байтове, което е полезно, когато искаш да преминеш към следващ запис или поле.
