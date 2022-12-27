#include<iostream>
#include<string>
#include <fstream>
using namespace std;

class timedt
{
    public:
    int sec;
    int min;
    int hour;
};
    struct song{
    // MetaData of the Song
    int sId;
    string sName;
    float rating;
    timedt duration;
    song(){
        cout << "Enter Song ID : ";
        cin >> sId;
        cout << "Enter Name of Song : ";
        getchar();
        getline(cin , sName);
        cout << "Rating (0-5) : ";
        cin >> rating;
        cout << "Enter Duration of Song (in Sec): ";
        cin >> duration.sec;
        duration.hour = duration.sec/3600;
        duration.sec %= 3600;
        duration.min = duration.sec/60;
        duration.sec %= 60;
        cout << endl;
    }
    song(int x , string y , float  z ,int w)
    {
        sId = x;
        sName = y;
        rating = z;
        duration.sec = w;
        duration.hour = duration.sec/3600;
        duration.sec %= 3600;
        duration.min = duration.sec/60;
        duration.sec %= 60;
    }
};


struct node
{
    song data(int x , string y , float  z ,int w);
    node* next;
    node* prev;
    node(int x , string y , float  z ,int w)
    {
        next = NULL;
        prev = NULL;
    }
};
node* call()
{
    node* head = new node(1,"lover",4.5,278);
    head->next = new node(2,"lover",4.5,278);
    head->next->next= new node(3,"lover",4.5,278);
    head->next->next->next= new node(4,"lover",4.5,278);
    head->next->next->next->next = new node(5,"lover",4.5,278);
    head->next->next->next->next->next = new node(6,"lover",4.5,278);
    head->next->next->next->next->next->next = new node(7,"lover",4.5,278);
    head->next->next->next->next->next->next->next = new node(8,"lover",4.5,278);
    head->next->next->next->next->next->next->next->next = new node(9,"lover",4.5,278);
    return head;
}