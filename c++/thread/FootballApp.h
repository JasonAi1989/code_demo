#ifndef __FOOTBALLAPP__
#define __FOOTBALLAPP__

#include <Poco/Runnable.h>

class FootballApp : public Poco::Runnable{
    public:
        FootballApp();
        ~FootballApp();

        virtual void run();
};

#endif
