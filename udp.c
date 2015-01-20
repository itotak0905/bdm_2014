#include "library.h"
#include "mylib.h"

int udp_receive_init(struct sockaddr_in *p_addr, int port)
{
    int sock;

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock == -1) {
	perror("socket:");
	return -1;
    }

    p_addr->sin_family = AF_INET;
    p_addr->sin_port = htons(port);
    p_addr->sin_addr.s_addr = INADDR_ANY;

    if (bind(sock, (struct sockaddr *)p_addr, sizeof(*p_addr)) == -1) {
    	perror("bind:");
    	return -1;
    }

    int val;
    val = 1;
    ioctl(sock, FIONBIO, &val);

    return sock;
}

int udp_send_init(struct sockaddr_in *p_addr, int port)
{
    int sock;

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock == -1) {
	perror("socket:");
	return -1;
    }

    p_addr->sin_family = AF_INET;
    p_addr->sin_port = htons(port);
    if (inet_aton("127.0.0.1", &p_addr->sin_addr) == 0) {
    	printf("error:inet_aton\n");
    	return -1;
    }

    return sock;
}
