#include <stdio.h>

void insertSort(int* arr,int arrSize){
    int i,j;
	for (int i=0;i<arrSize;i++){ // 从第1个元素开始插入排序
        int key = arr[i];  // 将当前关键字复制到哨兵位置
        for (j=i-1;j>=0&&key<arr[j];--j){ // 从后往前查找插入位置
			arr[j+1] = arr[j]; //向后挪位
		}
        arr[j+1] = key;// 插入到正确位置
    }
}

int main(){
    int arr[] = {49,38,65,97,76,13,27};
    int size = sizeof(arr) / sizeof(arr[0]);
    insertSort(arr,size);
    for (int i = 0;i < size; i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
    return 0;
}