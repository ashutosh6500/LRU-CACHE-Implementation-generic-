#include "Doubly_List.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
     long long int n,i;
     string s;
    Doubly_List<string>LRU_Cache_1;     //LRU Cache for String data type
    LRU_Cache_1.Set_Capacity(3);
    for(i=0;i<7;i++)
    {
        cout<<"Enter string data: \n";
        cin>>s;
        LRU_Cache_1.Insert(s);
    }
    cout<<"LRU_Cache data: \n";
    LRU_Cache_1.Print();
    cout<<"\n";
    cout<<"Number of Page Faults : "<<LRU_Cache_1.Page_Faults<<"\n";

    //................................................................................................................................
    Doubly_List<double>LRU_Cache_2;     //LRU Cache for double data type
    LRU_Cache_2.Set_Capacity(4);
    for(i=0;i<7;i++)
    {
        cout<<"Enter double data: \n";
        double d;
        cin>>d;
        LRU_Cache_2.Insert(d);
    }
     cout<<"LRU_Cache data: \n";
    LRU_Cache_2.Print();
    cout<<"\n";
    cout<<"Number of Page Faults : "<<LRU_Cache_2.Page_Faults<<"\n";
    //Similarly,this can also be used for user defined data types.
    return 0;
}
