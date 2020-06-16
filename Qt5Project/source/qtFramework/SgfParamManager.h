/************************************************************************
* 版权所有 (C) 梁振    Email:  liang1057@163.com.cn
* 
* 文件名称： SgfParamManager.h
* 内容摘要： 平台内核-参数管理类头文件
* 其它说明： 无
* 当前版本： 0.1
* 作    者： leon
* 完成日期： 2016-11-22
* 
* 修改记录1：
*    修改日期： 
*    版 本 号：
*    修 改 人： 
*    修改内容：
* 修改记录2：…
************************************************************************/
#ifndef SWFPARAMMANAGER_H
#define SWFPARAMMANAGER_H

#include <map>
#include <string>
using namespace std;

class SgfParamManager
{
public:
    /** brief 单例模式.  */
    static SgfParamManager* GetInstance();

    /** @brief  添加参数函数.
    *
    *  @details   添加参数函数.
    *  @param   tKey  参数名称.
    *  @param   paramValue  参数值指针.
    *  @return  void.
    */
    void addParam(const string &tKey, void *paramValue);


    /** @brief  获取参数值指针函数.
    *
    *  @details   获取参数值指针函数.
    *  @param   tKey  参数名称.
    *  @return  void * 参数值指针.
    */
    void* getParamValue(const string &tKey);
};


#endif // SWFPARAMMANAGER_H
