/*
    MyService.h
*/
#include<stdio.h>
#include<windows.h>
#ifndef MYSERVICE_H
#define MYSERVICE_H

#define SERVICE_NAME "MyService.exe"
#define DISPLAY_NAME "MyService.exe"
#define SERVICE "C:\\Users\\hp\\Desktop\\MyService.exe"
#define LOGFILE "C:\\Users\\hp\\Desktop\\LOGFILE.txt"
#define SLEEP_TIME 5000

static char status[7][30]={
        "SERVICE_STOPPED",
        "SERVICE_START_PENDING",
        "SERVICE_STOP_PENDING",
        "SERVICE_RUNNING",
        "SERVICE_CONTINUE_PENDING",
        "SERVICE_PAUSE_PENDING",
        "SERVICE_PAUSED",
    };
static SERVICE_STATUS ServiceStatus;
static SC_HANDLE hSCManager;
static SC_HANDLE hOpenService;
static SERVICE_STATUS_HANDLE hStatus;
static char error[10];

int WriteLog(char * str);
VOID WINAPI ServiceMain(DWORD dwArgc,LPTSTR *lpszArgv);
VOID WINAPI ServiceHandler(DWORD fdwControl);
int InitService();
DWORD WINAPI MainProc(LPVOID lpParam);

#endif /* !MYSERVICE_H */
