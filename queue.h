/**
 * @file   queue.h
 * @brief  a simple queue data structural
 * @author Shin (wangq1998@outlook.com)
 * @date   2024-06-05 17:06
 *
 * @version    1.0
 * @copyright  Copyright (c) 2024  家里蹲能力有限公司
 */

#ifndef __QUEUE_H
#define __QUEUE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "cpu32.h"

#define QUEUE_PRINTF printf

#define QUEUE_MALLOC malloc
#define QUEUE_FREE free

typedef struct __tagQUEUE
{
    U8 *u8pQBuff;       //point to queue
    U32 u32QBuffSize;   //the size of queue
    U32 u32QHeader;     //Data Output
    U32 u32QTail;       //Data Input
} QUEUE_TypeDef;

typedef enum
{
    QUEUE_FALSE = 0,
    QUEUE_TRUE = 1,
} QUEUE_BOOL;

/**
 * @brief  Initialize a queue
 * @param  queue   
 * @date   2024-06-05 17:06
 */
void QUEUE_Init(QUEUE_TypeDef *queue);

/**
 * @brief  DeInit, free the used RAM
 * @param  queue   
 * @date   2024-06-05 17:06
 */
void QUEUE_Deinit(QUEUE_TypeDef *queue);

/**
 * @brief  Clear the data received
 * @param  queue   
 * @date   2024-06-05 17:06
 */
void QUEUE_Clear(QUEUE_TypeDef *queue);

/**
 * @brief  Get the size of queue
 * @param  queue   
 * @return U32     
 * @date   2024-06-05 17:06
 */
U32 QUEUE_GetSize(QUEUE_TypeDef *queue);

/**
 * @brief  Change the size of a exist queue
 * @param  queue   
 * @param  size    
 * @date   2024-06-05 17:06
 */
void QUEUE_ReSize(QUEUE_TypeDef *queue, U32 size);

/**
 * @brief  Get the length of received data
 * @param  queue   
 * @return U32     
 * @date   2024-06-05 17:06
 */
U32 QUEUE_GetQueueLen(QUEUE_TypeDef *queue);

/**
 * @brief  is the queue empty 
 * @param  queue   
 * @return QUEUE_BOOL
 * @date   2024-06-05 17:06
 */
QUEUE_BOOL QUEUE_IS_EMPTY(QUEUE_TypeDef *queue);

/**
 * @brief  store the data
 * @param  queue   
 * @param  data    
 * @param  size    data's size
 * @return U32     the size of data stored actually
 * @date   2024-06-05 17:06
 */
U32 QUEUE_PutBuff(QUEUE_TypeDef *queue, U8 *data, U32 size);

/**
 * @brief  get data from the queue
 * @param  queue   
 * @param  data    
 * @param  size    
 * @return U32     
 * @date   2024-06-05 17:06
 */
U32 QUEUE_GetBuff(QUEUE_TypeDef *queue, U8 *data, U32 size);

#ifdef __cplusplus
}
#endif

#endif
