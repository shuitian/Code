#include<windows.h>
#include<stdio.h>
#include<ntsecapi.h>
typedef DWORD (WINAPI *ZWQUERYSYSTEMINFORMATION)(DWORD,PVOID,DWORD,PDWORD);
typedef struct _SYSTEM_PROCESS_INFORMATION{
    DWORD NextEntryDelta;
    DWORD ThreadCount;
    DWORD Reserved1[6];
    FILETIME ftCreateTime;
    FILETIME ftUserTime;
    FILETIME ftKernelTime;
    UNICODE_STRING ProcessName;
    DWORD BasePriority;
    DWORD ProcessId;
    DWORD InheritedFromProcessId;
    DWORD HandleCount;
    DWORD Reserved2[2];
    DWORD VmCounters;
    DWORD dCommitCharge;
    PVOID ThreadInfos[1];
}SYSTEM_PROCEESS_INFORMATION,*PSYSTEM_PROCEESS_INFORMATION;
#define SystemProcessesAndThreadsInformation 5
int main(){
    HMODULE hNtDll=GetModuleHandle("ntdll.dll");
    if(hNtDll==NULL)
        return -1;
    ZWQUERYSYSTEMINFORMATION ZwQuerySystemInformation=
    (ZWQUERYSYSTEMINFORMATION)GetProcAddress(hNtDll,"ZwQuerySystemInformation");
    if(ZwQuerySystemInformation==NULL)
        return -1;
    DWORD cbBuffer=0x10000;
    LPVOID pBuffer=NULL;
    if((pBuffer=malloc(cbBuffer))==NULL)
        return -1;
    ZwQuerySystemInformation(SystemProcessesAndThreadsInformation,pBuffer,cbBuffer,NULL);
    PSYSTEM_PROCEESS_INFORMATION pInfo=(PSYSTEM_PROCEESS_INFORMATION)pBuffer;
    FILE *fp=fopen("limit.txt","r+");
    char buffer[100];
    if(fp==NULL)
        return -1;
while(1){
    ZwQuerySystemInformation(SystemProcessesAndThreadsInformation,pBuffer,cbBuffer,NULL);
    PSYSTEM_PROCEESS_INFORMATION pInfo=(PSYSTEM_PROCEESS_INFORMATION)pBuffer;
    for(;;){
        wcstombs(buffer,pInfo->ProcessName.Buffer,100);
        if(strcmp(buffer,"cdoj.exe")==0){
            fseek(fp,0,SEEK_SET);
            fread (buffer,3,1,fp) ;
            DWORD time=atoi(buffer);
            printf("%d\n",time);
            if(time<120)time++;
            else {
                HANDLE hProcess=OpenProcess(PROCESS_TERMINATE,FALSE,pInfo->ProcessId);
                TerminateProcess(hProcess,0);
            }
            fseek(fp,0,SEEK_SET);
            fprintf(fp,"%d",time);
        }
        printf("PID:%d \t%ls\n",pInfo->ProcessId,pInfo->ProcessName.Buffer);
        if(pInfo->NextEntryDelta==0){
            break;
        }pInfo=(PSYSTEM_PROCEESS_INFORMATION)(((PUCHAR)pInfo)+pInfo->NextEntryDelta);
    }sleep(1000);
}
    free(pBuffer);
    system("pause");
    return 0;
}
