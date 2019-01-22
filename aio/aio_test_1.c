

#include <linux/aio_abi.h>
#define _GNU_SOURCE
#include <inttypes.h>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <pthread.h>

#define TX_ALL  16
#define RX_ALL  16
#define RAW_DATA_TOT_SIZE   1*256*16*16*2    //100 frame
#define BK_SIZE  192*1
#define GAP_SIZE  64*1
#define SECTOR_SIZE (BK_SIZE+GAP_SIZE)
#define ZONE_SIZE SECTOR_SIZE*RX_ALL*TX_ALL //1 frame
#define FRAME_SIZE  ZONE_SIZE


#define SUBT    1
#define MAINT   1
struct wf6_struct {
    int32_t fd;
    off_t   start;
    off_t   fil_pos;
    size_t  blk_size;
    size_t  gap_size;
    int32_t blk_num;
    int32_t big_gap_cnt;
    size_t  big_gap_size;
};

int32_t data_ok = 0;
uint8_t *raw_data;
struct wf6_struct *sub_thread_data_info;

void *create_raw_data(int32_t tx_num)
{
    if(tx_num<1 || tx_num>16) {
        printf("para err %d\n",tx_num);
    }

    uint8_t *buf = malloc(RAW_DATA_TOT_SIZE);
    if(buf==NULL) {
        perror("init raw data fail:");
        exit(-1);
    }

    uint8_t val = 1;
    memset(buf, 0, RAW_DATA_TOT_SIZE);

    //construct data
    for(int k=0;k<2;k++){
        for(int i=0; i<RX_ALL; i++) {//rx
            for(int j=0; j<tx_num; j++) {//tx
                memset(buf+k*ZONE_SIZE+i*TX_ALL*SECTOR_SIZE+j*SECTOR_SIZE, val++, BK_SIZE);//blk
            }
        }
    }
#if 0
    //test
#if 0
    for(int i=0; i<512; i++) {
        printf("%x=%x\n", *(uint8_t*)(buf+i*256), *(uint8_t*)(buf+i*256+192));
    }
#endif
    int32_t fd = open("./data", O_CREAT|O_WRONLY, S_IRWXU|S_IRWXG|S_IROTH);
    if(fd < 0) {
        perror("open fd fail:");
        return NULL;
    }
    int ret= write(fd, buf, RAW_DATA_TOT_SIZE);
    if(ret < RAW_DATA_TOT_SIZE) {
        perror("wr fd fail:");
        exit(-1);
    }
    close(fd);
#endif
    return buf;
}

void write_data(void *ptr)
{
    printf("enter child\n");
    if(ptr == NULL) {
        printf("inval arg\n");
        return ;
    }
    struct wf6_struct *temp =(struct wf6_struct*)ptr;
    uint32_t bk_num = temp->blk_num;
    struct io_event *events;
    struct iocb **iocbpp ;
    struct iocb *cbs;
    aio_context_t ctx;
    uint8_t *buf;
    int32_t errcode;
    int32_t fd;
    off_t pos;
    int32_t tx_num;

    fd = temp->fd;
    printf("fd11 %d\n",fd);

    events = malloc(sizeof(struct io_event)*bk_num);
    iocbpp = malloc(sizeof(struct iocb *)*bk_num);
    cbs = malloc(sizeof(struct iocb)*bk_num);
    if(events == NULL || iocbpp == NULL || cbs == NULL){
        perror("X");
        return;
    }

    printf("bk %d %d\n",bk_num,temp->fd);
    memset(&ctx, 0, sizeof(ctx));
    errcode = io_setup(bk_num, &ctx);
    if (errcode != 0) {
        printf("io_setup error: :%d:%s\n", errcode, strerror(-errcode));
        return;
    }

    pos = 0;
    int32_t bg_cnt;
    off_t buf_pos=temp->start;
    tx_num = TX_ALL-temp->big_gap_cnt;
    while(1) {
        data_ok = 1;
        while(data_ok == 1)
            ;
        printf("ffff\n");
        bg_cnt = TX_ALL - temp->big_gap_cnt;
        buf_pos = temp->start;

        memset(iocbpp, 0, 4*bk_num);
        bk_num = temp->blk_num;

        printf("X%d\n",bk_num);
        for(int i=0; i<bk_num; i++) {
            cbs[i].aio_fildes         = fd;
            cbs[i].aio_data           = buf_pos;
            if(bg_cnt == 0) {
                cbs[i].aio_data       += temp->big_gap_size;
                bg_cnt = TX_ALL - temp->big_gap_cnt;
                buf_pos +=temp->big_gap_size ;
            }

            cbs[i].aio_buf            = cbs[i].aio_data;
//            printf("2=%d= %x addr %x - val %x %d %x\n",i, buf_pos, cbs[i].aio_data, *(uint8_t*)(cbs[i].aio_data), bg_cnt,temp->big_gap_size);
            cbs[i].aio_lio_opcode     = IOCB_CMD_PWRITE;
            cbs[i].aio_nbytes         = BK_SIZE;
            cbs[i].aio_offset         = pos+i*BK_SIZE;
            iocbpp[i]                = &cbs[i];
            buf_pos += SECTOR_SIZE;
            bg_cnt--;
        }

        int n = io_submit(ctx, bk_num, iocbpp);
        printf("==io_submit==: %d:%s\n", n, strerror(-n));
        perror("ff");
        n = io_getevents(ctx, bk_num, bk_num, events, NULL);
        printf("io_getevents: %d:%s\n", n, strerror(-n));

        pos += bk_num*BK_SIZE;
        memset(temp, 0, sizeof(struct wf6_struct));
    }
    io_destroy(ctx);

    syncfs(fd);
    close(fd);
    printf("done");
}

