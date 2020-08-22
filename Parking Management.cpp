#include<iostream>
using namespace std;
//#include<conio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
//#include<ctype.h>
#include<unistd.h>
#include<ctime>

class info
{
    private:
        string liscense_no;
        string vehicle_no;
        string name;
        int option;
        int v_type;
        int check;

        friend class entry;
        friend class four;
        friend class two;

    public:
        time_t inn;
        time_t outt;
        int total_time;

        info()
        {
            option=0;
            v_type=0;
            check=0;
        }
};

class entry
{
	private:
		int pass;
    public:
        static int T;
        int wheels;
        entry()
        {
        	pass=2707;
            wheels=0;
        }
    void new_customer();
    static void inc()
    {
        entry::T++;
    }
    static int T_print()
    {
        return T;
    }
};

int entry::T=0;

void entry::new_customer()
{
    cout<<"Enter Vehicle Type (2/4) -> ";
    cin>>wheels;
}

class four:public entry
{
    private:
        info *park[4][4];

    public:
    	int d;
        four()
        {
        	d=0;
            info *p;
            for(int i=0;i<4;i++)
            {
                for(int j=0;j<4;j++)
                {
                    p=new info;
                    park[i][j]=p;
                }
            }
        }

        void new_(int);
        void getdata(int i,int j,int);
        void in(int);
        void out();
        int compare(string x,int,int);
        int calculate(int i,int j);
        void receipt1(int i,int j);
        void time_in_out(int i,int j);
        void display();
};

void four::display()
{
	cout<<"Enter Passcode-> ";
	int n;
	cin>>n;
	if(n==2707)
	{
		cout<<"\nVehicle No.\tVehicle Type\tPackage\n\n";
		for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)
			{
				if(park[i][j]->check==1)
				{
					cout<<park[i][j]->vehicle_no<<"\t\t"<<park[i][j]->v_type<<"\t\t"<<park[i][j]->option<<" Hours"<<endl;
				}
			}
		}	
		d=1;
	}
	else
	{
		cout<<"\nWrong Passcode!";
		sleep(1);
		system("cls");
	}
}

void four::getdata(int l,int m,int wheels)
{
    int i=l,j=m;
    cout<<"\n\nEnter your vehicle number- ";
    cin>>park[i][j]->vehicle_no;
    cout<<"Enter your liscense number- ";
    cin>>park[i][j]->liscense_no;
    cout<<"Enter your name- ";
    cin>>park[i][j]->name;
    park[i][j]->v_type=wheels;
    cout<<"Enter the package number you want to select - ";
    cin>>park[i][j]->option;
    park[i][j]->check=1;
    time(&park[i][j]->inn);
}

void four::new_(int wheels)
{
    in(wheels);
}

void four::in(int wheels)
{
    int temp=0,i,j;
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            if(park[i][j]->check==0)
            {
                temp=1;
                break;
            }
        }
        if(temp==1)
        {
            break;
        }
    }
    if(temp==0)
    {
        cout<<"Sorry, No More Space Available!";
    }
    else
    {
        getdata(i,j,wheels);
        entry::inc();
        system("cls");
        receipt1(i,j);
    }
}

void four::out()
{
    cout<<"Enter vehicle number-> ";
    string x;
    cin>>x;
    int temp=0;
    int i,j;
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            if(park[i][j]->check!=0)
            {
                if(compare(x,i,j)==0)
                {
                    temp=1;
                    break;
                }
            }
        }
        if(temp==1)
        {
            break;
        }
    }
    system("cls");
    cout<<"Generating Reciept";
    for(int k=0;k<3;k++)
    {
        sleep(1);
	    cout<<".";
    }
    sleep(1);
    system("cls");

    if(temp==1)
    {
        cout<<"\n         RECEIPT\n";
        cout<<"     HnV Pay & Park"<<endl;
        cout<<"      Katraj, Pune"<<endl;
        cout<<"-------------------------"<<endl;
        cout<<"Vehicle Type-> 4 Wheeler";
        time(&park[i][j]->outt);
        park[i][j]->total_time=park[i][j]->outt-park[i][j]->inn;
        cout<<endl<<park[i][j]->total_time<<endl;
        time_in_out(i,j);
        cout<<"Total Rent= Rs "<<calculate(i,j)<<"\n";
        cout<<endl;
        cout<<"     ***Thank You***"<<endl;
        cout<<"-------------------------"<<endl;
        park[i][j]->check=0;
        for(int q=0;q<5;q++)
        {
            cout<<endl;
        }
    }
    else
    {
        cout<<"Vehicle not found.\n";
    }


}
int four::compare(string x,int i,int j)
{
    string temp;
    temp=park[i][j]->vehicle_no;
    int a=0;
    for(int L=0;x[L]!='\0'&&temp[L]!='\0';L++)
    {
        if(temp[L]!=x[L])
        {
            a=1;
            break;
        }
    }
    return a;
}

int four::calculate(int i,int j)
{
    int x;
    park[i][j]->total_time=park[i][j]->outt-park[i][j]->inn;
    x=park[i][j]->total_time/3600;
    int fare;
    if(x>=park[i][j]->option)
    {
        fare=((park[i][j]->option)*10)+((x+1-park[i][j]->option)*12);
    }
    else
    {
        fare=((park[i][j]->option)*10);
    }

    return fare;
}

