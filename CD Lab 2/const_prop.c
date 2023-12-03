#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

struct exp{
    char op[2],arg1[5],arg2[5],res[5];
    int flag;
}arr[10];
int n;

void change(int p,char *res){
    for(int i=p+1;i<n;i++){
        if(strcmp(arr[p].res,arr[i].arg1)==0){
            strcpy(arr[i].arg1,res);
        }
        if(strcmp(arr[p].res,arr[i].arg2)==0){
            strcpy(arr[i].arg2,res);
        }
    }
}

int main(){
    int i,arg1,arg2,res;
    char op,res1[5];

    printf("Enter the no of expressions = ");
    scanf("%d",&n);
    printf("Enter the expressions\n");
    for(i=0;i<n;i++){
        scanf("%s%s%s%s",arr[i].op,arr[i].arg1,arr[i].arg2,arr[i].res);
        arr[i].flag = 0;
    }

    for(i=0;i<n;i++){
        if(isdigit(arr[i].arg1[0]) && isdigit(arr[i].arg2[0]) || strcmp(arr[i].op,"=")==0){
            op = arr[i].op[0];
            arg1 = atoi(arr[i].arg1);
            arg2 = atoi(arr[i].arg2);

            switch(op){
                case '+' : res = arg1+arg2; break;
                case '-' : res = arg1-arg2; break;
                case '*' : res = arg1*arg2; break;
                case '/' : res = arg1/arg2; break;
                case '%' : res = arg1%arg2; break;
                case '=' : res = arg1; break;
                default : break;
            }
            arr[i].flag = 1;
            sprintf(res1,"%d",res);
            change(i,res1);
        }
    }

    printf("Optimized code\n");
    for(i=0;i<n;i++){
        if(arr[i].flag == 0){
            printf("%s %s %s %s\n",arr[i].op,arr[i].arg1,arr[i].arg2,arr[i].res);
        }
    }
    return 0;
}