这对客户端与服务器主要用于实现“客户端调用服务端的shell脚本，服务端返回脚本打印的信息给客户端”
主要用于解决项目中经常要调用一些脚本来获取设备的一些信息，如果直接调用脚本，每次调用都需要fork一下进程，并要配合管道才能获取到shell脚本打印的信息。
使用项目提供的api，可以直接通过TCP连接获取到脚本的信息，使客户端的复杂度降低。

客户端API

//返回建立连接的句柄，如果建立连接失败，返回-1
int SFS_connect_server(char* server_IP, int server_port)

//返回-1说明执行失败
int SFS_execl_shell(int fs, char*shell_path_name)

//返回写入到buffer中的字节数
int SFS_get_message(int fd, char* message_buffer, int buffer_len)