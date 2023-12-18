#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<list>
using namespace std;
class log_In                              // this class use for store data from logIn.csv
{
    public:
        string userName;
        string password;
        string user_Type;
        bool login_Status;
    
    log_In()
    {

    }
    log_In(string u,string p, string type, bool status )
    {
        userName=u;
        password=p;
        user_Type=type;
        login_Status=status;
    }
    
};

class AuthenticationOperations : public log_In
{
    public:
         
        vector<string> make_it_words(string s)   //get input row from .csv return a vector of string 
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
        string Login(string strUsername, string strPassword) // return 1 if sucessfill else NULL
        {
                fstream obj;
                list<log_In> LLobj;
                obj.open("logIn.csv",ios::in);
                string temp;
                while(obj>>temp)
                {   
                    vector<string> answer=make_it_words(temp);
                    log_In obj;
                   
                    obj.userName=answer[0];
                    obj.password=answer[1];
                    obj.user_Type=answer[2][0];
                    obj.login_Status=answer[3][0]-'0';
                    
                    LLobj.push_back(obj);
                }
                string flag="null";                                           // status of log In
                list<log_In>::iterator itr;
                for(itr=LLobj.begin();itr!=LLobj.end();itr++)
                {
                    
                    
                    if(itr->userName==strUsername && itr->password==strPassword)
                    {
                        flag="1";
                        flag=flag+itr->user_Type;
                        itr->login_Status=1+'0';
                        break;
                    }
                    
                }
                if(flag[0]=='1')
                {   fstream fout;
                    fout.open("newLogIn.csv", ios::out);
                    list<log_In>::iterator itr;
                    for(itr=LLobj.begin();itr!=LLobj.end();itr++)
                    {
                        fout<<itr->userName<<",";
                        fout<<itr->password<<",";
                        fout<<itr->user_Type<<",";
                        fout<<itr->login_Status<<"\n";

                    }
                    remove("LogIn.csv");
                    
                    rename("newLogIn.csv", "LogIn.csv");
                    fout.close();
                    cout<<"loged IN";
                }

                obj.close();                    // close .csv
                LLobj.clear();                 // free linkedlist
                return flag;
        }
        int Logout(string strUsername)
            {
                fstream obj;
                list<log_In> LLobj;
                obj.open("logIn.csv",ios::in);
                string temp;
                while(obj>>temp)
                {   
                    vector<string> answer=make_it_words(temp);
                    log_In obj;
                    obj.userName=answer[0];
                    obj.password=answer[1];
                    obj.user_Type=answer[2][0];
                    obj.login_Status=answer[3][0]-'0';
                    LLobj.push_back(obj);
                }
                obj.close();
                fstream fout;
                fout.open("newLogIn.csv", ios::out);
                list<log_In>::iterator itr;
                for(itr=LLobj.begin();itr!=LLobj.end();itr++)
                {
                    fout<<itr->userName<<",";
                    fout<<itr->password<<",";
                    fout<<itr->user_Type<<",";
                    fout<<0<<"\n";

                }
                fout.close();
                LLobj.clear();   
                remove("LogIn.csv");
                rename("newLogIn.csv", "LogIn.csv");
                                        
                return 1;
            }
            void DeleteUserFromLogIn(string userName)
            {
                fstream obj;
                list<log_In> LLobj;
                obj.open("logIn.csv",ios::in);
                string temp;
                while(obj>>temp)
                {   
                    vector<string> answer=make_it_words(temp);
                    log_In obj;
                    obj.userName=answer[0];
                    obj.password=answer[1];
                    obj.user_Type=answer[2][0];
                    obj.login_Status=answer[3][0]-'0';
                    LLobj.push_back(obj);
                }
                list<log_In>::iterator itr,ptr;
                int f=0;
                for(itr=LLobj.begin();itr!=LLobj.end();itr++)
                {
                    if(itr->userName==userName)
                    {
                        f=1;
                        ptr=itr;
                    }
                }
                if(f)
                {
                    LLobj.erase(ptr);
                }
                obj.close();
                fstream fout;
                fout.open("newLogIn.csv", ios::out);
                for(itr=LLobj.begin();itr!=LLobj.end();itr++)
                {
                    fout<<itr->userName<<",";
                    fout<<itr->password<<",";
                    fout<<itr->user_Type<<",";
                    fout<<0<<"\n";

                }
                fout.close();
                LLobj.clear();   
                remove("LogIn.csv");
                rename("newLogIn.csv", "LogIn.csv");
                                        
            }
};