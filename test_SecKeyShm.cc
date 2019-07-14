#include "SecKeyShm.h"

int main(void) {
	//创建网点密钥对象
	NodeShmInfo info;
	info.status = 0;
	info.seckeyID = 1;
	strcpy(info.clientID, "10086");
	strcpy(info.serverID, "10010");
	strcpy(info.secKey, "China!");
	
	//写入共享内存
	SecKeyShm* shmW = new SecKeyShm(2, 20);
	shmW->shmWrite(&info);
	NodeShmInfo* ttt = (NodeShmInfo*)shmW;

	//读取共享内存信息
	SecKeyShm* shmR = new SecKeyShm(2);
	NodeShmInfo* readBuf = new NodeShmInfo;
	int retval = shmR->shmRead("10086", "10010", readBuf);
	printf("return value: %d\n", retval);

	if (0 == retval)
	printf("status: %d\nseckeyID: %d\nclientID: %s\nserverID: %s\nsecKey: %s\n", 
				 readBuf->status,
				 readBuf->seckeyID,
				 readBuf->clientID,
				 readBuf->serverID,
				 readBuf->secKey);

	getchar();

	return 0;
}
