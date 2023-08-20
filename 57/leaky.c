#include <stdio.h>

void main(){
    int in[20], size, out, n, send, store =0;
    printf("Enter the bucket size: ");
    scanf("%d",&size);
    printf("Outgoing rate: ");
    scanf("%d",&out);
    printf("No of incoming packets: ");
    scanf("%d",&n);

    for (int i = 0; i < n; i++)
    {
        printf("\nSize of packet[%d]: ",i+1);
        scanf("%d",&in[i]);

        if (in[i]<=(size-store)){
            printf("%d bytes added to the bucket\n",in[i]);
            store += in[i];
            printf("Bucket space: %d/%d\n",store,size);
        }
        else{
            printf("Input size too high to accept...\n");
            int drop = in[i] - (size-store);
            store = size;
            printf("Dropped %d bytes\nBucket space full: %d/%d\n",drop,store,size);
        }
        if (store>=out){
            store-=out;
            send = out;
        }
        else{
            send = store;
            store = 0;
        }
        printf("%d bytes transmitted\n",send);
        printf("Bucket space: %d/%d\n",store,size);
    }
}