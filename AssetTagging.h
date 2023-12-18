#include<iostream>
#include<list>
#include<vector>
#include<string>
#include<fstream>
#include"Employee.h"
using namespace std;

class MyCustomException : public std::exception {
    private:
    int message;

    public:
    MyCustomException(int msg) : message(msg) {}
    int what () {
        return message;
    }
};

class AssetTagging
{
    public:
    string AssetID;
    string EmployeeID;
    string Tagging_Date;
    AssetTagging(){}
    AssetTagging(string AssetID,string EmployeeID,string Tagging_Date)
    {
        this->AssetID=AssetID;
        this->EmployeeID=EmployeeID;
        this->Tagging_Date=Tagging_Date;
    }
};

class AssetTaggingDataOpeations : public AssetTagging
{
    public:
        list<AssetTagging> ll_asset_tagging;
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
        AssetTaggingDataOpeations()
        {
            BuildAssetRequestList();
        }
        
        void BuildAssetRequestList()
        {
            fstream fobj;
            fobj.open("AssetTagging.csv",ios::in);
            string s;
            while(fobj>>s)
            { 
                vector<string> word_vector=make_it_words(s);
                AssetTagging obj(word_vector[0],word_vector[1],word_vector[2]);
                ll_asset_tagging.push_back(obj);
            }
        }
        // TagAsset caller 
        int TagAssetHelper(string intAssetID,string intEmployeeID,string strAssetTaggingDate)
        {
            return TagAsset(intAssetID,intEmployeeID,strAssetTaggingDate);
        }
        int TagAsset(string intAssetID, string intEmployeeID, string strAssetTaggingDate)
        {
            
            int e=0,a=0;
            
            list<AssetTagging>::iterator ptr;
            for(ptr=ll_asset_tagging.begin();ptr!=ll_asset_tagging.end();ptr++)
            {
                if(ptr->EmployeeID==intEmployeeID)
                  { 
                     e=1;
                  }
                if(ptr->AssetID==intAssetID)
                {
                    a=1;
                }           
            } 
            //cout<<e<<" + "<<a<<endl;
            int ans=0;
            if(e==1)
             {   ans=1;}
            else{
                if(a==1)
                    ans=2;
                }

            try {
                    throw MyCustomException(ans);
                }
            catch (MyCustomException mce) 
                {   
                    if(mce.what()==1)
                    {
                        cout<<"EmployeeNotFoundException"<<endl;
                    }
                    else{
                        if(mce.what()==2)
                            {
                                cout<<"InvalidTaggingException"<<endl;
                            }
                        
                        }
                }
            
            if(e==0 && a==0 )
            {   
                AssetTagging obj1(intAssetID,intEmployeeID,strAssetTaggingDate);
                ll_asset_tagging.push_back(obj1);
                 cout<<"opration is sucessful"<<endl;
                return 1;
            }
            return 0;
        }
        // Detag Asset
        int DeTagAssetHelper(string intAssetID,string strReleaseDate)
        {
            return DeTagAsset(intAssetID,strReleaseDate);
        }
        
        int DeTagAsset(string intAssetID , string strReleaseDate)
        {   int f=0;
            list<AssetTagging>::iterator ptr,del;
            for(ptr=ll_asset_tagging.begin();ptr!=ll_asset_tagging.end();ptr++)
            {   
                //cout<<ptr->AssetID<<" "<<intAssetID<<" "<<ptr->EmployeeID<<" "<<intEmployeeID <<endl;
                if(ptr->AssetID==intAssetID  )
                {
                    del=ptr;
                    f=1;
                }
            }
            
            if(f)            // to save asset details in AssetTaggingHistory after removing from asset.csv
            {
                fstream fobj;
                fobj.open("AssetTaggingHistory.csv",ios::in|ios::app);
                fobj<<del->AssetID<<",";
                fobj<<del->EmployeeID<<",";
                fobj<<del->Tagging_Date<<",";
                fobj<<strReleaseDate<<"\n";
                fobj.close();
                ll_asset_tagging.erase(del);
                fobj.close();
            }
            return f;
        }
        // searching history
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

