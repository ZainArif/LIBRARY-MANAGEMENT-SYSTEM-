#include<iostream>
//#include<cstdio>
#include<string>
#include<fstream>
#include<iomanip>
using namespace std;

fstream fp,fp1,fp2;

class LIBRARY {
public:
	string l_name;
	string location;
};
LIBRARY l2;

class INTERFACE {
public:
	virtual void info()=0;
};

class BOOK : public INTERFACE {
public:
	char title[20];	
	char author[20];
	int book_no;
	void add_books();
	void modify_book();
	void info();	
};
void BOOK::add_books() {
    cout<<endl<<"Enter author's name:";
    cin.ignore();
    cin.getline(author,20);
	cout<<endl<<"Enter name of book:";    
    cin.getline(title,20);
    cout<<endl<<"Enter book no:";
    cin>>book_no;
}
void BOOK::modify_book() {
    cout<<endl<<"Book no: "<<book_no;
	cout<<endl<<"Enter author's name:";
    cin.ignore();
    cin.getline(author,20);
	cout<<endl<<"Enter name of book:";    
    cin.getline(title,20);
}
void BOOK::info(){
    cout<<endl<<setw(14)<<book_no<<setw(28)<<title<<setw(25)<<author;
}
BOOK b1;

class READER : public INTERFACE {
public:
    int book,book1,ret,ret1;
    char r_name[20],issue_date[20];
    int id;
	void create_id();
	void modify_id();
	void info();
};
void READER::modify_id() {
	cout<<endl<<"Id no: "<<id;
	cout<<endl<<"Enter reader's name:";
    cin.ignore();
	cin.getline(r_name,20);
}
void READER::create_id() {
	cout<<endl<<"Enter id no:";
	cin>>id;
	cout<<endl<<"Enter reader's name:";
    cin.ignore();
	cin.getline(r_name,20);
}
void READER::info() {
    cout<<endl<<setw(13)<<id<<setw(20)<<r_name<<setw(19)<<book<<setw(19)<<book1;
}
READER r1;

class BOOK_BANK : public READER , public BOOK   {
public:
	int bno,ino,i,x,fl,fl1,fl2,seta,setb;
	void pbooks();
};
void BOOK_BANK::pbooks() {
	fl=0,fl1=0,fl2=0,i=0,seta=0,setb=0;
	fp.open("book123.dat",ios::in);
	fp1.open("reader.dat",ios::in|ios::out);
	cout<<endl<<"Enter reader id no:";
	cin>>ino;
	while(fp1.read((char*)&r1,sizeof(READER)))
	   {
	       if(r1.id==ino){	          
	          setb=1;
	          fl2=1;
	       }
	       if(setb==1){
	          cout<<endl<<"Enter book no:";
			  cin>>bno;   
		      while(fp.read((char*)&b1,sizeof(BOOK)) )
	          {   
	             if(b1.book_no==bno)
	             {
	             	if( (r1.book==bno) || (r1.book1==bno) )
					   cout<<endl<<"Book is already issued .";
					else
					   fl=1;
	             	fl1=1;
	                seta=1;	
	             }
				 if(fl==1){
				 	if(r1.ret==1)
				 	  cout<<"Please return the previous book.";
				 	else{
				 		cout<<"Enter issue date (DD/MM/YY): ";
				 		cin>>r1.issue_date;
				 		r1.ret=1;
				        r1.book=bno;
	                    long int pos=(i*sizeof(r1));
				        fp1.seekp(pos,ios::beg);
	                    fp1.write((char*)&r1,sizeof(READER));
			            cout<<endl<<"Book issued successfully."; 
		             } 
		         }
			     if(fl1==1)
				    break;		   
		      }
		      if(seta==0)
              cout<<endl<<"Book not found.";
           }
           i++;
	       if(fl2==1)
	         break;
       }
       if(fl2==0)
       cout<<endl<<"Id no not found.";
       fp.close();
       fp1.close();
}
BOOK_BANK bb;

