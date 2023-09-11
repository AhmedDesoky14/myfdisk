/*     
*   Author: Ahmed Desoky
*   Date:   28/8/2023
*   Description:    functions of fdisk header file
*/
/*==========================================================================INCLUDES===================================================================================*/
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include"structures.h"
/*==========================================================================DEFINES====================================================================================*/
#define Logical_Block_Size	512
/*=====================================================================FUNCTIONS PROTOTYPES============================================================================*/
/*Function description in .c file*/
void Print_Title(void);
void Print_Primary_Partition(PartitionEntry Partition,char* argv1,unsigned int count);
void Print_Extended_Partition(PartitionEntry Partition,uint32_t sector_offset,char* argv1,unsigned int count);
int Open_Drive(char* argv1);
void read_sector(int fd,uint32_t sector_offset,uint8_t* read_buffer);
float get_Size(uint32_t start_sector,uint32_t end_sector,uint32_t *size_unit);