        void SearchTaggingInfo()
        {   
            string s;
            int f=0;
            cout<<"Enter intAssetID for its History "<<endl;
            cin>>s;
            fstream fobj("AssetTaggingHistory.csv",ios::in);
            string temp;
            cout<<"ASSET ID , EMPLOYEE ID , TAG DATE , DE-TAG DATE "<<endl;
            while(fobj>>temp)
            {
                vector<string> row=Make_It_Words(temp);
                if(row[0]==s)
                {cout<<row[0]<<" "<<row[1]<<" "<<row[2]<<" "<<row[3]<<endl;
                f=1;
                }
            }
            fobj.close();
            if(f==0)
            {
                cout<<"for this asset there is No history "<<endl;
            }
        }
        void SaveChanges()
        {
            fstream obj;
            obj.open("newAssetTagging.csv",ios::out);
            list<AssetTagging>::iterator ptr;
            for(ptr=ll_asset_tagging.begin();ptr!=ll_asset_tagging.end();ptr++)
            {
                obj<<ptr->AssetID<<",";
                obj<<ptr->EmployeeID<<",";
                obj<<ptr->Tagging_Date<<"\n";
            }
            obj.close();
            ll_asset_tagging.clear();
            remove("AssetTagging.csv");
            rename("newAssetTagging.csv","AssetTagging.csv");
        }
        ~AssetTaggingDataOpeations()
        {
            SaveChanges();
        }

  
        void EmployeeCanViewTaggedAsset(string s)    
        {   int f=0;
            list<AssetTagging>::iterator ptr=ll_asset_tagging.begin();
            cout<<"List of asset tagged to Employee "<<s<<" are :- "<<endl;
            for( ; ptr!=ll_asset_tagging.end();ptr++)
            {
                if(ptr->EmployeeID==s)
                {
                    cout<<ptr->EmployeeID<<"  "<<ptr->AssetID<<"endl";
                    f=1;
                }
                
            }
            if(f==0)
            cout<<"Thare is No Asset allocated to "<<s<<" Employee."<<endl;
        }

             //this function is used to remove asset in assetTagging.csv
             // use when we remove asset from asset.csv 
             // so if that asset tagged to any employee that employee tagging must be free.
             // this function is call only in  mainhelper in AssetRemoveHelper()
        void  removeAssetAndEmployee(string s)
        {   int f=0;
            list<AssetTagging>::iterator obj=ll_asset_tagging.begin(),del;
            for( ; obj!=ll_asset_tagging.end();obj++)
            {
                if(obj->AssetID==s)
                {
                    f=1;
                    del=obj;
                }
            }
            if(f)
            {   string strReleaseDate=__DATE__;
                strReleaseDate = spaceRemover(strReleaseDate);
                fstream fobj;
                fobj.open("AssetTaggingHistory.csv",ios::in|ios::app);
                fobj<<del->AssetID<<",";
                fobj<<del->EmployeeID<<",";
                fobj<<del->Tagging_Date<<",";
                fobj<<strReleaseDate<<"\n";
                fobj.close();
                ll_asset_tagging.erase(del);
                fobj.close();
            }
           
        }
        int RemoveEmployeeDetailsFromAssetTagging(string eid)  // called in mainHelper/employeeDelte() case 3 for removing data from tagging.csv
        {   
            int f=0;
            list<AssetTagging>::iterator ptr= ll_asset_tagging.begin(),del;
            for( ; ptr!=ll_asset_tagging.end();ptr++)
            {
               
                if(ptr->EmployeeID==eid)
                {  
                     f=1;
                    del=ptr;
                }
            }
            
            if(f)
            {
                ll_asset_tagging.erase(del);
            }
            return f;
            
        }
        string getAssetID(string eid)
        {
            string f="0";
            list<AssetTagging>::iterator ptr= ll_asset_tagging.begin(),del;
            for( ; ptr!=ll_asset_tagging.end();ptr++)
            {
               
                if(ptr->EmployeeID==eid)
                {  
                     f=ptr->AssetID;
                    del=ptr;
                }
            }
            return f;
        }
        string spaceRemover(string s)
        {
            string ans;
            for(int i=0;i<s.size();i++)
            {   
                if(s[i]!=' ')
                ans.push_back(s[i]);
            }
            return ans;
        }
        int taggedAsset(string s)  // to know weather employee already tagged or not used in mainHelper/employee/case 2.
        {
            int f=0;
            list<AssetTagging>::iterator ptr= ll_asset_tagging.begin();
            for( ; ptr!=ll_asset_tagging.end();ptr++)
            {
               
                if(ptr->EmployeeID==s)
                {  
                     f=1;
                   
                }
            }
            return f;
        }
};
