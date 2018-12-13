#pragma once
#include <iostream>

class PmJobManager
{
public:
    static PmJobManager* GetInstance();
    bool Init();
    void Run();

private:
    PmJobManager();
    ~PmJobManager();
    static PmJobManager* m_pInstance;

    /*embeddable class to collect the garbage*/
    class Garbo
    {
    public:
        ~Garbo()
        {
            if(PmJobManager::m_pInstance)
            {
                std::cout<<"collect the garbage"<<std::endl;
                delete PmJobManager::m_pInstance;
            }
        }
    };
    static Garbo m_garbo; //when the process exit, the system will release the static variable automatically
};
