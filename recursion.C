#include<stdio.h>
// float convertTemp(float celsius);

// int main(){
//     float far= convertTemp(37);
//     printf("far : %f", far);
//     return 0;
// }

// float convertTemp(float celsius){
//     float far = celsius *(9.0/5.0)+32;
//     return far;
// }

int calcPercentage(int  science,int math,int eng);

int main(){
    int sc=98;
    int math=95;
    int eng=99;
    printf("percentege is :%d", calcPercentage(sc,math ,eng));
    return 0;
}

int calcPercentage(int  science,int math,int eng){
    return((science +math +eng)/3);
}

int fib(int n);

int main(){
    printf ("%d", fib(6));
    return 0;
}
int fib(int n){
    if (n==0){
        return 0;
    }
    if(n==1){
        return 1;
    }
    int fibNm1 =fib(n-1);
    int fibNm2 =fib(n-2);
int fibN =fibNm1+fibNm2;
// printf("fib of %d is %d\n",n,fibN);
return fibN;
}
