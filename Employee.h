#include<iostream>
#include<string>
#include<cstdlib>
#include<list>
#include<fstream>
#include<vector>
#include"log_In_Class.h"
#pragma once
using namespace std;
class Employee{

public:
    string Employee_ID;
    string First_Name;
    string Last_Name;
    string Designation;
    string Joining_Date;
    string Location;    
    Employee(string eid,string First,string Last, string Designation , string Joining , string Location)
    {
        this->First_Name=First;
        this->Last_Name=Last;
        this->Designation=Designation;
        this->Joining_Date=Joining;
        this->Location=Location;
        this->Employee_ID=eid;
        //Employee_ID_Generate(Joining,First,Last);
    }
    Employee(){}
    string Employee_ID_Generate(string Joining,string First  ,string Last)
    {   
        string answer = number_to_month(Joining);
        answer.push_back(First[0]);
        answer.push_back(First[1]);
        if(Last.size()<2)
        {
            srand(time(0));
            answer.push_back((rand()%26)+'a');
            answer.push_back((rand()%26)+'a');
        }
        else{
            int n=Last.size();
            answer.push_back(Last[n-2]);
            answer.push_back(Last[n-1]);
        }
        return answer;
    }
    string number_to_month(string date)
    {
        string s;
        s.push_back(date[3]);
        s.push_back(date[4]);
        s.push_back(date[5]);
        
        return s;
    }
};


class EmployeeDataOpeations : public Employee
{
    public:
        list<Employee> LLEmployeeObject;
         vector<string> Make_It_Words(string s)   //get input row string from .csv return a vector of string 
        {
            vector<string> ans;
            string temp;
            for(int i=0 ; i <s.size() ; i++)
            {
                if(s[i]==',')
                {
                    ans.push_back(temp);
                    temp="";
                }
                else{
                    temp.push_back(s[i]);
                }
            }
            ans.push_back(temp);
            return ans;
        }
       
        void BuildEmployeeList()
        {   
            fstream obj;
            obj.open("Employees.csv");
            string temp;
            while(obj>>temp)
            {
                vector<string> answer=Make_It_Words(temp);
                Employee obj;
                obj.Employee_ID=answer[0];
                obj.First_Name=answer[1];
                obj.Last_Name=answer[2];
                obj.Designation=answer[3];
                obj.Joining_Date=answer[4];
                obj.Location=answer[5];
                LLEmployeeObject.push_back(obj);
            }
            obj.close();
        }
        EmployeeDataOpeations()
        {
            BuildEmployeeList();
        }
        int valid(string s, string t)
        {   string answer=s+t;
            for(int i=0;i<answer.size();i++)
            {
                if(s[i]>='a' && s[i]<='z')
                {
                    return 1;
                }
                if(s[i]>='A'&& s[i]<='Z')
                {
                    return 1;
                }
            }
            return 0;
        }
        int AddEmployeeHelper()
        {   string eid,fname,lname,des,date,loc;
            cout<<"Enter Employee Details "<<endl;
            cout<<"Enter Employee ID"<<endl;
            cin>>eid;
            cout<<"Enter First name"<<endl;
            cin>>fname;
            cout<<"Enter Last name "<<endl;
            cin>>lname;
            cout<<"Enter Designation"<<endl;
            cin>>des;
            cout<<"Enter date of joining (DD-month_name-YYYY)"<<endl;
            cin>>date;
            cout<<"Enter Location"<<endl;
            cin>>loc;
            if(fname.size()>0 && loc.size() > 0  && valid(fname,loc)==1)
            {
                Employee new_emp_obj(eid,fname,lname,des,date,loc); 
                return AddEmployee(new_emp_obj);
            }
            return 0;
        }
        int AddEmployee(Employee obj) 
        {

            LLEmployeeObject.push_back(obj);
            AddDataLogCSV(obj);
            return 1;
        }

