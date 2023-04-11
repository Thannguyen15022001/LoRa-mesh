/*
 * rfm95.h
 *
 *  Created on: Feb 19, 2023
 *      Author: Nguyễn Viết Thân
 *       Gmail: thannguyen1502@gmail.com
 */

#ifndef INC_LORA_H_
#define INC_LORA_H_


#include "stdint.h"
#include "stm32l0xx_hal.h"
#include "stdbool.h"
#include "queue.h"
#include "flash.h"


#define TIMEOUT								500
#define BIT_WRITE							0x80U
#define ADD_RESET_RX						0x00U
#define ADD_RESET_TX						0x80U

/*--------------------------------- Address of registers LoRa Mode -------------------------------------------------------------------*/
#define LR_REG_FIFO							0x00U
/*Common Register Settings*/
#define LR_REG_OPMODE						0x01U
#define LR_REG_FRFMSB						0x06U
#define LR_REG_FRFMID						0x07U
#define LR_REG_FRFLSB						0x08U
/*Registers for RF blocks*/
#define LR_REG_PACONFIG						0x09U
#define LR_REG_PARAMP						0x0AU
#define LR_REG_OCP							0x0BU
#define LR_REG_LNA							0x0CU
/*Lora page registers*/
#define LR_REG_FIFOADDRPTR					0x0DU
#define LR_REG_FIFOTXBASEADDR				0x0EU
#define LR_REG_FIFORXBASEADDR				0x0FU
#define LR_REG_FIFORXCURRENTADDR			0x10U
#define LR_REG_IRQFLAGSMASK					0x11U
#define LR_REG_IRQFLAGS						0x12U
#define LR_REG_RXNBBNYTES		 			0x13U
#define LR_REG_RXHEADERCNTVALUEMSB			0x14U
#define	LR_REG_RXHEADERCNTVALUELSB			0x15U
#define	LR_REG_RXPACKETCNTVALUEMSB			0x16U
#define	LR_REG_RXPACKETCNTVALUELSB			0x17U
#define	LR_REG_MODEMSTAT					0x18U
#define	LR_REG_PKTSNRVALUE					0x19U
#define	LR_REG_PKTRSSIVALUE					0x1AU
#define	LR_REG_RSSIVALUE					0x1BU
#define	LR_REG_HOPCHANNEL					0x1CU
#define LR_REG_MODEMCONFIG1 				0x1DU
#define	LR_REG_MODEMCONFIG2 				0x1EU
#define	LR_REG_SYMBTIMEOUTLSB				0x1FU
#define	LR_REG_PREAMBLEMSB					0x20U
#define	LR_REG_PREAMBLELSB 					0x21U
#define	LR_REG_PAYLOADLENGTH 				0x22U
#define	LR_REG_MAXPAYLOADLENGTH 			0x23U
#define	LR_REG_HOPPERIOD					0x24U
#define	LR_REG_FIFORXBYTEADDR 				0x25U
#define	LR_REG_MODEMCONFIG3					0x26U
#define	LR_REG_FEIMSB						0x28U
#define	LR_REG_FEIMID						0x29U
#define	LR_REG_FEILSB						0x2AU
#define	LR_REG_RSSIWIDEBAND					0x2CU
#define	LR_REG_IFFREQ1						0x2FU
#define	LR_REG_IFFREQ2 						0x30U
#define	LR_REG_DETECTOPTIMIZE 				0x31U
#define	LR_REG_INVERTIQ				`		0x33U
#define	LR_REG_HIGHBWOPTIMZE				0x36U
#define	LR_REG_DETECTIONTHRESHOLD 			0x37U
#define	LR_REG_SYNCWORD						0x39U
#define	LR_REG_HIGHBWOPTIMIZE				0x3AU
#define	LR_REG_INVERTIQ2					0x3BU
#define	LR_REG_DIOMAPPING1					0x40U
#define	LR_REG_DIOMAPPING2 					0x41U
#define	LR_REG_VERSION						0x42U
#define	LR_REG_TCXO							0x4BU
#define	LR_REG_PADAC						0x4DU
#define	LR_REG_FORMERTEMP					0x5BU
#define	LR_REG_AGCREF						0x61U
#define	LR_REG_AGCTHRESH1					0x62U
#define	LR_REG_AGCTHRESH2					0x63U
#define	LR_REG_AGCTHRESH3					0x64U
#define	LR_REG_PLL							0x70U
/*Device modes*/
#define  RESET_MODE							0xF8U
#define  SLEEP_MODE							0x00U
#define  STDBY_MODE							0x01U
#define  FSTX_MODE							0x02U
#define  TX_MODE							0x03U
#define  RSRX_MODE							0x04U
#define  RXCONTINUOUS_MODE					0x05U
#define  RXSINGLE_MODE						0x06U
#define	 CAD_MODE							0x07U
#define  LORA_MODE							0x80U
/*Spreading Factor*/
#define RESET_SF							0x0FU
#define SF6	 								0x06U
#define SF7	 								0x07U
#define SF8	 								0x08U
#define SF9	 								0x09U
#define SF10	 							0x0AU
#define SF11	 							0x0BU
#define SF12								0x0CU
/*Signal bandwidth*/
#define RESET_BANDWIDTH						0x0FU
#define BW_7D8								0x00U	/*	7.8 kHz		*/
#define BW_10D4								0x01U	/* 	10.4 kHz	*/
#define BW_15D6								0x02U	/*	15.6 kHz	*/
#define BW_20D8								0x03U   /*	20.8kHz		*/
#define BW_31D25							0x04U	/*	31.25 kHz	*/
#define BW_41D7								0x05U	/*	41.7 kHz	*/
#define BW_62D5								0x06U	/*	62.5 kHz	*/
#define BW_125								0x07U	/*	125 kHz		*/
#define BW_250								0x08U	/*	250 kHz		*/
#define BW_500								0x09U	/*	500 kHz		*/
/*Error coding rate*/
#define RESET_CR							0xF1U
#define CR_45								0x01U		/* 4/5 */
#define CR_46								0x02U		/* 4/6 */
#define CR_47								0x03U		/* 4/7 */
#define CR_48								0x04U		/* 4/8 */
/*Power Tx*/
#define PW_RFO		    					0x70U
#define PW_PABOOST    						0x80U
#define PW_17DBM							0x0FU
#define PW_16DBM							0x0EU
#define PW_15DBM							0x0DU
#define PW_14DBM							0x0CU
#define PW_13DBM							0x0BU
#define PW_12DBM							0x0AU
#define PW_11DBM							0x09U
#define PW_10DBM							0x08U
#define PW_9DBM								0x07U
#define PW_8DBM								0x06U
#define PW_7DBM								0x05U
#define PW_6DBM								0x04U
#define PW_5DBM								0x03U
#define PW_4DBM								0x02U
#define PW_3DBM								0x01U
#define PW_2DBM								0x00U
/* LNA Set*/
#define BOOST_ON							0x03U

