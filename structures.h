/*     
*   Author: Ahmed Desoky
*   Date:   28/8/2023
*   Description:    functions of fdisk header file
*/
/*==========================================================================INCLUDES===================================================================================*/
#include <inttypes.h>
/*====================================================================STRUCTURES DATATYPES=============================================================================*/
typedef struct 
{
	uint8_t status;
	uint8_t chs_start[3];
	uint8_t type;
	uint8_t chs_end[3];
	uint32_t start_sector;
	uint32_t num_sectors;
}PartitionEntry;
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------*/
typedef struct __attribute__((packed))  /*This is used to prevent padding*/
{
	uint8_t Bootstrap[446];                 /*bootstrap code if MBR, or just unused area if EBR*/
	PartitionEntry Partition_Entries[4];    /*4 Primary Partitions in case of MBR, first and second entry in case of EBR*/        
	uint16_t Magic_num;
}MBR_Form;
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------*/
typedef struct __attribute__((packed))  /*This is used to prevent padding*/
{
	uint8_t Unused_space[446];  
    PartitionEntry EBR_First_Entry;
	PartitionEntry EBR_Second_Entry;				/*pointer to second logic partition, if exists*/
    PartitionEntry Unused_Entry1;
    PartitionEntry Unused_Entry2;
    uint16_t Magic_num;

}EBR_Form;