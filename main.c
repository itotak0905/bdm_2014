#include "mylib.h"
#include "library.h"

int main(void)
{
    /* init周りゴニョゴニョ */
    /* all_init(); */
    
    int sock;
    struct sockaddr_in addr;

    char buf[2048];

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock == -1) {
	perror("socket:");
	return -1;
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(12345);
    if (inet_aton("127.0.0.1", &addr.sin_addr) == 0) {
	printf("error:inet_aton\n");
	return -1;
    }
    /* addr.sin_addr.s_addr = INADDR_ANY; */

    /* if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) == -1) { */
    /* 	perror("bind:"); */
    /* 	return -1; */
    /* } */

    printf("test\n");

    
    int i;
    int value;
    for (i = 0; i < 10; i++) {
	/* int numrcv = recvfrom(sock, buf, 2048, 0, NULL, NULL); */
	/* if(numrcv == -1) {  */
	/*     close(sock); */
	/*     break; */
	/* } */
	/* printf("received: %s\n", buf); */
	
	printf("sending...\n");
	if (sendto(sock, "hello", 6, 0, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
	    perror("send");
	    return -1;
	}
	
	usleep(100000);
    }
    close(sock);    
    /* free_buff(); */

    return 0;
}