        int UpdateEmployeeHelper()
        {
            string eid,fname,lname,des,date,loc;
            cout<<"Enter ID of Employee for Update "<<endl;
            cin>>eid;
            cout<<"Enter First name"<<endl;
            cin>>fname;
            cout<<"Enter Last name "<<endl;
            cin>>lname;
            cout<<"Enter Designation"<<endl;
            cin>>des;
            cout<<"Enter date of joining (DD-month_name-YYYY)"<<endl;
            cin>>date;
            cout<<"Enter Location"<<endl;
            cin>>loc;
            if(fname.size()>0 && loc.size() > 0  && valid(fname,loc)==1)
            {
                Employee new_emp_obj(eid,fname,lname,des,date,loc); 
                return UpdateEmployee(eid,new_emp_obj);
            }
            return 0;
        }
        int UpdateEmployee(string intEmployeeID, Employee obj)
        {
            list<Employee>::iterator ptr;
            int flag=0;
            for(ptr=LLEmployeeObject.begin();ptr!=LLEmployeeObject.end();ptr++)
            {
                if(intEmployeeID==ptr->Employee_ID)
                {
                    
                    ptr->First_Name=obj.First_Name;
                    ptr->Last_Name=obj.Last_Name;
                    ptr->Joining_Date=obj.Joining_Date;
                    ptr->Location=obj.Location;
                    ptr->Designation=obj.Designation;
                    flag=1;
                }
            }
            return flag;
        }

        void SaveChanges()
        {
            fstream obj;
            obj.open("NewEmployee.csv",ios::out);
            list<Employee>::iterator itr;
            for(itr=LLEmployeeObject.begin();itr!=LLEmployeeObject.end();itr++)
            {
                obj<<itr->Employee_ID<<",";
                obj<<itr->First_Name<<",";
                obj<<itr->Last_Name<<",";
                obj<<itr->Designation<<",";
                obj<<itr->Joining_Date<<",";
                obj<<itr->Location<<"\n";
            }
            obj.close();
            this->LLEmployeeObject.clear();
            remove("Employees.csv");
            rename("NewEmployee.csv","Employees.csv");
        }
        ~EmployeeDataOpeations()
        {
            SaveChanges();
        }
        
        // delete employee
        string DeleteEmployeeHelper()
        {
            string id;
            cout<<"Enter Employee ID for DELET "<<endl;
            cin>>id;
            if (DeleteEmployee(id))
            return id;
            return "0";
        }
        int DeleteEmployee(string intEmployeeID)
        {   int f=0;
            list<Employee>::iterator ptr;
            list<Employee>::iterator del_ptr;
            for(ptr=LLEmployeeObject.begin();ptr!=LLEmployeeObject.end();ptr++)
            {
                if(ptr->Employee_ID==intEmployeeID)
                    {
                        f=1;
                        del_ptr=ptr;
                    }
            }
            if(f)
             {LLEmployeeObject.erase(del_ptr);}
            if(f)
            {
              AuthenticationOperations obj;
                obj.DeleteUserFromLogIn(intEmployeeID);
            }
            
            return f;
        } 
        int SearchEmployeeHelper()
        {
            cout<<"Enter EmployeeID"<<endl;
            string id;
            cin>>id;
            Employee ans=SearchEmployee(id);
            if(ans.Employee_ID=="0")
            return 0;
            cout<<"FOUNDED!!! Details "<<endl;
            cout<<"employee ID  "<<ans.Employee_ID<<endl;
            cout<<"First name "<<ans.First_Name<<endl;
            cout<<"Last Name "<<ans.Last_Name<<endl;
            cout<<"Location "<<ans.Location<<endl;
            cout<<"Designation "<<ans.Designation<<endl;
            cout<<"Date of Joining : "<<ans.Joining_Date<<endl;
            return 1;
        }
        Employee SearchEmployee(string intEmployeeID)
        {   Employee obj;
            obj.Employee_ID="0";
            list<Employee>::iterator ptr;
            for(ptr=LLEmployeeObject.begin();ptr!=LLEmployeeObject.end();ptr++)
            {
                if(intEmployeeID==ptr->Employee_ID)
                {
                    obj.Employee_ID=intEmployeeID;
                    obj.First_Name=ptr->First_Name;
                    obj.Last_Name=ptr->Last_Name;
                    obj.Location=ptr->Location;
                    obj.Designation=ptr->Designation;
                    obj.Joining_Date=ptr->Joining_Date;
                }
            }
            return obj;
        }
        void AddDataLogCSV(Employee obj)
        {
            fstream fobj;
            string password=Employee_ID_Generate(obj.Joining_Date,obj.First_Name,obj.Last_Name);
            fobj.open("LogIn.csv",ios::in|ios::app);
            fobj<<obj.Employee_ID<<",";
            fobj<<password<<",";
            fobj<<"E"<<",";
            fobj<<"0"<<"\n";
            fobj.close();
        }


//-------------------------------------------------------------//
       int dd__MonthName_yyyyValidate(string s)
       {
            string temp;
            return 0;
       }
};
