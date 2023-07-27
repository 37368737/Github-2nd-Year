//W.G. Kotzee
//REII 211 PRAK 2 DIJIKSTRAS ALGORITHM
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define INFINITY 9999
#define MAX 20

void dijkstrafunc(int matrix[MAX][MAX],int n,int startnode, int stopnode);  //dijkstra algorithm
int arr[MAX];
int count=0;

int main()
{
   int matrix[MAX][MAX]; //initializing 2d array
   int i,j,n;
   char a;
   char b;

   printf("Enter the number of vertices:");
   scanf(" %d",&n);

   printf("\nEnter the initial vertex: ");
   scanf(" %c",&a);

   printf("\nEnter the goal vertex: ");
   scanf(" %c",&b);

   printf("\nEnter the adjacency matrix: \n");
   for(i=1;i<=n;i++)
       for(j=1;j<=n;j++)
           scanf("%d",&matrix[i][j]);
    int c = a-64;                                       //Change
    int d = b-64;

   dijkstrafunc(matrix,n,c,d);

   return 0;
}

void dijkstrafunc(int matrix[MAX][MAX],int n,int startnode, int stopnode)
{

   int cost[MAX][MAX];
   int distance[MAX];
   int previous[MAX];                                                          //previous stores the best value of each node
   int visited[MAX];                                                           //previos cost value of node
   int tel;                                                                    //tel gives all the nodes visited
   int MinnimumDistance;                                                       //minimum distance works with next node to get minimum distance of nodes
   int nextnode;                                                           //nextnode gives the node at minimum distance,
   int i,j;
                                                                               //creatiing the cost matrix
   for(i=1;i<=n;i++)
       for(j=1;j<=n;j++)

           if(matrix[i][j]==0)
               cost[i][j]=INFINITY;

           else
               cost[i][j]=matrix[i][j];
                                                                               // keeps track of all previos nodes, visited nodes, and weigths from the starting node
   for(i=1;i<=n;i++)
   {
       distance[i]=cost[startnode][i];
       previous[i]=startnode;
       visited[i]=0;
   }

   distance[startnode]=0;
   visited[startnode]=1;
   tel=1;

   while(tel<n-1)
   {
       MinnimumDistance=INFINITY;
                                                                               //volgendenode gives the node at minimum distance
       for(i=1;i<=n;i++)
           if(distance[i]<MinnimumDistance&&!visited[i])
           {
               MinnimumDistance=distance[i];
               nextnode=i;
           }
                                                                               //check if a better path exists
       visited[nextnode]=1;
       for(i=1;i<=n;i++)
           if(!visited[i])
               if(MinnimumDistance+cost[nextnode][i]<distance[i])
               {
                   distance[i]=MinnimumDistance+cost[nextnode][i];
                   previous[i]=nextnode;
               }
       tel++;
   }

        char e = startnode + 64;
        char f = stopnode + 64;
        printf("\nInitial vertex: %c",e);
        printf("\nGoal vertex: %c",f);

       if(i!=startnode)
       {


           j=stopnode;

           while(j!=startnode)
           {
                j=previous[j];
                arr[count]=j;
                count++;

           }


   }
    printf("\nShortest path cost: %d",distance[stopnode]);
   printf("\nShortest path route: ");
   for (int p=count-1;p>=0;p--)
   {
        char w = arr[p] +64 ;
      printf("%c",w);
   }
    char w = stopnode +64 ;
   printf("%c",w);
}
