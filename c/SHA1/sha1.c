#include <stdlib.h>
#include <string.h>
#include "sha1.h"

#define K1 0x5a827999
#define K2 0x6ed9eba1
#define K3 0x8f1bbcdc
#define K4 0xca62c1d6

#define f1(x,y,z)   (z ^ (x & (y ^ z)))		/* x ? y : z */
#define f2(x,y,z)   (x ^ y ^ z)			/* XOR */
#define f3(x,y,z)   ((x & y) + (z & (x ^ y)))	/* majority */

static inline unsigned int rol32(unsigned int word, unsigned int shift)
{
	return (word << shift) | (word >> (32 - shift));
}

//对输入的一个64字节的数据块进行运算
static void sha_transform(unsigned int *digest, const unsigned char *in, unsigned int *W)
{
	unsigned int a, b, c, d, e, t, i;
	unsigned int tmp[4];

	for (i = 0; i < 16; i++)
	{
		W[i] = (unsigned int)in[i*4 + 0]<<24 
				| (unsigned int)in[i*4 +1]<<16 
				| (unsigned int)in[i*4 +2]<<8 
				| (unsigned int)in[i*4 +3]; 
	}

	for (i = 0; i < 64; i++)
	{
		W[i+16] = rol32(W[i+13] ^ W[i+8] ^ W[i+2] ^ W[i], 1);
	}

	a = digest[0];
	b = digest[1];
	c = digest[2];
	d = digest[3];
	e = digest[4];

	for (i = 0; i < 20; i++) 
	{
		t = f1(b, c, d) + K1 + rol32(a, 5) + e + W[i];
		e = d; d = c; c = rol32(b, 30); b = a; a = t;
	}

	for (; i < 40; i ++) 
	{
		t = f2(b, c, d) + K2 + rol32(a, 5) + e + W[i];
		e = d; d = c; c = rol32(b, 30); b = a; a = t;
	}

	for (; i < 60; i ++) 
	{
		t = f3(b, c, d) + K3 + rol32(a, 5) + e + W[i];
		e = d; d = c; c = rol32(b, 30); b = a; a = t;
	}

	for (; i < 80; i ++) 
	{
		t = f2(b, c, d) + K4 + rol32(a, 5) + e + W[i];
		e = d; d = c; c = rol32(b, 30); b = a; a = t;
	}

	digest[0] += a;
	digest[1] += b;
	digest[2] += c;
	digest[3] += d;
	digest[4] += e;
}

//sha1句柄创建
SHA1_CTX* sha1_create()
{
	SHA1_CTX* sctx = malloc(sizeof(SHA1_CTX));
	if(!sctx)
	{
		exit(0);
	}
	bzero(sctx, sizeof(SHA1_CTX));

	return sctx;
}
//sha1初始化函数
void sha1_init(SHA1_CTX* initstate)
{
	if(!initstate)
	{
		return;
	}

	initstate->state[0] = 0x67452301;
	initstate->state[1] = 0xEFCDAB89;
	initstate->state[2] = 0x98BADCFE;
	initstate->state[3] = 0x10325476;
	initstate->state[4] = 0xC3D2E1F0;
}

//sha1计算函数，此函数会将字符串中最后一个未满64字节的数据块存储到sha1_ctx->buffer中，
//等待下次追加字符串时使用
void sha1_update(SHA1_CTX *sctx, const unsigned char *data,
		unsigned int len)
{
	unsigned int partial, done;
	const unsigned char *src;

	partial = sctx->count & 0x3f;
	sctx->count += len;
	done = 0;
	src = (unsigned char*)data;

	if ((partial + len) > 63) 
	{
		unsigned int temp[80];

		if (partial) 
		{
			done = -partial;
			memcpy(sctx->buffer + partial, data, done + 64);
			src = sctx->buffer;
		}

		do {
			sha_transform(sctx->state, src, temp);
			done += 64;
			src = data + done;
		} while (done + 63 < len);

		memset(temp, 0, sizeof(temp));
		partial = 0;
	}
	memcpy(sctx->buffer + partial, src, len - done);
}

void sha1_final(SHA1_CTX *sctx, unsigned char *out)
{
	unsigned int i, index, padlen;
	unsigned long long  bits;
	unsigned char* p;
	unsigned char bit_tmp[8];
	static const unsigned char padding[64] = { 0x80, };

	bits = sctx->count << 3;
	p = (unsigned char*) &bits;
	for(i=0; i<8; i++)
	{
		memcpy(&bit_tmp[7-i], p+i, 1);
	}

	/* Pad out to 56 mod 64 */
	index = sctx->count & 0x3f;
	padlen = (index < 56) ? (56 - index) : ((64+56) - index);
	sha1_update(sctx, padding, padlen);

	/* Append length */
	//sha1_update(sctx, (const unsigned char *)&bits, sizeof(bits));
	sha1_update(sctx, bit_tmp, 8);

	/* Store state in digest */
	p = (unsigned char*)sctx->state;
	for (i = 0; i < 5; i++)
	{
		out[i*4+3] = p[i*4];
		out[i*4+2] = p[i*4+1];
		out[i*4+1] = p[i*4+2];
		out[i*4] = p[i*4+3];
	}
	/* Wipe context */
	memset(sctx, 0, sizeof *sctx);
}

void sha1_clean(SHA1_CTX* sctx)
{
	bzero(sctx, sizeof(SHA1_CTX));
	sha1_init(sctx);
}

void sha1_destory(SHA1_CTX *sctx)
{
	if(sctx)
	{
		free(sctx);
	}
}

//集成sha1初始化，计算，结束函数，适用于只对一个字符串进行计算的时候
void sha1_digest(unsigned char* md, const char* str)
{
	if(!md || !str)
	{
		return;
	}

	SHA1_CTX *sctx = NULL;
	
	sctx = sha1_create();
	sha1_init(sctx);
	sha1_update(sctx, (const unsigned char*)str, strlen(str));
	sha1_final(sctx, md);
	sha1_destory(sctx);
}	
