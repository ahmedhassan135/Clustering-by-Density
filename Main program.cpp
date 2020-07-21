#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>

using namespace std;
//Function Declaration
int getNoOfEdges();
int getNoOfNodes();
double density(int, int);
double clusterProperty(int, int, double);

struct edges
{
	int val=0;
	int weight=0;
};

struct node
{
	int index=0;
	int degree=0;
	int weight=0;
};
int maxWeightIndex(node *,int);
int maxDegreeIndex(node *,int);

int maxWeight(node *,int);
int maxDegree(node *,int);

void sortPriorityW(node *x,int size);
void sortPriorityD(node *x,int size);
//Globally Declared Matrix
edges G[6][6];                  //In the actual dataset the array size will be huge and takes hours to work. This takes a very small sample to demonstrate that the program works
edges G_[6][6];
//Driver Function
int main()
{
    int n=getNoOfNodes();
	int e=getNoOfEdges();
	node nodes[n];
	node nodes_[n];

	ifstream file("Temp.txt");
	int x1,x2;
	float w;
	while(file>>x1)
	{
		file>>x2;
		file>>w;
		G[x1-1][x2-1].val=1;
		G[x1-1][x2-1].weight=w;
		G[x2-1][x1-1].val=1;
		G[x2-1][x1-1].weight=w;
	}
	file.close();

	//finding weight of edges
	cout<<"Finding Weight ... "<<endl;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			G[i][j].weight=0;

			if(i==j)
			continue;

			for(int k=0;k<n;k++)
			{
				G[i][j].weight+=(G[i][k].val*G[k][j].val);
			}
		}
	}
	cout<<endl;
	//Assigning degree and weight of the nodes
	cout<<"Assigning degree and weight ... "<<endl;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			nodes[i].index=i;
			nodes[i].degree+=G[i][j].val;
			nodes[i].weight+=G[i][j].weight;
		}
	}
	double d_=0.0,d=1.0,cp_=0.0,cp=1.0;
	cout<<"\nEnter a threshold density(0<=d<=1): ";
	cin>>d_;
	cout<<"Enter a threshold cluster property(0<=cp<=1) ";
	cin>>cp_;
	int max_w,max_d,i_w,i_d;
	int noOfFile=1;
	cout<<endl;
	do
	{
	int noOfNodes=0,noOfEdges=0;
	max_w=maxWeight(nodes,n);
	max_d=maxDegree(nodes,n);
	i_w=maxWeightIndex(nodes,n);
	i_d=maxDegreeIndex(nodes,n);

	//Priority nodes
	node temp[n];
	for(int i=0;i<n;i++)
	{
			if(i==i_w)
			continue;
			//Initializing zero if not already zero
			temp[i].index=temp[i].degree=temp[i].weight=0;

			temp[i].degree=nodes[i].degree;
			temp[i].weight=nodes[i].weight;
			temp[i].index=i;
	}
	if(max_w>0)
	{
		sortPriorityW(temp,n);
		nodes_[i_w]=nodes[i_w];
		nodes[i_w].index=nodes[i_w].degree=nodes[i_w].weight=0;
		int check=0;
		noOfNodes++;
		do
		{
			for(int i=0;i<n;i++)
			{
				int index=temp[i].index;
				check++;
				if(G[i_w][index].val==1)
				{
					noOfNodes++;
					int e=0;
					nodes_[index]=nodes[index];

					for(int i=0;i<n;i++)
					{
						if(G[nodes_[index].index][i].val==1 and nodes_[i].weight!=0)
						{
							e++;
						}
					}
					noOfEdges+=e;
					d=density(noOfEdges,noOfNodes);
					cp=clusterProperty(e,noOfNodes-1,d);
					if(d>=d_ and cp>=cp_)
					{
						for(int i=0;i<n;i++)
						{
							if(G[nodes_[index].index][i].val==1 and nodes_[i].weight!=0)
							{
								G_[nodes_[index].index][i]=G[nodes_[index].index][i];
								G_[i][nodes_[index].index]=G[i][nodes_[index].index];
							}
						}
					}
					else
					{
						nodes_[index].weight=0;
						nodes_[index].degree=0;
						nodes_[index].index=0;
						noOfEdges-=e;
						noOfNodes--;
					}
				}
			}
		}while(d>d_ and check!=n);
		for(int i=0;i<n;i++)
		{
			if(nodes_[i].weight!=0)
			{
				nodes[i].weight=nodes[i].degree=nodes[i].index=0;
			}
			for(int j=0;j<n;j++)
			{
				if(nodes_[i].weight!=0)
				{
					G[i][j].val=G[i][j].weight=0;
					G[j][i].val=G[j][i].weight=0;
				}
			}
		}
	}
	else if(max_d>0)
	{
		sortPriorityD(temp,n);
		nodes_[i_d]=nodes[i_d];
		nodes[i_d].index=nodes[i_d].degree=nodes[i_d].weight=0;
		int check=0;
		noOfNodes++;
		do
		{
			for(int i=0;i<n;i++)
			{
				int index=temp[i].index;
				check++;
				if(G[i_d][index].val==1)
				{
					noOfNodes++;
					int e=0;
					nodes_[index]=nodes[index];

					for(int i=0;i<n;i++)
					{
						if(G[nodes_[index].index][i].val==1 and nodes_[i].weight!=0)
						{
							e++;
						}
					}
					noOfEdges+=e;
					d=density(noOfEdges,noOfNodes);
					cp=clusterProperty(e,noOfNodes-1,d);
					if(d>=d_ and cp>=cp_)
					{
						for(int i=0;i<n;i++)
						{
							if(G[nodes_[index].index][i].val==1 and nodes_[i].weight!=0)
							{
								G_[nodes_[index].index][i]=G[nodes_[index].index][i];
								G_[i][nodes_[index].index]=G[i][nodes_[index].index];
							}
						}
					}
					else
					{
						nodes_[index].weight=0;
						nodes_[index].degree=0;
						nodes_[index].index=0;
						noOfEdges-=e;
						noOfNodes--;
					}
				}
			}
		}while(d>d_ and check!=n);
		for(int i=0;i<n;i++)
		{
			if(nodes_[i].weight!=0)
			{
				nodes[i].weight=nodes[i].degree=nodes[i].index=0;
			}
			for(int j=0;j<n;j++)
			{
				if(nodes_[i].weight!=0)
				{
					G[i][j].val=G[i][j].weight=0;
					G[j][i].val=G[j][i].weight=0;
				}
			}
		}
	}
	//Creating the file of the Cluster
	string filename="\0";
	ofstream files;
	stringstream a;
	a<<noOfFile;
	filename = "Clusters/Cluster#" + a.str();
    filename += ".txt";
    files.open(filename.c_str(), ios::out);
    files<<"Cluster: \n";
    bool c=false;
	for(int i=0;i<n;i++)
	{
		for(int j=i+1;j<n;j++)
		{
			if(G_[i][j].val==1)
			{
				files<<i+1<<"\t"<<j+1<<"\t"<<G_[i][j].weight<<endl;
				c=true;
			}
			G_[i][j].val=G_[i][j].weight=0;
		}
	}
	for(int i=0;i<n;i++)
	{
		if(!c && nodes_[i].weight!=0 and nodes_[i].degree!=0)
		{
			files<<nodes_[i].index<<"\tNo Connection\n";
		}
		nodes_[i].index=nodes_[i].degree=d=nodes_[i].weight=0;
	}
	files.close();

	cout<<"Clusters Created: "<<noOfFile<<endl;
	max_w=maxWeight(nodes,n);
	max_d=maxDegree(nodes,n);
	noOfFile++;
	}while(max_w>0 || max_d>0);
	cout<<"\nMATRIX: \n\nNodes: \n";
	for(int i=0;i<n;i++)
	{
		if(nodes[i].index==0 && (nodes[i].weight==0 or nodes[i].degree==0))
		cout<<nodes_[i].index<<endl;
		else
		cout<<nodes_[i].index+1<<endl;
	}
	cout<<"\nConnection: \n";
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			cout<<G[i][j].val<<" ";
		}
		cout<<endl;
	}
	return 0;
}
//Functions Definitions
int maxWeightIndex(node *n,int no)
{
	int max=n[0].weight,index=0;
	for(int i=0;i<no;i++)
	{
		if(max<n[i].weight)
		{
			max=n[i].weight;
			index=i;
		}
	}
	return index;
}
int maxDegreeIndex(node *n,int no)
{
	int max=n[0].degree,index=0;
	for(int i=0;i<no;i++)
	{
		if(max<=n[i].degree)
		{
			max=n[i].degree;
			index=i;
		}
	}
	return index;
}
int maxWeight(node *n,int no)
{
	int max=n[0].weight;
	for(int i=0;i<no;i++)
	{
		if(max<n[i].weight)
		{
			max=n[i].weight;
		}
	}
	return max;
}
int maxDegree(node *n,int no)
{
	int max=n[0].degree,index=0;
	for(int i=0;i<no;i++)
	{
		if(max<=n[i].degree)
		{
			max=n[i].degree;
		}
	}
	return max;
}
int getNoOfNodes()
{
	ifstream file("Temp.txt");
	int x1,x2,max=0;
	float w;
	while(file>>x1)
	{
		file>>x2;
		file>>w;
		if(x1>max)
		max=x1;
		if(x2>max)
		max=x2;
	}
	file.close();
	return max;
}
int getNoOfEdges()
{
	ifstream file;
	file.open("Temp.txt");
	int e=0,i;
	float x;
	while(file>>i)
	{
		file>>i;
		file>>x;
		e++;
	}
	file.close();
	return e;
}
void sortPriorityW(node x[],int size)
{
	for(int i=0;i<size;i++)
	{
		for(int j=0;j<size;j++)
		{
			if(x[i].weight>x[j].weight)
			{
				node temp;
				temp=x[i];
				x[i]=x[j];
				x[j]=temp;
			}
		}
	}
}
void sortPriorityD(node x[],int size)
{
	for(int i=0;i<size;i++)
	{
		for(int j=0;j<size;j++)
		{
			if(x[i].degree>x[j].degree)
			{
				node temp;
				temp=x[i];
				x[i]=x[j];
				x[j]=temp;
			}
		}
	}
}
double clusterProperty(int Ec, int Nc, double d)
{
	if(Nc==0 or d==0)
	return 0.0;

	return Ec/(d*Nc);
}
double density(int e, int n)
{
	if(n<2)
	return 0;

	return (e*2.0)/(n*(n-1.0));
}
