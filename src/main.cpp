// #include <stdio.h>
// #include <string.h>
// #include <stdint.h>

// struct A
// {
//   uint16_t id;
//   uint32_t value;
//   uint64_t times;
// };

// int foo(int n)
// {
//   if(n < 2)
//     return n;
//   else 
//     return 2*foo(n-1)+foo(n-2);
// }
// #define SQR(A) A*A
// int main()
// {
//   A task;

//   uint64_t a = 0x00010001;
//   memcpy(&task, &a, sizeof(uint64_t));
//   printf("%11u, %11u, %1lu", task.id, task.value, task.times);
//   return 0;
// }

#include <iostream>
#include <string>
using namespace std;

int main()
{
    string input;
    while(cin >> input)
    {
        int count = 1;
        for(int i = 0; i < input.size(); i++)
        {
            if(input[i] == '"')
            {
                i++;
                while(input[i] != '"')
                {
                    i++;
                }
            }
            if(input[i] == ' ')
            {
                count++;
            }
        }
        cout << count << endl;
        for(auto c : input)
        {
            if(c != ' ')
            {
                cout << c;
            } else
            {
                cout << '\n';
            }
            if(c == '"')
            {
                continue;
            }
        }
    }
    return 0;
}