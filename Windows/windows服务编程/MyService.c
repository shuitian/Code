/*
    MyService.c
*/
#include<MyService.h>

VOID WINAPI ServiceMain(DWORD dwArgc,LPTSTR *lpszArgv){
    if(!InitService()){
        WriteLog("Init Failed!");
        return;
    }
    DWORD bRet=0xFFFFFFFF;
    DWORD result;
    ServiceStatus.dwServiceType   = SERVICE_WIN32;
    ServiceStatus.dwCurrentState = SERVICE_START_PENDING;
    ServiceStatus.dwControlsAccepted   = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_PAUSE_CONTINUE | SERVICE_ACCEPT_SHUTDOWN ;
    ServiceStatus.dwWin32ExitCode = 0;
    ServiceStatus.dwCheckPoint   = 0;
    ServiceStatus.dwWaitHint   = 0;
    ServiceStatus.dwServiceSpecificExitCode = 0;
    hStatus = RegisterServiceCtrlHandler(SERVICE_NAME, (LPHANDLER_FUNCTION)ServiceHandler);
    if(hStatus == 0){
        WriteLog("RegisterServiceCtrlHandler Error!");
        sprintf(error,"%d",GetLastError());
        WriteLog(error);
        return;
    }WriteLog("RegisterServiceCtrlHandler Success!");
    ServiceStatus.dwCurrentState = SERVICE_RUNNING;
    ServiceStatus.dwCheckPoint   = 0;
    ServiceStatus.dwWaitHint   = 0;
    SetServiceStatus(hStatus,&ServiceStatus);
    HANDLE hThread=CreateThread(NULL,0,MainProc,NULL,0,NULL);
    if(hThread==NULL)
        return;
    CloseHandle(hThread);
    WriteLog("ServiceMain End!");
}

VOID WINAPI ServiceHandler(DWORD fdwControl){
    switch(fdwControl)
    {
        case SERVICE_CONTROL_PAUSE:
            WriteLog("Service Pause.");
            ServiceStatus.dwCurrentState=SERVICE_PAUSED;
            break;
        case SERVICE_CONTROL_CONTINUE:
            WriteLog("Service Resume.");
            ServiceStatus.dwCurrentState=SERVICE_RUNNING;
            break;
        case SERVICE_CONTROL_STOP:
        case SERVICE_CONTROL_SHUTDOWN:
            WriteLog("Service Stop.");
            ServiceStatus.dwCurrentState=SERVICE_STOPPED;
            ServiceStatus.dwCheckPoint   = 0;
            ServiceStatus.dwWaitHint   = 0;
            ServiceStatus.dwWin32ExitCode = 0;
            break;
        default:
            WriteLog("Service Default.");
            break;
    }
    SetServiceStatus (hStatus, &ServiceStatus); 
    return;
}

DWORD WINAPI MainProc(LPVOID lpParam){
    WriteLog("MainProc!");
    return 1;
}

int main(){
    SERVICE_TABLE_ENTRY ServiceTable[2]={
       {SERVICE_NAME,(LPSERVICE_MAIN_FUNCTION)ServiceMain},
       {NULL,NULL}
    };
    StartServiceCtrlDispatcher(ServiceTable);
    return 0;
}

int InitService(){
    int result;
    result = WriteLog("Service Started.");
    return(result);
}

int WriteLog(char * str){
    FILE *log=fopen(LOGFILE,"a+");
    if(log==NULL)
        return 0;
    SYSTEMTIME stNow;
    GetLocalTime(&stNow);
    fprintf(log,"%d-%d-%d %d:%d:%d\t%s\n",stNow.wYear,stNow.wMonth,stNow.wDay,stNow.wHour,stNow.wMinute,stNow.wSecond,str);
    fclose(log);
    return 1;
}
