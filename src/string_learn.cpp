#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
    string array;

    getline(cin, array);

    reverse(array.begin(), array.end());
    int end = 0;
    int start = 0;
    while (end < array.size())
    {
        while (end < array.size() && array[end] == ' ')
            ++end;
        start = end;
        while (end < array.size() && array[end] != ' ')
            ++end;
        reverse(array.begin() + start, array.begin() + end);
        start = end;
    }
    cout << array;

    return 0;
}

// #include <iostream>
// #include <vector>
// using namespace std;

// int main()
// {
//     int len = 0;
//     int num = 0;
//     vector<int> array;

//     cin >> len;
//     for (int i = 0; i < len; i++)
//     {
//         cin >> num;
//         array.push_back(num);
//     }

//     int flag = 0;

//     int result = 1;

//     for (int i = 1; i < len; i++)
//     {

//         if (array[i] > array[i - 1])
//         {

//             if (flag == 0)
//             {

//                 flag = 1;
//             }

//             if (flag == -1)
//             {

//                 flag = 0;

//                 result++;
//             }
//         }
//         else if (array[i] < array[i - 1])
//         {

//             if (flag == 0)
//             {

//                 flag = -1;
//             }

//             if (flag == 1)
//             {

//                 flag = 0;

//                 result++;
//             }
//         }
//     }
//     cout << result;
// }

// #include <iostream>
// #include <string>
// #include <algorithm>
// using namespace std;

// int main()
// {
//     string str;
//     while (getline(cin, str))
//     {
//         reverse(str.begin(), str.end());
//         int i = 0, j = i;
//         while (i < str.size())
//         {
//             while (i < str.size() && str[i] == ' ')
//                 ++i;
//             j = i;
//             while (i < str.size() && str[i] != ' ')
//                 ++i;
//             reverse(str.begin() + j, str.begin() + i);
//             j = i;
//         }
//         cout << str << endl;
//     }
//     return 0;
// }