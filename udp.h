#ifndef MY_UDP_H
#define MY_UDP_H

int udp_send_init(struct sockaddr_in *p_addr);
int udp_receive_init(struct sockaddr_in *p_addr);

#endif
