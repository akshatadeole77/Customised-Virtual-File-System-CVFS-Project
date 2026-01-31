/////////////////////////////////////////////////////////////////////
//
//      Header File Inclusion
//
/////////////////////////////////////////////////////////////////////

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdbool.h>
#include<string.h>

/////////////////////////////////////////////////////////////////////
//
//      User Defined Macros
//
/////////////////////////////////////////////////////////////////////

//Maximum file size that we allow in the project
#define MAXFILESIZE 50

#define MAXOPENFILE 20

#define MAXINODE 5

#define READ 1
#define WRITE 2
#define EXECUTE 4

#define START 0
#define CURRENT 1
#define END 2

#define EXECUTE_SUCCESS 0

/////////////////////////////////////////////////////////////////////
//
//     User Defined Structures
//
/////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////
//
//     Structure Name:     BootBlock
//     Description :       Holds the information to boot the OS
//
/////////////////////////////////////////////////////////////////////

struct BootBlock
{
    char Information[100];
};

/////////////////////////////////////////////////////////////////////
//
//     Structure Name:     SuperBlock
//     Description :       Holds the information about the file system
//
/////////////////////////////////////////////////////////////////////

struct SuperBlock
{
    int TotalInodes;
    int FreeInodes;
};

/////////////////////////////////////////////////////////////////////
//
//     Structure Name:     Inode
//     Description :       Holds the information about the file
//
/////////////////////////////////////////////////////////////////////

#pragma pack (1)
struct Inode
{
    char  FileName[20];
    int InodeNumber;
    int FileSize;
    int ActualFileSize;
    int ReferenceCount;
    int Permission;
    char *Buffer;
    struct Inode *next;
};

typedef struct Inode INODE;
typedef struct Inode * PINODE;
typedef struct Inode ** PPINODE;

/////////////////////////////////////////////////////////////////////
//
//     Structure Name:     FileTable
//     Description :       Holds the information about the opened file
//
/////////////////////////////////////////////////////////////////////

struct FileTable    //IMPORTANT
{
    int ReadOfSet;
    int WriteOfSet;
    int Mode;
    PINODE ptrinode;
};

typedef FileTable FILETABLE;
typedef FileTable * PFILETABLE;

/////////////////////////////////////////////////////////////////////
//
//     Structure Name:     UAREA
//     Description :       Holds the information about the process file
//
/////////////////////////////////////////////////////////////////////

struct UAREA        //IMPORTANT
{
    char ProcessName[20];
    PFILETABLE UFDT[MAXOPENFILE];
};

/////////////////////////////////////////////////////////////////////
//
//   Global Variables function of the project
//
/////////////////////////////////////////////////////////////////////

BootBlock bootobj;
SuperBlock superobj;
UAREA uareaobj;

PINODE head = NULL;

///////////////////////////////////////////////////////////////////////
//
//      Function Name:      InitialiseUAREA
//      Description:        It is used to initialise UAREA members
//      Author:             Akshata Dhananjay Deole
//      Date:               13/01/2026
//
///////////////////////////////////////////////////////////////////////

void InitialiseUAREA()
{
    strcpy(uareaobj.ProcessName,"Myexe");

    int i = 0;

    for(i = 0; i < MAXOPENFILE; i++)
    {
        uareaobj.UFDT[i] = NULL;
    }
    printf("Infosystems CVFS : UAREA gets initialised successfully\n ");
}

///////////////////////////////////////////////////////////////////////
//
//      Function Name:      InitialiseSuperBlock
//      Description:        It is used to initialise Super block members
//      Author:             Akshata Dhananjay Deole
//      Date:               13/01/2026
//
///////////////////////////////////////////////////////////////////////

void InitialiseSuperBlock()
{
    superobj.TotalInodes = MAXINODE;
    superobj.FreeInodes = MAXINODE;

    printf("Infosystems CVFS : Super block gets initialised successfully\n ");
}

///////////////////////////////////////////////////////////////////////
//
//      Function Name:      CreateDILB
//      Description:        It is used to create LinkedList of inodes
//      Author:             Akshata Dhananjay Deole
//      Date:               13/01/2026
//
///////////////////////////////////////////////////////////////////////

void CreateDILB()
{
    int i = 1;
    PINODE newn = NULL;
    PINODE temp = head;

    for(i = 1; i <= MAXINODE; i++)
    {
        newn = (PINODE)malloc(sizeof(INODE));

        strcpy (newn -> FileName, "\0");
        newn -> InodeNumber = i;
        newn -> FileSize = 0;
        newn -> ActualFileSize = 0;
        newn -> ReferenceCount = 0;
        newn -> Permission = 0;
        newn -> Buffer = NULL;
        newn -> next = NULL;

        if(temp == NULL)    //LL is empty
        {
            head = newn;
            temp = head;
        }
        else        //LL Contains atleast 1 node
        {
            temp -> next = newn;
            temp = temp -> next;
        }
    }

    printf("Infosystems CVFS : DILB created successfully\n");
}

///////////////////////////////////////////////////////////////////////
//
//      Function Name:      StartAuxillaryDataInitilisation
//      Description:        It is used to call all such function which 
//                          are used to initialise auxillary data
//      Author:             Akshata Dhananjay Deole
//      Date:               13/01/2026
//
///////////////////////////////////////////////////////////////////////

void StartAuxillaryDataInitilisation()
{
    strcpy(bootobj.Information,"Booting process of Marvellous CVFS is done");

    printf("%s",bootobj.Information);

    InitialiseSuperBlock();

    CreateDILB();

    InitialiseUAREA();

    printf("Infosystems CVFS : Auxillary data initialised successfully\n");
}


/////////////////////////////////////////////////////////////////////
//
//     Entry Point Function Of The Project
//
/////////////////////////////////////////////////////////////////////


int main()
{
    StartAuxillaryDataInitilisation();



    return 0;
}