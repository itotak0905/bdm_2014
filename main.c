#include "library.h"
#include "mylib.h"

#define BUF_SIZE 2048

int main(void)
{
    /* init周りゴニョゴニョ */
    /* all_init(); */
    
    int sock;
    struct sockaddr_in addr;
    char buf[BUF_SIZE];

    sock = udp_send_init(&addr);


    printf("test\n");

    int i;
    int value;
    for (;;) {
	/* int numrcv = recvfrom(sock, buf, BUF_SIZE, 0, NULL, NULL); */
	/* if (numrcv < 1) { */
	/* 	if (errno == EAGAIN) { */
	/* 		/\* まだ来ない。*\/ */
	/* 		printf("MADA KONAI\n"); */
	/* 	} else { */
	/* 		perror("recv"); */
	/* 		break; */
	/* 	} */
	/* } else { */
	/* 	printf("received data\n"); */
	/* 	printf("%s\n", buf); */
	/* 	/\* break; *\/ */
	/* } */

	printf("sending...\n");
	if (sendto(sock, "hello1", 6, 0, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
	    perror("send");
	    return -1;
	}
	
	usleep(10000);
    }
    close(sock);    
    /* free_buff(); */

    return 0;
}
