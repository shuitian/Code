/*
    PauseAndResume.c
*/
#include<MyService.h>
int main(){
    DWORD dwError;
    DWORD bRet;
    hSCManager=OpenSCManager(NULL,NULL,SC_MANAGER_ALL_ACCESS);
    if(!hSCManager)return -1;
    hOpenService=OpenService(hSCManager,SERVICE_NAME,SERVICE_ALL_ACCESS );
    if(GetLastError()==ERROR_SERVICE_DOES_NOT_EXIST){
        return;
    }
    QueryServiceStatus(hOpenService,&ServiceStatus);
    printf("%s\n",status[ServiceStatus.dwCurrentState-1]);
    bRet=ControlService(hOpenService,SERVICE_CONTROL_PAUSE,&ServiceStatus);
    if(bRet==0)
    printf("after pause return :0 LastError:%d\n",GetLastError());
    
    QueryServiceStatus(hOpenService,&ServiceStatus);
    printf("%s\n",status[ServiceStatus.dwCurrentState-1]);
    sleep(3000);
    bRet=ControlService(hOpenService,SERVICE_CONTROL_CONTINUE,&ServiceStatus);
    if(bRet==0)
    printf("after resume return :0 LastError:%d\n",GetLastError());
    QueryServiceStatus(hOpenService,&ServiceStatus);
    printf("%s\n",status[ServiceStatus.dwCurrentState-1]);
    

    CloseServiceHandle(hSCManager);
    CloseServiceHandle(hOpenService);
    system("pause");
    return 0;
}
