#ifndef __CLIENTOPERATION_H__
#define __CLIENTOPERATION_H__
#include "SecKeyShm.h"
#include "TcpSocket.h"
#include "Codec.h"
#include "FactoryCodec.h"

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

//密钥协商客户端业务类
class ClientOperation {
 public:
	ClientOperation(ClientInfo* cliInfo);
	~ClientOperation();

  //密钥协商
	int secKeyAgree();
	//密钥校验
	int secKeyCheck();
	//密钥注销
	int secKeyRevoke();
	//密钥查看
	int secKeyView();
	//生成随机序列
	void getRandString(int len, char* buf);
	
 private:
	ClientInfo* m_info;		//密钥协商客户端配置信息对象指针
	SecKeyShm* m_shm;			//共享内存操作对象指针
	TcpSocket* m_socket;	//tcp通信客户端对象指针
}

#endif
