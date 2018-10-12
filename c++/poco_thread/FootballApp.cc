#include <Poco/Runnable.h>
#include <iostream>

#include "FootballApp.h"

using namespace std;

FootballApp::FootballApp()
{
    cout<<"FootballApp new"<<endl;
}

FootballApp::~FootballApp()
{

}

void FootballApp::run()
{
    cout<<"run, hello world"<<endl;
}
