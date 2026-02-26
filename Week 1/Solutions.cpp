//1
char* concatLowerUpper(const char* first, const char* second) {
    size_t resultLength = 0;

   
    for (size_t i = 0; first[i] != '\0'; i++) {
        if (first[i] >= 'a' && first[i] <= 'z') {
            resultLength++;
        }
    }

    
    for (size_t i = 0; second[i] != '\0'; i++) {
        if (second[i] >= 'A' && second[i] <= 'Z') {
            resultLength++;
        }
    }

  
    char* result = new char[resultLength + 1];

    size_t index = 0;

   
    for (size_t i = 0; first[i] != '\0'; i++) {
        if (first[i] >= 'a' && first[i] <= 'z') {
            result[index++] = first[i];
        }
    }

    
    for (size_t i = 0; second[i] != '\0'; i++) {
        if (second[i] >= 'A' && second[i] <= 'Z') {
            result[index++] = second[i];
        }
    }

    result[index] = '\0';
    return result;
}

//2
#include <iostream>
#include <cstring>


bool isSeparator(char c, char separator) {
    return c == separator;
}


int getWordLength(const char* text, int startIndex, char separator) {
    int length = 0;
    while (text[startIndex + length] != '\0' &&
           !isSeparator(text[startIndex + length], separator)) {
        length++;
    }
    return length;
}

char* copyWord(const char* text, int startIndex, int length) {
    char* word = new char[length + 1];
    for (int i = 0; i < length; i++) {
        word[i] = text[startIndex + i];
    }
    word[length] = '\0';
    return word;
}

char** split(const char* text, char separator) {
    if (!text) return nullptr;

   
    int partsCount = 1;
    for (int i = 0; text[i] != '\0'; i++) {
        if (isSeparator(text[i], separator)) {
            partsCount++;
        }
    }

    
    char** result = new char*[partsCount + 1];
    result[partsCount] = nullptr; 

    
    int index = 0;       
    int i = 0;      

    while (text[i] != '\0') {
        int wordLength = getWordLength(text, i, separator);

        result[index] = copyWord(text, i, wordLength);
        index++;

        i += wordLength;

        if (text[i] == separator) {
            i++; 
        }
    }

    return result;
}

int main() {
    const char* text = "C++,Java,Python,Go";
    char separator = ',';

    char** parts = split(text, separator);
  
    for (int i = 0; parts[i] != nullptr; i++) {
      std::cout << "Part " << i << ": " << parts[i] << std::endl;
    }

    for (int i = 0; parts[i] != nullptr; i++) {
      delete[] parts[i];
    }

    delete[] parts;

    return 0;
}


//3
#include <iostream>
using namespace std;

bool isPrime(int value) {
    if (value < 2) return false;
    for (int i = 2; i * i <= value; i++)
        if (value % i == 0) return false;
    return true;
}

int nextPrime(int value) {
    int candidate = value + 1;
    while (!isPrime(candidate)) candidate++;
    return candidate;
}

int doubleNumber(int value) {
    return value * 2;
}

int filter(int* numbers, int count, bool (*predicate)(int)) {
    int newCount = 0;
    for (int i = 0; i < count; i++) {
        if (predicate(numbers[i])) {
            numbers[newCount++] = numbers[i];
        }
    }
    return newCount;
}

void mapArray(int* numbers, int count, int (*transform)(int)) {
    for (int i = 0; i < count; i++)
        numbers[i] = transform(numbers[i]);
}

void printArray(const int* numbers, int count) {
    for (int i = 0; i < count; i++)
        cout << numbers[i] << " ";
    cout << "\n";
}

int main() {
    int values[] = {1,2,3,4,5,6,7,8};
    int count = sizeof(values) / sizeof(values[0]);

    count = filter(values, count, isPrime);
    mapArray(values, count, nextPrime);
    printArray(values, count);

    return 0;
}



-----------------------------------------
//4

#include <iostream>
using namespace std;

int add(int a, int b) {
 return a + b;
}

int sub(int a, int b) { 
return a - b; 
}

int mul(int a, int b) {
 return a * b;
}


int executeOperation(int index, int a, int b, int (**ops)(int,int), int opsCount) {
    if (index < 0 || index >= opsCount) {
        cout << "Invalid operation index!\n";
        return 0;
    }
    return ops[index](a, b);
}

int main() {
   
    int (*ops[])(int,int) = { add, sub, mul };
    int opsCount = sizeof(ops) / sizeof(ops[0]);

    cout << executeOperation(2, 7, 6, ops, opsCount) << "\n"; 

    return 0;
}


//5
bool isEven(unsigned int x) {
    return (x & 1) == 0;
}
//6
int clearBit(int a, int pos) {
    return a & ~(1 << pos);
}

//7
int makeBitOne(int a, int pos) {
    return a | (1 << pos);
}

//8
int toggleBit(int a, int pos) {
    return a ^ (1 << pos);
}