#define LNA_G1								0x01U
#define LNA_G2								0x02U
#define LNA_G3								0x03U
#define LNA_G4								0x04U
#define LNA_G5								0x05U
#define LNA_G6								0x06U

#define TX_FLAGS							0x08U
#define RX_FLAGS							0x40U

#define RESET_BITCRC						0xFBU
#define EN_BITCRC							0x04U

#define RSSI_ULF							525
#define RSSI_UHF							860
#define RSSI_OFFSETLF						164
#define RSSI_OFFSETHF						157

#define EN_IMPLICITHEADERMODE				0x01U
#define EN_EXPLICITHEADERMODE				0xFEU

typedef enum
{
	RFM95_ERROR, RFM95_OK, RFM95_TIMEOUT,CAD_DETEC,NONE_CAD,
} RFM95_StatusTypedef;

typedef struct
{
	GPIO_TypeDef *Port;
	uint16_t Pin;
} RFM95_Pin;

typedef struct
{
	/*Hardware Configure*/
	RFM95_Pin Reset;			//Pin RST
//	RFM95_Pin DIO0;				//pin WAKEUP
	RFM95_Pin NSS;
	void *SPI;
} RFM95_PinTypedef;

typedef struct
{
	RFM95_PinTypedef Module;
	uint16_t Frequency;              //Mhz
	uint8_t SpredingFactor;
	uint8_t BandWidth;
	uint8_t CodingRate;
	uint8_t Power;
	uint16_t Preamble;
	uint8_t LNA;					//độ nhạy -> G1 là lớn nhất
	uint16_t Timeout;
} RFM95_HandleTypedef;

