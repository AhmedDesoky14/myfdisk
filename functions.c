/*     
*   Author: Ahmed Desoky
*   Date:   28/8/2023
*   Description:    functions of fdisk source file
*/
/*==========================================================================INCLUDES===================================================================================*/
#include "functions.h"
/*=====================================================================FUNCTIONS DEFINITION============================================================================*/
/***********************************************************************************************************************************************
    Function Description:   This is the main function in builtin.c used to operate all builtin commands
    [INPUTS]:   NONE
    [OUTPUTS]:  integer, indicating which command is performed
    NOTES:  This function uses all functions of builtin_backend files
************************************************************************************************************************************************/
void Print_Title(void)
{
    printf("Device\t\tBoot\tStart\t\tEnd\t\tSectors\t\tSize\t\t\tId\n");
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------*/
void Print_Primary_Partition(PartitionEntry Partition,char* argv1,unsigned int count)
{
    uint32_t Start_Sector = Partition.start_sector;
    uint32_t End_Sector = Partition.num_sectors+Partition.start_sector-1;
    uint32_t     Size_unit = 0;
    float Size = get_Size(Start_Sector,End_Sector,&Size_unit);
    printf("%s%d\t%d\t%u\t\t%u\t\t%u\t\t%f",argv1,count+1,
    (Partition.status== 0x80)? 1:0,
    Partition.start_sector,End_Sector,Partition.num_sectors,Size);
    switch(Size_unit)
    {
        case 0:
            printf("Bytes\t\t");
            break;
        case 1:
            printf("KB\t\t");
            break;
        case 2:
            printf("MB\t\t");
            break;
        case 3:
            printf("GB\t\t");
            break;
        case 4:
            printf("TB\t\t");
            break;
    }
    printf("%x\n",Partition.type);
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------*/
void Print_Extended_Partition(PartitionEntry Partition,uint32_t sector_offset,char* argv1,unsigned int count)
{   
    uint32_t Start_Sector = sector_offset;
    uint32_t End_Sector = Start_Sector+Partition.num_sectors-1;
    uint32_t Size_unit = 0;
    float Size = get_Size(Start_Sector,End_Sector,&Size_unit);     
    printf("%s%d\t%d\t%u\t\t%u\t\t%u\t\t%f",argv1,count+1,    /*passed k+3*/
    (Partition.status== 0x80)? 1:0,
    Start_Sector,End_Sector,Partition.num_sectors,Size);
    switch(Size_unit)
    {
        case 0:
            printf("Bytes\t\t");
            break;
        case 1:
            printf("KB\t\t");
            break;
        case 2:
            printf("MB\t\t");
            break;
        case 3:
            printf("GB\t\t");
            break;
        case 4:
            printf("TB\t\t");
            break;
    }
    printf("%x\n",Partition.type);
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------*/
int Open_Drive(char* argv1)
{
    int fd = open(argv1, O_RDONLY);	/*open the file given*/
	if (fd < 0)
	{
		printf("Could not open file: %s\n", argv1);	/*Error for opening the file*/
		return -2;
	}
    return fd;
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------*/
void read_sector(int fd,uint32_t sector_offset,uint8_t* read_buffer)
{
    int check_read;
    uint64_t offset = sector_offset*Logical_Block_Size; /*Logical_Block_Size=512*/
    if(sector_offset == 0)
    {
        check_read = read(fd,read_buffer,Logical_Block_Size);	
    }
    else
    {
        uint64_t pos = lseek(fd,offset,SEEK_SET);
        check_read = read(fd,read_buffer,Logical_Block_Size);
    }
    if (check_read != 512)
	{
		printf("Could not read %d byte\n",Logical_Block_Size);
	}
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------*/
float get_Size(uint32_t start_sector,uint32_t end_sector,uint32_t *size_unit)
{
    uint32_t sectors = end_sector - start_sector + 1;
    float size = sectors * Logical_Block_Size;
    uint32_t siz_uni = 0;
    while(size > 1024)
    {
        size = size / 1024;
        siz_uni++;    /*1=KB,2=MB,3=GB,4=TB*/
    }
    *(size_unit) = siz_uni;
    return size;
}