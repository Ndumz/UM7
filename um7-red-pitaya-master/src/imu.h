#ifndef UM7_IMU_H
#define UM7_IMU_H

#include <stdint.h>
#include <stdio.h>
#include <unistd.h>		
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "/home/ndumiso/Documents/EEE4022S/Code/um7-red-pitaya-master/libserialport/libserialport.h"

#include "colour.h"
#include "binary.h"

#define UART_PORT  				"/dev/ttyUSB0"
#define UART_BAUD_RATE			115200
#define UART_BITS				8
#define UART_STOPBITS			1
#define UART_BYTE_BUFFER		4096

#define MAX_PACKET_DATA			50
#define TX_PACKET_ATTEMPTS 		100

#define CREG_COM_SETTINGS 		0x00
#define CREG_COM_RATES1 		0x01
#define CREG_COM_RATES2 		0x02
#define CREG_COM_RATES3 		0x03
#define CREG_COM_RATES4 		0x04
#define CREG_COM_RATES5 		0x05
#define CREG_COM_RATES6 		0x06
#define CREG_COM_RATES7 		0x07
#define CREG_MISC_SETTINGS		0x08

#define CREG_HOME_NORTH			0x09
#define CREG_HOME_EAST			0x0A
#define CREG_HOME_UP			0x0B

#define DREG_HEALTH 			0x55

#define DREG_TEMPERATURE 		0x5F

#define DREG_ALL_PROC  			0x61

#define DREG_GYRO_PROC_X  		0x61
#define DREG_GYRO_PROC_Y  		0x62
#define DREG_GYRO_PROC_Z  		0x63
#define DREG_GYRO_PROC_TIME		0x64

#define DREG_ACCEL_PROC_X		0x65
#define DREG_ACCEL_PROC_Y		0x66
#define DREG_ACCEL_PROC_Z		0x67
#define DREG_ACCEL_PROC_TIME	0x67

#define DREG_MAG_PROC_X 		0x69
#define DREG_MAG_PROC_Y 		0x6A
#define DREG_MAG_PROC_Z 		0x6B
#define DREG_MAG_PROC_TIME 		0x6C

#define DREG_QUAT_AB			0x6D
#define DREG_QUAT_CD			0x6E
#define DREG_QUAT_TIME			0x6F

#define DREG_EULER_PHI_THETA	0x70
#define DREG_EULER_PSI			0x71
#define DREG_EULER_PHI_THETA_DOT 0x72
#define DREG_EULER_PSI_DOT		0x73
#define DREG_EULER_TIME			0x74

#define DREG_POSITION_N 		0x75
#define DREG_POSITION_E 		0x76
#define DREG_POSITION_UP 		0x77
#define DREG_POSITION_TIME 		0x78

#define DREG_VELOCITY_N			0x79
#define DREG_VELOCITY_E			0x7A
#define DREG_VELOCITY_UP		0x7B
#define DREG_VELOCITY_TIME		0x7C

#define DREG_GPS_LATITUDE		0x7D
#define DREG_GPS_LONGITUDE		0x7E
#define DREG_GPS_ALTITUDE		0x7F
#define DREG_GPS_COURSE			0x80
#define DREG_GPS_SPEED			0x81
#define DREG_GPS_TIME			0x82

#define GET_FW_REVISION			0xAA
#define FLASH_COMMIT			0xAB
#define RESET_TO_FACTORY		0xAC
#define ZERO_GYROS				0xAD
#define SET_HOME_POSITION		0xAE
#define SET_MAG_REFERENCE		0xB0
#define RESET_EKF				0xB3

#define DREG_GPS_LATITUDE		0x7D
#define DREG_GPS_LONGITUDE	    0x7E
#define DREG_GPS_ALTITUDE		0x7F
#define DREG_GPS_COURSE			0x80
#define DREG_GPS_SPEED			0x81
#define DREG_GPS_TIME			0x82

#define PT_HAS_DATA 			0b10000000
#define PT_IS_BATCH 			0b01000000
#define PT_BL_3		 			0b00100000
#define PT_BL_2 				0b00010000
#define PT_BL_1					0b00001000
#define PT_BL_0 				0b00000100
#define PT_CF	 				0b00000001
#define PT_READ	 				0b00000000

typedef struct 
{
  uint8_t is_valid;
  uint8_t address;
  uint8_t packet_type;
  uint8_t data[MAX_PACKET_DATA];
  uint8_t n_data_bytes;
  uint16_t checksum; 
} packet;

typedef struct 
{
  uint8_t sats_used;
  uint8_t sats_view;
  uint8_t mag_norm;
  uint8_t acc_norm; 
  uint8_t acc_fail;
  uint8_t gyro_fail;
  uint8_t mag_fail;
  uint8_t gps_fail;
  uint8_t uart_fail;
  uint16_t hdop;  
} heartbeat;

void initIMU(int is_debug_mode, int is_reset);

int rxPacket(int address, int attempts);
int txPacket(packet* tx_packet);

int writeCommand(int command);
void printRegister(uint8_t address);
int writeRegister(uint8_t address, uint8_t n_data_bytes, uint8_t *data);

void printConfiguration(void);

void getHeartbeat(void);
void printHeartbeat(void);
void printHome(void);

uint8_t parseUART(int address, uint8_t* rx_data, uint8_t rx_length);

void initUART(void);
void dnitUART(void);
int getUART(void);
void list_ports(void);


#endif
