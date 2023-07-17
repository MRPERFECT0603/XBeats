/*                              *******JAYPPEE INSTITUE OF INFORMATION TECHNOLOGY*******
                                                      SEC-62

                                                *DATA STRUCTURES*
                
                                             SEMESTER-3 MINOR PROJECT


                INTRODUCTION:
                *                  *OUR PROJECT IS BASICALLY A PROTOTYPE OF*                    *
                *                  *AN AUDIO PLAYER WHICH WOULD BE ACTING AS*                   *   
                *                    *THE BACKEND FOR IN HOUSE STANDALONE*                      *
                *                               *MUSIC PLAYER.*                                 *
                    
                *                                *X BEAT*                                       *


                SUBMITTED TO:-
                Dr. Bharat Gupta
                

                SUMITTED BY:-
                
                1.TANYA VASHISTHA (21803006)
                2.ANSH MISHRA     (21803011)
                3.VIVEK SHAURYA   (21803013)
                4.HARSHIT VIJAY   (21803015)

*/

#include <iostream>
#include <string>
#include<iomanip>
#include<ctime>
#include<fstream>
using namespace std;

//CHECKING OS FOR DIFFERENT FUNCTIONS.

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
int count1 =0;
//function to print Date on the right corner of the screen.
void showDate()
{
    cout<<setw(250)<<__DATE__; 
    cout<<endl;
}
//function to clear the terminal on different operating system.
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
//function to sleep the program for user defined time.
void sleep()
{
    if(OS==1 || OS==2)
    {
        usleep(20000);
    }
    else
    {
        sleep((int)0.018);
    }
}
//structure of the user defined time
struct time
{
    int hour;
    int min;
    int sec;
};
//structure of the song
struct song
{
    int sid;
    string name;
    string singer;
    float rating;
    struct time duration;
    char language;
    string genre;
    string path; 
};
//function to count the song in the database.
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
//class node used for Binary search tree
class nodeForBst
{
    public:
    song data;
    nodeForBst* left;
    nodeForBst* right;
    nodeForBst()
    {
        left = NULL;
        right = NULL;
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
// class node for the linked list.
class nodeForLL
{
    public:
    song data;
    nodeForLL* next;
    nodeForLL* prev;
    nodeForLL()
    {
        next = NULL;
        prev = NULL;
    }
    void printdata()
    {
        cout<<endl<<endl<<endl;
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
//functions declarations
void mainPage(void);
void selectOption(void);
void searchForSong(void);
void searchByName(nodeForLL* head); 
void searchBySinger(nodeForLL* head);   
void searchByRating(nodeForBst* root);   
void searchByGenre(nodeForLL* head);
void myPlaylist(void);
//to retrive the nodes from the binary file in form of linked list.
nodeForLL* retriveAsLinkedList()
{
    int x;
    x = songcount();
    nodeForLL* head = NULL;
    ifstream file2("database1.dat" , ios::in | ios::binary);
    if(!file2)
    {
        cout<<"file is not working"<<endl;
    }
    for(int i=0;i<x;i++)
    {
        nodeForLL* temp = new nodeForLL;
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
           nodeForLL* curr = head;
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
//to print the whole binary tree inorder printing
void printtree(nodeForBst *root)
{
    if(root==NULL)
        return;
    else
    {
        printtree(root->left);
        root->printdata();
        printtree(root->right);
    }
}
//print tree with some constraint used in filtering by rating
void printtreeconstr(nodeForBst *root , float x)
{
    if(root==NULL)
        return;
    else
    {
        printtreeconstr(root->left , x);
        if(root->data.rating >= x)
        {
            root->printdata();
        }
        printtreeconstr(root->right , x);
    }
}
//function to insert node in the binary file.
nodeForBst *insertb(nodeForBst *root , nodeForBst *temp)
{   
    if(root==NULL)
    {
        root=temp;
        return root;
    }
    else
    {

        if(root->data.sid>temp->data.sid)
        {
           if(root->left==NULL)
            root->left=temp;
           else
            root->left= insertb(root->left,temp);
        }
        else
        {  
            if(root->right==NULL)
            root->right=temp;
            else
            root->right=insertb(root->right,temp);

        }   
        return root;
    }
}
//function to retieve data from the file as binary tree
nodeForBst*  retriveAsBinarySearchTree()
{
    int x;
    x = songcount();
    nodeForBst* root = NULL;
    ifstream file2("database1.dat" , ios::in | ios::binary);
    if(!file2)
    {
        cout<<"ERROR IN OPENING THE FILE."<<endl;
    }
    for(int i=0;i<x;i++)
    {
        nodeForBst* temp = new nodeForBst;
        // cout<<file2.tellg()<<endl;
        file2.read((char*)&temp->data , sizeof(song));
        root = insertb(root ,temp);
    }
    return root;
    file2.close();
}
//function to use the searching page
void searchingPage()
{
    clearScreen();
    showDate();
    for(int i=0 ; i<5 ;i++)
    {
        cout<<"\n";
    }
    cout<<setw(38)<<endl; 
    for(int i=0 ; i<50 ;i++)
    {
        cout<<"*";
    }
    cout<<endl<<endl<<endl;
    cout<<setw(70)<<endl;
    cout<<"1.SEARCH BY NAME."<<endl<<endl;
    cout<<setw(72)<<endl;
    cout<<"2.SEARCH BY SINGER."<<endl<<endl;
    cout<<setw(72)<<endl;
    cout<<"3.SEARCH BY RATING."<<endl<<endl;
    cout<<setw(71)<<endl;
    cout<<"4.SEARCH BY GENRE."<<endl<<endl;
    cout<<setw(38)<<endl<<endl<<endl;
    for(int i=0 ; i<50 ;i++)
    {
        cout<<"*";
    }
}
//function to search the linked list for a specific genre
void searchByGenre(nodeForLL* head)
{
    clearScreen();
    showDate();
    nodeForLL* curr = head;
    string genre;
    for(int i=0 ;i<5;i++)
    {
        cout<<"\n";
    }
    int flag = 0;
    cout<<setw(70)<<endl;
    cout<<"ENTER THE GENRE OF THE SONG:"<<endl;
    cout<<setw(45)<<endl;
    cout<<"->";
    getchar();
    getline(cin,genre);
    while(curr!= NULL)
    {
        if(curr->data.genre == genre)
        {
            flag = 1;
            curr->printdata();
        }
        curr = curr->next;
    }
    if(flag == 0)
    {
        cout<<"NO SONG OF THIS GENRE."<<endl;
    }
}
//function to go to different options.
void searchForSong()
{
    nodeForLL* head = retriveAsLinkedList();
    nodeForBst* root = retriveAsBinarySearchTree();
    searchingPage();
    cout<<endl<<endl<<setw(61)<<"->";
    int option;
    cin>>option;
    switch(option)
    {
        case 1:
            searchByName(head);
        break;
        case 2:
            searchBySinger(head);
        break;
        case 3:
            searchByRating(root);
        break;
        case 4:
            searchByGenre(head);
        break;
        default:
        break;
    }

}
//function to search the linked list according to name.
void searchByName(nodeForLL* head)       
{
    nodeForLL* curr;
    clearScreen();
    showDate();
    // curr = head;
    // while(curr != NULL)
    // {       
    //     curr->printdata();
    //     curr=curr->next;

    // }
    string name;
    for(int i=0 ;i<5;i++)
    {
        cout<<"\n";
    }
    cout<<setw(70)<<endl;
    cout<<"ENTER THE NAME OF THE SONG:"<<endl;
    cout<<setw(44)<<endl;
    cout<<"->";
    getchar();
    getline(cin,name);
    curr=head;
    int flag=0;
    while(curr != NULL)
    {
        if(curr->data.name == name)
        {
            curr->printdata();
            flag=1;
        }
        curr=curr->next;
    }
    if(flag==0)
    {
        cout<<setw(43)<<endl;
        cout<<"SONG COMING SOON."<<endl;
    }
}
//function to search the linked list according to singer's name.
void searchBySinger(nodeForLL* head)       
{
    nodeForLL* curr;
    clearScreen();
    showDate();
    // curr = head;
    // while(curr != NULL)
    // {       
    //     curr->printdata();
    //     curr=curr->next;

    // }
    string singer;
    for(int i=0 ;i<5;i++)
    {
        cout<<"\n";
    }
    cout<<setw(70)<<endl;
    cout<<"ENTER THE NAME OF THE SINGER:"<<endl;
    cout<<setw(44)<<endl;
    cout<<"->";
    getchar();
    getline(cin,singer);
    curr=head;
    int flag=0;
    while(curr != NULL)
    {
        if(curr->data.singer == singer)
        {
            curr->printdata();
            flag=1;
        }
        curr=curr->next;
    }
    if(flag==0)
    {
        cout<<setw(43)<<endl;
        cout<<"NO SONG BY THIS SINGER."<<endl;
    }
}
//to search for a song id by the song name.
int searchPos(nodeForLL* head , string name)
{
    nodeForLL* curr = head;
    while(curr != NULL)
    {
        if(curr->data.name == name)
        {
            return curr->data.sid;
        }
        curr = curr->next;
    }
    cout<<"NO DATA FOUND."<<endl;
    return 0;
}
//the whole playlist function.
void myPlaylist()
{
    clearScreen();
    showDate();
    nodeForLL* head = NULL;
    head = retriveAsLinkedList();
    nodeForLL* curr = NULL;
    // nodeForLL* curr = head;
    // while(curr!=NULL)
    // {
    //     curr->printdata();
    //     curr = curr->next;
    // }
    string playlist;
    string name;
    cout<<setw(70)<<"ENTER THE NAME OF THE PLAYLIST"<<endl;
    cout<<setw(50)<<"->";
    cin>>name;
    playlist = name + ".dat";
    fstream file2(playlist , ios::out | ios::binary | ios::app);
    if(!file2)
    {
        cout<<"ERROR IN OPENING THE FILE."<<endl;
    }
    file2.close();
    string songName;
    int num;
    cout<<endl<<endl;
    cout<<setw(66)<<"ENTER THE NUMBER OF SONGS:"<<endl;
    cout<<setw(50)<<"->";
    cin>>num;
    for(int i =0 ; i<num ;i++)
    {
        ofstream file1;
        file1.open(playlist , ios::out | ios::binary | ios::app);
        if(!file1)
        {
            cout<<setw(70)<<"ERROR IN OPENING THE FILE."<<endl;
        }
        cout<<endl<<endl;
        cout<<setw(67)<<"ENTER THE NAME OF THE SONG:"<<endl;
        cout<<setw(50)<<"->";
        getchar();
        getline(cin,songName);
        curr = head;
        while(curr!=NULL)
        {
            if(curr->data.name == songName)
            {
                file1.write((char*)&curr->data , sizeof(song));
                break;
            }
            curr = curr->next;
        }
        file1.close();
    }
    ifstream file8(playlist , ios::in | ios::binary);
    if(!file8)
    {
        cout<<setw(70)<<"ERROR IN OPENING THE FILE."<<endl;
    }
    nodeForLL* head2 = NULL;
    for(int i=0;i<num;i++)
    {
        nodeForLL* temp = new nodeForLL;
        // cout<<file2.tellg()<<endl;
        file8.read((char*)&temp->data , sizeof(song));
        // temp->printdata();
        if(head2 == NULL)
        {
            head2 = temp;
            temp = NULL;
            delete temp;
        }
        else
        {
           nodeForLL* curr = head2;
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
    file8.close();
    curr = head;
    for(int i=0;i<num;i++)
    {
        curr->printdata();
        curr=curr->next;
    }
}
//enque function in the queue
nodeForLL* enque(nodeForLL* head , nodeForLL* head1)
{
    string name;
    cout<<endl;
    cout<<setw(68)<<"ENTER THE NAME OF THE SONG:"<<endl;
    cout<<setw(50)<<"->";
    cin>>name;
    nodeForLL* curr = head;
    while(curr!= NULL)
    {
        if(curr->data.name == name)
        {break;}
        curr=curr->next;
    }
    nodeForLL* temp = new nodeForLL();
    temp->data.sid = curr->data.sid;
    temp->data.name = curr->data.name;
    temp->data.singer = curr->data.singer;
    temp->data.rating = curr->data.rating;
    temp->data.duration.hour = curr->data.duration.hour;
    temp->data.duration.min = curr->data.duration.min;
    temp->data.duration.sec = curr->data.duration.sec;
    temp->data.language = curr->data.language;
    temp->data.genre = curr->data.genre;
    temp->data.path = curr->data.path;
    nodeForLL* curr1 = head1;
    if(head1 == NULL)
    {
        head1 = curr1 = temp;
    }
    else
    {
        while(curr1->next!= NULL)
        {
            curr1 = curr1->next;
        }
        curr1->next=temp;
        temp->prev=curr1;
    }
    return head1;
    
}
//deque function for the queue
nodeForLL* dequee(nodeForLL* head)
{
    nodeForLL* curr = head;
    head = head->next;
    delete curr;
    return head;
}
//add function to constraint the queue to have size 5 only
nodeForLL* addFunction(nodeForLL* head,nodeForLL* head1)
{
    here:
    if(count1<5)
    {
        head1 = enque(head,head1);
        count1++;
    }
    else
    {
        count1--;
        head1 = dequee(head1);
       goto here;
    }
    return head1;
    
}
//to print the queue
void showqueue(nodeForLL* head)
{
    nodeForLL* curr = head;
    while (curr!=NULL)
    {
        curr->printdata();
        curr = curr->next;
    }
}
//to access the queue options
void queue()
{
    clearScreen();
    showDate();
    nodeForLL* head = retriveAsLinkedList();
    nodeForLL* head1 = NULL;
    label: cout<<setw(59)<<"1. ADD SONGS."<<endl<<endl;
    cout<<setw(60)<<"2. SHOW QUEUE."<<endl<<endl<<endl;
    int option;
    cout<<setw(50)<<"->";
    cin>>option;
    switch(option)
    {
        case 1:
            head1 = addFunction(head,head1);
            goto label;
        break;
        case 2:
            showqueue(head1);
        break;
        default:
        break;
    }
}
//to search in the binary file according to rating
void searchByRating(nodeForBst* root)
{
    clearScreen();
    showDate();
    for(int i=0 ;i<5;i++)
    {
        cout<<"\n";
    }
    cout<<setw(42)<<endl;
    for(int i=0 ; i<50 ;i++)
    {
        cout<<"*";
    }
    cout<<endl<<endl<<endl;
    cout<<setw(82)<<endl;
    cout<<"SELECT FROM THE GIVEN OPTIONS:"<<endl<<endl<<endl;
    cout<<setw(67)<<endl;
    cout<<"1. 5 STAR"<<endl;
    cout<<setw(73)<<endl;
    cout<<"2. ABOVE 4 STAR"<<endl;
    cout<<setw(73)<<endl;
    cout<<"3. ABOVE 3 STAR"<<endl;
    cout<<setw(73)<<endl;
    cout<<"4. ABOVE 2 STAR"<<endl;
    cout<<setw(73)<<endl;
    cout<<"5. ABOVE 1 STAR"<<endl;
    cout<<setw(42)<<endl<<endl<<endl;
    for(int i=0 ; i<50 ;i++)
    {
        cout<<"*";
    }
    int option;
    cout<<endl<<endl;
    cout<<setw(66);
    cout<<"->";
    cin>>option;
    switch(option)
    {
        case 1:
            clearScreen();
            showDate();
            printtreeconstr(root , 5);
        break;
        case 2:
            clearScreen();
            showDate();
            printtreeconstr(root , 4);
        break;
        case 3:
            clearScreen();
            showDate();
            printtreeconstr(root , 3);
        break;
        case 4:
            clearScreen();
            showDate();
            printtreeconstr(root , 2);
        break;
        case 5:
            clearScreen();
            showDate();
            printtreeconstr(root , 1);
        break;
        default:
        break;
    }
}
void selectOption()
{
    int option;
    cin>>option;
    switch(option)
    {
        case 1: 
            searchForSong();
        break;
        case 2:
            myPlaylist();
        break;
        case 3:
            queue();
        break;
        default:
        mainPage();
    }
}
//to access the main page on the screen
void mainPage(void)
{
    if (OS==1||OS==2)
    {
        system("clear");
    }
    else
    {
        system("cls");
    } 
    showDate();
    cout<<setw(50);     
    for(int i=0;i<9;i++)
    {
        cout<<"*";
    }
    cout<<endl;
    cout<<setw(56);
    cout<<"XBEAT"<<endl;   
    cout<<setw(50);     
    for(int i=0;i<9;i++)
    {
        cout<<"*";
    }                      
    cout<<endl<<endl<<endl;
    cout<<setw(45);     
    for(int i=0;i<20;i++)
    {
        cout<<"*";
    }     
    cout<<endl<<endl<<setw(63)<<"WE BRING THE MUSIC"<<endl<<endl;
    cout<<setw(45);     
    for(int i=0;i<20;i++)
    {
        cout<<"*";
    }     
    cout<<"\n\n\n";
    cout<<setw(35);
    for(int i=0;i<40;i++)
    {
        cout<<"*";
    }
    cout<<endl<<setw(35)<<"*";
    cout<<setw(39)<<"*"<<endl;
    cout<<setw(66);
    cout<<"1. SEARCH FOR A SONG.";
    cout<<endl;
    cout<<endl<<setw(35)<<"*";
    cout<<setw(39)<<"*"<<endl;
    cout<<setw(60);
    cout<<"2. MY PLAYLIST.";
    cout<<endl;
    cout<<endl<<setw(35)<<"*";
    cout<<setw(39)<<"*"<<endl;
    cout<<setw(57);
    cout<<"3. MY QUEUE.";
    cout<<endl;
    cout<<setw(35);
    for(int i=0;i<40;i++)
    {
        cout<<"*";
    }
    cout<<endl<<endl<<setw(51)<<"->";
    selectOption();
}
//main function
int main()
{
    mainPage();
    return 0;
}
