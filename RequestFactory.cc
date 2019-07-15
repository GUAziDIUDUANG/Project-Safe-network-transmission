#include "RequestFactory.h"

//构造
RequestFactory::RequestFactory() {}
//析构
RequestFactory::~RequestFactory() {}

//创建请求报文对象
Codec* RequestFactory::createCodec(void* arg) {

	Codec* codec = NULL;
	if (NULL == arg) {
		codec = new RequestCodec;
	}
	else {
		codec = new RequestCodec(static_cast<RequestMsg*>(arg));
	}

	return codec;
}
