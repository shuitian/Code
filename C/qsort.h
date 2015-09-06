#include<stdio.h>
void q_sort(int a[],int low,int high){//赋值快排 
    int k=a[low],i=low,j=high;
    while(i<j){
        while((a[j]>=k)&&(i<j))j--;if(i<j){a[i]=a[j];i++;}
        while((a[i]<=k)&&(i<j))i++;if(i<j){a[j]=a[i];j--;}
    }a[i]=k;
    if(low<j-1)q_sort(a,low,j-1);
    if(i+1<high)q_sort(a,i+1,high);
}
void cq_sort(int a[],int low,int high){//交换快排 
    int mid=a[(low+high)/2],i=low,j=high;
    while(i<j){
        while(a[i]<mid)i++;
        while(a[j]>mid)j--;
        int temp=a[i];a[i]=a[j];a[j]=temp;
        if(low<j-1)cq_sort(a,low,j-1);
        if(i+1<high)cq_sort(a,i+1,high);
    }
}
