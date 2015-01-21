#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define SERIAL_PORT "/dev/rfcomm1" // シリアルインターフェースに対応するデバイスファイル
#define SERIAL_BAUDRATE B57600 // シリアル通信のボーレート
#define BUFSIZE 173 // 受信パケットの最大サイズ

#define SYNC 0xAA // SYNC
#define EXCODE 0x55 // 拡張コード
#define CODE_POOR_SIGNAL 0x02
#define CODE_HEART_RATE 0x03
#define CODE_ATTENTION 0x04
#define CODE_MEDITATION 0x05
#define CODE_SINGLE_RAW 0x06
#define CODE_RAW_MARKER 0x07
#define CODE_MULTI_RAW 0x80
#define CODE_EEG_POWER 0x81
#define CODE_ASIC_EEG_POWER 0x83
#define CODE_RRINTERVAL 0x86

static int meditation = 0;
static int attention = 0;

// シリアル通信を開始する
int  serial_open(void);

// シリアル通信を終了する
void serial_close(int fd);

// パケットを受信するループ
void listen_loop(int fd);

// データペイロードを処理する
void read_payload(uint8_t payload[], int plength);

int get_meditation(void)
{
    return meditation;
}

int get_attention(void)
{
    return attention;
}

void read_payload(uint8_t payload[], int plength)
{
    int head = 0;
    bool output_flag = false;
    while (head < plength){
        int excode_level = 0;
        while (payload[head + excode_level] == EXCODE) excode_level++;
        if (excode_level == 0){
            if (payload[head + excode_level] < CODE_MULTI_RAW){
                switch (payload[head + excode_level]){
                case CODE_POOR_SIGNAL:
                    if (payload[head + 1] == 200){
                        printf("POOR_SIGNAL:electrodes aren't contacting a skin. ");
                    }else{
                        /* printf("POOR_SIGNAL:%d ", payload[head + 1]); */
                    }
                    output_flag = true;
                    break;
                case CODE_HEART_RATE:
                    printf("HEART_RATE:%d ", payload[head + 1]);
                    output_flag = true;
                    break;
                case CODE_ATTENTION:
                    if (payload[head + 1] == 0){
                        printf("ATTENTION:unable to calculate. ");
			attention = -1;
                    }else{
                        /* printf("ATTENTION:%d ", payload[head + 1]); */
			attention = payload[head + 1];
                    }
                    output_flag = true;
                    break;
                case CODE_MEDITATION:
                    if (payload[head + 1] == 0){
                        printf("MEDITATION:unable to calculate. ");
			meditation = -1;
                    }else{
                        /* printf("MEDITATION:%d ", payload[head + 1]); */
			meditation = payload[head + 1];
                    }
                    output_flag = true;
                    break;
                case CODE_SINGLE_RAW:
                    /*
		      printf("8bit_RAW:%d ", payload[head + 1]);
		      output_flag = true;
                    */
                    break;
                case CODE_RAW_MARKER:
                    /*
		      printf("RAW_MARKER:%d ", payload[head + 1]);
		      output_flag = true;
                    */
                    break;
                default:
                    printf("undefined code: %x", payload[head]);
                    output_flag = true;
                    break;
                }
                head += 2;
            }else{
                int vlength = payload[head + 1];
                switch (payload[head]){
                case CODE_MULTI_RAW:
                    /*
		      printf("16bit_RAW:%d ", (int16_t)((payload[head + 2] << 8) | payload[head + 3]));
		      output_flag = true;
                    */
                    break;
                case CODE_EEG_POWER:
                    /*
		      printf("DELTA:%f ", (float)((payload[head + 2] << 24) | (payload[head + 3] << 16) | (payload[head + 4] << 8) | payload[head + 5]));
		      printf("THETA:%f ", (float)((payload[head + 6] << 24) | (payload[head + 7] << 16) | (payload[head + 8] << 8) | payload[head + 9]));
		      printf("LOW_ALPHA:%f ", (float)((payload[head + 10] << 24) | (payload[head + 11] << 16) | (payload[head + 12] << 8) | payload[head + 13]));
		      printf("HIGH_ALPHA:%f ", (float)((payload[head + 14] << 24) | (payload[head + 15] << 16) | (payload[head + 16] << 8) | payload[head + 17]));
		      printf("LOW_BETA:%f ", (float)((payload[head + 18] << 24) | (payload[head + 19] << 16) | (payload[head + 20] << 8) | payload[head + 21]));
		      printf("HIGH_BETA:%f ", (float)((payload[head + 22] << 24) | (payload[head + 23] << 16) | (payload[head + 24] << 8) | payload[head + 25]));
		      printf("LOW_GAMMA:%f ", (float)((payload[head + 26] << 24) | (payload[head + 27] << 16) | (payload[head + 28] << 8) | payload[head + 29]));
		      printf("MIDDLE_GAMMA:%f ", (float)((payload[head + 30] << 24) | (payload[head + 31] << 16) | (payload[head + 32] << 8) | payload[head + 33]));
		      output_flag = true;
                    */
                    break;
                case CODE_ASIC_EEG_POWER:
                    /*
		      printf("DELTA:%d ", (uint32_t)((payload[head + 2] << 16) | (payload[head + 3] << 8) | payload[head + 4]));
		      printf("THETA:%d ", (uint32_t)((payload[head + 5] << 16) | (payload[head + 6] << 8) | payload[head + 7]));
		      printf("LOW_ALPHA:%d ", (uint32_t)((payload[head + 8] << 16) | (payload[head + 9] << 8) | payload[head + 10]));
		      printf("HIGH_ALPHA:%d ", (uint32_t)((payload[head + 11] << 16) | (payload[head + 12] << 8) | payload[head + 13]));
		      printf("LOW_BETA:%d ", (uint32_t)((payload[head + 14] << 16) | (payload[head + 15] << 8) | payload[head + 16]));
		      printf("HIGH_BETA:%d ", (uint32_t)((payload[head + 17] << 16) | (payload[head + 18] << 8) | payload[head + 19]));
		      printf("LOW_GAMMA:%d ", (uint32_t)((payload[head + 20] << 16) | (payload[head + 21] << 8) | payload[head + 22]));
		      printf("MIDDLE_GAMMA:%d ", (uint32_t)((payload[head + 23] << 16) | (payload[head + 24] << 8) | payload[head + 25]));
		      output_flag = true;
                    */
                    break;
                case CODE_RRINTERVAL:
                    printf("RRINTERVAL:%d ", (uint16_t)((payload[head + 2] << 8) | payload[head + 3]));
                    output_flag = true;
                    break;
                default:
                    printf("undefined code: %x", payload[head]);
                    output_flag = true;
                    break;
                }
                head += vlength + 2;
            }
        }else{
            printf("undefined excode level: %d", excode_level);
            output_flag = true;
        }
    }
    if (output_flag) puts("");
}

