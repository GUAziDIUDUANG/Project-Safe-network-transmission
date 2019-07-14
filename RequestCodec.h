#ifndef __02_REQUESTCODEC_H__
#define __02_REQUESTCODEC_H__
#define DISALLOW_COPY_AND_ASSIGN(Typename) \
        Typename(const Typename&) \
        void operator=(const Typename&)
#include "Codec.h"

//请求报文结构体类型
struct RequestMsg
{
  //1 密钥协商  	//2 密钥校验; 	// 3 密钥注销
  int	 cmdType;		// 报文类型 
  char	 clientId[12];	// 客户端编号
  char	 authCode[65];	// 认证码
  char	 serverId[12];	// 服务器端编号 
  char	 r1[64];			// 客户端随机数
};

class RequestCodec : public Codec {
 public:
  //构造
  RequestCodec();
  explicit RequestCodec(RequestMsg* msg);
  //析构
  ~RequestCodec();


  //编码(重写)
  int msgEncode(char** outData, int& len) override;
  //解码(重写)
  int msgDecode(char* inData, int inLen) override;
  //释放报文请求结构体(重写)
  int msgMemFree(void** point) override;

 private:
  //请求报文结构体
  RequestMsg* mRequsetMsg; 

  //防止自动生成拷贝构造和重载赋值运算符
  DISALLOW_COPY_AND_ASSIGN(RequestCodec);
};

#endif