#include<stdio.h>
#include<stdlib.h>
#define SIZE_Y 100
int main(int argc, char** argv){

    int *XXArray;
    int YYArray[SIZE_Y];
    int num, i, a, b;
    printf("enter a number which is a multiple of 5\n");
    scanf("%d", &num);
    printf("enter two numbers a and b greater than 0\n");
    scanf("%d %d", &a, &b);
    printf("You entered: a = %d, b = %d\n", a, b);
    XXArray = (int *)malloc(sizeof(int)*num);

    long long result = 0;

    for(i = 0; i < SIZE_Y; i+=5){
        YYArray[i] = i*2 + i-1;
        YYArray[i+1] = (i+1)*2 + (i);
        YYArray[i+2] = (i+2)*2 + (i+1);
        YYArray[i+3] = (i+3)*2 + (i+2);
        YYArray[i+4] = (i+4)*2 + (i+3);
    }
    for(i = 0; i< SIZE_Y; i++){
      result = result + YYArray[i];
    } 
    
    for(i = 0; i< num; i++){
        XXArray[i] = a*i + b;
    }
  
    for(i = 0; i< num; i++){
      printf("XXArray[%d]: %d\n",i,XXArray[i]);
      result = result + XXArray[i];
    } 
 
    printf("the result is %lld\n", result);
  
    free(XXArray);
    return 0;
}
