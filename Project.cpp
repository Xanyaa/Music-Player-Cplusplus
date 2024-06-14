#include<bits/stdc++.h>
#include<vector>
#include<cstdlib>
#include<windows.h>
#include<fstream>
#include<dirent.h>
#include<stdio.h>
#include<ctime>
#include<sstream>
#include<conio.h>
#include<unistd.h>
#include<iomanip>

using namespace std;

//Node class definition
class Node
{
public:
    char data[30];
    Node *next;
    Node *previous;

    Node()
    {
        strcpy(data,"\0");
        next = NULL;
        previous = NULL;
    }

    Node(char d[])
    {
        strcpy(data, d);
        next = NULL;
        previous = NULL;
    }
};

//circular doubly linked list definition
class circular_doubly_LL
{
public:
    class Node *head;

    circular_doubly_LL()
    {
        head = NULL;
    }

    circular_doubly_LL(Node *n)
    {
        head = n;
    }

    void displayNode()
    {
        Node *ptr=head;
        for (int i=0;i>=0;i++)
        {
            if (ptr->next!=head)
            {
                cout<<ptr->data<<endl;
                ptr=ptr->next;
            }
            else
            {
                cout<<ptr->data<<endl;
                ptr=ptr->next;
                break;
            }
        }
    }
    //a function to play song
    void playsong(char song_name[])
    {
        system("cls");//clear conslole
        int n;
        char en[] = ".wav";
        if (strstr(song_name,en) == NULL)
        {
            strcat(song_name,en);//concatenate .wav to send in the audio file name
        }

        cout<<song_name<<endl;

        cout << "Press 1 to play the file and press 2 to exit the file." << endl;
        cin >> n;
        while(1)
        {
            if (n == 1)
            {
                PlaySound(song_name, NULL, SND_FILENAME|SND_LOOP|SND_ASYNC);//a built-in function to play song
                while(1)
                {
                    cin>>n;
                    if (n == 2)
                    {
                        PlaySound(0,0,0);//stop song
                        break;
                    }
                }
                break;
            }
            else if (n == 2)
            {
                break;
            }
        }
        return;
    }
    //a function to search a specific song name in a list
    Node* searchNode(char d[])
    {
        Node *temp = head;
        for (int i = 0 ; i >= 0 ; i++)
        {
            if (!strcmp(temp->data,d))
            {
                return temp;
            }
            else
            {
                temp = temp->next;
            }
            if (temp == head)
            {
                return NULL;
            }
        }
    }

    void appendNode(char d[])
    {
        Node *n=new Node(d);
        if (head==NULL)
        {
            head=n;
            return;
        }
        else
        {
            if (head->next==NULL)
            {
                head->next=n;
                head->previous=n;
                n->previous=head;
                n->next=head;
            }
            else
            {
                Node *ptr=head;
                for (int i=0;i>=0;i++)
                {
                    if (ptr->next!=head)
                    {
                        ptr=ptr->next;
                    }
                    else
                    {
                        break;
                    }
                }
                ptr->next=n;
                n->previous=ptr;
                n->next=head;
            }
        }
    }

    void deleteNode(char d[])
    {
        Node *ptr=head;
        Node *temp=head;
        if (!strcmp(head->data,d))
        {
            for (int i=0;i>=0;i++)
            {
                if (ptr->next!=head)
                {
                    ptr=ptr->next;
                }
                else
                {
                    break;
                }
            }
            head = head->next;
            head->previous=ptr;
            ptr->next=head;
            delete temp;
            return;
        }
        else
        {
            for (int i=0;i>=0;i++)
            {
                if (ptr->next!=head)
                {
                    if (!strcmp(ptr->next->data,d))
                    {
                        break;
                    }
                    ptr=ptr->next;
                }
                else
                {
                    cout<<"Node Does Not Exist";
                    return;
                }
            }
            temp=ptr->next;
            ptr->next=ptr->next->next;
            ptr->next->next->previous=ptr;
        }
    }
};

//show loading screen
void loader()
{
    int i;
    for(i = 0 ; i < 2 ; i++)
	{
		cout<<"\nLOADING";
        for(int j=0 ; j<3 ; j++)
        {
        	cout<<".";
        	sleep(1);
		}
        system("CLS");
    }
}

