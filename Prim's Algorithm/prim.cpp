#include <iostream>
#define INF 10000
using namespace std;

struct HNode
{
  int key;
  int label;
};  

class Heap
{
  HNode* h;
  int pos, size;
  int* position;
public:
  Heap(int n)
  {
    pos=n;
    size=n;
    h=new HNode[n];
    position=new int[n];
    for(int i=0; i<n; i++)
      {
	h[i].key=i;
	h[i].label=INF;
	position[i]=i;
      }
  }

  int empty()
  {
    if(pos==0)
      {
	return 1;
      }
    else
      {
	return 0;
      }
  }
  
  int parent(int i)
  {
    return (((i+1)/2)-1);
  }

  void swap(int* a, int* b)
  {
    *a=*a+*b;
    *b=*a-*b;
    *a=*a-*b;
  }
  
  void insert(int x, int k)
  {
    h[pos].key=x;
    h[pos].label=k;
    pos=pos+1;
    int i=pos-1;
    position[x]=i;
    while(i>0 && h[i].label<h[parent(i)].label)
      {
	swap(&h[i].key, &h[parent(i)].key);
	swap(&h[i].label, &h[parent(i)].label);
	position[h[i].key]=i;
	position[h[parent(i)].key]=parent(i);
	i=parent(i);
      }
  }

  void heapify(int root)
  {
    int min=root;
    if(((2*root)+1)<pos && h[(2*root)+1].label<h[min].label)
      {
	min=(2*root)+1;
      }
    if(((2*root)+2)<pos && h[(2*root)+2].label<h[min].label)
      {
	min=(2*root)+2;
      }
    if(min!=root)
      {
	swap(&h[root].key, &h[min].key);
	swap(&h[root].label, &h[min].label);
	heapify(min);
      }
    position[h[root].key]=root;
    position[h[min].key]=min;
  }

  HNode extractmin()
  {
    HNode temp=h[0];
    position[h[0].key]=-1;
    h[0].key=h[pos-1].key;
    h[0].label=h[pos-1].label;
    pos=pos-1;
    heapify(0);
    return temp;
  }

  void deckey(int x, int l)
  {
    int i=position[x];
    if(h[i].label<l)
      {
	return;
      }
    h[i].label=l;
    while(i>0 && h[i].label<h[parent(i)].label)
      {
	swap(&h[i].key, &h[parent(i)].key);
	swap(&h[i].label, &h[parent(i)].label);
	position[h[i].key]=i;
	position[h[parent(i)].key]=parent(i);
	i=parent(i);
      }
  }
  
  void display()
  {
    for(int i=0; i<pos; i++)
      {
	cout<<h[i].key<<","<<h[i].label<<" ";
      }
    cout<<endl;
    cout<<"Positions"<<endl;
    for(int i=0; i<size; i++)
      {
	cout<<position[i]<<" ";
      }
    cout<<endl;
  }
};

struct Node
{
  int data;
  int weight;
  Node* next;
};

Node* Graph;

void vlist(int n)
{
  Graph=new Node[n];
  for(int i=0; i<n; i++)
    {
      Graph[i].data=i;
      Graph[i].weight=0;
      Graph[i].next=NULL;
    }
}

void addedge(int u, int v, int w)
{
  Node* temp=new Node;
  temp->data=v;
  temp->weight=w;
  temp->next=Graph[u].next;
  Graph[u].next=temp;
}

void display(int n)
{
  for(int i=0; i<n; i++)
    {
      Node* temp=Graph+i;
      while(temp!=NULL)
	{
	  cout<<((temp->data)+1)<<"("<<temp->weight<<")"<<"->";
	  temp=temp->next;
	}
      cout<<endl;
    }
}

int prim(int n)
{
  int* visited=new int[n];
  int w=0;
  for(int i=0; i<n; i++)
    {
      visited[i]=0;
    }
  Heap h(n);
  h.deckey(0,0);
  while(!h.empty())
    {
      HNode m=h.extractmin();
      visited[m.key]=1;
      w=w+m.label;
      Node* temp=&Graph[m.key];
      cout<<(m.key+1)<<"("<<m.label<<")"<<" ";
      temp=temp->next;
      while(temp!=NULL)
	{
	  if(visited[temp->data]==0)
	    {
	      h.deckey(temp->data, temp->weight);
	    }
	  temp=temp->next;
	}
    }
  cout<<endl;
  return w;
}

int main()
{
  int n, e, u, v, w, mstw;
  cout<<"Enter the number of vertices"<<endl;
  cin>>n;
  vlist(n);
  cout<<"Enter the number of edges"<<endl;
  cin>>e;
  cout<<"Enter the edges"<<endl;
  for(int i=0; i<e; i++)
    {
      cin>>u>>v>>w;
      u=u-1;
      v=v-1;
      addedge(u, v, w);
      addedge(v, u, w);
    }
  display(n);
  cout<<"Minimum spanning tree by applying Prim's algorithm"<<endl;
  mstw=prim(n);
  cout<<"Weight of the minimum spanning tree="<<mstw<<endl;
  return 0;
}