class REFERENCE_SECTION : public READER , public BOOK  {
public:
	int bno,ino,i,x,fl,fl1,fl2,seta,setb;
	void pbooks();
};
void REFERENCE_SECTION::pbooks() {
	fl=0,fl1=0,fl2=0,i=0,seta=0,setb=0;
	fp.open("book123.dat",ios::in);
	fp1.open("reader.dat",ios::in|ios::out);
	cout<<endl<<"Enter reader id no:";
	   cin>>ino;
	while(fp1.read((char*)&r1,sizeof(READER)))
	   {
	       if(r1.id==ino){
	       	  setb=1;
	          fl2=1;	
	       }
	       if(setb==1){
	          cout<<endl<<"Enter book no:";
			  cin>>bno;   
		      while(fp.read((char*)&b1,sizeof(BOOK)) )
	          {
	             if(b1.book_no==bno)
	             {
	             	if( (r1.book1==bno) || (r1.book==bno) )
					   cout<<endl<<"Book is already issued.";
	             	else
					    fl=1;
	             	fl1=1;
	                seta=1;	   
	             }
				 if(fl==1){	   
				 	if(r1.ret1==1)
				 	    cout<<"Please return the previous book.";
				 	else{
				 		r1.ret1=1;
	                    r1.book1=bno;
	                    long int pos=(i*sizeof(r1));
					    fp1.seekp(pos,ios::beg);
	                    fp1.write((char*)&r1,sizeof(READER));
			            cout<<endl<<"Book issued successfully."; 
		            }
			     }
			     if(fl1==1)
				    break;
				   
		      }
		      if(seta==0)
               cout<<endl<<"Book not found.";      
           }
           i++;
	       if(fl2==1)
	         break;
       }
       if(fl2==0)
       cout<<endl<<"Id no not found.";
       fp.close();
       fp1.close();
}
REFERENCE_SECTION rs;

class LIBRARIAN :  public REFERENCE_SECTION , public BOOK_BANK {
public:
	int k;
	void issue_books();
	int bno,ino,i,fl,fl2,fl1,setb,day,fine;
	void collect_books();
};

void LIBRARIAN::issue_books() {
	cout<<endl<<"What reader wants either borrow or read book?";
	cout<<endl<<"Press 1 for borrow and press 2 for reading:";
	cin>>k;
	if(k==1)
	  bb.pbooks();
	else
	  rs.pbooks();  
}
void LIBRARIAN::collect_books() {
	fl=0,fl2=0,fl1=0,i=0,setb=0,day,fine;
	fp1.open("reader.dat",ios::in|ios::out);
	cout<<endl<<"Enter reader id no:";
	cin>>ino;
	while(fp1.read((char*)&r1,sizeof(READER)))
	   {
	       if(r1.id==ino){
	       	setb=1;
	        fl2=1;
	       }
	       if(setb==1){
	          cout<<endl<<"Enter book no:";
			  cin>>bno;   
	          if(r1.book1==bno){
	            fl=1;
	          }
	          else if(r1.book==bno){
	            fl1=1;
	          }
	          else
	            cout<<endl<<"Book not found.";
			  if(fl==1){
			  	r1.ret1=0;
	            r1.book1=0;
	            long int pos=(i*sizeof(r1));
				fp1.seekp(pos,ios::beg);
	            fp1.write((char*)&r1,sizeof(READER));
			    cout<<endl<<"Book returned."; 
		      }
		      if(fl1==1){
		      	cout<<endl<<"Issue date: "<<r1.issue_date;
		      	cout<<endl<<"In how many days book is depositing ? ";
				cin>>day;
				if(day>15)
				{
				   fine=(day-15)*5;
				   cout<<endl<<"Fine = Rs. "<<fine;
				}
		      	r1.ret=0;
	            r1.book=0;
	            long int pos=(i*sizeof(r1));
				fp1.seekp(pos,ios::beg);
	            fp1.write((char*)&r1,sizeof(READER));
			    cout<<endl<<"Book returned."; 
		      } 
           }
           i++;
	       if(fl2==1)
	         break;
       }
       if(fl2==0)
       cout<<endl<<"Id no not found.";
       fp.close();
       fp1.close();
}
LIBRARIAN l1;

class FILING {
public:	
	void write_book();
	void modify_book();
	void del_book();
	void write_reader();
	void modify_reader();
	void del_reader();
	void display_allb();
	void display_allr();
};

