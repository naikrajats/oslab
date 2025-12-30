//FCFS Program with Arrival Time
#include<stdio.h>
int main()
{
//Variable declarations
int n,p[20],at[20],bt[20],wt[20],tat[20],i,j;
float avwt=0,avtat=0;
//Input from user for the program n: No.of Process, at: Arrival Time bt: Burst Time etc..
printf("Enter total number of processes(maximum 20): ");
scanf("%d",&n);
printf("\nEnter the Process Arrival Time and Burst Time:\n");
for(i=0;i<n;i++)
{
	printf("P[%d]: ",i+1);
	scanf("%d%d",&at[i],&bt[i]);
	p[i]=i+1;
}

//Code for calculating the waiting time of each process
wt[0]=0;
for(i=1;i<n;i++)
{
	wt[i]=0;
	for(j=0;j<i;j++)
		wt[i]+=bt[j];
	wt[i]-=at[i];
}
printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time");
//code for calculating turnaround time
for(i=0;i<n;i++)
{
tat[i]=bt[i]+wt[i];
avwt+=wt[i];
avtat+=tat[i];
printf("\nP[%d]\t%d\t\t\t\t%d\t\t\t\t%d\t\t\t\t%d",p[i],at[i],bt[i],wt[i],tat[i]);
}
avwt/=n;
avtat/=n;
printf("\n\nAverage Waiting Time:%f",avwt);
printf("\nAverage Turnaround Time:%f",avtat);
return 0;
}