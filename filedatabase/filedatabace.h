#pragma once

#include <stdint.h>

#define MAX_GROUP_SIZE (3)


class CFileDataBase
{
private:
    //\ 文件信息头, 保存人员的相关结构的大小
    typedef struct PERSON_HEAD_INFO_T
    {
        uint32_t persionNum;
        uint32_t nodeSize;
        uint32_t tokenLen;
        uint32_t featureLen;
    }person_head_info_t;

    //\ 人员节点信息
    typedef struct PERSON_NODE_INFO_T
    {
        uint32_t    offset;         //\ 在文件中的偏移量
        uint32_t    personId;       //\ 人员ID
    }person_node_info_t;

    //\ 人员信息索引
    typedef struct PERSON_NODE_INDEX_T
    {
        uint32_t    freeSize;       //\ 空闲大小，如果== 0,表示此块被占用
        uint32_t    offset;         //\ 在文件中的偏移量
    }person_node_index_t;

    //\ 文件空闲块的集合
    typedef struct FILE_DATABASE_INDEX_T
    {
        uint32_t cap;
        uint32_t size;
        person_node_index_t   *pPersonNode;
    }file_database_index_t;

public:
    static CFileDataBase *instance();

    ~CFileDataBase();

    bool loadFeature();

    bool deleteFeature(uint32_t personID);

    bool addFeature(uint32_t personID, uint8_t *faceToken);

private:
    CFileDataBase();

    bool init();

    bool initHeadLength();

    bool seek(uint32_t offset);

    bool addFeature2Alg(person_node_info_t *pNode);

    bool addIndex(person_node_info_t *pNode);
private:
    int32_t                     m_fd;                     
    bool                        m_initFlag;
    person_head_info_t          m_personHead;
    file_database_index_t       m_index;
};