#include <stdio.h>

int patition(int* arr,int left,int right){
	int key = arr[left];
	while (left < right) {
		while (left < right && arr[right] >= key) --right; 
		arr[left] = arr[right];                         //将关键字比key小的记录交换到前面
		while (left < right && arr[left] <= key) ++left;  
		arr[right] = arr[left];                         //将关键字比key大的记录交换到后面
	}
	arr[left] = key;
	return left;
}

void quickSort(int* arr,int left,int right){
	if (left < right){
		int pivot = patition(arr,left,right);
		quickSort(arr,left,pivot-1);
		quickSort(arr,pivot+1,right);
	}
}

int main(){
    int arr[] = {49,38,65,97,76,13,27};
    int size = sizeof(arr) / sizeof(arr[0]);
    quickSort(arr,0,size-1);
    for (int i = 0;i < size; i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
    return 0;
}