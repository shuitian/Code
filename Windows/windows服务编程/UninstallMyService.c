/*
    UninstallMyService.c
*/
#include<MyService.h>
int main(){
    hSCManager=OpenSCManager(NULL,NULL,SC_MANAGER_ALL_ACCESS);
    if(!hSCManager)return -1;
    hOpenService=OpenService(hSCManager,SERVICE_NAME,SC_MANAGER_ALL_ACCESS);
    if(GetLastError()==ERROR_SERVICE_DOES_NOT_EXIST){
        return;
    }
    
    QueryServiceStatus(hOpenService,&ServiceStatus);
    printf("%d ",ServiceStatus.dwCurrentState);
    printf("%d ",ControlService(hOpenService,SERVICE_CONTROL_STOP,&ServiceStatus));
    QueryServiceStatus(hOpenService,&ServiceStatus);
    printf("%d ",ServiceStatus.dwCurrentState);
    printf("%d\n",GetLastError());
    DeleteService(hOpenService);
    CloseServiceHandle(hSCManager);
    CloseServiceHandle(hOpenService);
    system("pause");
    return 0;
}
