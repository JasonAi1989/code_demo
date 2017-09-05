#include <iostream>
#include "Poco/String.h"

using namespace std;

int main(int argc, char** argv)
{
    string str("    hello world    ");
    cout<<str<<endl;

    string new_str = Poco::trim(str);
    cout<<new_str<<endl;

    return 0;
}
