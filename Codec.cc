#include "Codec.h"

//构造
Codec::Codec() {}

//析构
Codec::~Codec() {}

//编码(虚函数)
int Codec::msgEncode(char** outData, int& len) {

  return 0;
}

//解码(虚函数)
int Codec::msgDecode(char* inData, int inLen) {

  return 0;
}

//释放内存(虚函数)
int Codec::msgMemFree(void** point) {

  return 0;
}
