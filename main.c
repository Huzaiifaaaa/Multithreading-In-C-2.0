#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include <time.h>
#include <sys/file.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>   //including respective header files

int GenerateRandom(int upper,int lower);//generates random number & returns it
void AssignSeat(int *AllocationData);
int SeatNotFound(int *AllocationData,int BusID);

int GenerateRandom(int upper,int lower)
{
    int number = (rand()%(upper-lower+1)) + lower;
    return number;
}

int SeatNotFound(int *AllocationData,int BusID)
{
    int count=0;
    int true=1;
    int false=0;

    if(BusID==1)
    {
        for(int i=0;i<12;i++)
        {
            if(AllocationData[i]==1)
            {
                count++;
            }
        }
    }
    else if(BusID==2)
    {
        for(int i=20;i<=32;i++)
        {
            if(AllocationData[i]==1)
            {
                count++;
            }
        }
    }
    else if(BusID==3)
    {
        for(int i=40;i<=52;i++)
        {
            if(AllocationData[i]==1)
            {
                count++;
            }
        }
    }

    if(count==12)
        return true;
    else
        return false;
}

void AssignSeat(int *AllocationData)
{
    int BusID;
    int SeatID;
    int SellerID=AllocationData[98];
    int PassengerID=AllocationData[99];

    AllocationData[98]=0;
    AllocationData[99]=0;

    srand (time(NULL));

    NOTFOUND:
    BusID=GenerateRandom(3,1);

    if(BusID==1 && SeatNotFound(AllocationData,1)==0)
    {
        for(int i=0;i<=100;i++)
        {
            SeatID=GenerateRandom(12,1);
            if(AllocationData[SeatID]==0)
            {
                AllocationData[SeatID]=1;
                break;
            }
            else
                continue;
        }
    }
    else if(BusID==1 && SeatNotFound(AllocationData,1)==1)
    {
        goto NOTFOUND;
    }
    else if(BusID==2 && SeatNotFound(AllocationData,2)==0)
    {
        for(int i=0;i<=100;i++)
        {
            SeatID=GenerateRandom(32,21);
            if(AllocationData[SeatID]==0)
            {
                AllocationData[SeatID]=1;
                break;
            }
            else
                continue;
        }
        SeatID=SeatID-20;
    }
    else if(BusID==2 && SeatNotFound(AllocationData,2)==1)
    {
        goto NOTFOUND;
    }
    else if(BusID==3 && SeatNotFound(AllocationData,3)==0)
    {
        for(int i=0;i<=100;i++)
        {
            SeatID=GenerateRandom(52,41);
            if(AllocationData[SeatID]==0)
            {
                AllocationData[SeatID]=1;
                break;
            }
            else
                continue;
        }
        SeatID=SeatID-40;
    }
    else if(BusID==3 && SeatNotFound(AllocationData,3)==1)
    {
        goto NOTFOUND;
    }

    printf("---%d---------%d----------%d-------%d\n",SellerID,BusID,PassengerID,SeatID);
}

int main()//main function
{
    srand(time(0));

    int PassengerIDs[37]={0,5,12,25,21,9,4,16,2,1,34,28,27,20,19,6,7,36,33,24,17,26,30,10,22,13,35,14,8,23,18,31,15,29,11,32,3};

    int *AllocationData;  //pointer for dynamic memory location
    AllocationData= (int*) malloc((99)* sizeof(int));  //initializing memory

    for(int i=0;i < 99; i++)
    {
        AllocationData[i] = 0;
    }

    printf("SellerID---BusID---PassengerID---SeatID\n");

    //we have 3 buses each with 12 seats so ---> 36 passengers at max.
    for(int i=1;i<=36;i++)
    {
        int MachineID=GenerateRandom(5,1);

        if(MachineID==1)
        {
            AllocationData[98]=1;
            AllocationData[99]=PassengerIDs[i];//i;
            pthread_t Machine1;
            pthread_create(&Machine1,NULL,AssignSeat,AllocationData);
            pthread_join(Machine1,NULL);
        }
        else if(MachineID==2)
        {
            AllocationData[98]=2;
            AllocationData[99]=PassengerIDs[i];//i;
            pthread_t Machine2;
            pthread_create(&Machine2,NULL,AssignSeat,AllocationData);
            pthread_join(Machine2,NULL);
        }
        else if(MachineID==3)
        {
            AllocationData[98]=3;
            AllocationData[99]=PassengerIDs[i];//i;
            pthread_t Machine3;
            pthread_create(&Machine3,NULL,AssignSeat,AllocationData);
            pthread_join(Machine3,NULL);
        }
        else if(MachineID==4)
        {
            AllocationData[98]=4;
            AllocationData[99]=PassengerIDs[i];//i;
            pthread_t Machine4;
            pthread_create(&Machine4,NULL,AssignSeat,AllocationData);
            pthread_join(Machine4,NULL);
        }
        else
        {
            AllocationData[98]=5;
            AllocationData[99]=PassengerIDs[i];//i;
            pthread_t Machine5;
            pthread_create(&Machine5,NULL,AssignSeat,AllocationData);
            pthread_join(Machine5,NULL);
        }
    }
    return 0;
}

