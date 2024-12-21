#include<stdio.h>

// int main(){
//     char day; //m-mon;t-tues; w-wed; T; f; s;  S
//     printf("enter day(1-7):");
//     scanf("%d",& day);

//     switch (day) {
//         case 1  : printf("monday \n");
//                  break;
//         case 2  : printf("tuesday \n");
//                  break;
//         case 3  : printf("wednesday \n");
//                  break;
//         case 4  : printf("thursday \n");
//                  break;
//         case 5 : printf("friday \n");
//                  break;
//         case 6  : printf("saturday \n");
//                  break;
//         case 7  : printf("sunday \n");
//                  break;         

//         default : printf("not a valid day! \n");
//     }
//         return 0;
//     }

    int main(){
        int number;
        printf("enter number:");
        scanf("%d", & number);

        if (number >= 0){
            printf("positive\n");
            if (number % 2 ==0){
                printf("even\n");

            }else{
                printf("odd \n");
            }

        }else {
            printf("negative no \n");
        }
        return 0;
    }

  int  main(){
    int marks;
    printf("enter number(0-100):");
    scanf("%d", & marks);

    if (marks >= 0 && marks <=30){
        printf("FAIL \n");

    }else if (marks> 30 && marks <=100){
        printf("PASS\n");
    }else {
        printf("wrong marks");
    }
    marks <= 30 ? printf("fail\n"): printf("PASS\n");
   
    if(marks < 30){
        printf("C\n");
    }
    else if(marks >= 30 && marks < 70){
        printf("B\n");
    }
    else if(marks >= 70 && marks< 90) {
        printf("A \n");
    }
    else{
        printf("A+\n");
    } 



    return 0;
  }

   
int main()  { 
    char ch;
    printf("enter character:");
    scanf("%c" , & ch);

    if (ch >='A' && ch <= 'Z'){
        printf("upper case \n");
    }
    else if(ch >= 'a' && ch <= 'z'){
        printf("lower case\n");

    }
    else{
        printf("not english letter\n");

    }
    return 0;   
}    
  
float convertTemp(float celsius);

int main(){
    float far= convertTemp(37);
    printf("far : %f", far);
    return 0;
}

float convertTemp(float celsius){
    float far = celsius *(9.0/5.0)+32;
    return far;
}









    
    
    