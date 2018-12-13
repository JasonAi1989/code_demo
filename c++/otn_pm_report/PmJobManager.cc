#include <iostream>

#include "PmJobManager.h"

/*
 *the static class member variable should be initialized
 *as the global variable, otherwise, this variable couldn't
 *be called in class functions
 */
PmJobManager* PmJobManager::m_pInstance = nullptr;
PmJobManager::Garbo PmJobManager::m_garbo;

PmJobManager::PmJobManager()
{
    std::cout<<"PmJobManager"<<std::endl;
}
PmJobManager::~PmJobManager()
{
    std::cout<<"~PmJobManager"<<std::endl;
}

PmJobManager* PmJobManager::GetInstance()
{
    if(m_pInstance == nullptr)
    {
        std::cout<<"GetInstance"<<std::endl;
        m_pInstance = new PmJobManager();
    }

    return m_pInstance;
}

bool PmJobManager::Init()
{
    return true;
}

void PmJobManager::Run()
{

}
