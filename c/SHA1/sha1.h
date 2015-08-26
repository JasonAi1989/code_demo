#ifndef SHA1_H
#define SHA1_H

//sha1上下文，用于存储sha1计算中的数据
typedef struct tag
{
	unsigned long long count;	//记录输入字符串的长度，在追加后会改变
	unsigned int state[5];		//摘要值存储缓冲
	unsigned char buffer[64];	//字符串中最后一个未满64个字节的数据块
}SHA1_CTX;

SHA1_CTX* sha1_create();
void sha1_init(SHA1_CTX* initstate);
void sha1_update(SHA1_CTX *sctx, const unsigned char *data, unsigned int len);
void sha1_final(SHA1_CTX *sctx, unsigned char *out);
void sha1_clean(SHA1_CTX* sctx);
void sha1_destory(SHA1_CTX *sctx);
void sha1_digest(unsigned char* md, const char* str);

#endif

