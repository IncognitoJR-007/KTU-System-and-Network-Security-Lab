#include<stdio.h>
int main()
{
    int n,TAT[10],WT[10],AT[10],BT[10],CT[10],totlalTAT=0,totalWT=0;
    float avgTAT=0,avgWT=0;
    printf("Enter the number of processes: ");
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        printf("Enter the arrival time of process %d: ",i+1);
        scanf("%d",&AT[i]);
        printf("Enter the burst time of process %d: ",i+1);
        scanf("%d",&BT[i]);
    }
    for(int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            if(BT[i]>BT[j])
            {
                int temp=BT[i];
                BT[i]=BT[j];
                BT[j]=temp;
                temp=AT[i];
                AT[i]=AT[j];
                AT[j]=temp;
            }
        }
    }
    CT[0]=AT[0]+BT[0];
    for(int i=1;i<n;i++)
    {
        CT[i]=CT[i-1]+BT[i];
    }
    for(int i=0;i<n;i++)
    {
        TAT[i]=CT[i]-AT[i];
        totlalTAT+=TAT[i];
        WT[i]=TAT[i]-BT[i];
        totalWT+=WT[i];
    }
    avgTAT=(float)totlalTAT/n;
    avgWT=(float)totalWT/n;
    printf("Process\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i=0;i<n;i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",i+1,AT[i],BT[i],CT[i],TAT[i],WT[i]);
    }
    printf("Average Turn Around Time: %f\n",avgTAT);
    printf("Average Waiting Time: %f\n",avgWT);
    printf("\t\t\t Gantt Chart \t\t\t\n");
    printf("0");
    for (int i = 0; i < n; i++)
        printf("  P%d  %d", i+1, TAT[i]);
    printf("\n");
    return 0;
}