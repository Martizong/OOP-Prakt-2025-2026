#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const int MAX_PLACEHOLDERS = 10;

struct Placeholder
{
    char key[30];
    char value[200];
};

int findValue(const char* key, Placeholder arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        if (strcmp(key, arr[i].key) == 0)
            return i;
    }
    return -1;
}

int main()
{
    Placeholder arr[MAX_PLACEHOLDERS];
    int count = 0;

    ifstream values("values.txt");

    if (!values.is_open())
    {
        cout << "Cannot open values file\n";
        return 1;
    }

    while (count < MAX_PLACEHOLDERS && values >> arr[count].key)
    {
        values.get();
        values.getline(arr[count].value, 200);
        count++;
    }

    values.close();

    ifstream in("template.txt");

    if (!in.is_open())
    {
        cout << "Cannot open template file\n";
        return 1;
    }

    ofstream out("result.txt");

    if (!out.is_open())
    {
        cout << "Cannot create result file\n";
        in.close();
        return 1;
    }

    char ch;

    while (in.get(ch))
    {
        if (ch == '{')
        {
            char key[30];
            int i = 0;

            while (in.get(ch) && ch != '}')
            {
                key[i++] = ch;
            }

            key[i] = '\0';

            int index = findValue(key, arr, count);

            if (index != -1)
                out << arr[index].value;
            else
                out << "{" << key << "}";
        }
        else
        {
            out << ch;
        }
    }

    in.close();
    out.close();

    return 0;
}
