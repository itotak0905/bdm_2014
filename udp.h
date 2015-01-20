#ifndef MY_UDP_H
#define MY_UDP_H

//送信側のinit関数
//返り値はsock、ミスったら−1
int udp_send_init(struct sockaddr_in *p_addr, int port);

//受信側のinit関数
//返り値はsock、ミスったら−1
int udp_receive_init(struct sockaddr_in *p_addr, int port);

#endif
