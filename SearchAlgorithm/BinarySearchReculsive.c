#include <stdio.h>

int binarySearchReculsive(int arr[],int element,int left,int right){
    if (left > right) return -1;
    int mid = (right - left) / 2 + left;
    if (arr[mid] == element){
        return mid;
    } else if (arr[mid] > element){
        return binarySearchReculsive(arr, element, left, mid - 1);
    } else {
        return binarySearchReculsive(arr, element, mid + 1, right);
    }
}

int main(){
    int arr[] = {1,3,5,7,11,23,45,66,89,1000};
    int n = sizeof(arr) / sizeof(arr[0]);
    int element = 5;
    int index = binarySearchReculsive(arr,element,0,n - 1);

    if (index == -1){
        printf("Element not found");
    } else {
        printf("Element found at index %d",index);
    }
    
    return 0;
}