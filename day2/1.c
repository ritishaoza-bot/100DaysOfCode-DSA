# include<stdio.h>
int main(){
    int arr[10],n,pos;
    printf("enter the no of the elements:");
    scanf("%d",&n);
    printf("enter the elements:\n");
    for(int i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }
    printf("enter the position to delete:");
    scanf("%d",&pos);
    if (pos < 1 || pos > n) {
        printf("Invalid position!\n");
    } else {

    for(int i=pos;i<n;i++){ 
        arr[i]=arr[i+1];
    }
        n--;
    printf("final array:\n");
    for(int i=0;i<n;i++){
        printf("%d",arr[i]);
    }
    printf("\n");
}
return 0;
}