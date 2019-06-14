#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class point
{
public:
    point(int x, int y) : x_(x), y_(x) {}

    int x_, y_;
};

bool isOk(point &pos, int row, int col, vector<vector<int>> &map)
{
    if (pos.x_ < 0 || pos.x_ >= row || pos.y_ < 0 || pos.y_ >= col || map[pos.x_][pos.y_] == 1)
        return false;
    return true;
}

int main()
{
    int row, col;
    while (cin >> row >> col)
    {
        vector<vector<int>> map(row);
        for (int i = 0; i < col; ++i)
        {
            map[i].resize(col);
        }
        // 输入
        for (int i = 0; i < row; ++i)
        {
            for (int j = 0; j < col; ++j)
            {
                cin >> map[i][j];
            }
        }
        stack<point> st;
        point top(0, 0);
        point step(0, 0);

        st.push(point(0, 0));
        while (!st.empty())
        {
            // 获得栈顶元素
            top = st.top();

            if (top.x_ == row - 1 && top.y_ == col - 1)
            {
                break;
            }
            step = top;
            // 上
            step.y_--;
            if (isOk(step, row, col, map))
            {
                st.push(step);
                continue;
            }
            step = top;
            // 下
            step.y_++;
            if (isOk(step, row, col, map))
            {
                st.push(step);
                continue;
            }
            step = top;
            // 左
            step.x_--;
            if (isOk(step, row, col, map))
            {
                st.push(step);
                continue;
            }
            step = top;
            // 右
            step.x_++;
            if (isOk(step, row, col, map))
            {
                st.push(step);
                continue;
            }
            st.pop();
        }
        point pos(0, 0);
        while (!st.empty())
        {
            pos = st.top();
            cout << "(" << pos.x_ << "," << pos.y_ << ")" << endl;
        }
    }
    return 0;
}