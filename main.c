/*    
*   Author: Ahmed Desoky
*   Date:   28/8/2023
*   Description:    main file for fdisk
    *******************************************************************************
*/
/*==========================================================================INCLUDES===================================================================================*/
#include <stdio.h>
#include <inttypes.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "functions.h"
/*============================================================================MAIN=====================================================================================*/
int main (int argc, char* argv[])
{
    uint8_t read_buffer[Logical_Block_Size];	/*buffer to read from the file, Logical_Block_Size=512*/
	//Printed_data Data_space[4];
    if(argc != 2)
	{
		printf("Please, Provide a hard disk file\n");
		return -1;
	}
	int fd = Open_Drive(argv[1]);	        /*open the Drive file*/
    read_sector(fd,0,read_buffer);
    MBR_Form* MBR =(MBR_Form*)read_buffer;	/*making pointer of type MBR_Form pointng to the read bytes*/
	if (MBR->Magic_num != 0xAA55)                   /*check Partition Table*/
	{
		printf("This drive is not an MBR (Magic = 0x%X)\n",MBR->Magic_num);
		return -4;
	}
    Print_Title();  /*Print Title columns*/
    for (unsigned int i = 0; i < 4; i++)	/*4 stands for max number of primary partitions*/
	{
        if (MBR->Partition_Entries[i].start_sector == 0)    /*if Entry is empty*/
			continue;
        Print_Primary_Partition(MBR->Partition_Entries[i],argv[1],i+1);
        if(MBR->Partition_Entries[i].type == 0x5) /*this is Extended partition*/
        {   
            uint32_t Extended_Start_Sector = MBR->Partition_Entries[i].start_sector;   /*create variable to store the start of the extended partition*/
            EBR_Form* EBR;
            uint32_t sector_offset = Extended_Start_Sector;
            read_sector(fd,sector_offset,read_buffer);
            EBR = (EBR_Form*)read_buffer;
            uint32_t Start_Sector = EBR->EBR_First_Entry.start_sector + Extended_Start_Sector;  /*start sector of the first partition*/
            /*first entry gives start sector realtive to the start of the EBR
            /*second entry gives start sector relative to the start of the extended partition*/
            for(unsigned int k=1; ;k++)
            {
                //printf("Start Sector of sdb5: %u\n",EBR->EBR_First_Entry.start_sector);
                if (EBR->Magic_num != 0xAA55)
	            {   
		            printf("This drive is not an EBR (Magic = 0x%X)\n",EBR->Magic_num);
		            return -5;
	            }
                Print_Extended_Partition(EBR->EBR_First_Entry,Start_Sector,argv[1],k+3);/*printing Extended Partitions*/
                if(EBR->EBR_Second_Entry.start_sector != 0)
                {
                    sector_offset = Extended_Start_Sector + EBR->EBR_Second_Entry.start_sector;
                    read_sector(fd,sector_offset,read_buffer);  /*read in the current buffer*/
                    Start_Sector = EBR->EBR_First_Entry.start_sector + sector_offset;
                }
                else
                {
                    break;
                }
            }
        }
	}
}