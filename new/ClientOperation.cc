#include "ClientOperation.h"

//密钥协商客户端配置信息
struct ClientInfo {
 public:
	char				 clientID[12];		//客户端ID
	char				 serverID[12];		//服务端ID
	char				 authCode[65];		//消息认证码
	char				 serverIP[32];		//服务器IP
	unsigned int serverPort;			//服务器端口
	int					 maxNode;					//共享节点个数 客户端默认1个
	int					 shmKey;					//共享内存key值
}

//构造
ClientOperation::ClientOperation(ClientInfo* cliInfo) {
	//参数检查
	if (NULL == cliInfo) {
		printf("ClientOperation: the parameter is invalid...\n");
		return;
	}

	//分配m_info空间 
	m_info = new ClientInfo();
	if (NULL == m_info) {
		printf("ClientOperation: new ClientINfo failed...\n");\
		return;
	}

	//拷贝数据
	memcpy(m_info, cliInfo, sizeof(ClientInfo));

	//创建TCP客户端对象
	m_socket = new TcpSocket();
	if (NULL == m_info) {
		printf("ClientOperation: new TcpSocket failed...\n");\
		return;
	}

	//创建共享内存业务类对象
	m_shm = new SecKeyShm(m_info->shmKey, m_info->maxNode);
	if (NULL == m_shm) {
		printf("ClientOperation: new SecKeyShm failed...\n");
		return;
	}

}

//析构
ClientOperation::~ClientOperation() {

	delete m_info;
	delete m_shm;
	delete m_socket;
}

//密钥协商
int ClientOperation::secKeyAgree();
//密钥校验
int ClientOperation::secKeyCheck();
//密钥注销
int ClientOperation::secKeyRevoke();
//密钥查看
int ClientOperation::secKeyView();
//生成随机序列
void ClientOperation::getRandString(int len, char* buf) {
	int i = 0;
	int tag = 0;

	//设置随机种子
	srand(time(NULL));
	memset(buf, 0 ,len);
	
	//随机字符种类 A-Z a-z 0-9 ~!@#$%^&*+=-
	tag = random() % 4;

	//随机字符
	switch (tag) {
		//大写字母
		case 0:
			break;

		//小写字母
		case 1:
			break;

		//随机数字
		case 2:
			break;

		//其他特殊字符
		case 3:
			break;
	}

}
	
 private:
	ClientInfoi* m_info;		//密钥协商客户端配置信息对象
	SecKeyShm* m_shm;			//共享内存操作对象指针
	TcpSocket* m_socket;		//tcp客户端对象
}

#endif
