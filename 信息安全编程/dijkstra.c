#include<stdio.h>
#define Max 200
int main(){
    int dist[Max][Max];//邻接矩阵 
    int short_point[Max];//每个点距离已找到最短距离点最近的点 
    int dis[Max];//每个节点离起始点的距离 
    int flag[Max];//判断节点是否包含在S集中，S集即已找到最短路径的节点 
    int path[Max];//输出最短路径所经过的点所用，path[i]表示从起始点到终点路径i的下一个节点 
    int i,j,n,num,a,b,d,min_p=0;
    //以下开始初始化1 
    for(i=0;i<Max;i++){
        short_point[i]=dis[i]=path[i]=-1;  //-1 
        flag[i]=0;
        for(j=0;j<Max;j++)
            dist[i][j]=-1;
    }
    dis[0]=0;flag[0]=1;short_point[0]=0;
    //初始化1结束 
    //开始输入数据 数据输入格式如下 
    /*
     第一行是n,num 分别代表几个节点和几天有向边
    一面是num行，每行3个数a,b,d 分别代表起始边，结束边，边长
    */ 
    scanf("%d%d",&n,&num);
    for(i=0;i<num;i++){
        scanf("%d%d%d",&a,&b,&d);
        dist[a][b]=d;
    }//输入数据结束
    //开始初始化2 
    for(i=0;i<n;i++){
        dist[i][i]=0;   
    }for(i=1;i<n;i++){
        if(dist[0][i]>=0)
            {short_point[i]=0;dis[i]=dist[0][i];}
    }
    //初始化2结束 
    for(j=1;j<n;j++){//j的递增代表着加入S集合边的递增 
        int min=Max,min_p=-1;
        for(i=1;i<n;i++){
            if((!flag[i]) && (dis[i]>=0) && (dis[i]<min))  
               {min=dis[i];min_p=i;}//筛选出离初始点最近的点 
        }//printf("%d %d\n",min,min_p);
        if(min_p==-1)break;//没有跟多的点 
        flag[min_p]=1;//min_p这个点加入S集 
        for(i=1;i<n;i++){//更新最短路 
            if(     (!flag[i]) && (dist[min_p][i]>=0) &&
                    (((dis[i]>=0)&&(min+dist[min_p][i]<dis[i]))||(dis[i]<0))       ) 
            {
                    dis[i]=   min+dist[min_p][i];
                    short_point[i]=min_p;
            }  
        }
    }printf("The shortest distance is :%d\n",dis[n-1]);
    //开始输出结果 
    for(i=n-1;i>0;){
        path[short_point[i]] = i;
        i = short_point[i];
    }
    printf("The shortest path is : 0");       
    for(i=0;i<n-1;){
        printf(" %d",path[i]);
        i = path[i];
    }
    //输出结束 
    /*调试代码(请忽略) 
    for(i=0;i<n;i++){
        printf("i:%d s_p:%d dis:%d flag:%d\n",i,short_point[i],dis[i],flag[i]);
    }*/ 
    system("pause");
    return 0;   
}
/*
数据输入 
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
