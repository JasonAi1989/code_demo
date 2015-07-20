#include <stdio.h>
#include <unistd.h>

int main()
{
	execl("/ca/bin/switch_logserver.sh", "switch_logserver.sh", "start", 1, 30, NULL);
	return 0;
}