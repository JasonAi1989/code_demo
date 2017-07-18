#include <Poco/Thread.h>
#include <Poco/SharedPtr.h>
#include <iostream>

#include "FootballApp.h"

using namespace std;
int main()
{

    Poco::SharedPtr<FootballApp> p = new FootballApp();
    Poco::Thread thread;

    thread.start(*p);

    cout << "thread start" << endl;

    thread.join();

    return 0;
}
