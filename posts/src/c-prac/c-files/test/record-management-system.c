#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "record_management_system.h"

int main() {
    
    FILE *file = NULL;
    FILE **filePtr = &file;
    char fileName[] = "records.dat";
    createFile(fileName, strlen(fileName), filePtr);
    addRecord(file);
    
    fclose(file);

    return 0;
}

void* memoryAlloc(int iRecordSize, int iRecordCount){
    
    // arguments validation
    if(0 >= iRecordSize){
        fprintf(stderr, "[%s]:[%d] Invalid iRecordSize\n", __func__, __LINE__);
        exit(0);
    }
    if(0 >= iRecordCount){
        fprintf(stderr, "[%s]:[%d] Invalid iRecordCount\n", __func__, __LINE__);
        exit(0);
    }
    
    void* allocMem = malloc(iRecordCount * iRecordSize);

    if(NULL == allocMem){
        fprintf(stderr, "[%s]:[%d] Memory could not be allocated!\n", __func__, __LINE__);
        exit(0);
    }
    return allocMem;
}

void memoryDealloc(void* iAllocMem){
    
    // Argument Validation
    if(NULL == iAllocMem){
        fprintf(stderr, "[%s]:[%d] iAllocMem pointing to NULL\n", __func__, __LINE__);
        exit(0);
    }

    free(iAllocMem);
}

Bool setRecord(record* iRecord, field iField, void* fieldPtr){
    
    // Argument Validation
    if(NULL == iRecord){
        fprintf(stderr, "[%s]:[%d] iRecord pointing to NULL\n", __func__, __LINE__);
        return FAIL;
    }
    if(NULL == fieldPtr){
        fprintf(stderr, "[%s]:[%d] fieldPtr pointing to NULL!\n", __func__, __LINE__);
        return FAIL;
    }
    
    switch (iField){
        case STATUS:
            return setStatus(iRecord, *(int *)fieldPtr);
        case NAME:
            return setName(iRecord, (char *)fieldPtr);
        case STATIONTYPE:
            return setStationType(iRecord, *(StationType *)fieldPtr);
        case MSGWAITFLAG:
            return setMsgWaitFlag(iRecord, *(int *)fieldPtr);
        case VMAMSGWAITFLAG:
            return setVmsMsgWaitFlag(iRecord, *(int *)fieldPtr);
        case VMSTONELEN:
            return setVmsToneLen(iRecord, *(int *)fieldPtr);
        
        default:
            fprintf(stderr, "[%s]:[%d] Invalid Field type!\n", __func__, __LINE__);
            return FAIL;
    }
}

Bool getRecord(record* iRecord, field iField, void* fieldPtr){
    
    // Argument Validation
    if(NULL == iRecord){
        fprintf(stderr, "[%s]:[%d] iRecord pointing to NULL\n", __func__, __LINE__);
        return FAIL;
    }
    if(NULL == fieldPtr){
        fprintf(stderr, "[%s]:[%d] fieldPtr pointing to NULL!\n", __func__, __LINE__);
        return FAIL;
    }
    int status;
    char name[19];
    int stationType;
    int msgWaitFlag, vmsMsgWaitFlag, vmsToneLen;

    status = iRecord->status;
    strcpy(name, iRecord->name);
    stationType = iRecord->stationType;
    msgWaitFlag = iRecord->msgWaitFlag;
    vmsMsgWaitFlag = iRecord->vmsMsgWaitFlag;
    vmsToneLen = iRecord->vmsToneLen;
    
    switch (iField){
        case STATUS:
            fieldPtr = &status;
            break;
        case NAME:
            // fieldPtr = (int *)fieldPtr;
            fieldPtr = name;
            break;
        case STATIONTYPE:
            fieldPtr = &stationType;
            break;
        case MSGWAITFLAG:
            fieldPtr = &msgWaitFlag;
            break;
        case VMAMSGWAITFLAG:
            fieldPtr = &vmsMsgWaitFlag;
            break;
        case VMSTONELEN:
            fieldPtr = &vmsToneLen;
            break;
        
        default:
            fprintf(stderr, "[%s]:[%d] Invalid Field type!\n", __func__, __LINE__);
            return FAIL;
    }
}

Bool setStatus(record* iRecord, int iStatus){
    
    // Argument Validation
    if(NULL == iRecord){
        fprintf(stderr, "[%s]:[%d] iRecord pointing to NULL!\n", __func__, __LINE__);
        return FAIL;
    }
    if((0 != iStatus) && (1 != iStatus)){
        fprintf(stderr, "[%s]:[%d] Invalid iStatus!\n", __func__, __LINE__);
        return FAIL;
    }
    
    // Value Assignment
    iRecord->status = iStatus;
    return SUCCESS;
}

