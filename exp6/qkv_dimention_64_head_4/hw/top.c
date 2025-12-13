#include "hw_defines.h"

void top(uint64_t query_addr, uint64_t key_addr, uint64_t value_addr, uint64_t output_addr) {

    // Define Device MMRs
    volatile uint8_t *qkvFlags = (uint8_t *)QKV;
    volatile uint8_t *DmaFlags = (uint8_t *)(DMA_Flags);
    volatile uint64_t *DmaRdAddr = (uint64_t *)(DMA_RdAddr);
    volatile uint64_t *DmaWrAddr = (uint64_t *)(DMA_WrAddr);
    volatile uint32_t *DmaCopyLen = (uint32_t *)(DMA_CopyLen);

    // Transfer Input Matrices
    // Transfer M1
    *DmaRdAddr = query_addr;
    *DmaWrAddr = query;
    *DmaCopyLen = qkv_size ;
    *DmaFlags = DEV_INIT;
    // Poll DMA for finish
    //printf("1\n");
    while ((*DmaFlags & DEV_INTR) != DEV_INTR)
        ;
    //printf("2\n");
    // Transfer M2
    *DmaRdAddr = key_addr;
    *DmaWrAddr = key;
    *DmaCopyLen = qkv_size;
    *DmaFlags = DEV_INIT;
    // Poll DMA for finish
    while ((*DmaFlags & DEV_INTR) != DEV_INTR)
        ;
    //printf("3\n");
// Transfer M2
    *DmaRdAddr = value_addr;
    *DmaWrAddr = value;
    *DmaCopyLen = qkv_size;
    *DmaFlags = DEV_INIT;
    // Poll DMA for finish
    while ((*DmaFlags & DEV_INTR) != DEV_INTR)
        ;
    //printf("4\n");


    // Start the accelerated function
    *qkvFlags = DEV_INIT;
    //printf("5\n");
    // Poll function for finish
    while ((*qkvFlags & DEV_INTR) != DEV_INTR)
        ;

    //printf("6\n");
    // Transfer M3
    *DmaRdAddr = output;
    *DmaWrAddr = output_addr;
    *DmaCopyLen = qkv_size;
    *DmaFlags = DEV_INIT;
    // Poll DMA for finish
    while ((*DmaFlags & DEV_INTR) != DEV_INTR)
        ;
    //printf("7\n");
    return;
}
