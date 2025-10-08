#include <stdio.h>

int binarySearch(int arr[],int n,int element){
	int left = 0;
	int right = n;
	while (left <= right){
		int mid = (right - left) / 2;
		if (arr[mid] < element) {
			left = mid + 1;
		} else if(arr[mid] > element){
			right = mid - 1;
		} else {
			return mid;
		}
	}
	return -1;
}

int main(){
    int arr[] = {1,3,5,7,11,23,45,66,89,1000};
    int n = sizeof(arr) / sizeof(arr[0]);
    int element = 5;
    int index = binarySearch(arr,n,element);

    if (index == -1){
        printf("Element not found");
    } else {
        printf("Element found at index %d",index);
    }

}