Bool setName(record* iRecord, char* iName){
        
    // Argument Validation
    if(NULL == iRecord){
        fprintf(stderr, "[%s]:[%d] iRecord pointing to NULL!\n", __func__, __LINE__);
        return FAIL;
    }
    if(NULL == iName){
        fprintf(stderr, "[%s]:[%d] iName pointing to NULL!\n", __func__, __LINE__);
        return FAIL;
    }
    // if((0 >= iNameLen) && (19 <= iNameLen)){
    //     fprintf(stderr, "[%s]:[%d] Invalid Name Length!\n", __func__, __LINE__);
    //     return FAIL;
    // }

    // Value Assignment
    strcpy(iRecord->name, iName);
    return SUCCESS;
}

Bool setStationType(record* iRecord, StationType iStationType){
    
    // Argument Validation
    if(NULL == iRecord){
        fprintf(stderr, "[%s]:[%d] iRecord pointing to NULL!\n", __func__, __LINE__);
        return FAIL;
    }
    
    // Value Assignment
    iRecord->stationType = iStationType;
    return SUCCESS;
}

Bool setMsgWaitFlag(record* iRecord, int iMsgWaitFlag){
    
    // Argument Validation
    if(NULL == iRecord){
        fprintf(stderr, "[%s]:[%d] iRecord pointing to NULL!\n", __func__, __LINE__);
        return FAIL;
    }
    
    // Value Assignment
    iRecord->msgWaitFlag = iMsgWaitFlag;
    return SUCCESS;
}

Bool setVmsMsgWaitFlag(record* iRecord, int iVmsMsgWaitFlag){
    
    // Argument Validation
    if(NULL == iRecord){
        fprintf(stderr, "[%s]:[%d] iRecord pointing to NULL!\n", __func__, __LINE__);
        return FAIL;
    }
    
    // Value Assignment
    iRecord->vmsMsgWaitFlag = iVmsMsgWaitFlag;
    return SUCCESS;
}

Bool setVmsToneLen(record* iRecord, int iVmsToneLen){
    
    // Argument Validation
    if(NULL == iRecord){
        fprintf(stderr, "[%s]:[%d] iRecord pointing to NULL!\n", __func__, __LINE__);
        return FAIL;
    }
    
    // Value Assignment
    iRecord->vmsToneLen = iVmsToneLen;
    return SUCCESS;
}

Bool createFile(char * iFileName, int iFileNameLen, FILE **oFile){
    
    // Argument Validation
    if(NULL == iFileName){
        fprintf(stderr, "[%s]:[%d] iFileName pointing to NULL\n", __func__, __LINE__);
        return FAIL;
    }
    if(strlen(iFileName) != iFileNameLen){
        fprintf(stderr, "[%s]:[%d] Invalid FileName Length\n", __func__, __LINE__);
        return FAIL;
    }
    
    // opening file
    *oFile = fopen(iFileName, "w+");

    if(NULL == oFile){
        fprintf(stderr, "[%s]:[%d] oFile creation failed!\n", __func__, __LINE__);
        return FAIL;
    }

    return SUCCESS;
}

Bool getDateTime(time* oTime){

    // Argument Validation
    if(NULL == oTime){
        fprintf(stderr, "[%s]:[%d] iTime pointing to NULL\n", __func__, __LINE__);
        return FAIL;
    }
    
    int hour, min, sec, date, year;
    char month[4];
    sscanf(__TIME__, "%d:%d:%d", &hour, &min, &sec);
    sscanf(__DATE__, "%s %d %d", month, &date, &year);
    oTime->hour = hour;
    oTime->minute = min;
    oTime->second = sec;
    strcpy(oTime->month, month);
    oTime->date = date;
    oTime->year = year;
    
    return SUCCESS;
}

Bool writeDateTime(FILE *oFile, struct time* iTime){
    
    // Argument Validation
    if(NULL == iTime){
        fprintf(stderr, "[%s]:[%d] iTime pointing to NULL\n", __func__, __LINE__);
        return FAIL;
    }
    
    fseek(oFile, 0, SEEK_SET);
    fwrite(iTime, sizeof(time), 1, oFile);
}

Bool defaultRecord(record* iRecord){
    
    // Argument Validation
    if(NULL == iRecord){
        fprintf(stderr, "[%s]:[%d] iRecord pointing to NULL!\n", __func__, __LINE__);
        return FAIL;
    }
    
    memset(iRecord, 0, sizeof(record));
    
    // Verifying if memset is successful
    if(NULL == iRecord){
        fprintf(stderr, "[%s]:[%d] Memset failed, iRecord pointing to NULL!\n", __func__, __LINE__);
        return FAIL;
    }
}

