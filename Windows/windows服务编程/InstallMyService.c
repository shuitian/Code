/*
    InstallMyService.c
*/
#include<MyService.h>
int main(){
    hSCManager=OpenSCManager(NULL,NULL,SC_MANAGER_ALL_ACCESS);
    if(!hSCManager)return -1;
    hOpenService=OpenService(hSCManager,SERVICE_NAME,SC_MANAGER_ALL_ACCESS);
    if(GetLastError()==ERROR_SERVICE_DOES_NOT_EXIST){
        CreateService(hSCManager,SERVICE_NAME,DISPLAY_NAME,
        SERVICE_ALL_ACCESS,
        SERVICE_WIN32_OWN_PROCESS,
        SERVICE_AUTO_START,
        SERVICE_ERROR_IGNORE,
        SERVICE,
        NULL,NULL,NULL,NULL,NULL);
    }
    StartService(hOpenService,0,NULL);
    CloseServiceHandle(hSCManager);
    CloseServiceHandle(hOpenService);
    return 0;
}
