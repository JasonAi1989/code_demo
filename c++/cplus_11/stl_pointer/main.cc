#include <iostream>
#include <list>

using namespace std;
int main()
{
    list<int*> ll;
    int a = 10;
    int b = 20;

    int* pa = &a;
    int* pb = &b;

    ll.push_back(pa);
    ll.push_back(pb);

    cout<<"pa address:"<<pa<<endl;
    cout<<"pb address:"<<pb<<endl;
    for(auto it=ll.begin(); it!=ll.end();++it)
    {
        cout<<"member:"<<*it<<endl;
        cout<<"value:"<<**it<<endl;
    }

    return 0;
}
