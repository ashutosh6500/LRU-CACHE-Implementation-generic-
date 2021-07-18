#include <iostream>
#include <unordered_map>
using namespace std;

//Node Defination
template <typename T>
class Node
{
public:
    T data;
    Node <T> * next;
    Node <T> * prev;
    Node(){next=prev=NULL;}
};
//Class Defination
template <typename T>
class Doubly_List
{
public:
    Doubly_List();
    long long int N;    //Number of nodes
    long long int Page_Faults,Capacity;
    T Front();
    T Back();
    bool Empty();
    bool Full();
    long long int Search(T data);
    void Set_Capacity(long long int cap);
    void Insert(T data);
    void Print();
private:
    Node<T> * head;
    Node<T> * tail;
    unordered_map<T,long long int>mp;   //Mapping: {Data -> Position in LRU Structure(1 based indexing)}
};
template<typename T>
Doubly_List<T>:: Doubly_List()
{
    head=NULL;
    tail=NULL;
    N=0;
    Page_Faults=0;
}
template <typename T>
T Doubly_List<T>:: Front()
{
    return head->data;
}

template <typename T>
T Doubly_List<T>:: Back()
{
    return tail->data;
}

template <typename T>
bool Doubly_List<T>:: Empty()
{
    return (head==NULL);
}

template <typename T>
bool Doubly_List<T>:: Full()
{
    return (N==Capacity);
}

template <typename T>
long long int Doubly_List<T>:: Search(T data)
{
    return (mp[data] ? mp[data] : 0);
}

template <typename T>
void Doubly_List<T> :: Set_Capacity(long long int n)
{
    Capacity=n;
}

template <typename T>
void Doubly_List<T> :: Print()
{
    Node<T> * tmp=head;
    while(tmp!=NULL)
    {
        cout<<tmp->data<<" ";
        tmp=tmp->next;
    }
}

template <typename T>
void Doubly_List<T> :: Insert(T data)
{
    if(Search(data))
    {
        long long int pos=mp[data];
        if(pos!=Capacity)
        {
            long long int i=1;
            if(pos==1)
            {
                Node <T> * tmp=head;
                head=head->next;
                delete(tmp);
                Node<T> * newnode=new Node<T>();
                newnode->data=data;
                if(head==NULL)
                {
                    head=newnode;
                    tail=newnode;
                    mp[data]=1;
                }
                else
                {
                    tail->next=newnode;
                    newnode->prev=tail;
                    tail=newnode;
                    mp[data]=N+1;
                }
                return;
            }
            if(pos <= N/2) //Traverse from first
            {
                Node <T> * no=head;
                while(i != pos)
                {
                    no=no->next;
                    i++;
                }
                no->prev ->next=no->next ;
                no->next ->prev=no -> prev;
                delete(no);
            }
            else    //Traverse from last
            {
                pos=N-pos +1;
                 Node <T> * no=tail;
                while(i != pos)
                {
                    no=no->prev;
                    i++;
                }
                no->prev ->next=no->next ;
                no->next ->prev=no -> prev;
                delete(no);
            }
            Node<T> * newnode=new Node<T>();
            newnode->data=data;
            if(head==NULL)
            {
                head=newnode;
                tail=newnode;
                mp[data]=1;
            }
            else
            {
                tail->next=newnode;
                newnode->prev=tail;
                tail=newnode;
                mp[data]=N+1;
            }
        }
    }
    else
    {
        if(Full())
        {
            //LRU Structure is full,so its needed to replace with Least Recently Used data.
            mp.erase(head->data);
            mp[data]=Capacity;
            Node<T> * tmp=head;
            head=head->next;
            delete(tmp);
            Node<T> * newnode=new Node<T>();
            newnode->data=data;
            if(head==NULL)
            {
                head=newnode;
                tail=newnode;
            }
            else
            {
                tail->next=newnode;
                newnode->prev=tail;
                tail=newnode;
            }
            Page_Faults++;
        }
        else
        {
            //Insert at tail
            Node<T> * newnode=new Node<T>();
            newnode->data=data;
            if(head==NULL)
            {
                head=newnode;
                tail=newnode;
                mp[data]=1;
            }
            else
            {
                tail->next=newnode;
                newnode->prev=tail;
                tail=newnode;
                mp[data]=N+1;
            }
            N++;
            Page_Faults++;
        }
    }
}

