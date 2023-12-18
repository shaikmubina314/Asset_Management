#include<iostream>
#include<vector>
#include<string>
#include<list>
#include<fstream>
#pragma once
using namespace std;
class AssetRequests
{
public:
    string Employee_ID;
    string Request_ID;
    string Request_Date;
    string Device;
    string Request_Status;
    AssetRequests(){
        this->Request_Status="1";
    }
    AssetRequests(string eID,string rID , string Device ,string date){
        this->Employee_ID=eID;
        this->Request_ID=rID;
        this->Device=Device;
        this->Request_Date=date;
        this->Request_Status="1";
    }
};
class AssetRequestDataOpeations : public AssetRequests
{
    public:

    list<AssetRequests> LLAsserRequestObject;
    AssetRequestDataOpeations()
    {
        BuildAssetRequestList();
    }
    void BuildAssetRequestList()
    {
        fstream fobj;
        fobj.open("AssetRequests.csv",ios::in);
        string temp;
        while(fobj>>temp)
        {
            vector<string> ans=Make_It_Words(temp);
            AssetRequests obj;
            obj.Employee_ID=ans[0];
            obj.Request_ID=ans[1];
            obj.Request_Date=ans[2];
            obj.Device=ans[3];
            obj.Request_Status=ans[4];
            LLAsserRequestObject.push_back(obj);
        }
        fobj.close();
    }
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
    ~AssetRequestDataOpeations()
    {
        SaveChanges();
    }
    void SaveChanges()
    {
        fstream fobj;
        fobj.open("newAssetRequests.csv",ios::out) ;
        list<AssetRequests>::iterator ptr;
        for(ptr=LLAsserRequestObject.begin();ptr!=LLAsserRequestObject.end();ptr++)
        {   //cout<<ptr->Employee_ID<<" " <<ptr->Request_ID<<" "<<ptr->Request_Date<<" "<<ptr->Device<<endl;
            fobj<<ptr->Employee_ID<<",";
            fobj<<ptr->Request_ID<<",";
            fobj<<ptr->Request_Date<<",";
            fobj<<ptr->Device<<",";
            fobj<<ptr->Request_Status<<"\n";
        }
        fobj.close();
        LLAsserRequestObject.clear();
        remove("AssetRequests.csv");
        rename("newAssetRequests.csv","AssetRequests.csv");
    } 
    int  RequestAssetHelper(string s)
    {  
        AssetRequests obj;
        //cout<<"Enter Employee ID for Request "<<endl;
        obj.Employee_ID=s;
        cout<<"Enter Request ID "<<endl;
        cin>>obj.Request_ID;
        cout<<"Enter Device laptop/desktop/voip"<<endl;
        cin>>obj.Device;
        cout<<"ENTER DATE DD-MM-YYYY"<<endl;
        cin>>obj.Request_Date;
        return RequestAsset(obj);
    }
    int RequestAsset(AssetRequests obj)
    {   
        LLAsserRequestObject.push_back(obj);
        return 1;
    }
    void RequestStatus(string s)
    {
        list<AssetRequests>::iterator ptr;
        int f=0;
        //cout<<"Enter a Employee ID to Know status "<<endl;
        for(ptr=LLAsserRequestObject.begin();ptr!=LLAsserRequestObject.end();ptr++)
        {
            if(ptr->Employee_ID==s)
            {
                
                if(ptr->Request_Status=="1")
                {   f=1;
                    cout<<"Request is Raise for "<<ptr->Device<<endl;
                }
               
            }
        }
        //cout<<"HELLO";
        if(f==0)
        {
            cout<<"Request is not Raise "<<endl;
        }
    }

};