void four::receipt1(int i,int j)
{
    cout<<"\nHnV Pay & Park\n";
    cout<<"\nTicket no. "<<100000+entry::T_print()<<endl;
    cout<<"Vehicle no. "<<park[i][j]->vehicle_no<<endl;
    cout<<"Your Ticket Expires in "<<park[i][j]->option<<" hours.";
    cout<<endl<<"Base fare-> "<<park[i][j]->option*10<<endl<<endl;
}

void four::time_in_out(int i,int j)
{
   struct tm ltm;
    ltm=*localtime(&park[i][j]->inn);

   // print various components of tm structure.
   cout<<"Date:"<<ltm.tm_mday<<"/"<<1 + ltm.tm_mon<<"/"<<1900 + ltm.tm_year<<endl;
   //cout << "Year" << 1900 + ltm.tm_year<<endl;
   //cout << "Month: "<< 1 + ltm.tm_mon<< endl;
   //cout << "Day: "<<  ltm.tm_mday << endl;
   cout << "In Time: "<< ltm.tm_hour << ":";
   cout <<  ltm.tm_min << ":";
   cout << 1 + ltm.tm_sec << endl;
   ltm=*localtime(&park[i][j]->outt);
   cout << "Out Time: "<< ltm.tm_hour << ":";
   cout <<  ltm.tm_min << ":";
   cout << 1 + ltm.tm_sec << endl;

}

//-----------------------------------------------------------------------------------------------------------------------------------------------------
class two:public entry
{
    private:
        info *park[4][4];
        friend class four;

    public:
        two()
        {
            info *p;
            for(int i=0;i<4;i++)
            {
                for(int j=0;j<4;j++)
                {
                    p=new info;
                    park[i][j]=p;
                }
            }
        }

        void new_();
        void getdata(int i,int j);
        void in();
        void out();
        int compare(string x,int,int);
        int calculate(int i,int j);
        void time_in_out(int i,int j);
        void receipt1(int i,int j);
		void display();
};

void two::display()
{
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			if(park[i][j]->check==1)
			{
				cout<<park[i][j]->vehicle_no<<"\t2"<<"\t"<<park[i][j]->option<<" Hours"<<endl;
			}
		}
	}	
}


void two::getdata(int l,int m)
{
    int i=l,j=m;
    cout<<"\n\nEnter your vehicle number- ";
    cin>>park[i][j]->vehicle_no;
    cout<<"Enter your liscense number- ";
    cin>>park[i][j]->liscense_no;
    cout<<"Enter your name- ";
    cin>>park[i][j]->name;
    park[i][j]->v_type=wheels;
    cout<<"Enter the package number you want to select - ";
    cin>>park[0][j]->option;
    park[i][j]->check=1;
    time(&park[i][j]->inn);
}

void two::new_()
{
    in();
}

void two::in()
{
    int temp=0,i,j;
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            if(park[i][j]->check==0)
            {
                temp=1;
                break;
            }
        }
        if(temp==1)
        {
            break;
        }
    }
    if(temp==0)
    {
        cout<<"Sorry, No More Space Available!";
    }
    else
    {
        getdata(i,j);
        entry::inc();
        system("cls");
        receipt1(i,j);
    }
}

void two::out()
{
    cout<<"Enter vehicle number-> ";
    string x;
    cin>>x;
    int temp=0;
    int i,j;
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            if(park[i][j]->check!=0)
            {
                if(compare(x,i,j)==0)
                {
                    temp=1;
                    break;
                }
            }
        }
        if(temp==1)
        {
            break;
        }
    }
    system("cls");
    cout<<"Generating Reciept";
    for(int k=0;k<3;k++)
    {
        sleep(1);
	    cout<<".";
    }
    sleep(1);
    system("cls");

    if(temp==1)
    {
        cout<<"\n         RECEIPT\n";
        cout<<"     HnV Pay & Park"<<endl;
        cout<<"      Katraj, Pune"<<endl;
        cout<<"-------------------------"<<endl;
        cout<<"Vehicle Type-> 2 Wheeler";
        time(&park[i][j]->outt);
        park[i][j]->total_time=park[i][j]->outt-park[i][j]->inn;
        cout<<endl<<park[i][j]->total_time<<endl;
        time_in_out(i,j);
        cout<<"Total Rent= Rs "<<calculate(i,j)<<"\n";
        cout<<endl;
        cout<<"     ***Thank You***"<<endl;
        cout<<"-------------------------"<<endl;
        park[i][j]->check=0;
        for(int q=0;q<5;q++)
        {
            cout<<endl;
        }
    }
    else
    {
        cout<<"Vehicle not found.\n";
    }


}

int two::compare(string x,int i,int j)
{
    string temp;
    temp=park[i][j]->vehicle_no;
    int a=0;
    for(int L=0;x[L]!='\0'&&temp[L]!='\0';L++)
    {
        if(temp[L]!=x[L])
        {
            a=1;
            break;
        }
    }
    return a;
}

