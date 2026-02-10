#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void bubbleSort(int *arr, int size){
    int sorted = 0;

    while(!sorted){
        sorted = 1;
        for(int i = 0; i < size-1; i++){
            if(arr[i] > arr[i+1]){
                int tmp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = tmp;
                sorted = 0;
            }
        }
    }
   printf("\nBubble Sorted Array: ");
    for(int i = 0; i < size; i++){
        printf("%d ", arr[i]);
    } 
    return;
}



int main(){
    clock_t start_t, end_t;
    double total_t;
    int unsorted[] = {21,15,57,44,33};
    int size = sizeof(unsorted) / sizeof(unsorted[0]);
    printf("\nUnsorted Array: ");
    for(int i = 0; i < size; i++){
        printf("%d ", unsorted[i]);
    }
    
    start_t = clock();
    bubbleSort(unsorted, size);
    end_t = clock();
    total_t = (double)(end_t - start_t)/CLOCKS_PER_SEC;
    printf("\nBubble Sort finished in %f seconds", total_t);
    return 0;
}
