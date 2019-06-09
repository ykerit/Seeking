/*
 * @Description: template
 * @Author: yker
 * @Date: 2019-05-31 16:36:00
 * @LastEditTime: 2019-05-31 16:45:24
 */

#include <cstddef>

namespace yker
{
// 非类型模板参数
template <class T, size_t N = 10>
class Array
{
private:
    T array_[N];
    size_t size_;

public:
    Array(/* args */);
    ~Array();
    T &operator[](size_t index) { return array_[index]; }
    const T &operator[](size_t index) const { return array_[index]; }
    size_t size() const { return size_; }
    bool empty() const { return 0 == size_; }
};

} // namespace yker

int main()
{
    yker::Array<int> asd;
}