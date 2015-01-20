#ifndef MY_READ_SERIAL_H
#define MY_READ_SERIAL_H

// シリアル通信を開始する
int  serial_open(void);

// シリアル通信を終了する
void serial_close(int fd);

// パケットを受信するループ
void listen_loop(int fd);

// パケットを受信する(1回)
void listen_once(int fd);

// 集中度を取得
int get_attention(void);

// 瞑想度を取得
int get_meditation(void);

#endif