//playing songs
void startplaylist(string playlist_name)
{
    ifstream fin;
    fin.open(playlist_name);

    circular_doubly_LL l1;

    if (fin.is_open())//open file
    {
        char song_name[30];
        while(!fin.eof())
        {
            fin.getline(song_name,30);
            cout<<song_name<<endl;
            l1.appendNode(song_name);//make a linked list with all songs
        }
    }
    else
    {
        return;
    }
    fin.close();

    int choice;
    Node *temp = l1.head;
    loader();
    l1.playsong(temp->data);
    while(1)
    {
        cout<<"1. Play next song"<<endl;
        cout<<"2. Play previous song"<<endl;
        cout<<"3. Play current song"<<endl;
        cout<<"4. Back"<<endl;
        cin>>choice;

        if (choice == 1)
        {
            temp = temp->next;//point to next song
            l1.playsong(temp->data);
        }
        else if (choice == 2)
        {
            temp = temp->previous;//point to previous song
            l1.playsong(temp->data);
        }
        else if (choice == 3)
        {
            l1.playsong(temp->data);//points to current
        }
        else if (choice == 4)
        {
            break;
        }
        else
        {
            cout<<"Invalid option."<<endl;
        }
    }

    return;
}

void createplaylist()
{
    cout<<"Creating playlist: "<<endl<<endl;
    string playlist_name;

    cout<<"Enter name of the playlist: ";
    cin.ignore();
    getline(cin, playlist_name);

    DIR *di;
    char *ptr1,*ptr2;
    int retn;
    struct dirent *dir;
    di = opendir("."); //specify the directory name
    bool flag = true; //a variable to check if user inputs a name which is same to an already created playlist.
    if (di)
    {
        while ((dir = readdir(di)) != NULL)
        {
            ptr1=strtok(dir->d_name,".");
            ptr2=strtok(NULL,".");
            if(ptr2!=NULL)
            {
                retn=strcmp(ptr2,"txt");
                if(retn==0)
                {
                    if (!playlist_name.compare(ptr1))
                    {
                        cout<<"There is already a playlist with this name."<<endl<<endl;
                        flag = false;//if file already occurs with the name entered by user, flag is false.
                    }
                }
            }
        }
        closedir(di);
    }

    if (flag)//if flag is true, only then a playlist will be created. Else not.
    {
        ofstream fout;

        fout.open(playlist_name + ".txt",ios::app);

        if (fout.is_open())
        {
            vector <string> song_comparison;//a dynamic array to compare user entered songs with the song name in the directory.
            cout<<"Enter song name to add to your playlist. Enter None to complete your process. Following is the list of all songs: "<<endl<<endl;
            cout<<endl;
            DIR *di;
            char *ptr1,*ptr2;
            int retn;
            struct dirent *dir;
            di = opendir("."); //specify the directory name
            if (di)
            {
                while ((dir = readdir(di)) != NULL)
                {
                    ptr1=strtok(dir->d_name,".");
                    ptr2=strtok(NULL,".");
                    if(ptr2!=NULL)
                    {
                        retn=strcmp(ptr2,"wav");
                        if(retn==0)
                        {
                            song_comparison.push_back(ptr1); //push all the songs in the directory to compare afterwards with the user entered song.
                            printf("%s\n",ptr1);
                        }
                    }
                }
                closedir(di);
            }

            string song_name;
            string check = "None";
            while(1)
            {
                fflush(stdin);
                getline(cin,song_name);
                if (check == song_name)
                {
                    break;
                }
                else
                {
                    int i;
                    for (i = 0 ; i < song_comparison.size() ; i++)
                    {
                        if (song_name == song_comparison[i])
                        {
                            fout<<song_name<<endl;
                            break;
                        }
                    }
                    //if song name occurs in the vector, then the process will be continued.
                    if (i == song_comparison.size())
                    {
                        cout<<"There is no song with this name."<<endl;
                    }
                }
            }
            fout.close();
        }
    }

    else
    {
        return;
    }
}

