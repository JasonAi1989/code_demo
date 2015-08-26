#ifndef SHA1_H
#define SHA1_H

//sha1�����ģ����ڴ洢sha1�����е�����
typedef struct tag
{
	unsigned long long count;	//��¼�����ַ����ĳ��ȣ���׷�Ӻ��ı�
	unsigned int state[5];		//ժҪֵ�洢����
	unsigned char buffer[64];	//�ַ��������һ��δ��64���ֽڵ����ݿ�
}SHA1_CTX;

SHA1_CTX* sha1_create();
void sha1_init(SHA1_CTX* initstate);
void sha1_update(SHA1_CTX *sctx, const unsigned char *data, unsigned int len);
void sha1_final(SHA1_CTX *sctx, unsigned char *out);
void sha1_clean(SHA1_CTX* sctx);
void sha1_destory(SHA1_CTX *sctx);
void sha1_digest(unsigned char* md, const char* str);

#endif

