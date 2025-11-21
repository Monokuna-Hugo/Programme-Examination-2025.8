#include "stdio.h"
#include "stdlib.h"

void AdjustHead(int* arr,int k,int arrSize);
void BuildMaxHeap(int* arr,int arrSize){
	// 从最后一个非叶子结点开始向上调整，注意数组下标从0开始
	for (int i = arrSize/2 - 1;i >= 0;i--){
		AdjustHead(arr,i,arrSize);
	}
}
void AdjustHead(int* arr,int k,int arrSize){
	int temp = arr[k];
	for (int i = 2*k + 1;i < arrSize;i = 2*i + 1){
		if (i + 1 < arrSize && arr[i] < arr[i + 1]) 
            i++;
		if (temp >= arr[i]) break;
		else{
			arr[k] = arr[i];
			k = i;
		}
	}
	arr[k] = temp;
}
void swap(int *a,int *b);
void heapSort(int* arr,int arrSize){
	BuildMaxHeap(arr,arrSize);
	// 每次将堆顶（最大值）与当前未排序部分的末尾交换，并重新调整堆
	for (int i = arrSize - 1;i > 0;i--){
		swap(&arr[i],&arr[0]);
		AdjustHead(arr,0,i);
	}
}
void swap(int* a,int* b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

int main(){
    int arr[] = {49,38,65,97,76,13,27};
    int size = sizeof(arr) / sizeof(arr[0]);
    heapSort(arr,size);
    for (int i = 0;i < size; i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
    return 0;
}