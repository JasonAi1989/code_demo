/* studio */

#include <stdio.h>
#include <stdlib.h>
#include "struct_t.h"
#define DEBUG

int main( int argc, char ** argv)
{
#ifdef  DEBUG

     space_3d sp;
     char sp_name[] = "gps";
     
     sp.x = 255;
     sp.y = 512;
     sp.z = 1024;
     sp.name = sp_name;
     printf(" sp.x (value is %d)\n sp.y (value is %f) \n", sp.x, sp.y);
     printf(" sp.z (value is %f)\n sp.name (name is %s)\n", sp.z, (char*)sp.name);

#else

    space_3D sp=(space_3D)malloc(sizeof(space_3d));
    char sp_name[] = "gps";

    sp->x = 255;
    sp->y = 512;
    sp->z = 1024;
    sp->name = sp_name;
    printf(" sp->x (value id %d)\n sp->y (value is %f) \n",sp->x, sp->y);
    printf(" sp->z (value is %f)\n sp->name (name is %s)\n", sp->z, (char *)sp->name);
    free(sp);

#endif

     return 0;
}