Bool saveRecord(FILE *oFile, record* iRecord, int iIndex){
    
    // Argument Validation
    if(NULL == oFile){
        fprintf(stderr, "[%s]:[%d] oFile pointing to NULL!\n", __func__, __LINE__);
        return FAIL;
    }
    if(NULL == iRecord){
        fprintf(stderr, "[%s]:[%d] iRecord pointing to NULL!\n", __func__, __LINE__);
        return FAIL;
    }
    if(iIndex < 0 || iIndex >= MAX_RECORD){
        fprintf(stderr, "[%s]:[%d] iIndex is exceeding its limits\n", __func__, __LINE__);
        return FAIL;
    }

    int seekSize = sizeof(time) + iIndex * sizeof(record);
    int returnStatus = fseek(oFile, seekSize, SEEK_SET);
    
    if(returnStatus < 0){
        fprintf(stderr, "[%s]:[%d] Failed to fseek within file!\n", __func__, __LINE__);
        return FAIL;
    }
    
    returnStatus = fwrite(iRecord, sizeof(record), 1, oFile);

    if(returnStatus <= 0){
        fprintf(stderr, "[%s]:[%d] Failed to fwrite within file!\n", __func__, __LINE__);
        return FAIL;
    }

    time *tTime;
    getDateTime(tTime);

    if(FAIL == writeDateTime(oFile, tTime)){
        fprintf(stderr, "[%s]:[%d] Failed to write time within file!\n", __func__, __LINE__);
        return FAIL;
    }

    return SUCCESS;
}

Bool addRecord(FILE* oFile){
    /*
    Take user input and assign it to members of record.
    Store this data in a file created by createFile()
    save this record.
    Copy this record into dataBase.
    Add will always add the record at the end (append)
    Output: 0 (failed) or 1 (success)
    Note: Record will be added at the last or a free location.
    */
    
    int status;
    char name[19];
    int stationType;
    int msgWaitFlag, vmsMsgWaitFlag, vmsToneLen;

    printf("Record Entry:-\n");
    printf("Enter Status: \n");
    scanf("%d", &status);
    printf("Enter Name: \n");
    fflush(stdin);
    scanf("%s", name);
    printf("Enter Station Type: \n");
    scanf("%d", &stationType);
    printf("Set Message Wait Flag: \n");
    scanf("%d", &msgWaitFlag);
    printf("Set VMS Message Wait Flag: \n");
    scanf("%d", &vmsMsgWaitFlag);
    printf("Enter VMS Tone Length: \n");
    scanf("%d", &vmsToneLen);

    record *tRecord = memoryAlloc(sizeof(record), 1);
    // *tRecord = {status, name, stationType, msgWaitFlag, vmsMsgWaitFlag, vmsToneLen};
    tRecord->status = status;
    strcpy(tRecord->name, name);
    tRecord->stationType = stationType;
    tRecord->msgWaitFlag = msgWaitFlag;
    tRecord->vmsMsgWaitFlag = vmsMsgWaitFlag;
    tRecord->vmsToneLen = vmsToneLen;
    
    saveRecord(oFile, tRecord, 0);
    defaultRecord(tRecord);
    saveRecord(oFile, tRecord, 1);
    saveRecord(oFile, tRecord, 2);
    displayRecord(oFile, tRecord, 1);

    free(tRecord);
    tRecord = NULL;
    return SUCCESS;
}

Bool updateRecord(FILE* ioFile, int iIndex){

    // Argument Validation
    if(NULL == ioFile){
        fprintf(stderr, "[%s]:[%d] ioFile pointing to NULL!\n", __func__, __LINE__);
        return FAIL;
    }
    if(iIndex < 0 || iIndex >= MAX_RECORD){
        fprintf(stderr, "[%s]:[%d] iIndex is exceeding its limits\n", __func__, __LINE__);
        return FAIL;
    }
    
    // TODO: Complete this function

    return SUCCESS;

}

