#include "RequestCodec.h"

//构造
RequestCodec::RequestCodec() {

  mRequsetMsg = new RequestMsg;
  memset(mRequsetMsg, 0, sizeof(mRequsetMsg));
}

RequestCodec::RequestCodec(RequestMsg* msg) {

  mRequsetMsg = new RequestMsg;
  memset(mRequsetMsg, 0, sizeof(mRequsetMsg));
  memcpy(mRequsetMsg, msg, sizeof(msg));
}

//析构
RequestCodec::~RequestCodec() {

  delete mRequsetMsg;
}

//编码
int RequestCodec::msgEncode(char** outData, int& len) {
  //编码报文类型(int)
  int retval = writeHeadNode(mRequsetMsg->cmdType);
  if (0 != retval) {
    printf("encode mRequsetMsg->cmdType failed...\n");
    return 25;
  }

  //编码客户端编号(char[])
  retval = writeNextNode(mRequsetMsg->clientId, 
                          strlen(mRequsetMsg->clientId));

  if (0 != retval) {
    printf("encode mRequsetMsg->clientId failed...\n");
    return 26;
  }
  //编码认证码(char[])
  retval = writeNextNode(mRequsetMsg->authCode, 
                          strlen(mRequsetMsg->authCode));

  if (0 != retval) {
    printf("encode mRequsetMsg->authCode failed...\n");
    return 27;
  }
  //编码服务端编号(char[])
  retval = writeNextNode(mRequsetMsg->serverId, 
                          strlen(mRequsetMsg->serverId));

  if (0 != retval) {
    printf("encode mRequsetMsg->serverId failed...\n");
    return 28;
  }
  //编码客户端随机数(char[])
  retval = writeNextNode(mRequsetMsg->r1, 
                          strlen(mRequsetMsg->r1));

  if (0 != retval) {
    printf("encode mRequsetMsg->r1 failed...\n");
    return 29;
  }
  //编码序列
  retval = packSequence(outData, len);

  if (0 != retval) {
    printf("packSequence failed...\n");
    return 30;
  }
  //释放内存
  freeSequnce();

  return 0;
}

//解码
int RequestCodec::msgDecode(char* inData, int inLen) {
  
  //参数检查
  if (NULL == inData || inLen <= 0) {
    printf("msgDecode: the parameter is invalid...\n");
    return 31;
  }

  //解码序列
  int retval = unpackSequence(inData, inLen);
  if (0 != retval) {
    printf("unpackSequence failed...\n");
    return 32;
  }

  //编码报文类型
  retval = readHeadNode(mRequsetMsg->cmdType);
  if (0 != retval) {
    printf("decode cmdType failed...\n");
    return 33;
  }

  //编码客户端编号
  retval = readNextNode(mRequsetMsg->clientId);
  if (0 != retval) {
    printf("decode clientId failed...\n");
    return 34;
  }

  //编码认证码
  retval = readNextNode(mRequsetMsg->authCode);
  if (0 != retval) {
    printf("decode authCode failed...\n");
    return 35;
  }


  //编码服务端编号
  retval = readNextNode(mRequsetMsg->serverId);
  if (0 != retval) {
    printf("decode serverId failed...\n");
    return 36;
  }

  //编码客户端随机数
  retval = readHeadNode(mRequsetMsg->r1);
  if (0 != retval) {
    printf("decode r1 failed...\n");
    return 37;
  }

  //释放内存
  freeSequnce();

  return 0;
}

//释放内存报文请求结构体
int RequestCodec::msgMemFree(void** point) {
  if (NULL == point) {
    return 38;
  }
  else {
    delete *point;
    *point = NULL;
  }

  return 0;
}
