#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

//rscallback
int rscallback (void *p,int argc, char **argv,char **argvv)
{
    int i;
    *(int *)p = 0;

    for(i=0;i<argc;i++){
        printf("%s=%s,",argvv[i],argv[i]?argv[i]:"NULL");
    }
    putchar('\n');

return 0;
}


// display
int  display(void)
{

    sqlite3 *db = 0;
    char *err = 0;
    int empty = 1;
    int ret = 0;
    ret = sqlite3_open("./test.db",&db);
    if (ret != SQLITE_OK)
    {
        fputs(sqlite3_errmsg(db),stderr);
        fputs("\n",stderr);
        exit(1);
    }


   
    ret = sqlite3_exec(db,"select * from student;",\
                    rscallback,&empty,&err);
    if(ret != SQLITE_OK)
    {
        fputs(err,stderr);
        fputs("\n",stderr);
        sqlite3_close(db);
        exit(1);
    }
    if(empty)
    {
        fputs("table student is empty\n",stderr);
        exit(1);
    }
    sqlite3_close(db);
    return 0;
}

//delete
int delete(void)
{
    sqlite3 *db = 0;
    char *err = 0;
    int ret = 0;
    ret = sqlite3_open("./test.db",&db);
    if (ret != SQLITE_OK)
    {
        fputs(sqlite3_errmsg(db),stderr);
        fputs("\n",stderr);
        exit(1);
    }
    
    int sel,id;
    char name[15] = {};
    char *sql = 0;
    int empty = 1;

    while(1){
        printf("1.delete by ID\n");
        printf("2.delete by name\n");
        printf("3.exit\n");
        printf("your choice:");
        scanf("%d",&sel);
        
        switch(sel){
            case 1:
                printf("please input the ID:");
                scanf("%d",&id);
                sql = sqlite3_mprintf("delete \
                    from student where id=\
                    %d;",id);
                break;
            case 2:
                printf("please input the name:");
                scanf("%s",name);
                sql = sqlite3_mprintf("delete \
                    from student where name = \
                    %Q;",name);
                break;
            case 3:
                return 0;
            default :
                printf("error\n");
                break;
            }
            if (sel==1||sel==2)
                break;
        }

    ret = sqlite3_exec(db,sql,rscallback,&empty,NULL); 
    sqlite3_free(sql);
    sqlite3_close(db);
    return 0;
}

//insert
int insert(void)
{
    char *sql = 0;
    sqlite3 *db = 0;
    char *err = 0;
    int ret = 0;
    ret = sqlite3_open("./test.db",&db);
    if (ret != SQLITE_OK)
    {
        fputs(sqlite3_errmsg(db),stderr);
        fputs("\n",stderr);
        exit(1);
    }

    int id,age;
    char name[1024] = {};
    char gender[1024] = {};
    int empty = 1;

    printf("please input ID(1~100) name(Within 15 characters) \
            gender(female or male) age(1~120):\n");    
    scanf("%d %s %s %d",&id,name,gender,&age);
        
    if (id>100||id<1)
        printf("ID error\n");


    sql = sqlite3_mprintf("insert into student\
            values(%d,%Q,%Q,%d);",id,name,gender\
            ,age);
     ret = sqlite3_exec(db,sql,rscallback,\
            &empty,NULL); 
    sqlite3_free(sql);
    sqlite3_close(db);
    return 0;


}


int main(int argc, const char *argv[])
{
    int sel;
    while (1)
    {

        printf("1.display all record\n");
        printf("2.Insert record\n");
        printf("3.Delete record\n");
        printf("4.exit\n");

        scanf("%d",&sel);

        switch (sel)
        {
            case 1:
                display();
                break;
            case 2:
                insert();
                break;
            case 3:
                delete();
                break;       
            case 4:
                return 0;
        }
    }
}

