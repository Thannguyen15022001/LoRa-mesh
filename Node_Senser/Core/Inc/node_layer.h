/*
 * node_layer.h
 *
 *  Created on: Apr 9, 2023
 *      Author: DELL
 */

#ifndef INC_NODE_LAYER_H_
#define INC_NODE_LAYER_H_

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "rtc.h"
#include <math.h>
#include "lora.h"
#include "queue.h"
#include "flash.h"

#define UNDEFINE_NEXTWORK			0xFFFF
#define NODE_ID						0xA125U
#define BROADCAST_ID				0xD222U
#define PERMIT_ID					0xD111U
#define START_ID					0xD444U
#define DATA_ID						0xD333U
#define FLAG_START					0x01U
#define SIZE_TABLE_ID				5
#define MAX_SIZE_DATA				255
/*Adds save ID of node and getway*/
#define MEM_NODE_ID					0x08003F80UL			// node ID
#define MEM_GETWAY_ID				0x08003F84UL			// getway ID

/*Adds save ID of message type*/
#define MEM_BROADCAST_ID			0x08003F88UL
#define MEM_PERMIT_ID				0x08003F8CUL			// GW connect node
#define MEM_START_ID				0x08003F90UL			// using Node connect to getway
#define MEM_DATA_ID					0x08003F94UL			// using sent data
#define MEM_FLAG_START				0x08003F98UL



typedef struct {
	uint16_t Network;			// ID network
	uint16_t Sender;			// ID of sender
	uint16_t Packet;			// ID of packet
	uint16_t Type_mes;			// ID of message type
}packetID_HandleTypedef;


void initAddrIntoFlash();
void initLoRa();
uint16_t getNodeID();
void saveNodeID();
uint16_t getbroadcastID();
void savebroadcastID();
uint16_t getPermitID();
void savePermitID();
uint16_t getStartID();
void saveStartID();
uint16_t getDataID();
void saveDataID();
uint16_t getGWayID();
void saveGWayID(uint16_t getwayID);
bool getFlagStart();
void setFlagStart();
void nodeStart();
bool checkIDNextwork(packetID_HandleTypedef *packetID);
void separatePacket(uint8_t *pbuffer,packetID_HandleTypedef *packetID,
		uint8_t *pdata);
void process();

#endif /* INC_NODE_LAYER_H_ */
