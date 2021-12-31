/*
HOW IT WORKS?

We have 3 Buses, each with 12 seats so Total Passengers = Buses x Seats = 3 x 12=36
We have made an array for these 36 passengers, having PassengerIDs randomly.
We have a global array which stores all data (BEFORE BOOKING ALL ZERO)(INDEX 1 TO 12 FOR BUS1) (INDEX 21 TO 32 FOR BUS2) (INDEX 41 TO 52 FOR BUS3) , INDEX 59 STORES MACHINEID(RANDOMLY GENERTED) AND INDEX 60 HAS PASSENGER ID FROM ARRAY
A for loop is run 36 times (once for each passenger), in for loop we have 5 Threads/Machines which are selected randomly by random number generator.
When a thread is selected the function AssignSeats is executed.

In assignSeat function, we get MachineID/SellerID & PassengerID from global array.
We generate random number between 1 & 3 for randomly selected bus.

Once bus is selected, it is checked whether it is filled or not via *SeatNotFound Function. If not filled random seat numbers are generated, then corresponding global array is checked if its filled or not. If not filled(fill it), otherwise repeat it.
It is repeated for each bus

*SEATNOTFOUND FUNCTION

Takes BusID & Global Array.
Counts for corresponding number of occupied seats in respected bus & respective array range.
If count==12, returns filled, else not filled
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include <time.h>
#include <sys/file.h>
#include<sys/types.h>
#include<fcntl.h>
#include<semaphore.h>
#include<unistd.h>//including respective header files

int GenerateRandom(int upper,int lower);//generates random number & returns it
void AssignSeat(int *AllocationData);//allocated seat
int SeatNotFound(int *AllocationData,int BusID);//if no seat is found

sem_t semaphore;//declaring semaphore

int GenerateRandom(int upper,int lower)//generates random numbers,takes upper & lower limit, returns number between limits
{
    int number = (rand()%(upper-lower+1)) + lower;
    return number;
}

int SeatNotFound(int *AllocationData,int BusID)//checks if seat is available or not
{
    int count=0;
    int filled=1;
    int notfilled=0;//declaring & initializing variables

    if(BusID==1)//if BUS1 is to be checked
    {
        for(int i=1;i<=12;i++)//we have stored seat numbers of BUS1 in Global Array, ranging from 1 to 12
        {
            if(AllocationData[i]==1)//if seat is booked, it will have "1" as value
            {
                count++;//adding count
            }
        }
    }
    else if(BusID==2)//if BUS2 is to be checked
    {
        for(int i=21;i<=32;i++)//we have stored seat numbers of BUS2 in Global Array, ranging from 20 to 32
        {
            if(AllocationData[i]==1)//if seat is booked, it will have "1" as value
            {
                count++;//adding count
            }
        }
    }
    else if(BusID==3)//if BUS3 is to be checked
    {
        for(int i=41;i<=52;i++)//we have stored seat numbers of BUS2 in Global Array, ranging from 40 to 52
        {
            if(AllocationData[i]==1)//if seat is booked, it will have "1" as value
            {
                count++;//adding count
            }
        }
    }

    if(count==12)//if count is 12, all seats are occupied for respective bus, returned filled(1)
        return filled;
    else//if not return notfilled(0)
        return notfilled;
}

void AssignSeat(int *AllocationData)//responsible for assigning seats, takes global array
{
    sem_wait(&semaphore);//semaphore wait
    sleep(1);//adds delay of 1 second
    int BusID;
    int SeatID;//declaring & initializing array
    int SellerID=AllocationData[59];
    int PassengerID=AllocationData[60];

    srand (time(NULL));//random sead

    NOTFOUND://label NOTOUND;
    BusID=GenerateRandom(3,1);//getting BusID randomly via random generator

    if(BusID==1 && SeatNotFound(AllocationData,1)==0)//if BusID=1 AND BUS-1 seats not filled
    {
        for(int i=0;i<=100;i++)//looping 100 times to make sure that we don't get repeated seat
        {
            SeatID=GenerateRandom(12,1);//generating random seat number via random number(BUS-1 SEATS 1 TO 12)
            if(AllocationData[SeatID]==0)//if number at INDEXX[SeatID] is zero i.e., seat is empty
            {
                AllocationData[SeatID]=1;//allocating seat i.e., assigning 1
                break;//break statement
            }
            else
                continue;//continue statement
        }
    }
    else if(BusID==1 && SeatNotFound(AllocationData,1)==1)//if BusID=1 AND BUS-1 seats ARE filled
    {
        goto NOTFOUND;//going to label(line-73) if seats are filled
    }
    else if(BusID==2 && SeatNotFound(AllocationData,2)==0)//if BusID=2 AND BUS-2 seats not filled
    {
        for(int i=0;i<=100;i++)//looping 100 times to make sure that we don't get repeated seat
        {
            SeatID=GenerateRandom(32,21);//generating random seat number via random number(BUS-2 SEATS 21 TO 32)
            if(AllocationData[SeatID]==0)//if number at INDEXX[SeatID] is zero i.e., seat is empty
            {
                AllocationData[SeatID]=1;//allocating seat i.e., assigning 1
                break;//break statement
            }
            else
                continue;//continue statement
        }
        SeatID=SeatID-20;//getting orignal seat number/ID
    }
    else if(BusID==2 && SeatNotFound(AllocationData,2)==1)//if BusID=2 AND BUS-2 seats ARE filled
    {
        goto NOTFOUND;//going to label(line-73) if seats are filled
    }
    else if(BusID==3 && SeatNotFound(AllocationData,3)==0)//if BusID=3 AND BUS-3 seats not filled
    {
        for(int i=0;i<=100;i++)//looping 100 times to make sure that we don't get repeated seat
        {
            SeatID=GenerateRandom(52,41);//generating random seat number via random number(BUS-3 SEATS 41 TO 42)
            if(AllocationData[SeatID]==0)//if number at INDEXX[SeatID] is zero i.e., seat is empty
            {
                AllocationData[SeatID]=1;//allocating seat i.e., assigning 1
                break;//break statement
            }
            else
                continue;//continue statement
        }
        SeatID=SeatID-40;//getting orignal seat number/ID
    }
    else if(BusID==3 && SeatNotFound(AllocationData,3)==1)//if BusID=3 AND BUS-3 seats ARE filled
    {
        goto NOTFOUND;//going to label(line-73) if seats are filled
    }

    printf("---%d---------%d----------%d-------%d\n",SellerID,BusID,PassengerID,SeatID);//printing SellerID--BusID--PassengerID--SeatID
    sem_post(&semaphore);//semaphore post
}

int main()//main function
{
    srand(time(0));//random sead

    //array for passenger IDs-->3 Buses x 12 Seats===36 Seats
    int PassengerIDs[37]={0,5,12,25,21,9,4,16,2,1,34,28,27,20,19,6,7,36,33,24,17,26,30,10,22,13,35,14,8,23,18,31,15,29,11,32,3};

    int *AllocationData;  //pointer for dynamic memory location
    AllocationData= (int*) malloc((60)* sizeof(int));  //initializing memory

    for(int i=0;i <=60; i++)//looping 60 times, assigning 0 to global array
    {
        AllocationData[i] = 0;//assigning zero
    }

    printf("SellerID---BusID---PassengerID---SeatID\n");//printing message

    //we have 3 buses each with 12 seats so ---> 36 passengers at max.
    for(int i=1;i<=36;i++)//looping 36 times for 36 passengers
    {
        int MachineID=GenerateRandom(5,1);//5 ticketing machines--> selecting randomly by random number generator(range 1 to 5)

        if(MachineID==1)//if machine 1 is selected
        {
            sem_init(&semaphore,0,1);//initializing semaphore
            AllocationData[59]=1;//passing machineID at allocationData[59]
            AllocationData[60]=PassengerIDs[i];//passing passengerID at allocationData[60]
            pthread_t Machine1;//creating Machine 1 Thread
            pthread_create(&Machine1,NULL,AssignSeat,AllocationData);//passing args
            pthread_join(Machine1,NULL);
            sem_destroy(&semaphore);//destroying semaphore
        }
        else if(MachineID==2)//if machine 2 is selected
        {
            sem_init(&semaphore,0,1);//initializing semaphore
            AllocationData[59]=2;//passing machineID at allocationData[59]
            AllocationData[60]=PassengerIDs[i];//passing passengerID at allocationData[60]
            pthread_t Machine2;//creating Machine 2 Thread
            pthread_create(&Machine2,NULL,AssignSeat,AllocationData);//passing args
            pthread_join(Machine2,NULL);
            sem_destroy(&semaphore);//destroying semaphore
        }
        else if(MachineID==3)//if machine 3 is selected
        {
            sem_init(&semaphore,0,1);//initializing semaphore
            AllocationData[59]=3;//passing machineID at allocationData[59]
            AllocationData[60]=PassengerIDs[i];//passing passengerID at allocationData[60]
            pthread_t Machine3;//creating Machine 3 Thread
            pthread_create(&Machine3,NULL,AssignSeat,AllocationData);//passing args
            pthread_join(Machine3,NULL);
            sem_destroy(&semaphore);//destroying semaphore
        }
        else if(MachineID==4)//if machine 4 is selected
        {
            sem_init(&semaphore,0,1);//initializing semaphore
            AllocationData[59]=4;//passing machineID at allocationData[59]
            AllocationData[60]=PassengerIDs[i];//passing passengerID at allocationData[60]
            pthread_t Machine4;//creating Machine 4 Thread
            pthread_create(&Machine4,NULL,AssignSeat,AllocationData);//passing args
            pthread_join(Machine4,NULL);
            sem_destroy(&semaphore);//destroying semaphore
        }
        else//if machine 5 is selected
        {
            sem_init(&semaphore,0,1);//initializing semaphore
            AllocationData[59]=5;//passing machineID at allocationData[59]
            AllocationData[60]=PassengerIDs[i];//passing passengerID at allocationData[60]
            pthread_t Machine5;//creating Machine 5 Thread
            pthread_create(&Machine5,NULL,AssignSeat,AllocationData);//passing args
            pthread_join(Machine5,NULL);
            sem_destroy(&semaphore);//destroying semaphore
        }
    }//end of for loop
    return 0;//returning zero
}

