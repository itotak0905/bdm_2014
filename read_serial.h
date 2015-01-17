#ifndef MY_READ_SERIAL_H
#define MY_READ_SERIAL_H

// シリアル通信を開始する
int  serial_open(void);

// シリアル通信を終了する
void serial_close(int fd);

// パケットを受信するループ
void listen_loop(int fd);


#endif
