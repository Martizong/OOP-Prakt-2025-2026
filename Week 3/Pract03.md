## Разделна компилация - 4 основни стъпки.  Разделната компилация означава, че програмата се изгражда на части.

# 1. Препроцесиране (Preprocessing) -  Това е първият етап, в който C++ препроцесорът обработва всички директиви, започващи с #.

- Разгръщат се всички #include – съдържанието на включените файлове се копира в кода.

- Заменят се макросите от #define.

- Премахват се коментарите.

- Обработват се условните компилации (#ifdef, #ifndef, #if).

- Резултат: Получава се огромен междинен файл с чист C++ код(един разширен изходен файл), без коментари и с вече вмъкнати хедъри. Този файл се подава към следващата стъпка.

# 2. Компилация (Compilation) - Тук компилаторът превръща вече обработения C++ код в асемблерен код за конкретния процесор.

- Проверява се синтаксисът (дали кодът е валиден C++).

- Извършва се семантичен анализ (дали типовете, променливите и функциите са използвани правилно).

- Генерира се оптимизиран асемблерен код.

- Резултат: Файл с асемблерни инструкции (обикновено .s).

# 3. Асемблиране (Assembly) - Асемблерът превръща асемблерния код в машинен код, който процесорът може да изпълнява.

- Всяка асемблерна инструкция се превежда в бинарна форма (0 и 1).

- Създава се обектен файл (.o или .obj).

- Резултат: Обектни файлове, съдържащи машинен код, но все още не свързани помежду си.

# 4. Линкване (Linking) - Линкерът събира всички обектни файлове и външни библиотеки в едно цяло – изпълним файл.

- Свързват се всички .o файлове от проекта.

- Добавят се нужните функции от стандартната библиотека (например std::cout).

- Разрешават се външни символи – например ако файл А извиква функция от файл Б.

- Създава се крайният .exe (Windows) или ELF файл (Linux).
  
- Резултат: Готов изпълним файл, който можеш да стартираш.
  
## Потоци (streams) и файлове

# Видове потоци

- Поток (stream) - последователност от байтове данни влизащи в и излизащи от програмата.

- При операциите за вход, байтовете идват от източник за вход (клавиатура, файл, мрежа или друга програма)

- При операциите за изход, байтовете данни излизат от програмата и се "вливат" във външно "устройство" (конзола, файл, мрежа или друга програма)

- Потоците служат като посредници между програмите и самите IO устройства по начин, който освобождава програмиста от боравене с тях.

- Потокът дефинира интерфейс с операции върху него, които не зависят от избора на IO устройство

<img width="347" height="194" alt="streams" src="https://github.com/user-attachments/assets/09517f40-c697-45cc-b6c1-c395f53e2efd" />  


# Видове потоци:

- Потоци за вход (istream).
- Потоци за изход (ostream).

  <img width="402" height="221" alt="image" src="https://github.com/user-attachments/assets/03503e84-edab-414c-a410-25cff324f07f" />


istream: Клас, в който е дефиниран оператор >>, както и член-функциите get(), getline(), read().
ostream: Клас, в който е дефиниран оператор <<, както и член-функциите put(), write().
iostream: Наследник на класовете istream и ostream. Притежава всички техни член-функции.

cin - обект от класа istream
cout - обект от класа ostream


# Пример за работа с поток за вход (cin)

```c++
#include <iostream>
using namespace std;

int main()
{
   int a, b;
   cin >> a >> b;
}
//Четем от стандартния вход.

```

# Пример за работа с поток за изход (cout)

```c++
#include <iostream>
using namespace std;

int main()
{
   int a = 10;
   int b = 12;
   int c = a + b;

   cout << a << " + " << b << " = " << c << endl;
}
```



## Текстови файлове

- Отваряне на файл за четене

```c++ 
#include <iostream>
#include <fstream>

int main()
{
    std::ifstream file("myFile.txt"); // Отваряме файла myFile.txt за четене

    if (!file.is_open())
    {
        std::cout << "File can't be opened!" << std::endl;
        return -1;
    }

    file.close();
}
```

- Четене от файл

```c++
int main()
{
    std::ifstream file("myFile.txt");

    if (!file.is_open())
    {
        std::cout << "File can't be opened!" << std::endl;
        return -1;
    }

    char a, b;
    file >> a >> b;

    std::cout << a << b; // a == първия символ от myFile.txt, b == втория символ от myFile.txt

    file.close();
}
```

- Прочитане на цялото съдържание на файл

```c++
#include <iostream>
#include <fstream>

const unsigned BUFF_SIZE = 1024;

int main()
{
    std::ifstream file("myFile.txt");

    if (!file.is_open())
    {
        std::cout << "File can't be opened!" << std::endl;
        return -1;
    }

    char buff[BUFF_SIZE];
    while (!file.eof())
    {
        file.getline(buff, BUFF_SIZE);
        std::cout << buff << std::endl;
    }

    file.close();
}
```

- Отваряне на файл за писане

```c++
#include <iostream>
#include <fstream>

int main()
{
    std::ofstream file("myFile.txt"); // Отваряме файла myFile.txt за писане

    if (!file.is_open())
    {
        std::cout << "File can't be opened!" << std::endl;
        return -1;
    }

    file.close();
}
```

- Писане във файл

```c++
int main()
{
    std::ofstream file("myFile.txt");

    if (!file.is_open())
    {
        std::cout << "File can't be opened!" << std::endl;
        return -1;
    }

    char a = 'x', b = 'y';
    file << a << b; // съдържанието на myFile.txt == xy

    if(!file.eof()) { //check if the file has ended
   	std::cout << "The file contains more data after the two integers!" << std::endl;
   }

    file.close();
}
```

- (istream) get - функция, която чете следващия character в потока.
  
- (ostream) put - функция, която поставя на следваща позиция character в потока.

- ifstream или istream - съдържа get указател, който реферира елемента, който ще се прочете при следващата входна операция.
  
- ofstream или ostream - съдържа put указател, който реферира мястото, където ще се запише следващият елемент.

- put и get не са форматирани за разлика от operator<< и operator>>, тоест не пропускат whitespaces и др.

# Позициониране във файл

- tellg() - Връща позицития на текущия символ в потока за четене
 
- tellp() - Връща позицития на текущия символ в потока за писане

- seekg(offset, direction) - Премества get-указателят на позцития на потока за четене.

- seekg(streampos idx) - Премества get-указателят на позция idx на потока за четене.

- seekp(offset, direction) - Премества put-указателят на позцития на потока за писане.

- seekp(streampos idx) - Премества put-указателят на позция idx на потока за писане.

-offset : целочислена стойност. Отместването от direction.

-direction : Може да заема следите стойностти:

1. ios::beg - началото на файла.
2. ios::cur - текущата позиция във файла.
3. ios::end - края на файла.

# Режими на работа

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










## Задачи

# Бонус задача
