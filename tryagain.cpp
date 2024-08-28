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
    Student(int ID, string NAME, string GENDER, string CLASSNAME, int OLD, double GPA)
    {
        this->id = ID;
        this->name = NAME;
        this->gender = GENDER;
        this->classname = CLASSNAME;
        this->old = OLD;
        this->gpa = GPA;
    }

    // function use to set details
    void SET_OLD(int NEW_OLD) { old = NEW_OLD; }
    void SET_NAME(string NEW_NAME) { name = NEW_NAME; }
    void SET_GENDER(string NEW_GENDER) { gender = NEW_GENDER; }

    // get private details
    int GET_ID()
    {
        return this->id;
    }
    string GET_NAME()
    {
        return this->name;
    }
    int GET_OLD()
    {
        return this->old;
    }
    string GET_GENDER()
    {
        return this->gender;
    }

    void INPUT_ID_AGAIN() // use for case found duplicated ID
    {
        cout << "The ID is duplicated, try again: ";
        cin >> id;
    }

    string STANDARDIZE(string NAME) // nGUyen tHAi An ->>>>> Nguyen Thai An
    {
        stringstream ss(NAME);
        string res = "";
        string token;
        while (ss >> token)
        {
            res += toupper(token[0]);
            for (int i = 1; i < token.length(); i++)
                res += tolower(token[i]);
            res += " ";
        }
        res.erase(res.length() - 1);
        return res;
    }

    void INPUT_STUDENT_DATA()
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

    void DISPLAY_STUDENT_DATA()
    {
        cout << "ID: " << id << ", Name: " << STANDARDIZE(name) << ", Gender: " << gender << ", Class: " << classname << ", Age: " << old << ", GPA: " << setprecision(3) << gpa << endl;
    }

    void SAVE_TO_FILE(ofstream &outfile) // use for save file replace inputStudentData
    {
        outfile << id << endl;
        outfile << name << endl;
        outfile << gender << endl;
        outfile << classname << endl;
        outfile << old << endl;
        outfile << gpa << endl;
    }
};

class MANAGER : public Student
{
public:
    Student a[1000];
    int n;
    void IMPORT();
    void EXPORT_STUDENT();
    void ADD();
    void EDIT();
    void DELETE_STUDENT();
    void SAVE_FILE();
    bool CHECK_DUPLICATED(int INDEX, int ID);
    void EXPORT_DESIGNATED_STUDENT();
};

int BINARY(Student a[], int l, int r, int id) // use GET_ID to find binary + Sort
{
    while (l <= r)
    {
        int m = (l + r) / 2;
        if (a[m].GET_ID() == id)
            return m;
        else if (a[m].GET_ID() < id)
            l = m + 1;
        else
            r = m - 1;
    }
    return -1;
}

bool CHECK_ID(Student a[], int l, int r, int UID)
{
    while (l <= r)
    {
        int m = (l + r) / 2;
        if (a[m].GET_ID() == UID)
            return true;
        else if (a[m].GET_ID() < UID)
            l = m + 1;
        else
            r = m - 1;
    }
    return false;
}

bool CMP(Student a, Student b)
{
    return a.GET_ID() < b.GET_ID();
}

bool MANAGER::CHECK_DUPLICATED(int INDEX, int ID)
{
    for (int i = INDEX; i < n; i++)
    {
        if (a[i].GET_ID() == ID)
            return true;
    }
    return false;
}

void MANAGER::IMPORT()
{
    cout << "Enter the number of students: ";
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int temp;
        do
        {
            a[i].INPUT_STUDENT_DATA();
            cout << '\n';
            temp = a[i].GET_ID();
            if (CHECK_DUPLICATED(i + 1, temp))
            {
                a[i].INPUT_ID_AGAIN();
            }
        } while (CHECK_DUPLICATED(i + 1, temp));
    }
    cout << "Import data completed\n";
}

void MANAGER::EXPORT_STUDENT()
{
    cout << "List of students: \n";
    for (int i = 0; i < n; i++)
    {
        a[i].DISPLAY_STUDENT_DATA();
    }
    cout << "Export completed\n";
    cout << '\n';
}

void MANAGER::EXPORT_DESIGNATED_STUDENT()
{
    int UID = -1;
    cout << "Enter the student ID: ";
    cin >> UID;
    while (!CHECK_ID(a, 0, n - 1, UID))
    {
        cout << "The duplicated found, try again: ";
        cin >> UID;
    }
    int temp = BINARY(a, 0, n - 1, UID);
    a[temp].DISPLAY_STUDENT_DATA();
}

