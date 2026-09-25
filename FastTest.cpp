#include "FastCin.hpp"
#include "FastOut.hpp"

using std::string;

int main()
{
    string name;
    int age;
    print("Your name?");
    cin >> name;
    print("okay,");
    print("your age?");
    cin >> age;
    print("your name:",name, ", your age:",age);
    return 0;
}