void FILING::write_book()
{
	char ch;
	do
	{	
 	    fp.open("book123.dat",ios::out|ios::app);
		b1.add_books();
		fp.write((char*)&b1,sizeof(BOOK));
	    fp.close();
		cout<<"\n\nDo you want to add more record? (Y/N)";
		cin>>ch;
		system("cls");
	}while(ch=='y'||ch=='Y');
}

void FILING::modify_book()
{
	char ch;
	int bno,i,fl,fl1,seta;
	do
	{	
	    i=0,fl=0,fl1=0,seta=0;
 	    cout<<endl<<"Enter book no:";
		cin>>bno;
		fp.open("book123.dat",ios::out|ios::in); 
		while(fp.read((char*)&b1,sizeof(BOOK)) )
	          {
	             if(b1.book_no==bno)
	             {
	            	fl=1;
	             	fl1=1;
	                seta=1;	   
	             }
				 if(fl==1){
				 	cout<<"========================================================================\n";
	                cout<<"\tBook Number"<<setw(25)<<"Book Name"<<setw(25)<<"Author Name\n";
	                cout<<"========================================================================\n";
	                b1.info();
	                cout<<endl<<"\n\nEnter new details of book.";
	                b1.modify_book();
					long int pos=(i*sizeof(b1));
					fp.seekp(pos,ios::beg);
	                fp.write((char*)&b1,sizeof(BOOK));
			        cout<<endl<<"Book modified successfully."; 
		         }
		         i++;
			     if(fl1==1)
				    break;
		      }
		      if(seta==0)
                cout<<endl<<"Book not found.";
	    fp.close();
		cout<<"\n\nDo you want to modify more record? (Y/N)";
		cin>>ch;
		system("cls");
	}while(ch=='y'||ch=='Y');
}

void FILING::del_book()
{
	int bno,flag=0;
	cout<<endl<<"Enter book no. : ";
	cin>>bno;
	fp.open("book123.dat",ios::in|ios::out);
	fp2.open("temp.dat",ios::out);
	fp.seekg(0,ios::beg);
	while(fp.read((char*)&b1,sizeof(BOOK)))
	{
		if(b1.book_no!=bno)  
			fp2.write((char*)&b1,sizeof(BOOK));
		else
		   flag=1;
	}
	fp2.close();
    fp.close();
    remove("book123.dat");
    rename("temp.dat","book123.dat");
    if(flag==1)
      cout<<"Book deleted.";
    else
      cout<<"Book not found.";
}

void FILING::write_reader()
{
	char ch;
	do
	{
	    fp1.open("reader.dat",ios::out|ios::app);
		r1.create_id();
		fp1.write((char*)&r1,sizeof(READER));
	    fp1.close();
		cout<<"\n\nDo you want to add more record? (Y/N)";
		cin>>ch;
		system("cls");
	}while(ch=='y'||ch=='Y');
}

void FILING::modify_reader()
{
	char ch;
	int ino,i,fl,fl1,seta;
	do
	{	
	    i=0,fl=0,fl1=0,seta=0;
 	    cout<<endl<<"Enter id no:";
		cin>>ino;
		fp1.open("reader.dat",ios::out|ios::in); 
		while(fp1.read((char*)&r1,sizeof(READER)) )
	          {
	             if(r1.id==ino)
	             {
	            	fl=1;
	             	fl1=1;
	                seta=1;	   
	             }
				 if(fl==1){
				 	cout<<"===============================================================================\n";
	                cout<<"\tId Number"<<setw(20)<<"Reader Name"<<setw(29)<<"Book Number\n\n";
	                cout<<setw(55)<<"Book Bank"<<setw(25)<<"Reference Section\n";
	                cout<<"===============================================================================\n";	
				 	r1.info();
	                cout<<endl<<"\n\nEnter new details of reader.";
	                r1.modify_id();
					long int pos=(i*sizeof(r1));
					fp1.seekp(pos,ios::beg);
	                fp1.write((char*)&r1,sizeof(READER));
			        cout<<endl<<"Reader modified successfully."; 
		         }
		         i++;
			     if(fl1==1)
				    break;
		      }
		      if(seta==0)
                cout<<endl<<"Id no not found.";
	    fp1.close();
		cout<<"\n\nDo you want to modify more record? (Y/N)";
		cin>>ch;
		system("cls");
	}while(ch=='y'||ch=='Y');
}

