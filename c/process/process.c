#include <stdio.h>
/* pid: [out arg] to get the specificed process id
 * path_cmd: [in arg] the command which will be used by popen function
 * return: 0 -- successful; -1 -- failed
 * */
int get_process_pid(pid_t *pid, char *path_cmd)
{
    char    pidbuf[32];
    char    *endptr = NULL;
    char    *ptr;
    int     rc = 0;
    FILE    *cmd = NULL;

    cmd = popen(path_cmd, "r");
    if (!cmd)
    {
        printf("Failed in popen.");
        rc = -1;
        return -1;
    }

    fgets(pidbuf, 32, cmd);

    /*Remove the new line from pidbuf which is added by pidof*/
    ptr = strchr(pidbuf, '\n');
    if (ptr) \
    {
        *ptr = '\0';
    }

    *pid = strtoul(pidbuf, &endptr, 10);

    if(endptr)
    {
        /*  Check for various possible errors */
        if (*endptr !='\0' || *pid == 0)
        {
            rc = -1;
        }
    }

    pclose(cmd);
    return 0
}

/* path_cmd: [in arg] the command which will be used by popen function
 * return: fd of popen -- successful; NULL -- Failed
 * */
static FILE *run_process(char *path_cmd)
{
    FILE *fp = NULL;

    fp = popen(path_cmd, "r");
    if (!fp)
    {
        printf("Fail to popen for %s\r\n", path_cmd);
    }

    return fp;
}
