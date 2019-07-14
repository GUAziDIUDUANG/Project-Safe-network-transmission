#include "SecKeyShm.h"

//构造1-通过key打开共享内存
SecKeyShm::SecKeyShm(int key) 
    : ShareMemory(key), mMaxNode(10) {}

//构造2-通过文件打开共享内存
SecKeyShm::SecKeyShm(char* pathName) 
    : ShareMemory(pathName), mMaxNode(10) {}

//构造3-通过key创建共享内存
SecKeyShm::SecKeyShm(int key, int maxNode) 
    : ShareMemory(key,sizeof(NodeShmInfo) *  maxNode),
      mMaxNode(maxNode) {}

//构造4-通过文件创建共享内存
SecKeyShm::SecKeyShm(char* pathName, int maxNode)
    : ShareMemory(pathName, maxNode * sizeof(NodeShmInfo)),
			mMaxNode(maxNode) {} 

//析构
SecKeyShm::~SecKeyShm() {}


//将网点信息写入共享内存
int SecKeyShm::shmWrite(NodeShmInfo* pNodeInfo) {
	//1.关联共享内存
	void* addr = mapShm();
	if (NULL == addr) {
		printf("ERROR:\nfile: %s\nline: %s\nfunction: SecKeyShm::%s", 
					 __FILE__, 
					 __LINE__,
					 __FUNCTION__);
		return 60;
	}
	
	//2.写共享内存
	//2.1.共享内存有对应信息,直接覆盖
	//2.2.共享内存没有对应信息,找一个空白区域写入
	
	//查找是否重
	NodeShmInfo* tmp = (NodeShmInfo*)addr;
	int i = 0;

	for (i = 0; i < mMaxNode; ++i) {
		bool retval = (!strcmp(tmp[i].clientID, 
												   pNodeInfo->clientID)  &&
									 !strcmp(tmp[i].serverID,
												   pNodeInfo->serverID));

		//找到重复元素
		if (true == retval) {
			printf("存在对应网点,现在覆盖\n");
			memcpy(&tmp[i], pNodeInfo, sizeof(NodeShmInfo));	
			break;
		}
  }

	//没有重复
	NodeShmInfo tmpNode;
	memset(&tmpNode, 0, sizeof(tmpNode));

	if (i == mMaxNode) {
		//寻找空白区域
		for (i = 0; i < mMaxNode; ++i) {
			if (0 == memcmp(&tmpNode, &tmp[i], sizeof(tmpNode))) {
				printf("找到空白位置,现在写入共享内\n");
				memcpy(&tmp[i], pNodeInfo, sizeof(pNodeInfo));
				printf("[%s]\n", (&tmp[i])->serverID);
				printf("[%s]\n", tmpNode.serverID);
				printf("[%s]\n", pNodeInfo->serverID);
				break;
			}
		}

		//未找到空白区域
		if (i == mMaxNode) {
			printf("未找到空白区域,写入失败\n");
		}
	}
	
	//3.解除关联共享内存
	int retval = unmapShm();

	if (0 != retval) {
		printf("shmWrite: unmapShm failed...\n");
		return 63;
	}	

	return 0;
}

//从共享内存中读取网点密钥信息
int SecKeyShm::shmRead(char* clientID, char* serverID, NodeShmInfo* pNodeInfo) {
	//参数判断
	if (NULL == clientID || NULL == serverID || NULL == pNodeInfo) {
		printf("shmRead: the parameter is invalid...\n");
		return 62;
	}

	//1.关联共享内存
	int i = 0;
	void* addr = mapShm();

	if (NULL == addr) {
		printf("shmRead: mapShm failed...\n");
		return 64;
	}
	
	//2.读取内容	
	NodeShmInfo* tmp = static_cast<NodeShmInfo*>(addr);
	for (i = 0; i < mMaxNode; ++i) {
		if (!strcmp(tmp[i].clientID, clientID) &&
				!strcmp(tmp[i].serverID, serverID)) {
			memcpy(pNodeInfo, tmp, sizeof(NodeShmInfo));
			break;
		}
	}

	if (i == mMaxNode) {
		printf("未找到对应网点密钥信息\n");
	  unmapShm();	
		return 65;
	}

	//3.解除共享内存关联
	int retval = unmapShm();
	if (0 != retval) {
		printf("shmRead: unmapShm failed...\n");
		return 64;
	}

	return 0;
}

