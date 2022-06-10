#include<iostream>
#include<fstream>
#include<iomanip>
 
using namespace std;
 
 
 
class student
{
	int idnum;
	char name[100];
	int cc202, cc201, stat203, mth101, ss110, psy110, pe111, nstp101;
	double per;
	char grade;
	void calculate();	
public:
	void getdata();		
	void showdata() const;	
	void show_tabular() const;
	int getIDNum() const;
}; 
 
 
void student::calculate()
{
	per=(cc202+cc201+stat203+mth101+ss110+psy110+pe111+nstp101)/8.0;
	if(per>=90)
	 cout<<"\nTotal Grade is A+";
	else if(per>=80)
	cout<<"\nTotal Grade is A";
	else if(per>=75)
	cout<<"\nTotal Grade is A-";
	else if(per>=70)
	cout<<"\nTotal Grade is B+";
	else if(per>=65)
	cout<<"\nTotal Grade is B";
	else if(per>=60)
	cout<<"\nTotal Grade is B-";
	else if(per>=55)
	cout<<"\nTotal Grade is C+";
	else if(per>=50)
	cout<<"\nTotal Grade is C";
	else
	cout<<"vTotal Grade is F";
}
 
void student::getdata()
{
	cout<<"\nEnter The ID number of the student "; /*only accepts int value, otherwise, loop*/
	cin>>idnum;
	cout<<"\n\nEnter student's Name: ";
	cin.ignore();
	cin.getline(name,100);
	cout<<"\nEnter student's CC 202 grade: ";
	cin>>cc202;
	cout<<"\nEnter student's CC 201 grade: ";
	cin>>cc201;
	cout<<"\nEnter student's STAT 203 grade: ";
	cin>>stat203;
	cout<<"\nEnter student's MTH 101 grade: ";
	cin>>mth101;
	cout<<"\nEnter student's SS 110 grade: ";
	cin>>ss110;
	cout<<"\nEnter student's PSY 110 grade: ";
	cin>>psy110;
	cout<<"\nEnter student's PE 111 grade: ";
	cin>>pe111;
	cout<<"\nEnter student's NSTP 101 grade: ";
	cin>>nstp101;
	calculate();
}
 
void student::showdata() const
{
	cout<<"\nID Number: "<<idnum;
	cout<<"\nName: "<<name;
	cout<<"\nCC202: "<<cc202;
	cout<<"\nCC201: "<<cc201;
	cout<<"\nSTAT203: "<<stat203;
	cout<<"\nMTH101: "<<mth101;
	cout<<"\nSS110: "<<ss110;
	cout<<"\nPSY110: "<<psy110;
	cout<<"\nPE111: "<<pe111;
	cout<<"\nNSTP101: "<<nstp101;
	cout<<"\nPercentage: "<<per;
	cout<<"\nLetter Grade: "<<grade;
}
 
void student::show_tabular() const
{
	cout<<idnum<<setw(6)<<" "<<name<<setw(6)<<cc202<<setw(5)<<cc201<<setw(7)<<stat203<<setw(7)
		<<mth101<<setw(7)<<ss110<<setw(6)<<psy110<<setw(7)<<pe111<<setw(7)<<nstp101<<setw(10)<<per<<setw(5)<<grade<<endl;
}
 
int  student::getIDNum() const
{
	return idnum;
}
 
 
 
void SaveStudent();	
void displayAll();	
void Searchdisplay(int);	
void modifyStudent(int);	
void deleteStudent(int);	
void DisplayClassResult();	
void DisplayResult();			
	
 
 
 
 
void write_student()
{
	student st;
	ofstream outFile;
	outFile.open("student.dat",ios::binary|ios::app);
	st.getdata();
	outFile.write(reinterpret_cast<char *> (&st), sizeof(student));
	outFile.close();
    	cout<<"\n\nStudent Registered succsesfully ";
	cin.ignore();
	cin.get();
}
 
 
 
void display_all()
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be opened !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		st.showdata();
		cout<<"\n\n====================================\n";
	}
	inFile.close();
	cin.ignore();
	cin.get();
}
 
 
 
void display_sp(int n)
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	bool flag=false;
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		if(st.getIDNum()==n)
		{
	  		 st.showdata();
			 flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\n\nrecord not exist";
	cin.ignore();
	cin.get();
}
 
 
void modify_student(int n)
{
	bool found=false;
	student st;
	fstream File;
	File.open("student.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
    	while(!File.eof() && found==false)
	{
 
		File.read(reinterpret_cast<char *> (&st), sizeof(student));
		if(st.getIDNum()==n)
		{
			st.showdata();
			cout<<"\n\nPlease Enter The New Details of student"<<endl;
			st.getdata();
		    	int pos=(-1)*static_cast<int>(sizeof(st));
		    	File.seekp(pos,ios::cur);
		    	File.write(reinterpret_cast<char *> (&st), sizeof(student));
		    	cout<<"\n\n\t Record Updated";
		    	found=true;
		}
	}
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
	cin.ignore();
	cin.get();
}
 
 
 
void delete_student(int n)
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	ofstream outFile;
	outFile.open("Temp.dat",ios::out);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		if(st.getIDNum()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&st), sizeof(student));
		}
	}
	outFile.close();
	inFile.close();
	remove("student.dat");
	rename("Temp.dat","student.dat");
	cout<<"\n\n\tRecord Deleted ..";
	cin.ignore();
	cin.get();
}
 
 
void class_result()
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be opened !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	cout<<"\n\n\t\tALL STUDENTS RESULT \n\n";
	cout<<"=============================================================================\n";
	cout<<"R.No   Name   CC202 CC201 STAT203 MTH101 SS110 PSY110 PE111 NSTP101 %age Grade"<<endl;
	cout<<"=============================================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		st.show_tabular();
	}
	cin.ignore();
	cin.get();
	inFile.close();
}
 
 
 
 
int main()
{
	char ch;
	int num;
	cout.setf(ios::fixed|ios::showpoint);
	cout<<setprecision(2); 
	do
	{
	system("cls");
    cout<<"     **********************************************\n";
    cout<<"     *  STUDENT REGISTRATION AND MARK LIST SYSTEM *\n";
    cout<<"                  * BSCS COURSE *\n";
    cout<<"     **********************************************\n";
	cout<<"\n\t1.To Register New student";
	cout<<"\n\t2.To Show Registerd Students and Their Grade";
	cout<<"\n\t3.To Search for a student ";
	cout<<"\n\t4.To Edit a student record";
	cout<<"\n\t5.To Delete a student record";
	cout<<"\n\t6.To Display Class Result";
	cout<<"\n\t7.To Exit";

	cout<<"\n\tPlease Enter Your Choice (1-7): ";
	cin>>ch;
	system("cls");
	switch(ch)
	{
	case '1':	write_student(); break;
	case '2':	display_all(); break;
	case '3':	cout<<"\n\n\tPlease Enter Student's ID number: "; cin>>num;
				display_sp(num); break;
	case '4':	cout<<"\n\n\tPlease Enter Student's ID number: "; cin>>num;
			modify_student(num);break;
	case '5':	cout<<"\n\n\tPlease Enter Student's ID number: "; cin>>num;
			delete_student(num);break;
    case '6' :	class_result(); break;
	case '7':	exit(0);;
	default:	cout<<"\a"; 
		
    }
	}while(ch!='7');
 
	return 0;
}
