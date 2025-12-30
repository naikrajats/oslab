//SJF Program without Arrival Time
#include<stdio.h>
int main()
{
//Variable declarations
int n,p[20],bt[20],pr[20],wt[20],tat[20],i,j,temp,pos;
float avwt=0,avtat=0;
//Input from user for the program n: No.of Process, at: Arrival Time bt: Burst Time etc..
printf("Enter total number of processes(maximum 20): ");
scanf("%d",&n);
printf("\nEnter the Process Burst Time and Priority:\n");
for(i=0;i<n;i++)
{
	printf("P[%d]: ",i+1);
	scanf("%d%d",&bt[i],&pr[i]);
	p[i]=i+1;
}
//Priority based Logic for sorting process as per their Priority(Highest Priority first)
for(i=0;i<n;i++)
{ 
	pos=i;
	for(j=i+1;j<n;j++)
	{ 
		if(pr[j]<pr[pos])
		pos=j;
	}
	temp=bt[i];
	bt[i]=bt[pos];
	bt[pos]=temp;
	temp=p[i];
	p[i]=p[pos];
	p[pos]=temp;
	temp=pr[i];
	pr[i]=pr[pos];
	pr[pos]=temp;
}

//Code for calculating the waiting time of each process
wt[0]=0;
for(i=1;i<n;i++)
{
	wt[i]=0;
	for(j=0;j<i;j++)
		wt[i]+=bt[j];
}
printf("\nProcess\t\tBurst Time\tWaiting Time\tTurnaround Time");
//code for calculating turnaround time
for(i=0;i<n;i++)
{
tat[i]=bt[i]+wt[i];
avwt+=wt[i];
avtat+=tat[i];
printf("\nP[%d]\t\t\t%d\t\t\t\t%d\t\t\t\t%d",p[i],bt[i],wt[i],tat[i]);
}
avwt/=n;
avtat/=n;
printf("\n\nAverage Waiting Time:%f",avwt);
printf("\nAverage Turnaround Time:%f",avtat);
return 0;
}