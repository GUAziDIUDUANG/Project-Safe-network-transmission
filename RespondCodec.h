#ifndef __02_RESPONDCODEC_H__
#define __02_RESPONDCODEC_H__
#define DISALLOW_COPY_AND_ASSIGN(Typename) \
        Typename(const Typename&) \
        void operator=(const Typename&)
#include "Codec.h"

//ÇëÇó±¨ÎÄ½á¹¹ÌåÀàĞÍ
struct RespondMsg
{
  //1 ÃÜÔ¿Ğ­ÉÌ  	//2 ÃÜÔ¿Ğ£Ñé; 	// 3 ÃÜÔ¿×¢Ïú
  int		 rv;						//¿¿¿ 
  char	 clientId[12];	//¿¿¿¿¿
  char	 serverId[12];	//¿¿¿¿¿
  char	 r2[64];			  //¿¿¿¿¿¿
	int    seckeyid;			//¿¿¿¿
};

class RespondCodec : public Codec {
 public:
  //¹¹Ôì
  RespondCodec();
  explicit RespondCodec(RespondMsg* msg);
  //Îö¹¹
  ~RespondCodec();


  //±àÂë(ÖØĞ´)
  int msgEncode(char** outData, int& len) override;
  //½âÂë(ÖØĞ´)
  int msgDecode(char* inData, int inLen) override;
  //ÊÍ·Å±¨ÎÄÇëÇó½á¹¹Ìå(ÖØĞ´)
  int msgMemFree(void** point) override;

 private:
  //ÇëÇó±¨ÎÄ½á¹¹Ìå
  RespondMsg* mRespondMsg; 

  //·ÀÖ¹×Ô¶¯Éú³É¿½±´¹¹ÔìºÍÖØÔØ¸³ÖµÔËËã·û
  DISALLOW_COPY_AND_ASSIGN(RespondCodec);
};

#endif
