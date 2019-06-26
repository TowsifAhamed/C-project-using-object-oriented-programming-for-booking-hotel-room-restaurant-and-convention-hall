#include <bits/stdc++.h>
using namespace std;
//base class
class client
{
public:
    //base class data members
    static int c_id_count;
    int cost_cnt;
    char c_type;
    //base class member functions
    //using csv file to store & check the user data
    //virtual function for polymorphism
    virtual void check()
    {
        //Here searching if a client has his / her account
        fstream fin;
        fin.open("client.csv", ios::in);
        int target_phn,phn,count = 0;
        cout << "Enter the phone number of the client to display details: ";
        cin >> target_phn;
        //using vector to get a line at a time
        vector<string> row;
        string line, word;
        while (fin >> line) {
            row.clear();
            stringstream s(line);
            //get the data splitting by comma from the line
            while (getline(s,word,',')) {
            row.push_back(word);
            }
            //changing the string input to int
            phn = atoi(row[2].c_str());
            if (target_phn == phn) {
                //printing the client data
                count = 1;
                cout << "Client ID: " << row[0] << "\n";
                cout << "Name: " << row[1] << "\n";
                cout << "Phone No: " << row[2] << "\n";
                cout << "Address: " << row[3] << "\n";
                cout << "NID: " << row[4] << "\n";
                break;
            }
        }
        //if the client isn't registered
        if (count == 0)
            cout << "Record not found\n";

    }
    // virtual function for polymorphism
    virtual int update()
    {
        fstream fout;
        //open file to append new client data
        fout.open("client.csv", ios::out | ios::app);
        int c_id;
        //getting the client informations
        string c_name;
        string c_phone_no;
        string c_address;
        string c_nid;
        cout<<"Enter Client ID:";cin>>c_id;
        cout<<endl<<"Enter Client Name:";cin>>c_name;
        cout<<endl<<"Enter Client Phone No:";cin>>c_phone_no;
        cout<<endl<<"Enter Client Address:";cin>>c_address;
        cout<<endl<<"Enter Client NID:";cin>>c_nid;
        //printing the client details in csv file
        fout << c_id << ","
                 << c_name << ","
                 << c_phone_no << ","
                 << c_address << ","
                 << c_nid << "\n";
        fout.close();
    }
    /*
    we can also get the informations using constructor
    client(string c_name,string c_phone_no,string c_address,string c_nid,char c_type)
    {
        c_id_count++; c_id=c_id_count;
        this->c_name=c_name; this->c_phone_no=c_phone_no; this->c_address=c_address; this->c_nid=c_nid; this->c_type=c_type;
    }
    */
};
//derived class of the base class client
//virtually iherited client to solve diamond problem
class client_hotelroom:virtual public client
{
public:
    //extented check function to check if a hotel room is vacant
    void check()
    {
        //opening txt file to read
        ifstream inf("hotelroom.txt");
        //if the text file is not available
        if(!inf) cout<<endl<<"Unable to open hotelroom file"<<endl;
        int room_id; string room_type; string room_book;
        cout<<endl<<"hotelrooms to book:"<<endl;
        //reading the whole file to print available hotel rooms
        while(!inf.eof())
        {
            inf>>room_id>>room_type>>room_book;
            if(room_book=="NULL")
            cout<<room_id<<" "<<room_type<<endl;
        }
        //closing the file
        inf.close();
    }
    //extented update funtion to book a hotel room
    int update()
    {
        //taking the information to book a definite room
        int target_room_id,c_id;
        cout<<"Please enter the required room id:";
        cin>>target_room_id;
        cout<<"Please enter the client id:";
        cin>>c_id;
        //changing the int c_id to string client_id to compare
        string client_id;
        stringstream ss;
        ss << c_id;
        client_id = ss.str();
        //opening the text file to read and append
        ifstream inf("hotelroom.txt");
        ofstream outf("hotelroom1.txt");
        if(!inf) cout<<endl<<"Unable to open hotelroom file"<<endl;
        int room_id; string room_type; string room_book;
        //taking all the data to book the required room
        while(!inf.eof())
        {
            inf>>room_id>>room_type>>room_book;
            if(room_id==target_room_id)
            {
                //using the base class data member to calculate client's cost
                cost_cnt+=1000;
                cout<<room_id<<" "<<room_type<<endl;
                //updating the room id with client_id to make it booked
                outf<<room_id<<" "<<room_type<<" "<<client_id<<endl;
            }
            else
            {
                //if it isn't the required room then simply rewriting it
                outf<<room_id<<" "<<room_type<<" "<<room_book<<endl;
            }
        }
        //closing the two files to save update
        outf.close();
        inf.close();
        //deleting previous text file then renaming the updated textfile to replace the previous one
        remove("hotelroom.txt");
        rename("hotelroom1.txt","hotelroom.txt");
        //return the cost of the client
        return cost_cnt;
    }
    //checkout a booked room to make it available again
    void checkout()
    {
        //getting necessary infos and changing to string
        int c_id;
        cout<<"Please enter the client id:";
        cin>>c_id;
        string client_id;
        stringstream ss;
        ss << c_id;
        client_id = ss.str();
        //read & write the text file
        ifstream inf("hotelroom.txt");
        ofstream outf("hotelroom1.txt");
        if(!inf) cout<<endl<<"Unable to open hotelroom file"<<endl;
        int room_id; string room_type; string room_book;
        //updating the rooms which the client hold to make it available
        while(true)
        {
            inf>>room_id>>room_type>>room_book;
            if(inf.eof()) break;
            if(room_book==client_id)
            {
                cout<<room_id<<" "<<room_type<<endl;
                outf<<room_id<<" "<<room_type<<" "<<"NULL"<<endl;
            }
            else
            {
                outf<<room_id<<" "<<room_type<<" "<<room_book<<endl;
            }
        }
        //closing the file and replacing the previous file
        outf.close();
        inf.close();
        remove("hotelroom.txt");
        rename("hotelroom1.txt","hotelroom.txt");
    }
    //virtual function for polymorphism in derived class cost
    virtual void display_cost(){};
};
//client's derived class to book the convention hall
class client_conventionhall:virtual public client
{
    public:
        //check function to check if the hall is empty in the required time
    void check()
    {
        //opening the text file and taking necessary informations
        ifstream inf("conventionhall.txt");
        if(!inf) cout<<endl<<"Unable to open conventionhall file"<<endl;
        string day,time,hall_book,target_day,target_time,res="Not booked";
        cout<<endl<<"Please enter the date(Ex: 23/05/2019):";cin>>target_day;
        cout<<endl<<"Please enter the time(07:00 / 11:00):";cin>>target_time;
        //If the required time exists then the result(res) will be changed to booked
        while(!inf.eof())
        {
            inf>>day>>time>>hall_book;
            cout<<day<<" "<<time<<" "<<hall_book<<endl;
            if(day==target_day && time==target_time) res="booked";
        }
        //if any of the previous booking not resembles then it will show not booked and closing the file
        cout<<endl<<res<<endl;
        inf.close();
    }
    //updating the booking of the convention hall
    int update()
    {
        //taking necessary infos to book a time
        string target_day,target_time;int c_id;
        cout<<"Please enter the required date:";
        cin>>target_day;
        cout<<"Please enter the required time:";
        cin>>target_time;
        cout<<"Please enter the client id:";
        cin>>c_id;
        //calculating the cost
        cost_cnt+=20000;
        //opening the text file to append and returning the cost
        ofstream outf("conventionhall.txt",ios::app);
        outf<<endl<<target_day<<" "<<target_time<<" "<<c_id;
        outf.close();
        return cost_cnt;
    }
    virtual void display_cost(){};
};
//derived class of client to book restaurant
class client_restaurant:virtual public client
{
public:
    //check if the restaurant is booked or not
    void check()
    {
        //input the necessary infos
        ifstream inf("restaurant.txt");
        if(!inf) cout<<endl<<"Unable to open restaurant file"<<endl;
        string day,time,res_book,target_day,target_time,res="Not booked";
        cout<<endl<<"Please enter the date(Ex: 23/05/2019):";cin>>target_day;
        cout<<endl<<"Please enter the time(Ex: 07:00):";cin>>target_time;
        //comparing with the required time and giving result
        while(!inf.eof())
        {
            inf>>day>>time>>res_book;
            cout<<day<<" "<<time<<" "<<res_book<<endl;
            if(day==target_day && time==target_time) res="booked";
        }
        cout<<endl<<res<<endl;
        inf.close();
    }
    //booking the restaurant
    int update()
    {
        //taking necessary data
        string target_day,target_time;int c_id;
        cout<<"Please enter the required date:";
        cin>>target_day;
        cout<<"Please enter the required time:";
        cin>>target_time;
        cout<<"Please enter the client id:";
        cin>>c_id;
        //cost count
        cost_cnt+=200;
        //write the text file and returning cost
        ofstream outf("restaurant.txt",ios::app);
        outf<<endl<<target_day<<" "<<target_time<<" "<<c_id;
        outf.close();
        return cost_cnt;
    }
    virtual void display_cost(){};
};
//derived class of children of the base class, creating diamond problem
//cost class derived from all the derived class of client
class cost : public client_conventionhall, public client_hotelroom, public client_restaurant
{
public:
    //check and update function for creating polymorphism
    void check(){}
    int update() {}
    //displaying the total cost of a client
    //previously declared virtually
    void display_cost(int cost)
    {
        cout<<endl<<"Total cost:"<<cost<<endl;
        int paid; cout<<endl<<"Paid money:"<<endl; cin>>paid;
        cout<<endl<<"Recievable change:"<<paid-cost<<endl;
    }
    //operator overloading to compute the cost
    cost operator - (cost c)
    {
        cost c3;
        c3.cost_cnt = c.cost_cnt - this->cost_cnt;
        return c3;
    }
};
//main function
int main()
{
    //base class pointer and other class objects
    client *bptr; int t;
    client c1;
    client_conventionhall ch1;
    client_hotelroom h1;
    client_restaurant r1;
    cost c2;
    //displaying the options
    while(true)
    {
        //options to create and check client id
        A:cout<<endl<<"Type 1 to search for a client id"<<endl<<"Type 2 to create a client id"<<endl<<"Type 0 end"<<endl;cin>>t;
        //base class pointer pointing to a base class object
        bptr=&c1;
        //exception handing if gives unnecessary inputs
        try
        {
            if(t==1) bptr->check();
            else if(t==2) bptr->update();
            else if (t==0) {}
            else throw(t);
        }
        catch(...)
        {
            cout<<endl<<"typed unavailable option"; goto A;
        }
        //options to book and checkout
        B:cout<<endl<<"Type 1 to book a hotelroom"<<endl<<"Type 2 to book convention hall"<<endl<<"Type 3 to reserve restaurant meal"<<endl<<"Type 4 to check out hotel room"<<endl<<"Type 0 to end"<<endl;cin>>t;
        //exception handing if gives unnecessary inputs
        try
        {
            //base class pointer pointing to derivved class objects
            //display costs if anything is booked
            if(t==1) {bptr= &h1;bptr->cost_cnt=0;bptr->check();cout<<endl<<"Type 1 to checkin , Type 0 to not"<<endl;cin>>t;
            if(t){int i,d;cout<<endl<<"How many rooms do you need?"<<endl;cin>>i;while(i--) d=bptr->update(); c2.display_cost(d);}}
            else if(t==2) {bptr= &ch1;bptr->cost_cnt=0; bptr->check();cout<<endl<<"Type 1 to book , Type 0 to not"<<endl;cin>>t;if(t) c2.display_cost(bptr->update());}
            else if(t==3) {bptr= &r1;bptr->cost_cnt=0; bptr->check();cout<<endl<<"Type 1 to book , Type 0 to not"<<endl;cin>>t;if(t) c2.display_cost(bptr->update());}
            else if(t==4) {h1.checkout();}
            else if (t==0) {}
            else throw(t);
        }
        catch(...)
        {
            cout<<endl<<"typed unavailable option";
            goto B;
        }
    }
}