void listen_loop(int fd){
    uint8_t buf[BUFSIZE];
    int head = 0;
    while (true){ // headが正の場合は、headだけbufの先頭が埋まっている
        int read_size = read(fd, &(buf[head]), BUFSIZE - head) + head; // パケットを受信
        if (read_size == 0) puts("failed to receive packets");
        // printf("read: %d\n", read_size);
        head = 0;
        while (true){
            if (read_size - head < 3){ // 受信したパケットの残りが3バイト未満なら再度受信する
                memmove(buf, &(buf[head]), read_size - head);
                head = read_size - head;
                break;
            }
            /* ヘッダ */
            if (buf[head + 0] != SYNC){ // ヘッダのSYNCが不正な場合
                head++;
                continue;
            }
            if (buf[head + 1] != SYNC){ // ヘッダのSYNCが不正な場合
                head += 2;
                continue;
            }
            int plength = buf[head + 2]; // ペイロード長
            if (plength > 169){ // ペイロード長が不正な場合
                head++;
                continue;
            }
            if (read_size - head < plength + 4){ // パケットの残りの長さが足りない場合
                memmove(buf, &(buf[head]), read_size - head);
                head = read_size - head;
                break;
            }
            /* チェックサム */
            int i;
            uint8_t sum = 0;
            for (i = 0; i < plength; i++) sum += buf[head + 3 + i];
            if ((uint8_t)(~sum) != buf[head + plength + 3]){ // チェックサムの値が不正な場合
                head++;
                continue;
            }
            /* ペイロードの値を利用 */
            read_payload(&(buf[head + 3]), plength);
            /* 次のパケットを読む準備 */
            head += plength + 4;
        }
    }
}