void RFM95_reset(RFM95_HandleTypedef *RFM_Init);
RFM95_StatusTypedef RFM95_enableReceive(RFM95_HandleTypedef *RFM_Init);
void RFM95_mappingDIO0(RFM95_HandleTypedef *RFM_Init);
void RFM95_setNSS(RFM95_HandleTypedef *RFM_Init, GPIO_PinState PinState);
RFM95_StatusTypedef RFM95_writeBurstRes(RFM95_HandleTypedef *RFM_Init,
		uint8_t addr, uint8_t *pData, uint8_t size);
RFM95_StatusTypedef RFM95_readBurstRes(RFM95_HandleTypedef *RFM_Init,
		uint8_t addr, uint8_t *pBuffer, uint8_t size);
RFM95_StatusTypedef RFM95_writeByteRes(RFM95_HandleTypedef *RFM_Init,
		uint8_t addr, uint8_t data);
RFM95_StatusTypedef RFM95_readByteRes(RFM95_HandleTypedef *RFM_Init,
		uint8_t addr, uint8_t *pBuffer);
RFM95_StatusTypedef RFM95_setPreamble(RFM95_HandleTypedef *RFM_Init);
RFM95_StatusTypedef RFM95_setCodingRate(RFM95_HandleTypedef *RFM_Init);
RFM95_StatusTypedef RFM95_setFrequency(RFM95_HandleTypedef *RFM_Init);
RFM95_StatusTypedef RFM95_setLNA(RFM95_HandleTypedef *RFM_Init);
RFM95_StatusTypedef RFM95_setPower(RFM95_HandleTypedef *RFM_Init,
		uint8_t powerMode);
RFM95_StatusTypedef RFM95_setBandWidth(RFM95_HandleTypedef *RFM_Init);
RFM95_StatusTypedef RFM95_setSpredingFactor(RFM95_HandleTypedef *RFM_Init);
RFM95_StatusTypedef RFM95_setTimeout(RFM95_HandleTypedef *RFM_Init);
RFM95_StatusTypedef RFM95_receiveFromEXTI(RFM95_HandleTypedef *RFM_Init, uint8_t *buffer, uint8_t size);
RFM95_StatusTypedef RFM95_Receive(RFM95_HandleTypedef *RFM_Init, uint8_t *buffer, uint8_t size);
RFM95_StatusTypedef RFM95_Transmit(RFM95_HandleTypedef *RFM_Init, uint8_t *buffer,
		uint8_t size, uint16_t timeout);
RFM95_StatusTypedef RFM95_checkLDRO(RFM95_HandleTypedef *RFM_Init);
RFM95_StatusTypedef RFM95_resetBaseAddr(RFM95_HandleTypedef *RFM_Init);
RFM95_StatusTypedef RFM95_setMode(RFM95_HandleTypedef *RFM_Init, uint8_t Mode);
RFM95_StatusTypedef RFM95_setExplicitHeaderMode(RFM95_HandleTypedef *RFM_Init);
RFM95_StatusTypedef RFM95_enableCRC(RFM95_HandleTypedef *RFM_Init);
RFM95_StatusTypedef RFM95_Init(RFM95_HandleTypedef *RFM_Init);
RFM95_StatusTypedef RFM95_setImplicitHeaderMode(RFM95_HandleTypedef *RFM_Init);
RFM95_StatusTypedef RFM95_disableCRC(RFM95_HandleTypedef *RFM_Init);
RFM95_StatusTypedef RFM95_enableAGC(RFM95_HandleTypedef *RFM_Init);
RFM95_StatusTypedef RFM95_detectionCAD(RFM95_HandleTypedef *RFM_Init);
RFM95_StatusTypedef RFM95_statusCAD(RFM95_HandleTypedef *RFM_Init);
int16_t RFM95_getRSSI(RFM95_HandleTypedef *RFM_Init);
#endif /* INC_LORA_H_ */
