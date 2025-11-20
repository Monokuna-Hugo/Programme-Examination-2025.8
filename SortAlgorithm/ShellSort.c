#include <stdio.h>

void shellSort(int* arr,int arrSize){
	for (int gap = arrSize / 2; gap >=1; gap /=2){
		for (int i = gap; i < arrSize; i++){
			int key = arr[i];
            int j;
			for (j=i ; j>=gap && arr[j-gap] > key;j-=gap){
				arr[j] = arr[j - gap];
			}
			arr[j] = key;
		}
	}
}

int main(){
    int arr[] = {49,38,65,97,76,13,27};
    int size = sizeof(arr) / sizeof(arr[0]);
    shellSort(arr,size);
    for (int i = 0;i < size; i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
    return 0;
}