void listen_once(int fd){
    uint8_t buf[BUFSIZE];
    int head = 0;
    // headが正の場合は、headだけbufの先頭が埋まっている
    int read_size = read(fd, &(buf[head]), BUFSIZE - head) + head; // パケットを受信
    if (read_size == 0) puts("failed to receive packets");
    // printf("read: %d\n", read_size);
    head = 0;
    while (true){
	if (read_size - head < 3){ // 受信したパケットの残りが3バイト未満なら再度受信する
	    memmove(buf, &(buf[head]), read_size - head);
	    head = read_size - head;
	    break;
	}
	/* ヘッダ */
	if (buf[head + 0] != SYNC){ // ヘッダのSYNCが不正な場合
	    head++;
	    continue;
	}
	if (buf[head + 1] != SYNC){ // ヘッダのSYNCが不正な場合
	    head += 2;
	    continue;
	}
	int plength = buf[head + 2]; // ペイロード長
	if (plength > 169){ // ペイロード長が不正な場合
	    head++;
	    continue;
	}
	if (read_size - head < plength + 4){ // パケットの残りの長さが足りない場合
	    memmove(buf, &(buf[head]), read_size - head);
	    head = read_size - head;
	    break;
	}
	/* チェックサム */
	int i;
	uint8_t sum = 0;
	for (i = 0; i < plength; i++) sum += buf[head + 3 + i];
	if ((uint8_t)(~sum) != buf[head + plength + 3]){ // チェックサムの値が不正な場合
	    head++;
	    continue;
	}
	/* ペイロードの値を利用 */
	read_payload(&(buf[head + 3]), plength);
	/* 次のパケットを読む準備 */
	head += plength + 4;
    }
}

/* int main(void) */
/* { */
/*     int fd = serial_open(); */
/*     listen_loop(fd); */
/*     serial_close(fd); */
/*     return 0; */
/* } */

int serial_open(void)
{
    /* シリアルポートを開く */
    int fd; // ファイルディスクリプタ
    fd = open(SERIAL_PORT, O_RDWR | O_NOCTTY); // 入出力モード、tty制御なしでシリアルポートを開く
    if (fd == -1){
        perror("open serial port");
        exit(-1);
    }

    /* シリアルポートの設定 */
    struct termios serial_settings; // シリアルポートの設定
    if (tcgetattr(fd, &serial_settings) == -1){ // シリアルポートの現在の設定を取得する
        perror("tcgetattr");
        exit(-1);
    }
    serial_settings.c_cflag = (SERIAL_BAUDRATE | CRTSCTS | CS8 | CLOCAL | CREAD); // 制御設定
    /*
      BAUDRATE: ボーレートの設定
      CRTSCTS : 出力のハードウェアフロー制御
      CS8     : 8n1 (8 ビット，ノンパリティ，ストップビット 1)
      CLOCAL  : ローカル接続，モデム制御なし
      CREAD   : 受信文字(receiving characters)を有効にする．
    */
    serial_settings.c_iflag = (IGNPAR | ICRNL); // 入力設定
    /*
      IGNPAR  : パリティエラーのデータは無視する
      ICRNL   : CR を NL に対応させる(これを行わないと，他のコンピュータで
      CR を入力しても，入力が終りにならない)
      それ以外の設定では，デバイスは raw モードである(他の入力処理は行わない)
    */
    serial_settings.c_oflag = 0; // 出力設定
    /*   Raw モードでの出力 */
    // serial_settings.c_lflag = ICANON; // ローカル設定
    serial_settings.c_lflag = 0; // ローカル設定
    /*
      ICANON  : カノニカル入力を有効にする
      全てのエコーを無効にし，プログラムに対してシグナルは送らせない
    */

    if (tcsetattr(fd, TCSANOW, &serial_settings) == -1){ // 設定を有効にする
        perror("tcsetattr");
        exit(-1);
    }
    return fd;
}

void serial_close(int fd)
{
    /* シリアルポート */
    if (close(fd) == -1){ // シリアルポートを閉じる
        perror("open serial port");
        exit(-1);
    }
}
