# include <stdio.h>

// int main() {
//     int age =22;
//     int *ptr =&age;
//     int _age =*ptr;

//     printf("%d", _age);
//     return 0;

// } 

// int main() {
//     int age =22;
//     int *ptr = &age;

    // address
    // printf("%p\n",& age);
    // printf("%u\n",& age);
    // printf("%u\n",ptr);
    // printf("%u\n",&ptr);
    
    // value
//     printf("%d\n",age);
//     printf("%d\n",*ptr);
//     printf("%d\n",*(&age));

//     return 0;

// }
// int main(){
//     int x;
//     int *ptr;

//     ptr = &x;
//     *ptr =0;    //x=0

//     printf("x=%d\n", x);
//     printf("*ptr =%d\n",*ptr);

//     return 0;
// } 


// call by value
// void swap(int a, int b){
//     int t= a;
//     a= b;
//     b=t;
//     printf("a= %d & b=%d\n",a ,b);
// }
// int main() {
//     int x= 3, y= 5;
//     swap(x,y);
//     printf("x=%d & y=%d\n",x, y);
//     return 0;
// }

void dowork(int a,int b, int *sum ,int *prod, int *avg){
    *sum = a+b;
    *prod = a*b;
    *avg =(a+b)/2;
}
int main(){
    int a= 3, b=5;
    int sum,prod ,avg;
    dowork(a,b, &sum, & prod ,& avg);
    printf("sum =%d, prod =%d,avg =%d\n", sum,prod ,avg);
    return 0;
}