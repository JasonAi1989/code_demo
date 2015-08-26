//本文件中的base64解码函数来源于其他开源软件

#include <string.h>
#include <stdlib.h>

#define BLKLEN         256
#define blank(c)    ((c)+1 > 0 && (c) <= 32)

const char base64i[81] = "\76XXX\77\64\65\66\67\70\71\72\73\74\75XXXXXXX\00\01\02\03\04\05\06\07\10\11\12\13\14\15\16\17\20\21\22\23\24\25\26\27\30\31XXXXXX\32\33\34\35\36\37\40\41\42\43\44\45\46\47\50\51\52\53\54\55\56\57\60\61\62\63";

//s：需要转换的字符串
//t：转换后的字符串，当此值为NULL时，第三个参数无效
//l：需要转换的长度
//n：转换后的长度
char* base64_decode(const char *s, char *t, int l, int *n)
{ 
	register int i, j;
    register int c;
    register unsigned int m;
    register char *p;
    if (!s || !*s)
    {
        return NULL;
    }

    if (!t)
    { 
        l = (strlen(s) + 3) / 4 * 3 + 1;    /* make sure enough space for \0 */
        t = (char*)malloc(l);
    }

    if (!t)
    {
        return NULL;
    }

    p = t;
    if (n)
        *n = 0;

    for (;;)
    { 
        for (i = 0; i < BLKLEN; i++)
        { 
            m = 0;
            j = 0;
            while (j < 4)
            { 
                c = *s++;
                if (c == '=' || !c)
                { i *= 3;
                    switch (j)
                    { case 2:
                        *t++ = (char)((m >> 4) & 0xFF);
                        i++;
                        break;
                        case 3:
                        *t++ = (char)((m >> 10) & 0xFF);
                        *t++ = (char)((m >> 2) & 0xFF);
                        i += 2;
                    }
                    if (n)
                        *n += (int)i;
                    if (l >= j)
                        *t = '\0';
                    return p;
                }
                c -= '+';
                if (c >= 0 && c <= 79)
                { int b = base64i[c];
                    if (b >= 64)
                    { 
                        return NULL;
                    }
                    m = (m << 6) + b;
                    j++;
                }
                else if (!blank(c + '+'))
                {
                    return NULL;
                }
            }
            if (l < 3)
            { if (n)
                *n += (int)i;
                *t = '\0';
                return p;
            }
            *t++ = (char)((m >> 16) & 0xFF);
            *t++ = (char)((m >> 8) & 0xFF);
            *t++ = (char)(m & 0xFF);
            l -= 3;
        }
        if (n)
            *n += 3 * BLKLEN;
    }

	return NULL;
}

