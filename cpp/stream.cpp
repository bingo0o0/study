#include <iostream>
#include <sstream>
#include <string>
#include <vector>


using namespace std;
struct person
{
    string name;
    vector<string> phone;
};

int main()
{
    string line, word;
    vector<person> persons;
    istringstream record;
    ostringstream outline;
    
    while(true)
    {
        cout << "Please entry your name and phone number:" << endl;
        if (not getline(cin , line))
        {
            cout << "entry error\n";
            cin.clear();
            break;
        }

        person onePerson;
        record.str(line);
        record >> onePerson.name;
        while(record >> word)
        {
            onePerson.phone.push_back(word);
        }
        persons.push_back(onePerson);
    }

    for (const auto & ele: persons)
    {
        outline << ele.name << " " << ele.phone.back();
        cout << outline.str() << endl;
    }

    return 0;
}