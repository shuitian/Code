#include<stdio.h>
#define Max 200
int main(){
    int dist[Max][Max];//�ڽӾ��� 
    int short_point[Max];//ÿ����������ҵ���̾��������ĵ� 
    int dis[Max];//ÿ���ڵ�����ʼ��ľ��� 
    int flag[Max];//�жϽڵ��Ƿ������S���У�S�������ҵ����·���Ľڵ� 
    int path[Max];//������·���������ĵ����ã�path[i]��ʾ����ʼ�㵽�յ�·��i����һ���ڵ� 
    int i,j,n,num,a,b,d,min_p=0;
    //���¿�ʼ��ʼ��1 
    for(i=0;i<Max;i++){
        short_point[i]=dis[i]=path[i]=-1;  //-1 
        flag[i]=0;
        for(j=0;j<Max;j++)
            dist[i][j]=-1;
    }
    dis[0]=0;flag[0]=1;short_point[0]=0;
    //��ʼ��1���� 
    //��ʼ�������� ���������ʽ���� 
    /*
     ��һ����n,num �ֱ�������ڵ�ͼ��������
    һ����num�У�ÿ��3����a,b,d �ֱ������ʼ�ߣ������ߣ��߳�
    */ 
    scanf("%d%d",&n,&num);
    for(i=0;i<num;i++){
        scanf("%d%d%d",&a,&b,&d);
        dist[a][b]=d;
    }//�������ݽ���
    //��ʼ��ʼ��2 
    for(i=0;i<n;i++){
        dist[i][i]=0;   
    }for(i=1;i<n;i++){
        if(dist[0][i]>=0)
            {short_point[i]=0;dis[i]=dist[0][i];}
    }
    //��ʼ��2���� 
    for(j=1;j<n;j++){//j�ĵ��������ż���S���ϱߵĵ��� 
        int min=Max,min_p=-1;
        for(i=1;i<n;i++){
            if((!flag[i]) && (dis[i]>=0) && (dis[i]<min))  
               {min=dis[i];min_p=i;}//ɸѡ�����ʼ������ĵ� 
        }//printf("%d %d\n",min,min_p);
        if(min_p==-1)break;//û�и���ĵ� 
        flag[min_p]=1;//min_p��������S�� 
        for(i=1;i<n;i++){//�������· 
            if(     (!flag[i]) && (dist[min_p][i]>=0) &&
                    (((dis[i]>=0)&&(min+dist[min_p][i]<dis[i]))||(dis[i]<0))       ) 
            {
                    dis[i]=   min+dist[min_p][i];
                    short_point[i]=min_p;
            }  
        }
    }printf("The shortest distance is :%d\n",dis[n-1]);
    //��ʼ������ 
    for(i=n-1;i>0;){
        path[short_point[i]] = i;
        i = short_point[i];
    }
    printf("The shortest path is : 0");       
    for(i=0;i<n-1;){
        printf(" %d",path[i]);
        i = path[i];
    }
    //������� 
    /*���Դ���(�����) 
    for(i=0;i<n;i++){
        printf("i:%d s_p:%d dis:%d flag:%d\n",i,short_point[i],dis[i],flag[i]);
    }*/ 
    system("pause");
    return 0;   
}
/*
�������� 
6 8
0 5 20
0 4 6
0 2 2
1 2 1
2 3 10
4 3 4
4 5 12
3 5 2

*/
