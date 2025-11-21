#include "stdio.h"

void swap(int* a,int* b){
	int temp = *a;
	*a = *b;
	*b = temp;
}
void selectSort(int* arr,int arrSize){
	for (int i = 0;i<arrSize-1;i++){
		int key = i;
		for (int j = i + 1;j<arrSize;j++){
			if (arr[key]>arr[j]){
				key = j;
			}
        }
	    if (i != key){
		    swap(&arr[i],&arr[key]);
		}
	}
}

int main(){
    int arr[] = {49,38,65,97,76,13,27};
    int size = sizeof(arr) / sizeof(arr[0]);
    selectSort(arr,size);
    for (int i = 0;i < size; i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
    return 0;
}