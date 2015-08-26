//本文件用于说明信息摘要中的两种常用算法——SHA1和MD5

#include <stdio.h>
#include <string.h>
#include <openssl/ssl.h>
#include <openssl/evp.h>

int main()
{
	EVP_MD_CTX *ctx = NULL;
	unsigned int SHA1_len;
	unsigned int MD5_len;
	unsigned char SHA1[20];
	unsigned char MD5[16];
	char *buf = "abc";
	int i;
	int ret;
	
	//初始化
    SSL_library_init();
    OpenSSL_add_all_algorithms(); 
    SSL_load_error_strings();
	
	//准备进行摘要运算
    ctx = EVP_MD_CTX_create();
    EVP_MD_CTX_init(ctx);
	
	//SHA1摘要算法
    ret = EVP_DigestInit(ctx, EVP_sha1());
	if(!ret)
	{
		printf("error:EVP_DigestInit:SHA1\n");
	}
    ret = EVP_DigestUpdate(ctx, buf, strlen(buf));
	if(!ret)
	{
		printf("error:EVP_DigestUpdate:SHA1\n");
	}
    ret = EVP_DigestFinal(ctx, SHA1, &SHA1_len);
	if(!ret)
	{
		printf("error:EVP_DigestFinal:SHA1\n");
	}
	ret = EVP_MD_CTX_cleanup(ctx);
    if(!ret)
	{
		printf("error:EVP_MD_CTX_cleanup:SHA1\n");
	}
	
	//MD5摘要算法
    ret = EVP_DigestInit(ctx, EVP_md5());
    if(!ret)
	{
		printf("error:EVP_DigestInit:MD5\n");
	}
    ret = EVP_DigestUpdate(ctx, buf, strlen(buf));
       if(!ret)
	{
		printf("error:EVP_DigestUpdate:MD5\n");
	}
	ret = EVP_DigestFinal(ctx, MD5, &MD5_len);
    if(!ret)
	{
		printf("error:EVP_DigestFinal:MD5\n");
	}
	ret = EVP_MD_CTX_cleanup(ctx);
    if(!ret)
	{
		printf("error:EVP_MD_CTX_cleanup:MD5\n");
	}
	
	//销毁
	EVP_MD_CTX_destroy(ctx);
	
	//显示
	printf("original message:%s\n", buf);
	
	printf("md length by SHA1:%d\n",SHA1_len);
	printf("md by SHA1:");
	for(i=0; i<SHA1_len; i++)
	{
		printf("%.2x", SHA1[i]);	
	}
	printf("\n");
	
	printf("md length by MD5:%d\n",MD5_len);
	printf("md by MD5:");
	for(i=0; i<MD5_len; i++)
	{
		printf("%.2x", MD5[i]);	
	}
	printf("\n");	

	return 0;
}



