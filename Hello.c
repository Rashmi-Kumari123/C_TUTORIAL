#include<stdio.h>

// int main(int argc, char const *argv[])
// {
//     printf("Hello world");
//     return 0;
// }

// int main(){
    // int number =25;
    // printf("number is %d. \n", number);
    
    // return 0;
    // char star ='*';
    // printf("star is %c. \n" ,star);
    // return 0;

    // int age =22;
    // age =24;
    // printf(" age is %d.\n" , age);
    // return 0;

    // float pi =3.14;
    // printf("value of pi is %f\n" , pi);
    // return 0;

    // char hashtag ='#'; 

    // int a= 20;
    // int A=30;
    // int _age =17; 

    // int final_price =100;
    // return 0;
// }
// int main() {


//     printf("Hello world!  C\n");
//     printf("Hello C\n");
//     printf("Hello C\n");
//     printf("Hello C\n");
//     char star = '*' ;
//     printf("star is %c \n" ,star);
//     return 0;
// }

// int main() {
//     int age;
//     printf("enter age");
//     scanf("%d" , & age);
//     printf("age is : %d",age );
//     return 0;
// }
// int main(){
//     int a, b;
//     printf("enter a");
//     scanf("%d" ,& a);

//     printf("enter b");
//     scanf("%d" ,& b);

//     int sum=a+b;
//     printf("sum is : %d" ,sum);
//     return 0;


//  }

// area of circle
// int main() {
//     int radius;
//     printf("Enter radius: ");
//     scanf("%d", &radius);   

//     printf("Area is : %f\n", 3.14 * radius * radius);
//     return 0;
// }
// #include<math.h>
// int main (){
//     int b,c ;
//     b=c=1;
//     int a=b+c;
//     int power =pow(b,c);
//     printf("%d",power);
//     return 0;

// }
// int main() {
//     printf("%d",16% 10);
//     return 0;
// }
// int main(){
//     int a =(int) 1.999999;
//     printf("%d\n",a);
//     return 0;
// }
// int main(){
//     int x;
//     printf("enter a number :");
//     scanf("%d" ,&x);
//     printf("%d", x% 2==0);
//     return 0;
// }

// int main(){
//     int age;
//     printf("enter age:");
//     scanf("%d",&age);

//     if (age >18){
//         printf("adult\n");
//         printf("they can vote\n");
//         printf("they can drive\n");
        
//     }
//     else{
//         printf(" not adult\n");
//         return 0;
//     }
// }   
// int main(){

//     int age;
//     printf("enter age :");
//     scanf("%d" ,&age);
//     age >= 18 ? printf("adult \n"): printf(" notadult \n");
//     return 0;
// }
void namaste();
void bonjour();

int main(){
    printf("enter f for french & i for indian:");
    char ch;
    scanf("%c", & ch);

    if (ch =='i'){
        namaste();
    }else{
        bonjour();
    }
    
    return 0;
}

void namaste(){
    printf("Namaste\n");
}

void bonjour(){
    printf("Bonjour\n");
}
























