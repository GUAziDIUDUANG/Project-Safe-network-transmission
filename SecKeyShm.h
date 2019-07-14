#ifndef __SECKEYSHM_H__
#define __SECKEYSHM_H__
#include "ShareMemory.h"

class NodeShmInfo {
 public:
	int status;					//密钥状态
	int seckeyID;				//密钥编号
	char clientID[12];	//客户端ID
	char serverID[12];	//服务器ID
	char secKey[128];		//密钥信息

};


class SecKeyShm : public ShareMemory {
 public:
	//构造1-通过key打开共享内存
	explicit SecKeyShm(int key);
	//构造2-通过文件打开共享内存
	explicit SecKeyShm(char* pathName);
	//构造3-通过key创建共享内存
	SecKeyShm(int key, int maxNode);
	//构造4-通过文件创建共享内存
	SecKeyShm(char* pathName, int shmSize);
	//析构
  virtual ~SecKeyShm();	

	//将网点信息写入共享内存
	int shmWrite(NodeShmInfo* pNodeInfo);
	//从共享内存中读取网点密钥信息
	int shmRead(char* clientID, char* serverID, NodeShmInfo* pNodeInfo);

 private:
	int mMaxNode;	//最大网点数
};

#endif
