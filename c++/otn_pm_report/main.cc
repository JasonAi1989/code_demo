
/*
*  Copyright (c) 2018 Ericsson AB.
*  All rights reserved.
*
*  Author: EAIZHAO
*/

#include "PmJobManager.h"

int main(int argc, char const* argv[])
{
    PmJobManager *manager = PmJobManager::GetInstance();
    if(!manager)
    {
        //OTN_ERR("Failed to get pm job manager instance");
        return -1;
    }

    if(manager->Init() == false)
    {
        //OTN_ERR("OTN pm job initialize failed");
        return -1;
    }

    manager->Run();
    //OTN_ERR("OTN pm job manager exits with error");

    return 0;
}
