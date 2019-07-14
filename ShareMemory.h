#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <iostream>
#include "sys/types.h"
#include "sys/ipc.h"
#include "sys/shm.h"

namespace share {
	const int PROJ_ID = 8080; 
}
class ShareMemory {
 public:
	//构造1-打开共享1
	ShareMemory(int key);
	//构造2-打开共享内存
	ShareMemory(const char* pathName);
	//构造3-创建共享内存
	ShareMemory(int key, int shmSize);
	//构造4-创建共享内存
	ShareMemory(const char* pathName, int shmSize);
	
	//关联共享内存
  void* mapShm();	
	//解除共享内存关联
	int unmapShm();
	//删除共享内存
  int delShm();

	//读
	int shmRead(size_t len, char** readBuf);
	//写
	int shmWrite(const char* writeBuf, size_t len);
	
 private:
	int m_shmID;	//共享内存id
	void* m_shmAddr;	//共享内存地址


};
