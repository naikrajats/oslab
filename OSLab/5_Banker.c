#include<stdio.h>

 int allocated[15][15],max[15][15],need[15][15],avail[15],tres[15],work[15],finish[15];
 int pno,rno,i,j,prc,count,t,total;
 int sequence[10];
 int workold[15],allocatedold[15][15],maxold[15][15];

 void getdetails()
 {
 printf("\n Enter number of process:");
 scanf("%d",&pno);
 printf("\n Enter number of resources:");
 scanf("%d",&rno);
 for(i=1;i<=pno;i++)
 {
  finish[i]=0;
 }
 printf("\n Enter Max instances of each resources:\n");
 for(i=1;i<=rno;i++){
  printf(" %c :",(i+96));
  scanf("%d",&tres[i]);
 }
 
 printf("\n Enter Max resources for each process:\n\t");
 for(i=1;i<=rno;i++)
printf(" %c",(i+96));
printf("\n");
 for(i=1;i<=pno;i++)
 {
  printf("P[%d]\t:",i);
  for(j=1;j<=rno;j++){
   scanf("%d",&max[i][j]);
   maxold[i][j]=max[i][j];
  }
 }
 
 
 printf("\n Enter allocated resources for each process:\n\t");
  for(i=1;i<=rno;i++)
printf(" %c",(i+96));
printf("\n");
 for(i=1;i<=pno;i++)
 {
  printf("P[%d]\t:",i);
  for(j=1;j<=rno;j++){
   scanf("%d",&allocated[i][j]);
   //save for later
   allocatedold[i][j]=allocated[i][j];
   }
  }
 
 printf("\n available resources:\n");
 for(j=1;j<=rno;j++)
 {
  avail[j]=0;
  total=0;
  for(i=1;i<=pno;i++)
  {
   total+=allocated[i][j];
  }
  avail[j]=tres[j]-total;
  work[j]=avail[j];
  printf("     %d \t",work[j]);
  //save initial work/available for later use by resource request
  workold[j]=work[j];
 }
 
 }//end of getdetails
 
 
 void call_safety()
 {
     count=0;
     
	 do
 {
 
 
 
 for(i=1;i<=pno;i++)
 {
  for(j=1;j<=rno;j++)
  {
   need[i][j]=max[i][j]-allocated[i][j];
  }
 }
 
 printf("\n Allocated matrix        Max      need");
 for(i=1;i<=pno;i++)
 {
  printf("\n");
  for(j=1;j<=rno;j++)
  {
   printf("%4d",allocated[i][j]);
  }
  printf("|");
  for(j=1;j<=rno;j++)
  {
   printf("%4d",max[i][j]);
  }
   printf("|");
  for(j=1;j<=rno;j++)
  {
   printf("%4d",need[i][j]);
  }
 }
 
 //save values for resource request algorithm
 
 
 
  prc=0;
 
  for(i=1;i<=pno;i++)
  {
   if(finish[i]==0)
   {
    prc=i;
 
    for(j=1;j<=rno;j++)
    {
     if(work[j]< need[i][j])
     {
       prc=0;
       break;
     }
    }
   }
 
   if(prc!=0)
   break;
  }
 
  if(prc!=0)
  {
   printf("\n Process %d completed",i);sequence[count]=i;
   count++;
   printf("\n Available matrix:");
   for(j=1;j<=rno;j++)
   {
    work[j]+=allocated[prc][j];
    allocated[prc][j]=0;
    max[prc][j]=0;
    finish[prc]=1;
    printf("   %d",work[j]);
   }
  }
 
 }while(count!=pno&&prc!=0);
 
 if(count==pno)
  {
	printf("\n\nThe system is in a safe state!!\nSafe Sequence:\n");
  	for(i=0;i<count;i++)
		printf("P%d\t",sequence[i]);
	printf("\n");
 }
 else
  printf("\nThe system is in an unsafe state!!\n\n");
	 
 }//end of call safety
 
 
 
 void resource_request()
 {
     int rqp,rrq;
     for(i=1;i<=pno;i++)
     {
         for(j=1;j<=rno;j++)
         {
             allocated[i][j]=allocatedold[i][j];
             max[i][j]=maxold[i][j];
         }
     }
       for(j=1;j<rno;j++)
         {
             work[j]=workold[j];
         }

    
	 printf("enter the process number making a request\n");
	 scanf("%d",&rqp);
	 printf("enter the new request\n");
tryagain:	
 	for(i=1;i<=rno;i++)
	 {
		 printf(" %c :",(i+96));
		 scanf("%d",&rrq);
		 if(rrq>work[j]){
			 printf("cannot grant reqest as it exceeds work\n");
			 goto tryagain;
		 }
		 allocated[rqp][i]=allocated[rqp][i]+rrq;
	 }
	 call_safety();
		 
     
 }
 
 void main()
{
 int ch;

 getdetails(); 
 call_safety();
 printf("do you want to call resource request??\n");
 scanf("%d",&ch);
 if(ch==1)
 {
      resource_request();
 }
 //printf("Good Bye!!!\n");
}
