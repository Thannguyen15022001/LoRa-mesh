/*
 * node_layer.c
 *
 *  Created on: Apr 9, 2023
 *      Author: DELL
 */
#include "node_layer.h"

/*----|Sender ID(2)|packet ID(2)|Destination ID(2)|type message ID(2)|(Direction ID)|data()|--*/

RFM95_HandleTypedef Node;
extern SPI_HandleTypeDef hspi1 ;
packetID_HandleTypedef TableID[SIZE_TABLE_ID];
uint8_t tableCNT = 0;
extern uint8_t alarm ;
extern Queue_HandleTypedef queue ;
void initLoRa(){
	Node.Module.NSS.Port = GPIOB;
	Node.Module.NSS.Pin = GPIO_PIN_6;
	Node.Module.Reset.Port = GPIOC;
	Node.Module.Reset.Pin = GPIO_PIN_7;
	Node.Module.SPI = &hspi1;
	Node.Frequency = 923;
	Node.SpredingFactor = SF7;
	Node.BandWidth = BW_125;
	Node.CodingRate = CR_45;
	Node.Power = PW_14DBM;
	Node.Preamble = 8;
	Node.LNA = LNA_G1;
	Node.Timeout = 1023;
	RFM95_Init(&Node);
	RFM95_enableReceive(&Node);
}

void initAddrIntoFlash(){
		  deletePage();
		  saveNodeID();
		  savebroadcastID();
		  savePermitID();
		  saveStartID();
		  saveDataID();

}


void makePacket(char *pbuffer,packetID_HandleTypedef *packetID,uint8_t *data)
{
	pbuffer[0]='\0';
	sprintf(pbuffer,"%d:%d:%d:%d:%s",packetID->Network,packetID->Sender,
			packetID->Packet,packetID->Type_mes,data);
}

void separatePacket(uint8_t *pbuffer,packetID_HandleTypedef *packetID,
		uint8_t *pdata)
{
    char *sPtr = strtok((char*)pbuffer, ":");
    packetID->Network = atoi(sPtr);
    sPtr = strtok(NULL, ":");
    packetID->Sender = atoi(sPtr);
    sPtr = strtok(NULL, ":");
    packetID->Packet = atoi(sPtr);
    sPtr = strtok(NULL, ":");
    packetID->Type_mes = atoi(sPtr);
    sPtr = strtok(NULL, "");
    strcpy((char*)pdata, sPtr);
}

bool alreadyPacket(packetID_HandleTypedef *packetID )
{
	for(uint8_t i = 0 ; i < tableCNT ;  i++)
	{
		if((packetID->Packet==TableID[i].Packet&&packetID->Sender==TableID[i].Sender)
				&&packetID->Network==TableID[i].Network)
		{
			return true;
		}
	}
	return false;
}

void addTableID(packetID_HandleTypedef *packetID)
{
	if(tableCNT >= SIZE_TABLE_ID)
	{
		memset(TableID,0,sizeof(TableID));
		tableCNT=0;
		TableID[tableCNT].Packet=packetID->Packet;
		TableID[tableCNT].Sender=packetID->Sender;
		TableID[tableCNT].Network=packetID->Network;
	}
	else
	{
		TableID[tableCNT].Packet=packetID->Packet;
		TableID[tableCNT].Sender=packetID->Sender;
		TableID[tableCNT].Network=packetID->Network;
	}
	tableCNT++;
}

void nodeStart(){
	char buffer[MAX_SIZE_DATA]={0};
	sprintf(buffer,"%d:%d:%d:%d:%s",getNodeID(),0xFFFF,
			UNDEFINE_NEXTWORK,getStartID(),"Hello World");
	RFM95_Transmit(&Node, (uint8_t *)buffer, strlen(buffer), 5000);
}

bool checkIDNextwork(packetID_HandleTypedef *packetID){
	if(packetID->Type_mes==PERMIT_ID){
//		saveGWayID(packetID->Network);
		return true;
	}
	return false;
}

uint16_t getNodeID(){
	 return flashReadNumber(MEM_NODE_ID);
}
void saveNodeID(){
	flashWriteNumber(MEM_NODE_ID,NODE_ID);
}
uint16_t getbroadcastID(){
	 return flashReadNumber(MEM_BROADCAST_ID);
}
void savebroadcastID(){
	flashWriteNumber(MEM_BROADCAST_ID,BROADCAST_ID);
}
uint16_t getPermitID(){
	 return flashReadNumber(MEM_PERMIT_ID);
}
void savePermitID(){
	flashWriteNumber(MEM_PERMIT_ID,PERMIT_ID);
}
uint16_t getStartID(){
	 return flashReadNumber(MEM_START_ID);
}
void saveStartID(){
	flashWriteNumber(MEM_START_ID,START_ID);
}
uint16_t getDataID(){
	 return flashReadNumber(MEM_DATA_ID);
}
void saveDataID(){
	flashWriteNumber(MEM_DATA_ID,DATA_ID);
}
uint16_t getGWayID(){
	 return flashReadNumber(MEM_GETWAY_ID);
}
void saveGWayID(uint16_t getwayID){
	flashWriteNumber(MEM_GETWAY_ID,getwayID);
}
bool getFlagStart(){
	if(flashReadNumber(MEM_FLAG_START)!=1){
		return false;
	}else{
		return true;
	}
}
void setFlagStart(){
	flashWriteNumber(MEM_FLAG_START,FLAG_START);
}

//void process(){
//	    initLoRa();
//	    if(getFlagStart()!=true){
//	  	  initAddrIntoFlash();
//	  	  nodeStart();
//	  	  uint8_t time[3]={0};
//	  	  getTime(time);
//	  	  time[2]+=5;
//	  	  			  	if(time[2]>=60){
//	  	  			  	time[2]=time[2]%10;
//	  	  			  		time[1]+=1;
//	  	  			  		if(time[1]>=60){
//	  	  			  			time[1]=time[1]%10;
//	  	  			  			time[0]+=1;
//	  	  			  			if(time[0]>=24){
//	  	  			  				time[0]=00;
//	  	  			  			}
//	  	  			  		}
//	  	  			  	}
//	  	  	setAlarm(binaryToBCD(time[0]),binaryToBCD(time[1]),binaryToBCD(time[2]));
//	  	  while(1){
//	  		  uint8_t buffer[MAX_SIZE_DATA]={0};
//	  		  uint8_t data[MAX_SIZE_DATA-10]={0};
//	  		  packetID_HandleTypedef bufferID ;
//	  		  if(isEmpty(&queue)!=true){
//	  			  popQueue(&queue,buffer);
//	  			  separatePacket(buffer,&bufferID,data);
//	  			  if(checkIDNextwork(&bufferID)){
//	  				setFlagStart();
//	  				  break;
//	  			  }
//	  		  }
//	  		  if(alarm==1){
//	  			  	uint8_t time[3]={0};
//	  			  	getTime(time);
//	  			  	time[2]+=5;
//	  				 nodeStart();
//	  			  	if(time[2]>=60){
//	  			  		time[2]=time[2]%10;
//	  			  		time[1]+=1;
//	  			  		if(time[1]>=60){
//	  			  			time[1]=time[1]%10;
//	  			  			time[0]+=1;
//	  			  			if(time[0]>=24){
//	  			  				time[0]=00;
//	  			  			}
//	  			  		}
//	  			  	}
//	  			  		setAlarm(binaryToBCD(time[0]),binaryToBCD(time[1]),binaryToBCD(time[2]));
//	  		//	  setTimeAlarmToConnect();
//	  			  alarm=0;
//	  		  }
//	  	  }
//	    }
//}