Bool readRecord(FILE* iFile, record* oRecord, int iIndex){

    // Argument Validation
    if(NULL == iFile){
        fprintf(stderr, "[%s]:[%d] iFile pointing to NULL!\n", __func__, __LINE__);
        return FAIL;
    }
    if(NULL == oRecord){
        fprintf(stderr, "[%s]:[%d] oRecord pointing to NULL!\n", __func__, __LINE__);
        return FAIL;
    }
    if(iIndex < 0 || iIndex >= MAX_RECORD){
        fprintf(stderr, "[%s]:[%d] iIndex is exceeding its limits\n", __func__, __LINE__);
        return FAIL;
    }

    int seekSize = sizeof(time) + iIndex * sizeof(record);
    int returnStatus = fseek(iFile, seekSize, SEEK_SET);
    
    if(returnStatus < 0){
        fprintf(stderr, "[%s]:[%d] Failed to fseek within file!\n", __func__, __LINE__);
        return FAIL;
    }
    
    returnStatus = fread(oRecord, sizeof(record), 1, iFile);

    if(returnStatus <= 0){
        fprintf(stderr, "[%s]:[%d] Failed to fread within file!\n", __func__, __LINE__);
        return FAIL;
    }

    return SUCCESS;
}

Bool displayRecord(FILE* iFile, record* iRecord, int iIndex){
    
    // Argument Validation
    if(NULL == iFile){
        fprintf(stderr, "[%s]:[%d] iFile pointing to NULL!\n", __func__, __LINE__);
        return FAIL;
    }
    if(NULL == iRecord){
        fprintf(stderr, "[%s]:[%d] iRecord pointing to NULL!\n", __func__, __LINE__);
        return FAIL;
    }
    if(iIndex < 0 || iIndex >= MAX_RECORD){
        fprintf(stderr, "[%s]:[%d] iIndex is exceeding its limits\n", __func__, __LINE__);
        return FAIL;
    }

    int seekSize = sizeof(time) + iIndex * sizeof(record);
    int returnStatus = fseek(iFile, seekSize, SEEK_SET);
    
    if(returnStatus < 0){
        fprintf(stderr, "[%s]:[%d] Failed to fseek within file!\n", __func__, __LINE__);
        return FAIL;
    }
    
    returnStatus = fread(iRecord, sizeof(record), 1, iFile);

    if(returnStatus <= 0){
        fprintf(stderr, "[%s]:[%d] Failed to fread within file!\n", __func__, __LINE__);
        return FAIL;
    }
    
    printf("Record Index: %d\n", iIndex);
    printf("Status: %d\n", iRecord->status);
    printf("Name: %s\n", iRecord->name);
    printf("Station Type: %d\n", iRecord->stationType);
    printf("Msg Wait Flag: %d\n", iRecord->msgWaitFlag);
    printf("VMS Msg Wait Flag: %d\n", iRecord->vmsMsgWaitFlag);
    printf("VMS Tone Length: %d\n", iRecord->vmsToneLen);

    return SUCCESS;
}

Bool displayAllRecords(FILE* iFile){
    
    // Argument Validation
    if(NULL == iFile){
        fprintf(stderr, "[%s]:[%d] iFile pointing to NULL!\n", __func__, __LINE__);
        return FAIL;
    }
    
    record tRecord = {0};

    int recordIndex = 0;
    for(recordIndex = 0; recordIndex < MAX_RECORD; recordIndex++){
        if(!displayRecord(iFile, &tRecord, recordIndex)){
            break;
        }
    }
    
    return SUCCESS;
}

Bool deleteRecord(FILE* oFile, int iIndex){
    
    // Argument Validation
    if(NULL == oFile){
        fprintf(stderr, "[%s]:[%d] oFile pointing to NULL!\n", __func__, __LINE__);
        return FAIL;
    }
    if(iIndex < 0 || iIndex >= MAX_RECORD){
        fprintf(stderr, "[%s]:[%d] iIndex is exceeding its limits\n", __func__, __LINE__);
        return FAIL;
    }

    int seekSize = sizeof(time) + iIndex * sizeof(record);
    int returnStatus = fseek(oFile, seekSize, SEEK_SET);
    
    if(returnStatus < 0){
        fprintf(stderr, "[%s]:[%d] Failed to fseek within file!\n", __func__, __LINE__);
        return FAIL;
    }
    
    record *tRecord;
    defaultRecord(tRecord);

    returnStatus = fwrite(tRecord, sizeof(record), 1, oFile);

    if(returnStatus <= 0){
        fprintf(stderr, "[%s]:[%d] Failed to fwrite within file!\n", __func__, __LINE__);
        free(tRecord);
        return FAIL;
    }
    // TODO: Update Master Database

    free(tRecord);
    return SUCCESS;

}

void operationMenu(){
    
    int operationType;

    printf("Enter operation type:\n");
    printf("1. Add a record\n2. Update a record\n3. Delete a record\n4. Display a record\n5. Display all records\n0. Quit\n");
    scanf("%d", &operationType);
    
    // int (*operation[])(FILE*) = {addRecord, updateRecord, deleteRecord, displayRecord};
    
    // void (*functionPtr) = *operation[operationType];

    // int returnStatus = (*functionPtr)(FILE*);
    // 
}