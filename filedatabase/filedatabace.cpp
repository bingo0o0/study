#include "filedatabace.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <assert.h>
#include <sys/stat.h>


#define MAX_INDEX_LEN (10000)
static const char *DATABASE_FILE = "./peron_list.db";
static const uint32_t MAX_READ_NODE_NUM = 512;

CFileDataBase * CFileDataBase::instance()
{
    CFileDataBase *s_file_database = NULL;
    if (NULL == s_file_database)
    {
        s_file_database = new CFileDataBase();
    }

    assert(s_file_database != NULL);

    return s_file_database;
}


CFileDataBase::CFileDataBase():m_fd(-1), m_initFlag(false)
{
    memset(&m_index, 0x0, sizeof(file_database_index_t));
    memset(&m_personHead, 0x0, sizeof(person_head_info_t));

    init();
}


CFileDataBase::~CFileDataBase()
{

}



bool CFileDataBase::init()
{
    if (m_initFlag)
    {
        return true;
    }

    int state;
    //\ 如果文件存在，初始化人员节点信息长度，由于算法不同，特征值的长度不同
    if (access(DATABASE_FILE, &state) != 0)
    {
        return false;
    }

    if (-1 == m_fd)
    {
        m_fd = open(DATABASE_FILE, O_CREAT|O_RDWR, 0777);
        if (m_fd < 0)
        {
            perror("open failed");
            return false;
        }
    }

    if (!m_index.pPersonNode)
    {
        m_index.pPersonNode = (person_node_index_t *)malloc(sizeof(person_node_index_t) * MAX_INDEX_LEN);
        assert(m_index.pPersonNode != NULL);

        m_index.cap = MAX_INDEX_LEN;
        m_index.size = 0;
    }
   

    struct stat dbStat;
    if (fstat(m_fd, &dbStat) !=0)
    {
        perror("get dbfile info failed");
        return false;
    }

    //\ 文件存在并且不为空，读取一个节点出来，初始化节点长度信息
    if (F_OK == state && dbStat.st_size > 0 && initHeadLength())
    {
        m_initFlag = true;
    }

    return true;
}


bool CFileDataBase::initHeadLength()
{
    int size;
    person_head_info_t buffer;

    if (m_initFlag)
    {
        return true;
    }

    size = read(m_fd, (int8_t *)&buffer, sizeof(person_head_info_t));
    if (size != sizeof(person_head_info_t))
    {
        perror("read file faile");
        return false;
    }

    m_personHead = buffer;

    return true;
}


bool CFileDataBase::seek(uint32_t offset)
{

}



bool CFileDataBase::addFeature2Alg(person_node_info_t *pNode)
{
    return true;
}


bool CFileDataBase::addIndex(person_node_info_t *pNode)
{
    return true;
}


 bool CFileDataBase::loadFeature()
 {
    //\ 文件不存在时， 直接返回成功
    if (!m_initFlag)
    {
        return true;
    }

    int err = 0;

    //\ 文件定位到人员信息开始的地方
    if (seek(sizeof(person_head_info_t)) == false)
    {
        return false;
    }

    uint32_t buffSize = MAX_READ_NODE_NUM * m_personHead.nodeSize;
    int8_t *buffer = (int8_t *)malloc(buffSize);
    if (!buffer)
    {
        perror("Mem alloc failed");
        return false;
    }

    //\ 循环读取，直到文件结束
    uint32_t rsize = 0;
    while(1)
    {
        rsize = read(m_fd, buffer, buffSize);
        if (rsize < m_personHead.nodeSize)
        {
            printf("read file end\n");
            break;
        }

        if (rsize%m_personHead.nodeSize != 0)
        {
            printf("fatal error file structure anomaly \n");
            break;
        }

        uint32_t loop = rsize/m_personHead.nodeSize;
        person_node_info_t *pNodeInfo = (person_node_info_t *)buffer;
        for (uint32_t i=0; i<loop; i++)
        {
            pNodeInfo += i;
            if (pNodeInfo->personId != 0)   //\ 节点有效
            {
                addFeature2Alg(pNodeInfo);
            }
            else
            {
                addIndex(pNodeInfo);    //\ 节点无效，加入到空闲节点中
            }
        }
    }

    return true;
 }

bool CFileDataBase::deleteFeature(uint32_t personID)
{
    return true;
}

bool CFileDataBase::addFeature(uint32_t personID, uint8_t *faceToken)
{
    return true;
}