#include<stdio.h>
#include<string.h>
#include<ctype.h>

char input[10];
int i, error;
void E();
void T();
void E_dash();
void T_dash();
void F();

int main(){
    i = 0;
    error = 0;
    printf("The Grammar implemented in this code\n E -> T E' \n E' -> + T E' | ε \n T -> F T' \n T' -> * F T' | ε \n F -> id | ( E ) \n");
    printf("Enter an arithmetic expression (either use numbers or single alphabets) : ");
    gets(input);

    E(); //first call the starting symbol
    if(strlen(input) == i && error == 0){
        printf("Accepted\n");
    }else{
        printf("Rejected\n");
    }

    return 0;
}

void E(){
    // E -> T E'
    T();
    E_dash();
}

void E_dash(){
    // E' -> + T E'
    if (input[i] == '+'){
        i++;
        T();
        E_dash();
    }
}

void T(){
    // T -> F T'
    F();
    T_dash();
}

void T_dash(){
    // T' -> * F T'
    if(input[i] == '*'){
        i++;
        F();
        T_dash();
    }
}

void F(){
    if(isalnum(input[i])){
        // F -> id 
        // Here id can be alpha-numeric
        i++;
    }else if(input[i] == '('){
        // F -> ( E )
        i++;
        E();
        if(input[i] == ')'){
            i++;
        }else{
            error = 1;
        }
    }else{
        error = 1;
    }
}