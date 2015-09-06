#include<stdio.h>
#include<windows.h>
#include<psapi.h>
int main(){
    DWORD ProcessCount;
    DWORD cbNeeded;
    DWORD ProcessId[1024];
    K32EnumProcesses(ProcessId,sizeof(ProcessId),&cbNeeded);
    ProcessCount=cbNeeded/sizeof(DWORD);
    HMODULE hModule;
    char szPath[MAX_PATH];
    int i;
    for(i=0;i<ProcessCount;i++){
        HANDLE hProcess=OpenProcess(PROCESS_QUERY_INFORMATION|PROCESS_VM_READ,FALSE,ProcessId[i]);
        if(hProcess){
            EnumProcessModule(hProcess,&hModule,sizeof(hModule),&cbNeeded);
            GetModuleFileNameEx(hProcess,hModule,szPath,sizeof(szPath));
            printf("PID:%d\t%s\n",ProcessId[i],szPath);
        }else {
            continue;
        }
    }
    return 0;
}



