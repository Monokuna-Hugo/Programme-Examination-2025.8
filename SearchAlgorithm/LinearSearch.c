#include <stdio.h>

int linearSearch(int* arr,int arrSize, int target){
    for (int i=0; i < arrSize; i++){
        if (arr[i] == target){
            return i;
        }
    }
    return -1;
}

int main(){
    int arr[] = {1,3,5,7,11,23,45,66,89,1000};
    int n = sizeof(arr) / sizeof(arr[0]);
    int element = 5;
    int index = linearSearch(arr,n,element);

    if (index == -1){
        printf("Element not found");
    } else {
        printf("Element found at index %d",index);
    }
    
    return 0;
}