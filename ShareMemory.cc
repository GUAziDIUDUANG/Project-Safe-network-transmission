#include "ShareMemory.h"

//构造1-打开共享内存
ShareMemory::ShareMemory(int key) {
	//check parameter
	if (key < 0) {
		printf("open ShareMemory by key failed...\n");
		return;
	}	
	 
	//打开共享内存
	int retval = shmget(key, 0, 0);
	if (retval < 0) {
		printf("One: open key failed...\n");
		return;
	}
	m_shmID = retval;
}


//构造2-打开共享内存
ShareMemory::ShareMemory(const char* pathName) {
	//check parameter
	if (NULL == pathName) {
		printf("open ShareMemory by pathName failed...\n");
		return;
	}

	//生成key
	int key = ftok(pathName, share::PROJ_ID);
	if (key < 0) {
		printf("Two: ftok failed...\n");
		return;
	}

	//打开共享内存
	int retval = shmget(key, 0, 0644);	
	if (retval < 0) {
		printf("Two: open pathName failed...\n");
		return;
	}

	m_shmID = retval;
}


//构造3-创建共享内存
ShareMemory::ShareMemory(int key, int shmSize) {
	//check parameter
	if (key < 0 || shmSize < 0) {
		printf("create ShareMemory by key failed...\n");
		return;
	}	

	//创建或打开共享内存
	int retval = shmget(key, shmSize, IPC_CREAT | 0644);
	if (retval < 0) {
		printf("Three: create ShareMemory by key failed...\n");
		return;
	}	
	 
	m_shmID = retval;
}


//构造4-创建共享内存
ShareMemory::ShareMemory(const char* pathName, int shmSize) {
	//check parameter
	if (shmSize < 0 || NULL == pathName) {
		printf("create ShareMemory by pathName failed...\n");
		return;
	}	
	
	//生成key
	int key = ftok(pathName, share::PROJ_ID);
	if (key < 0) {
		printf("Four: key failed...\n");
		return;
	}

	//创建或打开共享内存
	int retval = shmget(key, shmSize, IPC_CREAT | 0644);
	if (retval < 0) {
		printf("create ShareMemory by key failed...\n");
		return;
	}	
	 
	m_shmID = retval;
}


//关联共享内存
void* ShareMemory::mapShm() {
	//关联
	m_shmAddr = shmat(m_shmID, NULL, 0);
	if ((void*)(-1) == m_shmAddr) {
		printf("mapShm failed...\n");
		return NULL;
	}

	return m_shmAddr;
}	


//解除共享内存关联
int ShareMemory::unmapShm() {
	int retval = shmdt(m_shmAddr);
	if (retval < 0) {
		printf("unmapShm failed...\n");
		return -1;
	}

	return 0;
}


//删除共享内存
int ShareMemory::delShm() {
	if (m_shmID < 0) {
		printf("shmID error...\n");
		return -2;
	}

	//删除共享内存
	int retval = shmctl(m_shmID, IPC_RMID, NULL);
	if (retval < 0) {
		printf("delShm failed...\n");
		return -3;
	}

	return 0;
}


//读
int ShareMemory::shmRead(size_t len, char** readBuf) {
	//参数判断
	if (0 == len) {
		printf("shmRead: the parameter is invalid...\n");
		return -5;
	}

	//读取操作
	if (readBuf != NULL) {
	  *readBuf = (char*)malloc(len);
	  memset(*readBuf, 0, len);
		memcpy(*readBuf, m_shmAddr, len);
	}

	char buf[1024] = "";
	memcpy(buf, m_shmAddr, len);
	printf("read:	[%s]\n", buf);

	return 0;
}


//写
int ShareMemory::shmWrite(const char* writeBuf, size_t len) {
	//参数判断
	if (NULL == writeBuf || len == 0) {
		printf("shmWrite: the parameter is invalid...\n");
		return -6;
	}

	//写入操作
	for (size_t i = 0; i < len; ++i) {
		memset((char*)m_shmAddr + i, writeBuf[i], 1);
	}


	return 0;
}
