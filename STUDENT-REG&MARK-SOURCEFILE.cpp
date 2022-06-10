#include<iostream>
 
//fstream is needed because we will use file systems.
#include<fstream>
 
using namespace std;
 
/*declaring fstream global variable used 
  to open, write, read and close files in this program.*/
fstream storage;

 
struct student_profile{
    char FName[100];
    char LName[100];
    char reg_year[100];
    char course[100];
    char id[100];
    int no_courses;
    char course_Name[100];
    char course_code[100];
    int credit_hour;
    int quiz_one;
    int quiz_two;
    int quiz_three;
    int mid;
    int assignment;
    int lab;
    int final_exam;
};  
 
/* creating structure variable from student_profile.
   the name this structure variable is student.
   it is used to hold name, last name, id etc
*/
student_profile student; 
 
 
/* function used to register student.
   it accept student details then it write those data to file.
   so student details will be saved in text file for later use.
*/
void function_to_register(){
 cout<<"        Write First Name of student: ";
 cin>>student.FName;
 cout<<"        Write Last Name of student: ";
 cin>>student.LName;
 cout<<"        Write Registration year: ";
 cin>>student.reg_year;
 cout<<"        Write Course of student: ";
 cin>>student.course;
 cout<<"        Write number of courses that student learns in this semester and register them one by one\n";
 cout<<"        Number of courses: ";
 cin>> student.no_courses;
  
  
/* for loop used to register multiple courses for one student
   based on the student's number of courses entered.
 */
 for(int a=1; a<=student.no_courses; a++) {
 cout<<"         Write course Name: ";
 cin>>student.course_Name;
 cout<<"         Enter grade for quiz one: ";
 cin>>student.quiz_one;
 cout<<"         Enter grade for quiz two: ";
 cin>>student.quiz_two;
 cout<<"         Enter grade for quiz three: ";
 cin>>student.quiz_three;
 cout<<"         Enter midterm grade: ";
 cin>>student.mid;
 cout<<"         Enter assignment grade: ";
 cin>>student.assignment;
 cout<<"         Enter lab grade: ";
 cin>>student.lab;
 cout<<"         Enter final exam grade: ";
 cin>>student.final_exam;
 storage.open("marklist.txt",ios::app) ;
   storage.write((char*)&student,sizeof(student));
   //storage.write(student,sizeof(student));
 storage.close(); 
 }
}
  
 
 /* function used to calculate grade of each course. 
    we call this function when the program is displaying grade of student.
 */
void grade_calculator(int totalMark) { 
    if(totalMark>=90 && totalMark<=100)
        cout<<"A+";
    else if(totalMark>=80 && totalMark<90)
        cout<<"A";
    else if(totalMark>=70 && totalMark<80)
        cout<<"B";
    else if(totalMark>=60 && totalMark<70)
        cout<<"C+";
    else if(totalMark>=50 && totalMark<60)
        cout<<"D";
    else if(totalMark>=0 && totalMark<50)
        cout<<"F";
    else
        cout<<"NG";   
    }
     
     
/* function used to display registered students on the screen.
   this function gets the registered student from that file 
   we used above to store student details.
*/
void seeRegistered() {    
 storage.open("marklist.txt",ios::app);
 storage.close();
 
 storage.open("marklist.txt",ios::in);
 storage.read((char*)&student,sizeof(student));
 
 while (storage.eof()==0) { 
  cout<<"\n\n\n";
  cout<<"  Full Name: "<<student.FName<<"  "<<student.LName<<endl;
  cout<<"  Registration Year: "<<student.reg_year<<endl;
  cout<<"  Faculty: "<<student.course<<endl;
  cout<<"  *****************************************************************************\n";
  cout<<"  ******************************STUDENT MARK LIST******************************\n";
  cout<<"  *****************************************************************************\n";  
  cout<<"  Subject    Quiz1   Quiz2   Quiz3    Mid   Assignment    Final   Total   Grade\n";
  cout<<"  _____________________________________________________________________________\n";
   
   
/* for loop used to print all courses and their marks
   for a single student.
*/
     for(int t=1; t<=student.no_courses; t++) {     
     	int totalMark;
     	totalMark= (student.quiz_one+student.quiz_two+student.quiz_three+student.assignment+student.mid+student.final_exam)/6; 
  		cout<<"  "<<student.course_Name<<"      "<<student.quiz_one<<"      "<<student.quiz_two<<"       "<<student.quiz_three<<"       "<<student.mid<<"       "<<student.assignment<<"         "<<student.final_exam<<"       "<<totalMark<<"      "; 
     	grade_calculator(totalMark);
     	cout<<endl;
     	storage.read((char*)&student,sizeof(student)); 
     } 
  }
storage.close();
}
 


 
/* This is the main function which will be  executed before all functions,
   So in this program when the user select one option then by 
   the help switch statement the user redirects to appropriate function.
 */
 int main() { 
 char select;
 
/* while loop that help us to excute the program all time.
   this means the program will not exit without our interest.*/
 while(1) { 
  cout<<endl; cout<<endl; cout<<endl;
  cout<<endl;
  cout<<"     **********************************************\n";
  cout<<"     *  STUDENT REGISTRATION AND MARK LIST SYSTEM *\n";
  cout<<"     **********************************************\n";
  cout<<"     *\n";
  cout<<"     Enter 1 To Register New student \n";
  cout<<"     Enter 2 To Show Registerd Students and Their Grade \n";
  cout<<"     Enter 0 To Exit \n";
  cout<<"     : ";
  cin>>select;
 
  switch (select) {
         case '1':
     		function_to_register();
     		cout<<"          Student Registered succsesfully \n";
           break;
           case '2':
     seeRegistered();
            break;
          
            
  }
 }
 
}
