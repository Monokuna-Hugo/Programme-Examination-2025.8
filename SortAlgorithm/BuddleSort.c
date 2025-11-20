#include <stdio.h>

void swap(int* a,int* b){
	int temp = *a;
	*a = *b;
	*b = temp;
}
void buddleSort(int* arr,int arrSize){
	for (int i = 0;i<arrSize-1;i++){
		int flag = 1;
		for (int j = arrSize-1;j>i;j--){
			if (arr[j-1]>arr[j]){
				swap(&arr[j-1],&arr[j]);
				flag = 0;
			}
		}
		if (flag){
			return;
		}
	}
}

int main(){
    int arr[] = {49,38,65,97,76,13,27};
    int size = sizeof(arr) / sizeof(arr[0]);
    buddleSort(arr,size);
    for (int i = 0;i < size; i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
    return 0;
}