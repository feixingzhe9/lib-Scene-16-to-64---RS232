﻿/***************************Copyright BestFu 2014-05-14*************************
文	件：	cmdProcess.h
说	明：	FIFO指令处理函数头文件
编	译：	Keil uVision4 V4.54.0.0
版	本：	v1.0
编	写：	Unarty
日	期：	2013-11-01
修  改:     暂无
*******************************************************************************/
#ifndef __CMDPROCESS_H
#define __CMDPROCESS_H

#include "FIFO.h"
#include "UnitCfg.h"
#include "command.h"

#define FIFOBUFSZE     (0x400) // 1KB 
#define ADDFIFOBUFSZ   (0x80)  // 128B

typedef u8 (*ProcessFunction)(u8 *buf, u8 len, u8 level);
typedef u32 (*FIFOGetFun)(u8 *cmdBuf, FIFO_t *fifo);

typedef struct
{
	u8 len; 	//sendBuf处理数据长度
	u8 flag;	//处理标志
	u8 con;		//处理条件
	u8 mean;	//条件描述
	u8 type;  //消息类型 yanhuan adding 2015/12/30
	u8 level;	//消息等级
	u8 data[255];	//要处理的实际数据内容
	ProcessFunction fun;
	FIFOGetFun		Data_Get;	//队列数据获取函数
}Process_t;

typedef enum
{
	NORMAL,		//正常模式
	MANY_P,		//多次处理
}CMDcon_t;

typedef enum
{
	COMMON,//一般消息
	SHORT,//短帧消息
}CMDtype_t ;

extern FIFO_t rcv433fifo;
extern FIFO_t send433fifo;
extern Process_t rcv_433;
extern Process_t send_433;
#if (COMMUNICATION_SHORT_FRAME == 1)
	extern FIFO_t rcv433_shortfifo;
	extern FIFO_t send433_shortfifo;
	extern Process_t rcv_433short;
	extern Process_t send_433short;
#endif
void FIFOInit(void);

void ProcessSend_Fun(ProcessFunction sendFun);
void Process_FIFOData(FIFO_t *fifo, Process_t *prc);
void Process_FIFODataShort(FIFO_t *fifo, Process_t *prc); //短帧处理 yanhuan adding 2015/12/28
u8 Msg_Change(u8 *data, u8 len, u8 level);
MsgResult_t Msg_Execute(CMDPara_t *para);

#endif
/**************************Copyright BestFu 2014-05-14*************************/
