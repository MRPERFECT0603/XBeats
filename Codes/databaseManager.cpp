#include<iostream>
#include<string>
#include<fstream>
#include<cstring>
using namespace std;
#ifdef _WIN32                                       
    #define OS 0
    #include<windows.h>
#endif

#ifdef __APPLE__
    #define OS 1
    #include<unistd.h>
#endif


#ifdef __linux__
    #define OS 2
    #include<unistd.h>
#endif
void showDate()
{
    cout<<setw(250)<<__DATE__; 
    cout<<endl;
}
void updateNumber(int num);
int songcount();
//function to clear the terminal screen.
void clearScreen()
{
    if (OS==1||OS==2)
    {
        system("clear");
    }
    else
    {
        system("cls");
    }
    
}
//sleep function for different operating systems.
void sleep()
{
    if(OS==1|OS==2)
    {
        usleep(20000);
    }
    else
    {
        sleep((int)0.018);
    }
}
//user defined time structure.
struct time
{
    int hour;
    int min;
    int sec;
};
//structure of a song containg different attributes.
struct song
{
    //attributes
    int sid;
    string name;
    string singer;
    float rating;
    struct time duration;
    char language;
    string genre;
    string path;
    //function to insert data in the structure.
    void insertData()
    {
        clearScreen();
        cout<<setw(75)<<"***********************"<<endl<<endl;
        cout<<setw(70)<<"ENTER THE SONG ID:"<<endl;
        cout<<setw(55)<<"->";
        cin>>sid;
        cout<<setw(72)<<"ENTER THE SONG NAME:"<<endl;
        cout<<setw(55)<<"->";
        getchar();
        getline(cin,name);
        cout<<setw(69)<<"ENTER THE SINGER:"<<endl;
        cout<<setw(55)<<"->";
        getline(cin,singer);
        cout<<setw(69)<<"ENTER THE RATING:"<<endl;
        cout<<setw(55)<<"->";
        cin>>rating;
        cout<<setw(67)<<"ENTER THE TIME:"<<endl;
        cout<<setw(55)<<"->";
        cin >> duration.sec;
        duration.hour = duration.sec/3600;
        duration.sec %= 3600;
        duration.min = duration.sec/60;
        duration.sec %= 60;
        cout<<setw(71)<<"ENTER THE LANGUAGE:"<<endl;
        cout<<setw(55)<<"->";
        cin>>language;
        cout<<setw(68)<<"ENTER THE GENRE:"<<endl;
        cout<<setw(55)<<"->";
        getchar();
        getline(cin,genre);
        cout<<setw(67)<<"ENTER THE PATH:"<<endl;
        cout<<setw(55)<<"->";
        getchar();
        getline(cin,path);
        cout<<endl;
        cout<<setw(70)<<"***********************"<<endl<<endl;
    }

};
// structure of the node on which the different data structures are made.
class node
{
    public:
    song data;
    node* next;
    node* prev;
    node()
    {
        next = NULL;
        prev = NULL;
    }
    void insertData()
    {
        data.insertData();
    }
    void printdata()
    {
        cout<<setw(70)<<"***********************"<<endl<<endl;
        cout<<setw(60)<<"SONG ID:-"<<data.sid<<endl;
        cout<<setw(57)<<"NAME:-"<<data.name<<endl;
        cout<<setw(59)<<"SINGER:-"<<data.singer<<endl;
        cout<<setw(59)<<"RATING:-"<<data.rating<<endl;
        cout<<setw(62)<<"DURATIION:-"<<data.duration.hour<<":"<<data.duration.min<<":"<<data.duration.sec<<endl;
        cout<<setw(61)<<"LANGUAGE:-"<<data.language<<endl;
        cout<<setw(58)<<"GENRE:-"<<data.genre<<endl;
        cout<<endl;
        cout<<setw(70)<<"***********************"<<endl<<endl;
    }
};
//function to insert in the linked list
node* insert(node* head)
{
    if(head == NULL)
    {
        node* temp = new node;
        temp->insertData();
        return temp;
    }
    else
    {
        node* curr;
        node* temp = new node;
        temp->insertData();
        curr = head;
        while(curr->next != NULL)
        {
            curr = curr->next;
        }
        curr->next = temp;
        temp->prev = curr;
        return head;
    }
    
}
//print the linked list
void printlist(node* head)
{
    node* curr= head;
    while(curr != NULL)
    {
        curr->printdata();
        curr=curr->next;
    }
}
//insert the song in the database
void insertion(node* head ,int num)
{
    ofstream file1;
    file1.open("database1.dat" , ios::out | ios::binary | ios::app);
    if(!file1)
    {
        cout<<"file is not working"<<endl;
    }
    node* curr = head;
    for(int i=0 ; i<num ;i++)
    {
        file1.write((char*)&curr->data , sizeof(song));
        curr = curr->next;
    }
    file1.close();
    updateNumber(num);
}
//retriev the song from the database
node*  retrive()
{
    int x;
    x = songcount();
    node* head = NULL;
    ifstream file2("database1.dat" , ios::in | ios::binary);
    if(!file2)
    {
        cout<<"file is not working"<<endl;
    }
    for(int i=0;i<x;i++)
    {
        node* temp = new node;
        // cout<<file2.tellg()<<endl;
        file2.read((char*)&temp->data , sizeof(song));
        if(head == NULL)
        {
            head = temp;
            temp = NULL;
            delete temp;
        }
        else
        {
           node* curr = head;
           while(curr->next!= NULL)
           {
                curr=curr->next;
           }
            curr->next = temp;
            temp->prev = curr;
            temp = NULL;
            delete temp;
        }
    }
    return head;
    file2.close();
}
int searchPos(node* head , string name)
{
    node* curr = head;
    while(curr != NULL)
    {
        if(curr->data.name == name)
        {
            return curr->data.sid;
        }
        curr = curr->next;
    }
    cout<<"NO DATA FOUND TO DELETE"<<endl;
    return 0;
}
node* delnode(node* head, int pos)
{
    node* curr = head;
    node* temp = head;
    node* poss = head;

    for(int i=0;i<pos-2;i++)
    {
        curr = curr->next;
    }
    for(int i=0;i<pos-1;i++)
    {
        temp = temp->next;
    }
    for(int i=0;i<pos;i++)
    {
        poss = poss->next;
    }
    curr->next = poss;
    poss->prev = curr;
    delete temp;
    return head;
    

}
void updateDeletedData(node* head)
{
    int song=0;
    ifstream file1;
    // cout << "A";
    file1.open("songs.txt");
    if(!file1.is_open())
    {
        cout<<"ERROR IN OPENING THE FILE."<<endl;
    }
    file1>>song;
    song = song-1;
    file1.close();
    // cout << "X";
    ofstream file2;
    file2.open("songs.txt");
    if(!file2.is_open())
    {
        cout<<"ERROR IN OPENING THE FILE."<<endl;
    }
    file2<<song;
    file2.close();
}
int songcount()
{
    int song=0;
    ifstream file1;
    file1.open("songs.txt");
    if(!file1.is_open())
    {
        cout<<"ERROR IN OPENING THE FILE."<<endl;
    }
    file1>>song;
    return song;
}
void updateNumber(int num)
{
    int song=0;
    ifstream file1;
    file1.open("songs.txt");
    if(!file1.is_open())
    {
        cout<<"ERROR IN OPENING THE FILE."<<endl;
    }
    file1>>song;
    num = song+num;
    file1.close();
    ofstream file2;
    file2.open("songs.txt");
    if(!file2.is_open())
    {
        cout<<"ERROR IN OPENING THE FILE."<<endl;
    }
    file2<<num;
    file2.close();
}
void mainPage()
{
    label: clearScreen();
    int option;
    string name;
    int x;
    node* head = NULL;
    cout<<endl<<endl<<endl;
    cout<<endl;
    showDate(); 
    for(int i=0;i<48;i++)
    {
        cout<<endl;
        cout<<setw(70)<<"XBEAT MANAGEMENT PAGE:"<<endl;
        clearScreen();
        sleep();
    }
    cout<<setw(45);
    for(int i=0;i<30;i++)
    {
        cout<<"*";
    }
    cout<<endl;
    cout<<setw(70)<<"XBEAT MANAGEMENT PAGE:"<<endl;
    cout<<setw(45);
    for(int i=0;i<30;i++)
    {
        cout<<"*";
    }
    cout<<endl<<endl<<endl;
    cout<<setw(63)<<"1. ADD SONGS:"<<endl<<endl<<endl;
    cout<<setw(66)<<"2. DELETE SONGS:"<<endl<<endl<<endl;
    cout<<setw(66)<<"3.SHOW DATABASE:"<<endl<<endl<<endl;
    cout<<setw(45);
    for(int i=0;i<30;i++)
    {
        cout<<"*";
    }
    cout<<endl;
    cout<<setw(50)<<"->";
    cin>>option;
    switch (option)
    {
        case 1:
        clearScreen();
        showDate();
        cout<<endl<<endl<<endl;
        cout<<setw(80)<<"ENTER THE NUMBER OF SONGS TO ADD:"<<endl;
        cout<<endl<<endl<<endl;
        int num;
        cout<<setw(60)<<"->";
        cin>>num;
        for(int i = 1 ; i<=num ;i++)
        {
            head = insert(head);
        }
        printlist(head);
        insertion(head , num);
        break;
        case 2:
        clearScreen();
        showDate();
        cout<<endl<<endl<<endl;
        cout<<setw(70)<<"THIS FEATURE IS COMING SOON."<<endl;
        cout<<endl<<endl<<endl;
        // head = retrive();
        // printlist(head);
        // cout<<"ENTER THE NAME OF THE SONG TO DELETE:"<<endl;
        // cin>>name;
        // x = searchPos(head , name);
        // cout<<x<<endl;
        // head = delnode(head,x);
        // printlist(head);
        // updateDeletedData(head);
        break;
        case 3:
        clearScreen();
        showDate();
        head = retrive();
        printlist(head);
        break;
        default:
        goto label;
        break;
    }
}
int main()
{
    mainPage(); 
    return 0;
}   