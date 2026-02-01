# include<stdio.h>
int main(){
    int arr[10],pos,val,n;
    printf("enter the no of element in the array:");
    scanf("%d",&n);
    printf("enter the elements:\n");
    for(int i=0;i<n;i++)
    scanf("%d",&arr[i]);
    
    printf("enter the position:");
    scanf("%d",&pos);
    printf("enter the value to be entered:");
    scanf("%d",&val);
    for(int i=n;i>pos;i--){
        arr[i]=arr[i-1];
    }
arr[pos]=val;
n++;
    
printf("final array:\n");
for(int i=0;i<n;i++){
printf("%d",arr[i]);
}
    return 0;
}