void MANAGER::ADD()
{
    int num;
    cout << "Enter the number of students you want to add: ";
    cin >> num;
    for (int i = 0; i < num; i++)
    {
        a[n].INPUT_STUDENT_DATA();
        n++;
    }
    cout << "Add student completed\n";
}

void FIND_STUDENT(Student a[], int n, int ID)
{
    int index = -1;
    index = BINARY(a, 0, n - 1, ID);
    cout << index << '\n';
    if (index == -1)
    {
        cout << "Student not found\n";
    }
    else
    {
        int choose = -1;
        do
        {
            cout << "1. Edit name \n";
            cout << "2. Edit age \n";
            cout << "3. Edit gender \n";
            cout << "0. Exit\n";
            cout << "Enter your choice: ";
            cin >> choose;
            switch (choose)
            {
            case 1:
            {
                string new_name = "";
                cout << "Enter the new name: ";
                cin.ignore();
                getline(cin, new_name);
                a[index].SET_NAME(new_name);
                cout << "Rename completed\n";
            }
            break;
            case 2:
            {
                int new_old = 0;
                cout << "Enter the new age: ";
                cin >> new_old;
                a[index].SET_OLD(new_old);
                cout << "Reage completed\n";
            }
            break;
            case 3:
            {
                string new_gender = "";
                cin.ignore();
                getline(cin, new_gender);
                a[index].SET_GENDER(new_gender);
                cout << "Re-gender completed\n";
            }
            break;
            default:
                cout << "Invalid selection\n";
            }
        } while (choose != 0);
    }
}

void MANAGER::EDIT()
{
    int ID_TEXT = 0;
    cout << "Enter the ID you want to edit: ";
    cin >> ID_TEXT;
    sort(a, a + n, CMP);
    FIND_STUDENT(a, n, ID_TEXT);
    cout << "Edit completed\n";
}

void MANAGER::DELETE_STUDENT()
{
    int ID = 0;
    cout << "Enter the ID you want to delete: ";
    cin >> ID;
    sort(a, a + n, CMP);
    int index = BINARY(a, 0, n - 1, ID);
    for (int i = index; i < n - 1; i++)
    {
        a[i] = a[i + 1];
    }
    n--;
    cout << "Delete completed\n";
}

void MANAGER::SAVE_FILE()
{
    ofstream file("D://TryAgain.txt");
    if (file.is_open())
    {
        for (int i = 0; i < n; i++)
        {
            a[i].SAVE_TO_FILE(file);
        }
        cout << "Save information completed\n";	
    }
    else
    {
        cout << "Can't open file and save information\n";
    }
    file.close();
}

int main()
{
    MANAGER MAN;
    int choose = -1;
    do
    {
        cout << "\t\t.____________________________________________________________________." << endl 
             << "\t\t||_____________________________MENU_________________________________||" << endl 
             << "\t\t|| 1. IMPORT INFORMATION (ONLY FOR STEP 1)                          ||" << endl
             << "\t\t|| 2. EXPORT LIST INFORMATION                                       ||" << endl
             << "\t\t|| 3. EXPORT INFORMATION STUDENT (DESIGNATED)                       ||" << endl
             << "\t\t|| 4. ADD STUDENT                                                   ||" << endl
             << "\t\t|| 5. EDIT STUDENT                                                  ||" << endl
             << "\t\t|| 6. DELETE STUDENT                                                ||" << endl
             << "\t\t|| 7. SAVE INFORMATION(FILE.txt)                                    ||" << endl 
             << "\t\t|| 0. EXIT PROGRAM                                                  ||" << endl 
             << "\t\t||_________________________________________________________________ ||" << endl
             << "\t\t---->ENTER YOUR SELECTION : ";
        cin >> choose;
        switch (choose)
        {
            case 1:
                MAN.IMPORT();
                break;
            case 2:
                MAN.EXPORT_STUDENT();
                break;
            case 3:
                MAN.EXPORT_DESIGNATED_STUDENT();
                break;
            case 4:
                MAN.ADD();
                break;
            case 5:
                MAN.EDIT();
                break;
            case 6:
                MAN.DELETE_STUDENT();
                break;
            case 7:
                MAN.SAVE_FILE();
                break;
            case 0:
                cout << "PROGRAM END\n";  
                cout << "THANK YOU FOR USING\n";
                break;
            default:
                cout << "INVALID SELECTION!!!\n";
                break;
        }
    } while (choose != 0);
    return 0;
}

