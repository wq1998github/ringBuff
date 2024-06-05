#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"


void QUEUE_Init(QUEUE_TypeDef *queue)
{
    queue->u8pQBuff = (U8 *)QUEUE_MALLOC(queue->u32QBuffSize);
    QUEUE_Clear(queue);
}

void QUEUE_Deinit(QUEUE_TypeDef *queue)
{
    QUEUE_FREE(queue->u8pQBuff);
    queue->u8pQBuff = (void *)0;
}

void QUEUE_Clear(QUEUE_TypeDef *queue)
{
    memset(queue->u8pQBuff, 0x00, queue->u32QBuffSize);

    queue->u32QHeader = 0;
    queue->u32QTail = 0;
}

U32 QUEUE_GetSize(QUEUE_TypeDef *queue)
{
    return queue->u32QBuffSize;
}

void QUEUE_ReSize(QUEUE_TypeDef *queue, U32 size)
{
    if (QUEUE_GetSize(queue) != size)
    {
        QUEUE_Deinit(queue);

        queue->u32QBuffSize = size;
        QUEUE_Init(queue);
    }
    else
    {
        QUEUE_Clear(queue);
    }
}

U32 QUEUE_GetQueueLen(QUEUE_TypeDef *queue)
{
    int queueLen = queue->u32QTail - queue->u32QHeader;

    if (queue->u32QTail >= queue->u32QHeader)
    {
        return queueLen;
    }

    return queue->u32QBuffSize + queueLen;
}

QUEUE_BOOL QUEUE_IS_EMPTY(QUEUE_TypeDef *queue)
{
    QUEUE_BOOL ret = QUEUE_FALSE;

    if (queue->u32QHeader == queue->u32QTail)
    {
        ret = QUEUE_TRUE;
    }

    return ret;
}

static QUEUE_BOOL QUEUE_PutByte(QUEUE_TypeDef *queue, U8 data)
{
    U32 newTailIndex = (queue->u32QTail + 1) % queue->u32QBuffSize;
    U32 oldTailIndex = queue->u32QTail;

    if (newTailIndex == queue->u32QHeader)
    {
        QUEUE_PRINTF(">>>>>>>>>>>> queue is overflow <<<<<<<<<<<<\r\n");
        return QUEUE_FALSE; // overflow
    }

    queue->u8pQBuff[oldTailIndex] = data;
    queue->u32QTail = newTailIndex;

    return QUEUE_TRUE;
}

static U32 QUEUE_GetByte(QUEUE_TypeDef *queue, U8 *data)
{
    U32 newHeaderIndex = (queue->u32QHeader + 1) % queue->u32QBuffSize;
    U32 oldHeaderIndex = queue->u32QHeader;

    if (QUEUE_IS_EMPTY(queue) == QUEUE_TRUE)
    {
        QUEUE_PRINTF(">>>>>>>>>>>> queue is empty <<<<<<<<<<<<\r\n");
        return 0;
    }

    *data = queue->u8pQBuff[oldHeaderIndex];
    queue->u32QHeader = newHeaderIndex;

    return 1;
}

U32 QUEUE_PutBuff(QUEUE_TypeDef *queue, U8 *data, U32 size)
{
    int index = 0;
    QUEUE_BOOL ret = QUEUE_FALSE;

    while (1)
    {
        ret = QUEUE_PutByte(queue, data[index]);

        if (ret == QUEUE_FALSE)
        {
            break;
        }
        else
        {
            index++;
        }

        if (index == size)
        {
            break;
        }
    }

    return index;
}

U32 QUEUE_GetBuff(QUEUE_TypeDef *queue, U8 *data, U32 size)
{
    int index = 0;
    int ret = 0;

    while (1)
    {
        ret = QUEUE_GetByte(queue, &data[index]);

        if (ret == 0)
        {
            break;
        }
        else
        {
            index++;
        }

        if (index == size)
        {
            break;
        }
    }

    return index;
}

#if 0
static void QUEUE_TEST()
{
    QUEUE_TypeDef queue = {0};
    U8 data[256] = {0};
    U32 ret = 0;

    queue.u32QBuffSize = 10;

    QUEUE_Init(&queue);
    QUEUE_PRINTF("size: %d is empty: %d\r\n\r\n", QUEUE_GetSize(&queue), QUEUE_IS_EMPTY(&queue));

    QUEUE_PutBuff(&queue, "Hello|world!", strlen("Hello|world!"));
    QUEUE_PRINTF("length of queue: %d is empty: %d\r\n\r\n", QUEUE_GetQueueLen(&queue), QUEUE_IS_EMPTY(&queue));

    ret = QUEUE_GetBuff(&queue, data, 6);
    QUEUE_PRINTF("output:%s output len: %d remain_len: %d\r\n\r\n", data, ret, QUEUE_GetQueueLen(&queue));

    memset(data, 0x00, sizeof(data));
    ret = QUEUE_GetBuff(&queue, data, 9);
    QUEUE_PRINTF("output:%s output len: %d remain_len: %d\r\n\r\n", data, ret, QUEUE_GetQueueLen(&queue));

    QUEUE_ReSize(&queue, 2048);
    QUEUE_PRINTF("size: %d is empty: %d\r\n\r\n", QUEUE_GetSize(&queue), QUEUE_IS_EMPTY(&queue));

    QUEUE_PutBuff(&queue, "Hello|world!", strlen("Hello|world!"));
    QUEUE_PRINTF("length of queue: %d is empty: %d\r\n\r\n", QUEUE_GetQueueLen(&queue), QUEUE_IS_EMPTY(&queue));

    ret = QUEUE_GetBuff(&queue, data, 6);
    QUEUE_PRINTF("output:%s output len: %d remain_len: %d\r\n\r\n", data, ret, QUEUE_GetQueueLen(&queue));

    memset(data, 0x00, sizeof(data));
    ret = QUEUE_GetBuff(&queue, data, 9);
    QUEUE_PRINTF("output:%s output len: %d remain_len: %d\r\n\r\n", data, ret, QUEUE_GetQueueLen(&queue));
}

int main()
{
    QUEUE_TEST();
    return 0;
}
#endif
