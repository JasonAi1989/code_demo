#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

typedef struct file_context
{
	char* filename;
	FILE* fd;
}file_context_t;

#define NUMBER	8
int gen_tar_file(char* src_file, file_context_t* tar_file_table, int num)
{
	if(num > NUMBER || !src_file)
		return -1;
		
	int len = strlen(src_file) + 1;
	char* basic_name = (char*)malloc(len);
	strncpy(basic_name, src_file, len);
	char*p = strstr(basic_name, ".txt");
	*p=0;
	//printf("basic name:%s\n", basic_name);
	
	int newlen = len+1;
	int basic_name_len = strlen(basic_name);
	
	for(int i=0;i<num;i++)
	{
		tar_file_table[i].filename = (char*)malloc(newlen);
		bzero(tar_file_table[i].filename, newlen);
		strcpy(tar_file_table[i].filename, basic_name);
		p = tar_file_table[i].filename + basic_name_len;
		sprintf(p, "%d.txt", i);
		//printf("tar file %d: %s\n", i, tar_file_table[i].filename);
		
		tar_file_table[i].fd = fopen(tar_file_table[i].filename, "w");
	}
	
	free(basic_name);
	return 0;
}

int distory_tar_file(file_context_t* tar_file_table)
{
	for(int i=0; i<NUMBER; i++)
	{
		if(tar_file_table[i].filename != NULL)
		{
			free(tar_file_table[i].filename);
			tar_file_table[i].filename = NULL;
			fclose(tar_file_table[i].fd);
		}
	}
}

char* readline(FILE* fd)
{
	int size=0;
	char c;
	char* buf=NULL;
		
	while((c = fgetc(fd)) != '\n' && !feof(fd))
		size++;

	if(c == '\n')
		size++;

	if(size == 0)
		return NULL;
		
	fseek(fd, -size, SEEK_CUR);

	buf = (char*)malloc(size+1);
	bzero(buf, size+1);
	fread(buf, size, 1, fd);
	
	return buf;
}
int writeline(FILE* fd, char* buf)
{
	return fwrite(buf, strlen(buf), 1, fd);
}

int divide(file_context_t* src_file, file_context_t* tar_file_table, int num)
{
	if(!src_file || !tar_file_table || num > NUMBER)
		return -1;
	
	char* buf;
	for(int i=0;!feof(src_file->fd); i++)
	{
		if(i == num)
			i=0;
				
		if((buf = readline(src_file->fd)) == NULL)
			break;
		writeline(tar_file_table[i].fd, buf);
		free(buf);
	}
}

int main(int argc, char* argv[])
{
	if(argc == 1)
	{
		printf("please input the args:\ndivide [file] [num](2~8,default number is 2)\n");
		return -1;
	}
	
	file_context_t src_file = {argv[1], NULL};
	file_context_t tar_file[NUMBER];
	int num;
	
	bzero(tar_file, sizeof(file_context_t)*NUMBER);
	
	src_file.fd = fopen(src_file.filename, "r");
	if(src_file.fd == NULL)
	{
		printf("bad fd\n");
		return -1;
	}
	
	if(argc <3)
		num = 2;
	else
		num = atoi(argv[2]);
	
	if(num<2 || num>8)
		return -1;
		
	gen_tar_file(src_file.filename, tar_file, num);
	
	divide(&src_file, tar_file, num);
	
	distory_tar_file(tar_file);
	fclose(src_file.fd);
    return 0;
}
