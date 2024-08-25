#include <iostream>
#include <iomanip>
#include <string.h>
#include <algorithm>
#include <cctype>
#include <sstream> 
#include <fstream>
using namespace std;
class Student
{
private:
    string name, gender, classname;
    int old, id;
    double gpa;

public:
	// set object have 0 element
    Student()
    {
        name = gender = classname = "";
        id = old = gpa = 0;
    }
    // set object
    Student(int id, string name, string gender, string classname, int old, double gpa)
    {
        this->id = id;
        this->name = name;
        this->gender = gender;
        this->classname = classname;
        this->old = old;
        this->gpa = gpa;
    }
    // function use to set details
    void setOld(int new_old) { old = new_old; }
	void setName(string new_name) { name = new_name; }
	void set_gender(string new_gender) { gender = new_gender; }
	// get  private  details
    int getID()
    {
        return this->id; 
    }
    string getName()
    {
        return this->name;
    }
    int getOld()
    {
        return this->old;
    }
    string getGender()
    {
        return this->gender;
    }
    void inputIDagain(){ // use for case found dupclicate ID
    	cout << "The id's duplicated , try again : ";
    	cin >> id;
	}
	string standardize(string name){ // nGUyen tHAi An ->>>>> Nguyen Thai An
		stringstream ss(name);
		string res ="";
		string token;
		while(ss >> token){
			res+= toupper(token[0]);
			for(int i = 1 ; i< token.length() ; i++) res+= tolower(token[i]);
			res+=" ";
		}
		res.erase(res.length() - 1);
		return res;
	}	
    void inputStudentData()
    {
        cout << "Enter student ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter student name: ";
        getline(cin, name);
        cout << "Enter student gender: ";
        getline(cin, gender);
        cout << "Enter student class: ";
        getline(cin, classname);
        cout << "Enter student age: ";
        cin >> old;
        cout << "Enter student GPA: ";
        cin >> gpa;
        cin.ignore();
    }
    void displayStudentData()
    {
        cout << "ID: " << id << ", Name: " << standardize(name) << ", Gender: " << gender << ", Class: " << classname << ", Age: " << old << ", GPA: "<< setprecision(3) << gpa << endl;
    }
     void saveToFile(ofstream &outfile) // use for save file replace inputStudentData
    {
        outfile << id << endl;
        outfile << name << endl;
        outfile << gender << endl;
        outfile << classname << endl;
        outfile << old << endl;
        outfile << gpa << endl;
    }
};

class mananger : public Student
{
public:
    Student a[1000];
    int n;
    void import();
    void export_student();
    void add();
    void edit();
    void delete_student();
    void save_file(); 
    bool check_duplicated(int index,int id);
    void export_designated_student(); 
};

int binary(Student a[],int l, int r , int id){ // use getID to find binary + Sort
	while(l<=r){
		int m = (l+r)/2;
		if(a[m].getID() == id) return m;
		else if(a[m].getID() < id)  l = m + 1;
		else  r = m-1;
	}
	return -1;
}

bool check_id(Student a[],int l, int r , int UID){ 
	while(l<=r){
		int m = (l+r)/2;
		if(a[m].getID() == UID) return true;
		else if(a[m].getID() < UID)  l = m + 1;
		else  r = m-1;
	}
	return false;
}

bool cmp(Student a,Student b){
	return a.getID() < b.getID();
}

bool mananger::check_duplicated(int index,int id){
	for(int i = index ; i<n ; i++){
		if(a[i].getID() == id) return true;
	}
	return false;
}

void mananger::import()
{
	cout << "Enter the n student : "; cin >> n;
    for (int i = 0; i < n; i++)
    {
    	int temp;
    	do{
    		a[i].inputStudentData();
    		cout << '\n';
    		temp = a[i].getID();
    		if(check_duplicated(i+1,temp)){
    			a[i].inputIDagain();
			}
		}while(check_duplicated(i+1,temp)); 
    }
    cout << "Import data completed\n";
}

void mananger::export_student()
{
    cout << "List students : \n";
    for (int i = 0; i < n; i++)
    {
        a[i].displayStudentData();
    }
    cout << "Export completed\n";
    cout << '\n'; 
}

void mananger::export_designated_student(){
	int UID = -1;
	cout << "Enter the id student : "; cin >> UID;
	while(!check_id(a,0,n-1,UID)){
		cout << "The duplicated found , try again : ";
		cin >> UID;
	}
	int temp = binary(a,0,n-1,UID); 
	a[temp].displayStudentData();
}