int main(int argc, char *argv[])
{
    struct wf6_struct wf6_temp;
    int32_t tx_num = 2;
    int32_t fd1,fd2;
    uint32_t count =0;

    int32_t times = 0;
    if(argc >1){
        tx_num = atoi(argv[1]);
        printf("%d\n",tx_num);
    }
    else{
        return -1;
    }
#if SUBT == 1
    fd2 = open("./dir2", O_CREAT|O_WRONLY, S_IRWXU|S_IRWXG|S_IROTH);
    if(fd2 < 0) {
        perror("open fd2 fail:");
        return -1;
    }
#endif

#if MAINT == 1
    fd1 = open("./dir1", O_CREAT|O_WRONLY, S_IRWXU|S_IRWXG|S_IROTH);
    if(fd1 < 0) {
        perror("open fd1 fail:");
        return -2;
    }
    printf("fd1 %d\n",fd1);
#endif
    printf("tx %d\n",tx_num);
    raw_data = create_raw_data(tx_num);
redo:
#if SUBT == 1
    //for subthread
    sub_thread_data_info = malloc(sizeof(struct wf6_struct));
    if(sub_thread_data_info == NULL) {
        perror("malloc sub thread data fail:");
        return -3;
    }
    sub_thread_data_info->fd        = fd2;
    sub_thread_data_info->start     = raw_data + count*FRAME_SIZE + FRAME_SIZE/2;
    sub_thread_data_info->blk_size  = BK_SIZE;
    sub_thread_data_info->gap_size  = GAP_SIZE;
    sub_thread_data_info->blk_num   = RX_ALL*tx_num/2;
    sub_thread_data_info->big_gap_cnt   = TX_ALL - tx_num;
    sub_thread_data_info->big_gap_size  = (TX_ALL-tx_num)*(SECTOR_SIZE);

    pthread_t pc1;
    pthread_create(&pc1, NULL, &write_data, sub_thread_data_info);
#endif

#if MAINT == 1
    //for main thread
    wf6_temp.fd = fd1;
    wf6_temp.start = raw_data + count*FRAME_SIZE;
    wf6_temp.blk_size = BK_SIZE;
    wf6_temp.gap_size = GAP_SIZE;
    wf6_temp.blk_num = RX_ALL*tx_num/2;
    wf6_temp.big_gap_cnt = TX_ALL - tx_num;
    wf6_temp.big_gap_size = wf6_temp.big_gap_cnt*(SECTOR_SIZE);
    off_t buf_pos;
    off_t pos =0;
    int32_t bg_cnt;
    int32_t bk_num = wf6_temp.blk_num;

    struct iocb **iocbpp ;
    struct iocb *cbs;
    struct io_event *events;

    events = malloc(sizeof(struct io_event)*bk_num);
    iocbpp = malloc(sizeof(struct iocb *)*bk_num);
    cbs = malloc(sizeof(struct iocb)*bk_num);
    if(events == NULL || iocbpp == NULL || cbs == NULL){
        perror("y");
        return;
    }

    aio_context_t ctx1;
    memset(&ctx1, 0, sizeof(ctx1));
    int err = io_setup(bk_num, &ctx1);
    if (err!= 0) {
        printf("io_setup error: :%d:%s\n", err, strerror(-err));
        return -1;
    }
#endif
    //seperate one frame into two part
    off_t wrote_off;
    wrote_off = 0;
    while(1) {
#if SUBT == 1
        while(data_ok != 1);
        printf("prepare sub\n");
        //update for subthread
        sub_thread_data_info->start = raw_data + count*FRAME_SIZE + FRAME_SIZE/2;
        sub_thread_data_info->fd = fd2;
        sub_thread_data_info->blk_size = BK_SIZE;
        sub_thread_data_info->gap_size = GAP_SIZE;
        sub_thread_data_info->blk_num = RX_ALL*tx_num/2;
        sub_thread_data_info->big_gap_cnt = TX_ALL - tx_num;
        sub_thread_data_info->big_gap_size = (TX_ALL-tx_num)*(SECTOR_SIZE);
        //command sub thread starting writing
        data_ok = 2;
#endif

#if MAINT == 1
        printf("prepare main\n");
        //construct struct for main thread
        wf6_temp.fd = fd1;
        wf6_temp.start = raw_data + count*FRAME_SIZE;
        wf6_temp.blk_size = BK_SIZE;
        wf6_temp.gap_size = GAP_SIZE;
        wf6_temp.blk_num = RX_ALL*tx_num/2;
        wf6_temp.big_gap_cnt = TX_ALL - tx_num;
        wf6_temp.big_gap_size = (TX_ALL - tx_num)*(SECTOR_SIZE);

        buf_pos = wf6_temp.start;
        bg_cnt = TX_ALL - wf6_temp.big_gap_cnt;
        memset(iocbpp, 0, 4*bk_num);
        bk_num = wf6_temp.blk_num;
        printf("bk %d %d %d\n",bk_num,wf6_temp.fd,bg_cnt);
        for(int i=0; i<bk_num; i++){
            printf("i%d\n",i);
            cbs[i].aio_fildes         = wf6_temp.fd;
            cbs[i].aio_data           = buf_pos;
            if(bg_cnt == 0) {
                cbs[i].aio_data       += wf6_temp.big_gap_size;
                bg_cnt                 = TX_ALL - wf6_temp.big_gap_cnt;
                printf("bg %d\n",bg_cnt);
                buf_pos               += wf6_temp.big_gap_size ;
            }
            cbs[i].aio_buf            = cbs[i].aio_data;
            cbs[i].aio_lio_opcode     = IOCB_CMD_PWRITE;
            cbs[i].aio_nbytes         = BK_SIZE;
            cbs[i].aio_offset         = pos+i*BK_SIZE;
            iocbpp[i]                 = &cbs[i];
            buf_pos += SECTOR_SIZE;
            bg_cnt--;
            printf("1=%d= %x addr %x - val %x %d %x\n",i, buf_pos, cbs[i].aio_data, *(uint8_t*)(cbs[i].aio_data), bg_cnt,wf6_temp.big_gap_size);
//            printf("buf %x of %x nb %d start %x\n",cbs[i].aio_buf, cbs[i].aio_offset, cbs[i].aio_nbytes,wf6_temp.start);
        }
        printf("DD %d\n",bk_num);
        int n = io_submit(ctx1, bk_num, iocbpp);
        if(n != bk_num){
            perror("ios");
            printf("n %d\n",n);
            goto end;
        }
        n = io_getevents(ctx1, bk_num, bk_num, events, NULL);
        if(n != bk_num){
            perror("iog :");
            goto end;
        }
        pos+=bk_num*BK_SIZE;
#endif
        while(data_ok == 2);
        printf("cnt %d\n",count++);
        if( count ==2){
            count = 0;
        }
        wrote_off += BK_SIZE*bk_num;
        if(wrote_off > 4*192*10){
            goto end;
        }

    }
end:
#if SUBT == 1
    pthread_cancel(pc1);
    pthread_join(pc1, NULL);
#endif
#if MAINT == 1
    io_destroy(ctx1);
#endif
    free(raw_data);
    if(times <= 3){
        times++;
        printf("redo %d\n",times);
        goto redo;
    }
    return 0;
}

