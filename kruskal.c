#include<stdio.h>
int graph[10][10],n,d,w;
struct edge
{
    int v1;
    int v2;
    int wt;
};
struct edge ed[50];
struct edge span[50];
void merge_edges(int low,int mid,int high)
{
    int i=low,j=mid+1,k=0;
    struct edge b[high-low+1];

    while(i<=mid && j<=high)
    {
        if(ed[i].wt<=ed[j].wt)
        {
            b[k++]=ed[i++];
        }
        else
        {
            b[k++]=ed[j++];
        }
    }
    while(i<=mid)
    {
        b[k++]=ed[i++];
    }
    while(j<=high)
    {
        b[k++]=ed[j++];
    }
    k=0;
    for(int a=low;a<=high;a++)
    {
        ed[a]=b[k++];
    }
}

void mergeSort_edges(int low,int high)
{
    if(low<high)
    {
        int mid=(low+high)/2;
        mergeSort_edges(low,mid);
        mergeSort_edges(mid+1,high);
        merge_edges(low,mid,high);
    }
}
int find(int visited[],int vn)
{
    return(visited[vn]);
}
int applyunion(int visited[],int c1,int c2)
{
    int i;
    for(i=0;i<n;i++)
    {
        if(visited[i]==c2)
        {
            visited[i]=c1;
        }
    }
}
void kruskal(int k)
{
    mergeSort_edges(0,k-1);
    int visited[10];
    int i,j;
    for(i=0;i<k;i++)
    {
        visited[i]=i;
    }
    int sapn=0;
    for(i=0;i<k;i++)
    {
        int c=find(visited,ed[i].v1);
        int d=find(visited,ed[i].v2);
        if(c!=d)
        {
            span[sapn]=ed[i];
            sapn=sapn+1;
            applyunion(visited,c,d);
        }
    }
}
void print(int k)
{
    int i,cost=0;
    for(i=0;i<n-1;i++)
    {
        printf("\n %d -%d :%d",span[i].v1,span[i].v2,span[i].wt);
        cost=cost+span[i].wt;
    }
    printf("\n the spanning tree cost is %d",cost);
}
int main()
{
    int i,j,k=0;
    FILE *fp;
    fp=fopen("graph.txt","r");
    if(fp==NULL)
    {
        printf("error to open the file");
    }
    fscanf(fp,"%d",&n);
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            fscanf(fp,"%d",&graph[i][j]);
        }
    }
    fclose(fp);
    for(i=0;i<n;i++)
    {
        for(j=i;j<n;j++)
        {
            if(graph[i][j]>=1)
            {
                ed[k].v1=i;
                ed[k].v2=j;
                ed[k].wt=graph[i][j];
                k++;
            }
        }
    }
    printf("\n the total number of edge =%d",k);
    kruskal(k);   
    print(k); 
}   