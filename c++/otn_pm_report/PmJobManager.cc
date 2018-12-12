#include "PmJobManager.h"

PmJobManager::PmJobManager()
{

}

static PmJobManager* PmJobManager::GetInstance()
{
    if(m_pInstance == nullptr)
    {
        m_pInstance = new PmJobManager()
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