int two::calculate(int i,int j)
{
    int x;
    park[i][j]->total_time=park[i][j]->outt-park[i][j]->inn;
    x=park[i][j]->total_time/3600;
    int fare;
    if(x>=park[i][j]->option)
    {
        fare=((park[i][j]->option)*5)+((x+1-park[i][j]->option)*6);
    }
    else
    {
        fare=((park[i][j]->option)*5);
    }

    return fare;
}

void two::receipt1(int i,int j)
{
	cout<<"\nHnV Pay & Park\n";
    cout<<"\nTicket no. "<<100000+entry::T_print()<<endl;
    cout<<"Vehicle no. "<<park[i][j]->vehicle_no<<endl;
    cout<<"Your Ticket Expires in "<<park[i][j]->option<<" hours.";
    cout<<endl<<"Base fare-> "<<park[i][j]->option*5<<endl<<endl;
}

void two::time_in_out(int i,int j)
{
   struct tm ltm;
    ltm=*localtime(&park[i][j]->inn);

   // print various components of tm structure.
   cout<<"Date:"<<ltm.tm_mday<<"/"<<1 + ltm.tm_mon<<"/"<<1900 + ltm.tm_year<<endl;
   //cout << "Year" << 1900 + ltm.tm_year<<endl;
   //cout << "Month: "<< 1 + ltm.tm_mon<< endl;
   //cout << "Day: "<<  ltm.tm_mday << endl;
   cout << "In Time: "<< ltm.tm_hour << ":";
   cout <<  ltm.tm_min << ":";
   cout << 1 + ltm.tm_sec << endl;
   ltm=*localtime(&park[i][j]->outt);
   cout << "Out Time: "<< ltm.tm_hour << ":";
   cout <<  ltm.tm_min << ":";
   cout << 1 + ltm.tm_sec << endl;

}


int main()
{
    entry E;
    four A;
    two B;
    cout<<"HnV Pay & Park\nKatraj, Pune.\n";
    cout<<"\n";
    cout<<"Enter - '1' for arrival\n\t'2' for departure\n\t'3' to Display Parked Vehicles\n\t'0' to TERMINATE\n";
    int n;
    cin>>n;
    while(n>0)
    {
    	switch(n)
    	{
    		case 1:
    			{
    				system("cls");
    				cout<<"HnV Pay & Park\nKatraj, Pune."<<endl<<endl;
    				int temp=0;
    				do{
    					system("cls");
    					cout<<"HnV Pay & Park\nKatraj, Pune."<<endl<<endl;
    					E.new_customer();
 
    					if(E.wheels==4)
    					{
    						cout<<"\n\n\t\t***PACKAGES***\n";
    						cout<<"1-> 1 Hour - Rs 10.\n";
    						cout<<"2-> 2 Hour - Rs 20.\n";
    						cout<<"3-> 3 Hour - Rs 30.\n";
    						cout<<"and so on....";
    						cout<<"\n";
    						cout<<"Rs 12 per extra hour";
        					A.new_(E.wheels);
        					temp=0;
        					for(int z=0;z<10;z++)
        					{
        						cout<<endl;
							}
    					}
    					else if(E.wheels==2)
    					{
    						cout<<"\n\n\t\t***PACKAGES***\n";
    						cout<<"1-> 1 Hour - Rs 5.\n";
    						cout<<"2-> 2 Hour - Rs 10.\n";
    						cout<<"3-> 3 Hour - Rs 15.\n";
    						cout<<"and so on....";
    						cout<<"\n";
    						cout<<"Rs 6 per extra hour";    						
        					B.new_();
        					temp=0;
        					for(int z=0;z<10;z++)
        					{
        						cout<<endl;
							}
    					}
    					else
    					{
    						cout<<"\nEnter Correct Choice!!!";
    						temp=1;
    						cout<<"\n\nReloading";
    						sleep(1);
							for(int r=0;r<3;r++)
							{
								cout<<".";
								sleep(1);
							}
    						
						}
					}while(temp==1);
					break;
				}
				case 2:
					{
						cout<<"Enter Vehicle type(2/4)- ";
						int x;
						cin>>x;
						if(x==2)
						{
							B.out();
						}
						else if(x==4)
						{
							A.out();
						}
						else
						{
							cout<<"\nEnter correct choice.";
						}
						cout<<"\n\n\n\n\n\n\n";
						break;
					}
					case 3:
						{
							A.display();
							if(A.d==1)
							{
								B.display();
							}
							A.d=0;
							for(int x=0;x<10;x++)
							{
								cout<<endl;
							}
							break;
						}
				default:
					cout<<"\n\nEnter correct choice!!";
					sleep(1);
					system("cls");
		}
		cout<<"Enter 1 to continue.";
		cin>>n;
		system("cls");
		cout<<"HnV Pay & Park\nKatraj, Pune."<<endl<<endl;
		cout<<"Enter - '1' for arrival\n\t'2' for departure\n\t'3' to Display Parked Vehicles\n\t'0' to TERMINATE\n";
    	cin>>n;
	}
    
    
    return 0;
}