void createfavouriteplaylist()
{
    cout<<"Creating Favourites' playlist:"<<endl<<endl;
    ofstream fout;
    fout.open("Favourites.txt",ios::app);

    if (fout.is_open())
    {
        vector <string> song_comparison;
        cout<<"Enter song name to add to your playlist. Enter None to complete your process. Following is the list of all songs: "<<endl<<endl;
        cout<<endl;
        DIR *di;
        char *ptr1,*ptr2;
        int retn;
        struct dirent *dir;
        di = opendir("."); //specify the directory name
        if (di)
        {
            while ((dir = readdir(di)) != NULL)
            {
                ptr1=strtok(dir->d_name,".");
                ptr2=strtok(NULL,".");
                if(ptr2!=NULL)
                {
                    retn=strcmp(ptr2,"wav");
                    if(retn==0)
                    {
                        song_comparison.push_back(ptr1);
                        printf("%s\n",ptr1);
                    }
                }
            }
            closedir(di);
        }

        string song_name;
        string check = "None";
        while(1)
        {
            fflush(stdin);
            getline(cin,song_name);
            if (check == song_name)
            {
                break;
            }
            else
            {
                int i;
                for (i = 0 ; i < song_comparison.size(); i++)
                {
                    if (song_name == song_comparison[i])
                    {
                        fout<<song_name<<endl;
                        break;
                    }
                }
                if (i == song_comparison.size())
                {
                    cout<<"There is no song with this name."<<endl;
                }
            }
        }
        fout.close();
    }
    return;
}

void viewplaylist()
{
    cout<<"Viewing playlists: "<<endl<<endl;
    vector <string> playlist_comparison;
    DIR *di;
    char *ptr1,*ptr2;
    int retn;
    struct dirent *dir;
    bool flag = true; //a variable to check if user has created any playlist.
    di = opendir("."); //specify the directory name
    if (di)
    {
        while ((dir = readdir(di)) != NULL)
        {
            ptr1=strtok(dir->d_name,".");
            ptr2=strtok(NULL,".");
            if(ptr2!=NULL)
            {
                retn=strcmp(ptr2,"txt");
                if(retn==0)
                {
                    playlist_comparison.push_back(ptr1);
                    flag = false;
                    printf("%s\n",ptr1);
                }
            }
        }
        closedir(di);
    }

    if (flag)//if there is no playlist, then this line will execute.
    {
        cout<<"You have not created any playlist."<<endl;
        return;
    }
    string playlist_name;

    cout<<"Type name of playlist you want to open, or type None if you want to go back."<<endl;
    fflush(stdin);
    getline(cin,playlist_name);
    if (playlist_name == "None")
    {
        return;
    }

    int i;
    for (i = 0 ; i < playlist_comparison.size() ; i++)
    {
        if (playlist_name == playlist_comparison[i])
        {
            cout<<"Opening playlist."<<endl;
            break;
        }
    }

    if (i < playlist_comparison.size())
    {
        string choice;
        cout<<"Start this playlist? Type yes or no: ";
        cin>>choice;
        if (choice == "Yes" || choice == "yes")
        {
            startplaylist(playlist_name + ".txt");
        }
    }
    else
    {
        cout<<"There is no playlist with this name."<<endl;
    }
    return;
}

void playallsongs()
{
    cout<<"All songs: "<<endl<<endl;
    circular_doubly_LL l1;
    DIR *di;
    char *ptr1,*ptr2;
    int retn;
    struct dirent *dir;
    di = opendir("."); //specify the directory name
    if (di)
    {
        while ((dir = readdir(di)) != NULL)
        {
            ptr1=strtok(dir->d_name,".");
            ptr2=strtok(NULL,".");
            if(ptr2!=NULL)
            {
                retn=strcmp(ptr2,"wav");
                if(retn==0)
                {
                    l1.appendNode(ptr1);
                    printf("%s\n",ptr1);
                }
            }
        }
        closedir(di);
    }

    int choice;

    Node *temp = l1.head;
    cout<<"1.Play from start" <<endl;
    cout<<"2.Play a specific song?"<<endl;
    cin>>choice;
    while(1)
    {
        if (choice == 1)
        {
            loader();
            l1.playsong(temp->data);
            break;
        }
        else if (choice == 2)
        {
            while(1)
            {
                char song_name[30];
                cout<<"Enter song name: ";
                fflush(stdin);
                cin.getline(song_name,30);
                temp = l1.searchNode(song_name);
                if (temp == NULL)
                {
                    cout<<"There is no song with this name."<<endl;
                }
                else
                {
                    loader();
                    l1.playsong(temp->data);
                    break;
                }
            }
            break;
        }
    }
    while(1)
    {
        cout<<"1. Play next song"<<endl;
        cout<<"2. Play previous song"<<endl;
        cout<<"3. Play current song"<<endl;
        cout<<"4. Back"<<endl;
        cin>>choice;

        if (choice == 1)
        {
            temp = temp->next;
            l1.playsong(temp->data);
        }
        else if (choice == 2)
        {
            temp = temp->previous;
            l1.playsong(temp->data);
        }
        else if (choice == 3)
        {
            l1.playsong(temp->data);
        }
        else if (choice == 4)
        {
            break;
        }
        else
        {
            cout<<"Invalid option."<<endl;
        }
    }

    return;
}

