#ifndef __HASH__
#define __HASH__

unsigned int SDBMHash(char *str);
unsigned int RSHash(char *str);
unsigned int JSHash(char *str);
unsigned int PJWHash(char *str);
unsigned int ELFHash(char *str);
unsigned int BKDRHash(char *str);
unsigned int DJBHash(char *str);
unsigned int APHash(char *str);

#endif
