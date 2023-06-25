#include <stdio.h>
struct node
{
    int dist[20];
    int from[20];
} rt[10];
int main()
{
    int costmatrix[20][20];
    int nodes, i, j, k, count = 0;
    printf("\nEnter the number of nodes : ");
    scanf("%d", &nodes);
    printf("\nEnter the cost matrix :\n");
    for (i = 0; i < nodes; i++)
    {
        for (j = 0; j < nodes; j++)
        {
            scanf("%d", &costmatrix[i][j]);
            costmatrix[i][i] = 0;
            rt[i].dist[j] = costmatrix[i][j]; // initialize the distance equal to cost matrix

                rt[i]
                    .from[j] = j; // initialize the source node
        }
    }
    do
    {
        count = 0;
        for (i = 0; i < nodes; i++)
        {
            for (j = 0; j < nodes; j++)
            {
                for (k = 0; k < nodes; k++)
                {
                    if (rt[i].dist[j] > costmatrix[i][k] + rt[k].dist[j])
                    {

                        rt[i].dist[j]=rt[i].dist[k]+rt[k].dist[j];
                        rt[i].from[j]=k;
                        count++;
                    }
                }
            }
        }
    }while (count != 0);

    for (i = 0; i < nodes; i++)
    {
        printf("\n\nFor router %d\n", i + 1);
        for (j = 0; j < nodes; j++)
        {
            printf("\t\nnode %d via %d Distance %d ",j+1,rt[i].from[j]+1,rt[i].dist[j]);
        }
    }
    printf("\n\n");
}