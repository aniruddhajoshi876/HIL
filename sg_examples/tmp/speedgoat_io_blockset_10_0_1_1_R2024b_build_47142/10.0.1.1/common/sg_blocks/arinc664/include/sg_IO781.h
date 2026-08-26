#ifndef SG_IO781_H
#define SG_IO781_H

#define SG_BLOCK_TYPE_IO781_RECEIVE 7811
#define SG_BLOCK_TYPE_IO781_SEND    7812

extern A664EndSystemHandle 	esHandle[10];

//uint32_t            	deviceCount;

typedef struct sg_IO781_RX_T
{
    uint8_t *readData;
    A664RxComUdpHandle *rxComUdpHandles;
} sg_IO781_rx_t;


#endif