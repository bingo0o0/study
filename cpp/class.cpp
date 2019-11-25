#include <iostream>


class CTest
{
public:
    CTest() {} delete;
    CTest(int a) delete;
    ~CTest() {}
};

int main()
{
    return 0;
}