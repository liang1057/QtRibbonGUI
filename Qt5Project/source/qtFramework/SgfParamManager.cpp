#include "SgfParamManager.h"

/** @brief 参数容器变量*/
map<std::string, void *> m_mapParaManager;
static SgfParamManager* m_SgfParamManager_pInstance = NULL;

SgfParamManager* SgfParamManager::GetInstance()
{
    if (m_SgfParamManager_pInstance == NULL)
        m_SgfParamManager_pInstance = new SgfParamManager();

    return m_SgfParamManager_pInstance;
}

void SgfParamManager::addParam(const string &tKey, void *paramValue)
{
    string tKeyLow = strlwr((char*)(tKey.data()));
    map<string, void *>::iterator it = m_mapParaManager.find(tKey);
    if (it == m_mapParaManager.end())
    {
        m_mapParaManager.insert(std::pair<string, void*>(tKey, paramValue));
    }
    else
    {
        it->second = paramValue;
    }
}

void* SgfParamManager::getParamValue(const string &tKey)
{
    string tKeyLow = strlwr((char*)(tKey.data()));
    map<string, void *>::iterator it = m_mapParaManager.find(tKey);
    if (it == m_mapParaManager.end())
    {
        return NULL;
    }
    else
        return it->second;
}
