#include <map>
#include <unordered_map>
#include <set>
#include <vector>
#include <string>
#include <iostream>
#include <unistd.h>


using namespace std;
struct myData
{
    myData(int n): a(n), b(n) {}
    ~myData() { cout << "~mydata\n"; }
    int a {0};
    int b {0};
};



int main()
{
    unordered_map<string, myData> unoMaps;
    unoMaps.emplace("111", 10);

    cout << "22222" << endl;
    unoMaps = {};
    cout << "333333333333" << endl;

    sleep(10);
    return 0;
}
