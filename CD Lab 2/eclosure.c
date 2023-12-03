#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int n,m = 0;
char a[10][10],f[10];

void eclosure(char c) {
    int i;
    for(i=0;i<n;i++) {
        if(a[i][0]==c && a[i][1]=='e'){
            f[m] = a[i][2];
            m++;
            eclosure(a[i][2]);
        }
    }
}

int main() {
    int i,z;
    char c,ch;
    printf("Enter the no of transitions = ");
    scanf("%d", &n);

    printf("Enter the transitions\n");
    for(i=0;i<n;i++) {
        scanf("%s%c",a[i],&ch);

        if(strlen(a[i])==2 && a[i][1]=='e') {
            a[i][2] = '\0';  
            ch = getchar();  
        }
    }

    do{
        m = 0;
        printf("Enter the state whose e-closure to be found : ");
        scanf("%c",&c);

        printf("e-closure(%c) = { %c ",c,c);
        eclosure(c);
        for(i=0;i<m;i++) {
            printf("%c ",f[i]);
        }
        printf("}\n");
        strcpy(f," ");

        printf("Continue(0/1) = ");
        scanf("%d%c", &z, &ch);
    }while(z==1);

    return 0;
}