void mananger::add(){
	int num; cout << "Enter the numbers u want to add :"; 
	cin >> num;
	for(int i = 0 ; i<num ; i++){
		a[n].inputStudentData();
		n++;
	} 
	cout << "Add student completed\n";
}

void  find_student(Student a[],int n,int id){
	int index = -1; 
    index = binary(a,0,n-1,id);
    cout << index << '\n';
	if(index == -1){
		cout << "Student not found\n";
	}else{
        int choose = -1;
        do{
            cout << "1.Edit name \n";
            cout << "2.Edit old \n";
            cout << "3.Edit gender \n";
            cout << "0.Exit\n";
            cout << "Enter your choose : "; cin >> choose;
            switch(choose){
            	case 1 : 
            	{
				string new_name = "";
                cout << "Enter the new name student : "; cin.ignore();
                getline(cin,new_name);
                a[index].setName(new_name);
                cout << "rename completed\n";
                }break;
                case 2 :
				{ 
                 int new_old = 0;
                cout << "Enter teh new old student : " ;
                cin >> new_old;
                a[index].setOld(new_old);
                cout << "reold completed\n";
            	}
                break;
                case 3 : 
                {
                string new_gender = "";
                cin.ignore();
                getline(cin,new_gender);
                a[index].set_gender(new_gender);
                cout << "re gender completed\n";
            	}
                break;  
                default : 
                	cout << "have no your selection\n";
			}
        }while(choose!=0);
	}
}

void mananger::edit(){
    int id_text = 0;
    cout << "Enter the id u want to edit : ";
	cin >> id_text;
	sort(a,a+n,cmp);
	find_student(a,n,id_text);
    cout << "edit your student cmlt\n";
}

void mananger::delete_student(){
    int id = 0;
    cout << "Enter the id u want to delete : ";
	cin >> id;
    sort(a,a+n,cmp);
    int index = binary(a,0,n-1,id);
    for(int i = index ; i<n-1 ; i++){
        a[i] = a[i+1];
    }
    n--;
    cout << "Delete completed/n";
}

void mananger::save_file(){
	ofstream file("D://TryAgain.txt");
	if(file.is_open()){
		for(int i = 0 ; i<n ; i++){
			a[i].saveToFile(file);	
		}
		cout << "Save information completed\n";
	}
	else{
		cout << "Can't open file and save file \n";
	}
	file.close();
}

int main()
{
	mananger MAN;
	int choose = -1;
	do{
		cout<<"\t\t.____________________________________________________________________."<<endl 
            <<"\t\t||_____________________________MENU_________________________________||"<<endl 
            <<"\t\t|| 1. IMPORT INFORMATION (ONLY FOR STEP 1)                          ||"<<endl
            <<"\t\t|| 2. EXPORT LIST INFORMATION                                       ||"<<endl
            <<"\t\t|| 3. EXPORT INFORMATION STUDENT (DESIGNATED)                       ||"<<endl
            <<"\t\t|| 4. ADD STUDENT                                                   ||"<<endl
            <<"\t\t|| 5. EDIT STUDENT                                                  ||"<<endl
            <<"\t\t|| 6. DELETE STUDENT                                                ||"<<endl
	    <<"\t\t|| 7. SAVE INFORMATION(FILE.txt)                                    ||"<<endl 
            <<"\t\t|| 0. EXIT PROGRAM                                                  ||"<<endl 
            <<"\t\t||_________________________________________________________________ ||"<<endl
            <<"\t\t---->ENTER YOUR SELECTION : ";
	cin >> choose;
	switch(choose){
		case 1 : 
			MAN.import();
			break;
		case 2 : 
			MAN.export_student();
			break;
		case 3 : 
			MAN.export_designated_student();
			break;
		case 4 : 
			MAN.add();
			break;
		case 5 : 
			MAN.edit();
			break;
		case 6 : 
			MAN.delete_student();
			break;
		case 7 : 
			MAN.save_file();
			break;
		case 0 : 
			cout << "PROGRAM END\n";	
			cout << "THANK FOR USED\n";
		default : 
			cout << "HAVE NO YOUR CHOOSE!!!\n";
			break;
		}
	}while(choose!=0);
    return 0;
}
