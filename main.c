#include "library.h"
#include "mylib.h"

#define BUF_SIZE 2048
#define UDP_PORT_BRAIN 50000
#define UDP_PORT_HEART 50010

#define BDM_OUTPUT
//#define BDM_BRAIN
//#define BDM_HEART

//出力系
#ifdef BDM_OUTPUT
int main(void)
{
    /* init周りゴニョゴニョ */
    /* all_init(); */

    int sock_brain, sock_heart, addrlen, n;
    struct sockaddr_in addr_brain, addr_heart;
    char buf[BUF_SIZE];

    sock_heart = udp_receive_init(&addr_heart, UDP_PORT_HEART);
    sock_brain = udp_receive_init(&addr_brain, UDP_PORT_BRAIN);
    if (sock_heart == -1 || sock_brain == -1) {
	perror("socket:");
	return 1;
    }

    printf("#test output\n");
    while(1){

	//心拍の処理
	addrlen = sizeof(sock_heart);
	n = recvfrom(sock_heart, buf, sizeof(buf), 0, (struct sockaddr *)&addr_heart, &addrlen);
	if (n < 1) {
	    if (errno == EAGAIN) {
		/* まだ来ない。*/
		printf("MADA KONAI heart\n");
	    } else {
		perror("recv");
		break;
	    }
	} else {
	    int num;
	    printf("received data heart\n");
	    sscanf(buf, "heart %d\n",&num);
	    printf("%d\n", num);
	    /* break; */
	}

	//脳波の処理
	addrlen = sizeof(sock_brain);
	n = recvfrom(sock_brain, buf, sizeof(buf), 0, (struct sockaddr *)&addr_brain, &addrlen);
	if (n < 1) {
	    if (errno == EAGAIN) {
		/* まだ来ない。*/
		printf("MADA KONAI brain\n");
	    } else {
		perror("recv");
		break;
	    }
	} else {
	    int num;
	    printf("received data brain\n");
	    sscanf(buf, "brain %d\n",&num);
	    printf("%d\n", num);
	    /* break; */
	}
	
	/* all_led_status_update(); */
	usleep(1*1000); //1ms
    }
    
    /* free_buff(); */

    return 0;
}
#endif

//脳波系
#ifdef BDM_BRAIN 
int main(void)
{
    /* init周りゴニョゴニョ */
    /* all_init(); */
    
    struct sockaddr_in addr;
    int sock, n, sec=0;
    char buf[BUF_SIZE];
    int meditation, attention;

    sock = udp_send_init(&addr, UDP_PORT_BRAIN);
    if (sock == -1) {
	perror("socket:");
	return 1;
    }
    printf("#test brain\n");

    /* int fd = serial_open(); */

    while(1){

	/* listen_once(fd); */
	/* meditation = get_meditation(); */
	/* attention = get_attention(); */
	n = sprintf(buf, "brain %d\n", sec);
	sendto(sock, buf, n+1, 0, (struct sockaddr *)&addr, sizeof(addr));
	sec++;
	usleep(1*1000); /* 1ms */
    }
    /* serial_close(fd);     */
    /* free_buff(); */

    return 0;
}
#endif

//心拍系
#ifdef BDM_HEART
int main(void)
{
    /* init周りゴニョゴニョ */
    /* all_init(); */

    int sock, n;    
    struct sockaddr_in addr;
    char buf[BUF_SIZE];

    sock = udp_send_init(&addr, UDP_PORT_HEART);
    if (sock == -1) {
	perror("socket:");
	return 1;
    }

    printf("#test heart\n");
    printf("#sec(ms) value\n");
#define SPAN 150
    int i,value[SPAN],sec=0,total=0;
    for (i=0;i<SPAN;i++) value[i]=0;
    while(1){
	
	total -= value[sec%SPAN];
	value[sec%SPAN] = 0;//adc_get_value(0);
	total += value[sec%SPAN];
	/* printf("%5d %d %4.1f ",sec,value[sec%SPAN], total*1.0/SPAN); */
	/* if (value[sec%SPAN] >  total*1.0/SPAN) { */
	/*     printf("O\n"); */
	/* } else { */
	/*     printf("\n"); */
	/* } */
	n = sprintf(buf, "heart %d\n", sec);
	sendto(sock, buf, n+1, 0, (struct sockaddr *)&addr, sizeof(addr));

	sec++;
	usleep(1*1000); /* 1ms */
    }
    
    /* free_buff(); */

    return 0;
}
#endif
