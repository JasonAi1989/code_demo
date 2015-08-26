//本文件用于说明BASE64编解码，调用的是openssl的库

#include <stdio.h>
#include <string.h>
#include <openssl/ssl.h>
#include <openssl/evp.h>

int main()
{
	char *buf1 = "hello world";
	char *buf2 = "aGVsbG8gd29ybGQ=";
	char b64d_buf[30];
	char b64e_buf[30];
	
	//初始化
    SSL_library_init();
    OpenSSL_add_all_algorithms(); 
    SSL_load_error_strings();
	
	//BASE64编码
	EVP_EncodeBlock(b64e_buf, buf1, strlen(buf1));

	printf("original buf1:%s\n", buf1);
	printf("base64 encode:%s\n", b64e_buf);
	
	//BASE64解码
	EVP_DecodeBlock(b64d_buf, buf2, strlen(buf2));
	
	printf("original buf2:%s\n", buf2);
	printf("base64 decode:%s\n", b64d_buf);	
	
	return 0;
}



