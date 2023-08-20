#include <stdio.h>

// cost - cost or hops needed to move from one node to another
// routingtable[i].dist[j] = cost[i][j] = distance from i to j
// routingtable[i].from[j]. It indicates that the next-hop node to reach destination node j from source node i is node j itself.

struct node{
    int from[10];
    int dist[10];
}routingtable[10];

void main(){
    int n, cost[10][10], count = 0;

    printf("Enter the number of nodes: ");
    scanf("%d", &n);
    printf("Enter the cost:\n");
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            scanf("%d",&cost[i][j]);
            cost[i][i] = 0;
            routingtable[i].dist[j] = cost[i][j];
            routingtable[i].from[j] = j;
    }}

    do{
        count = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                for (int k = 0; k < n; k++){
                    if (routingtable[i].dist[j] > cost[i][k] + routingtable[j].dist[k]){
                        routingtable[i].dist[j] = cost[i][k]+routingtable[j].dist[k];
                        routingtable[i].from[j] = k;
                        count++;
                    }
                }
    } while (count!=0);

    for (int i = 0; i < n; i++){
        printf("\n");
        printf("\nRouting table of %d\n-----------------\nfrom  |\tto  |\tdist\n-----------------\n",i);
        for (int j = 0; j < n; j++){
            printf("%d\t%d\t%d\n",i,j,routingtable[i].dist[j]);
        }
    } 
}