void FILING::del_reader()
{
	int ino,flag=0;
	cout<<endl<<"Enter book no. : ";
	cin>>ino;
	fp1.open("reader.dat",ios::in|ios::out);
	fp2.open("temp.dat",ios::out);
	fp1.seekg(0,ios::beg);
	while(fp1.read((char*)&r1,sizeof(READER)))
	{
		if(r1.id!=ino)  
			fp2.write((char*)&r1,sizeof(READER));
		else
		   flag=1;
	}
	fp2.close();
    fp1.close();
    remove("reader.dat");
    rename("temp.dat","reader.dat");
    if(flag==1)
      cout<<"Reader information deleted.";
    else
      cout<<"Id no not found.";
}

void FILING::display_allb()
{
	fp.open("book123.dat",ios::in);
	cout<<"\n\n\t\t\t\tBOOK LIST\n\n\n";
	cout<<"========================================================================\n";
	cout<<"\tBook Number"<<setw(25)<<"Book Name"<<setw(25)<<"Author Name\n";
	cout<<"========================================================================\n";
	while(fp.read((char*)&b1,sizeof(BOOK)))
	{
		b1.info();
	}
    fp.close();
}

void FILING::display_allr()
{
	cout<<"\n\n\t\t\t\tREADER LIST\n\n";
	cout<<"===============================================================================\n";
	cout<<"\tId Number"<<setw(20)<<"Reader Name"<<setw(29)<<"Book Number\n\n";
	cout<<setw(55)<<"Book Bank"<<setw(25)<<"Reference Section\n";
	cout<<"===============================================================================\n";
	fp1.open("reader.dat",ios::in);
	while(fp1.read((char*)&r1,sizeof(READER)))
	{
		r1.info();
	}
    fp1.close();
}
FILING f1;

void adm()
{
	cout<<"\n\t\t\t\t\t\tLIBRARY MANAGEMENT SYSTEM";
	cout<<endl<<endl<<endl<<endl<<"\t* Press A to add a new book.";
	cout<<endl<<"\t* Press B to create a reader's account.";
	cout<<endl<<"\t* Press C to issue a book.";
	cout<<endl<<"\t* Press D to collect a book.";
	cout<<endl<<"\t* Press E to modify book.";
	cout<<endl<<"\t* Press F to modify reader.";
	cout<<endl<<"\t* Press G to delete book.";
	cout<<endl<<"\t* Press H to delete reader.";
	cout<<endl<<"\t* Press I for books information.";
	cout<<endl<<"\t* Press J for readers information.";	
	cout<<endl<<endl;
}

int main()
{	
	l2.l_name="Engr.Abdul KALAM Library";
	l2.location="NED UNIVERSITY";
	char sel,ch;
	do
	{
		cout<<"\t\t\t\t\t\t"<<l2.l_name<<"\n\t\t\t\t\t\t     "<<l2.location;
		adm();
		cin>>sel;
		switch(sel)
		{
			case 'A':{
				system("cls");
				f1.write_book();
				break;
			}
			case 'B':{
				system("cls");
				f1.write_reader();
				break;
			}
			case 'C':{
				system("cls");
				l1.issue_books();
				break;
			}	
			case 'D':{
				system("cls");
				l1.collect_books();
				break;
			}
			case 'E':{
				system("cls");
				f1.modify_book();
				break;
			}
			case 'F':{
				system("cls");
				f1.modify_reader();
				break;
			}
			case 'G':{
				system("cls");
				f1.del_book();
				break;
			}
			case 'H':{
				system("cls");
				f1.del_reader();
				break;
			}
			case 'I':{
				system("cls");
				f1.display_allb();
				cout<<"\n\n";
				break;
			}
			case 'J':{
				system("cls");
				f1.display_allr();
				cout<<"\n\n";
				break;
			}
			default:
				cout<<"Wrong input.";
		}
		cout<<endl<<"Do you want to go back to main menu? (Y/N)";
		cin>>ch;
		cout<<endl;
		system("cls");
	}while(ch=='Y'||ch=='y');	
}
