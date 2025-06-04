
/*
Create a Record Management System

1. Create a structure having following data
Use bit fields wherever applicable
struct SLT Parameters
Status : Enable/Disable
Name : Max length 19
Station Type : Admin, Guest, Assistant
Message Wait Flag : 1 bit
VMS Message Wait Flag : 1 bit
VMS Tone Length: 8 bits int (0-255)
2. Define ENUMS to represent these fields, say FILED_A, FIELD_B etc. (replace A and B with field name)
3. Max records = 10
*/

typedef enum {FAIL=0, SUCCESS=1} Bool;

typedef enum {ADMIN, GUEST, ASSISTANT} StationType;
typedef enum {DISABLE, ENABLE} Status;

typedef struct time{
    unsigned int date:5;
    char month[4];
    unsigned int year:11;
    unsigned int hour:5;
    unsigned int minute:6;
    unsigned int second:6;
} time;

typedef struct record{
    unsigned int status:1;
    char name[19];
    StationType stationType:2;
    unsigned int msgWaitFlag:1;
    unsigned int vmsMsgWaitFlag:1;
    unsigned int vmsToneLen:8;
} record;

typedef enum {STATUS, NAME, STATIONTYPE, MSGWAITFLAG, VMAMSGWAITFLAG, VMSTONELEN} field;

#define MAX_RECORD 10

/*
Input: record size and record count
Process: allocate memory of (record size * count)
Output: Return this allocated memory
Handle failure
*/
void* memoryAlloc(int, int);

/*
Input: memory pointer to be deallocate
Process: Deallocate memory
*/
void memoryDealloc(void *);

/*
6. Master Database
All the records should be stored in dataBase.
memory to dataBase should be allocated dynamically.
*/

/*
Input: dataBase pointer and count
Process: allocate memory of (record size * count)
Output: 0 or (count * record size)
Handle failure
*/
int allocDB();

/*
Input: dataBase pointer
Process: deallocate memory database pointer
Output: 0 (failed) or 1 (success)
Handle failure
*/
Bool deallocDB();

/*
Write different functions to set and get the values of each individual data.
Do proper validation of data in set/get functions as applicable to the concern data.
*/

Bool setRecord(record*, field, void*);
Bool getRecord(record*, field, void*);

Bool setStatus(record*, int);
Bool setName(record*, char*);
Bool setStationType(record*, StationType);
Bool setMsgWaitFlag(record*, int);
Bool setVmsMsgWaitFlag(record*, int);
Bool setVmsToneLen(record*, int);

/*
Input: File Name
Process:
The first data of the file will be the last updated date and time of the File.
                  Whenever some data is added to file or deleted from file, this date and time must be changed.
For date and time, take a structure representing Date, Month, Year, Hour, Minute, and Second; and write this structure in the start of the file.
If date is already written, it should be overwritten.
MAX records = 10
Output: 0 (failed) or 1 (success)
*/
Bool createFile(char *, int, FILE**);

/* 
Write Date and Time:
Input: Pointer to Date and Time structure
Process:
Write current data and time in the file.
Whenever a record is added, updated or deleted, this date and time should be updated.
Date and time in the file should be updated only on success of operation.
Output: 0 (failed) or 1 (success)
*/
Bool writeDateTime(FILE *, struct time*);

/*
Get current date and time
*/
Bool getDateTime(time*);

/*
Input: record pointer
Process: Set all zeros to memory located pointed to by the record pointer.
Output: 0 (failed) or 1 (success)
*/
Bool defaultRecord(record*);

/*
Input: record pointer, record index i
Process: write this record in file at its place or index. Use fseek here.
i'th index data will be written in file after (i-1)th data and before (i+1)th data in the file
Remember that the first data written in the file is date and time, your first record should be written after that only.
Output: 0 (failed) or 1 (success)
*/
Bool saveRecord(FILE*, record*, int);

/*
Write a function to add a record
Input: None
Process:
Dynamically allocate memory to a record.
Take user input and assign it to members of record.
Store this data in a file created by createFile()
save this record.
Copy this record into dataBase.
Add will always add the record at the end (append)
Output: 0 (failed) or 1 (success)
Note: Record will be added at the last or a free location.
*/
Bool addRecord(FILE*);

/*
Write a function to update a record
Input: Index i
Process:
Ask the user which field to update, say name (Use ENUMs for fields)
Example: record is having fields filedA and filedB (ENUM FIELD_A=0, FIELD_B=1, A and B must be replace by your field names)
1. Update A
2. Update B
3. return

Dynamically allocate memory to a record.
read the i'th record from file (do not read from dataBase)
Take user input and assign it to members of record.
update this data in a file created by createFile() at i'th index
save this record.
copy this record into dataBase.
Output: 0 (failed) or 1 (success)
*/
Bool updateRecord(FILE*, int);

/*
Write a function to read a record from file
Input: record pointer, index i
Process: read ith record from file and copy its value in the record pointer.
Output: 0 (failed) or 1 (success)
*/
Bool readRecord(FILE*, record*, int);

/*
Write a function to display a record
Input: record pointer, index i
Process: read ith record from file and display on the screen
Output: 0 (failed) or 1 (success)
*/
Bool displayRecord(FILE*, record*, int);

/*
Write a function to display all records
Input: none
Process: read all record from file and display on the screen
Output: 0 (failed) or 1 (success)
*/
Bool displayAllRecords();

/*
Write a function to display all records
Input: index i
Process: set the ith record to all zero in the file and then int the dataBase.
Output: 0 (failed) or 1 (success)
*/
Bool deleteRecord(FILE*, int);

/*
Create a function displaying the Menu
1. Add a record
2. Update a record
3. Delete a record
4. Display a record
5. Display all records
0. Quit
*/
void operationMenu();

/*
21. Create an array of function pointers having pointers to addRecord, updateRecord, deleteRecord, displayRecord.
These functions must be called using function pointers only.

- Any data passed between functions must be passed by address (call by value and reference variables should never be used).
- Use proper naming conventions for variables. Do not use variables like, i, j, k, temp, ptr, etc.  
*/