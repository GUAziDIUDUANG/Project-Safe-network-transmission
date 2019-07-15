#include "RespondFactory.h"

//构造
RespondFactory::RespondFactory() {}

//析构
RespondFactory::~RespondFactory() {}

//负责创建对应类的函数
Codec* RespondFactory::createCodec(void* arg) {

	Codec* codec = NULL;

	if (NULL == arg) {
		codec = new RespondCodec;
	}
	else {
		codec = new RespondCodec(static_cast<RespondMsg*>(arg));
	}

	return codec;
}
