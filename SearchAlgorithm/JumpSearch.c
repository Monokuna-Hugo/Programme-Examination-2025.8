#include <stdio.h>
#include <math.h>

int min(int a, int b){
    return (a < b) ? a : b;
}

int jumpSearch(int* arr, int arrSize, int target){
    //确定跳跃步长
    int step = sqrt(arrSize);
    // 确定目标元素所在的跳跃块
    int prev = 0;
    while (arr[min(step,arrSize) - 1] < target){
        prev = step;
        step += sqrt(arrSize);
        if (prev >= arrSize) return -1;
    }
    // 在跳跃块内进行线性搜索
    while (arr[prev] < target){
        prev++;
        if (prev == min(step,arrSize)) return -1;
    }
    // 检查是否找到目标元素
    if (arr[prev]== target){
        return prev;
    }
    // 如果目标元素不在跳跃块内，则返回-1
    return -1;
}

int main(){
    int arr[] = {1,3,5,7,11,23,45,66,89,1000};
    int n = sizeof(arr) / sizeof(arr[0]);
    int element = 5;
    int index = jumpSearch(arr,n,element);

    if (index == -1){
        printf("Element not found");
    } else {
        printf("Element found at index %d",index);
    }
    
    return 0;
}