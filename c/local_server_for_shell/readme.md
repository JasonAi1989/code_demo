��Կͻ������������Ҫ����ʵ�֡��ͻ��˵��÷���˵�shell�ű�������˷��ؽű���ӡ����Ϣ���ͻ��ˡ�
��Ҫ���ڽ����Ŀ�о���Ҫ����һЩ�ű�����ȡ�豸��һЩ��Ϣ�����ֱ�ӵ��ýű���ÿ�ε��ö���Ҫforkһ�½��̣���Ҫ��Ϲܵ����ܻ�ȡ��shell�ű���ӡ����Ϣ��
ʹ����Ŀ�ṩ��api������ֱ��ͨ��TCP���ӻ�ȡ���ű�����Ϣ��ʹ�ͻ��˵ĸ��ӶȽ��͡�

�ͻ���API

//���ؽ������ӵľ���������������ʧ�ܣ�����-1
int SFS_connect_server(char* server_IP, int server_port)

//����-1˵��ִ��ʧ��
int SFS_execl_shell(int fs, char*shell_path_name)

//����д�뵽buffer�е��ֽ���
int SFS_get_message(int fd, char* message_buffer, int buffer_len)