void deleteplaylist()
{
    cout<<"Deleting playlist:"<<endl<<endl;
    vector <string> playlist_comparison;
    DIR *di;
    char *ptr1,*ptr2;
    int retn;
    struct dirent *dir;
    bool flag = true;//a variable to check if playlists are created or not.
    di = opendir("."); //specify the directory name
    if (di)
    {
        while ((dir = readdir(di)) != NULL)
        {
            ptr1=strtok(dir->d_name,".");
            ptr2=strtok(NULL,".");
            if(ptr2!=NULL)
            {
                retn=strcmp(ptr2,"txt");
                if(retn==0)
                {
                    playlist_comparison.push_back(ptr1);
                    flag = false;
                    printf("%s\n",ptr1);
                }
            }
        }
        closedir(di);
    }

    if (flag)
    {
        cout<<"You have not created any playlist."<<endl;
        return;
    }
    string playlist_name;

    cout<<"Type name of playlist you want to delete, or type None if you want to go back."<<endl;
    fflush(stdin);
    getline(cin,playlist_name);
    if (playlist_name == "None")
    {
        return;
    }

    int i;
    for (i = 0 ; i < playlist_comparison.size() ; i++)
    {
        if (playlist_name == playlist_comparison[i])
        {

            playlist_name = playlist_name + ".txt";
            char temp[playlist_name.size() + 1];
            strcpy(temp,playlist_name.c_str());
            remove(temp);
            break;
        }
    }
}

void displaynames()
{
    cout<<endl;
    cout<<endl;
    cout<<"MUSIC PLAYER USING LINKED LIST"<<endl;
    cout<<"A project made by:"<<endl;
    cout<<"Muhammad Hasan (21K-4885)"<<endl;
    cout<<"Hannan Irfan (21K-4934)"<<endl;
    cout<<"Syeda Sania Hasan (21K-4671)"<<endl;
    system("pause");
    return;
}

void displaymenu()
{
    int choice;
    while(1)
    {
        system("cls");
        cout<<"Hello user! What do you want to do? Choose from the following options:"<<endl;
        cout<<"1. Show songs"<<endl;
        cout<<"2. Create new playlist"<<endl;
        cout<<"3. Create favourites' playlist"<<endl;
        cout<<"4. View your playlists"<<endl;
        cout<<"5. Delete a playlist"<<endl;
        cout<<"6. Exit"<<endl;

        cin >> choice;

        if (choice == 1)
        {
            system("cls");
            playallsongs();
        }
        else if (choice == 2)
        {
            system("cls");
            createplaylist();
        }
        else if (choice == 3)
        {
            system("cls");
            createfavouriteplaylist();
        }
        else if (choice == 4)
        {
            system("cls");
            viewplaylist();
        }
        else if (choice == 5)
        {
            system("cls");            deleteplaylist();
        }
        else if (choice == 6)
        {
            exit(0);
        }
        else
        {
            system("cls");
            cout<<"Invalid option."<<endl;
        }
    }
}

int clk()
{
    time_t t = time(NULL);
    tm* timePtr = localtime(&t);
    cout << " Date:" << setw(120) << "Time:" << endl;
    cout << " ---------" << setw(127) << " ---------------------------------";
    cout << endl <<"|"<<(timePtr->tm_mday)<<"|"<< (timePtr->tm_mon)+1 <<"|"<< (timePtr->tm_year)+1900<<"|"
         << setw(100) <<"|HOURS: "<<(timePtr->tm_hour)<<"|MINUTES: "<< (timePtr->tm_min)<<"|SECONDS: "<< (timePtr->tm_sec) <<"|"<<endl;
    cout << " ---------" << setw(127) << " ---------------------------------";
}

int main()
{
    clk();
    displaynames();
    displaymenu();

    return 0;
}
