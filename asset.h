#pragma once
#include<iostream>
#include<string>
#include<list>
#include<fstream>
#include<string>
#include<vector>
#include<iterator>
using namespace std;
class Asset
{
    public:
        string asset_id;
        string asset_name;
        string purchase_date;
        string tagging_status;
        string is_active;

        Asset(){}
        Asset( string asset_name , string purchase_date )
        {
            this->asset_id=Asset_Id_Generator();
            this->asset_name=asset_name;
            this->purchase_date=purchase_date;
            this->tagging_status="free";
            this->is_active="0";
        }
        string Asset_Id_Generator()    // use for Generate asset ID
        {
            string date=__DATE__;
            string time=__TIME__;
            string ans;
            for(int i=0;i<date.size();i++)
            {
                if(date[i]!=' ')
                ans.push_back(date[i]);
            }
            for(int i=0;i<time.size();i++)
            {
                if(time[i]!=':')
                ans.push_back(time[i]);
            }
            return ans;
        }
};
class AssetDataOperations : public Asset                     // AssetDataOperations class
{
    public:
        list<Asset> head ;
        AssetDataOperations()          // buld asset linlked list.
        {
            BuildAssetList();
        }
        void BuildAssetList()          // buld linked list 
        {
            fstream fobj;
            fobj.open("asset.csv");
            string temp;
            while(fobj>>temp)
            {
                vector<string> answer=Make_It_Words(temp);
                Asset obj;
                obj.asset_id=answer[0];
                obj.asset_name=answer[1];
                obj.purchase_date=answer[2];
                obj.tagging_status=answer[3];
                obj.is_active=answer[4];
                this->head.push_back(obj);
            }
            fobj.close();
        } 

        int AddAssetHelper()           // add asset .
        {   string asset_name,purchasedate;
            cout<<"Enter Asset Name (Laptop/ Desktop / VOIP ) "<<endl;
            cin>>asset_name;
            asset_name=make_small_case(asset_name);
            cout<<"Enter Purchase Date DD-MM-YYYY format"<<endl;

            cin>>purchasedate;
            Asset obj(asset_name,purchasedate);
            return AddAsset(obj);
        }
        int AddAsset(Asset &obj)
        {
            string asset_name=obj.asset_name,purchasedate=obj.purchase_date;
            int flag=Validation(asset_name,purchasedate);
            if(flag)
            {    
                Asset asset_object(asset_name,purchasedate);
                head.push_back(asset_object);
            }
            else{
                cout<<"Invalidation Input Format"<<endl;
            }
            return flag;
        }

        int UpdateAssetHelper()            // for update asset in asset.csv
        {   string id;
            cout<<"Enter asset_id for update "<<endl;
            cin>>id;
            Asset obj;
            obj.asset_id=id;
            string asset_name;
            cout<<"Enter asset name for update "<<endl;
            cin>>obj.asset_name;
            cout<<"Enter asset purchase_date(DD-MM-YYYY)"<<endl;
            cin>>obj.purchase_date;
            cout<<"Enter tagging status (Free/Tagged) "<<endl;
            cin>>obj.tagging_status;
            cout<<"Enter active status (0/1)"<<endl;
            cin>>obj.is_active;
            
            //validation 
            obj.asset_name=make_small_case(obj.asset_name);
            obj.tagging_status=make_small_case(obj.tagging_status);
            if("tagged" != obj.tagging_status ){}
            else if( "free"!=obj.tagging_status){}
                else{return 0;}
             
            if(obj.is_active!="0" ){}
            else if( obj.is_active!="1"){}
                else{return 0;}
            if(Validation(obj.asset_name,obj.purchase_date))
                return UpdateAsset(id,obj);
            return 0;
        }
        int UpdateAsset(string intAssetID, Asset obj)
        {   
            list<Asset>::iterator ptr;
            int flag=0;
            for(ptr= this->head.begin(); ptr!=this->head.end();ptr++)
            {
                if(ptr->asset_id == intAssetID)
                {
                    ptr->asset_name=obj.asset_name;
                    ptr->purchase_date=obj.purchase_date;
                    ptr->tagging_status=obj.tagging_status;
                    ptr->is_active=obj.is_active;
                    flag=1;
                }
            }
            return flag;
        }
        // delete asset from asset.csv
        int DeleteAssetHelper(string s)
        {
           
            return DeleteAsset(s);
        }
        int DeleteAsset(string intAssetID)
        {
            list<Asset>::iterator itr,del_node;
            int flag=0;
            for(itr=head.begin();itr!=head.end();itr++)
            {
                //cout<<itr->asset_id<<endl;
                if(intAssetID==itr->asset_id)
                {
                    del_node=itr;
                    flag=1;
                }
            }
            if(flag)
            {
                head.erase(del_node);
            }
            return flag;
        }
        //  searching asset by assetID for removing details of asset.
        int SearchAssetHelper()
        {   
            string s;
            cout<<"Enter Asset ID for searching"<<endl;
            cin>>s;
        
            Asset obj = SearchAsset(s);
            cout<<obj.asset_id<<"FLAG";
            if(obj.asset_id==s)
            {  
                cout<<"ID : "<<obj.asset_id<<endl;
                cout<<"ASSET NAME : "<<obj.asset_name<<endl;
                cout<<"IS ACTIVE : "<<obj.is_active<<endl;
                cout<<"DATE : "<<obj.purchase_date<<endl;
                cout<<"STATUS : "<<obj.tagging_status<<endl;
                return 1;
            }
            return 0;
        } 
        Asset SearchAsset(string intAssetID)
        {
            Asset obj;
            obj.asset_id="NULL";
            list<Asset>::iterator ptr;
            for(ptr=head.begin();ptr != head.end();ptr++)
            {   
                if(ptr->asset_id==intAssetID)
                {   cout<<"Details are "<<endl;
                    obj.asset_id=ptr->asset_id;
                    obj.asset_name=ptr->asset_name;
                    obj.is_active=ptr->is_active;
                    obj.purchase_date=ptr->purchase_date;
                    obj.tagging_status=ptr->tagging_status;
                }
            }
            return obj;
        }
        // GetAssets
        int GetAssetsHelper()
        {
            string s;
            cout<<"Enter Status to get list of Status 0/1 "<<endl;
            cin>>s;
            if(s!="0")
            if(s!="1")
                return 0;
            vector<Asset> obj = GetAssets(s);
            cout<<"LIST OF ALL ASSETS WITH STATUS ARE :-"<<s<<endl;
            if(obj.size()==0)
            cout<<"EMPTY LIST "<<endl;
            for(int i=0;i<obj.size();i++)
            {
                cout<<"ID : "<<obj[i].asset_id<<endl;
                cout<<"ASSET NAME : "<<obj[i].asset_name<<endl;
                cout<<"IS ACTIVE : "<<obj[i].is_active<<endl;
                cout<<"DATE : "<<obj[i].purchase_date<<endl;
                cout<<"STATUS : "<<obj[i].tagging_status<<endl;
                cout<<"-----------------------------------------------"<<endl;
            }
            return 1;
        }
        vector<Asset> GetAssets(string status)
        {
            vector<Asset> obj;
            list<Asset>::iterator ptr;
            for(ptr=head.begin();ptr != head.end();ptr++)
            {   
                if(ptr->is_active==status)
                {
                    Asset temp_obj;
                    temp_obj.asset_id=ptr->asset_id;
                    temp_obj.asset_name=ptr->asset_name;
                    temp_obj.is_active=ptr->is_active;
                    temp_obj.purchase_date=ptr->purchase_date;
                    temp_obj.tagging_status=ptr->tagging_status;
                   
                    obj.push_back(temp_obj);
                }
            }
            return obj;
        }
        // save data back in file from LL
        void SaveChanges()
        {
            fstream obj;
            obj.open("NewAsset.csv",ios::out);
            list<Asset>::iterator itr;
            for(itr=this->head.begin();itr!=this->head.end();itr++)
            {
                obj<<itr->asset_id<<",";
                obj<<itr->asset_name<<",";
                obj<<itr->purchase_date<<",";
                obj<<itr->tagging_status<<",";
                obj<<itr->is_active<<"\n";
            }
            obj.close();
            this->head.clear();
            remove("asset.csv");
            rename("NewAsset.csv","asset.csv");
        }
        ~AssetDataOperations()
        {
            SaveChanges();
        }
        void ViewFreePool()
        {
            list<Asset>::iterator ptr;
            for(ptr=head.begin();ptr!=head.end();ptr++)
            {       
                    string s=make_small_case(ptr->tagging_status);
                    if(s=="free")
                    {
                        cout<<"Details of asset in free pool : "<<endl;
                        cout<<"Asset ID : "<<ptr->asset_id<<endl;
                        cout<<"Asset name : "<<ptr->asset_name<<endl;
                        cout<<"is active : "<<ptr->is_active<<endl;
                        cout<<"purchase date of Asset : "<<ptr->purchase_date<<endl;
                        cout<<"Tagging status : "<<ptr->tagging_status<<endl;
                        cout<<"---------------------------------------"<<endl;
                    }
            }
            
        }
        void printEOL()
        {   cout<<"Printing EOL"<<endl;
            cout<<"Asset ID            ||       Asset Name            ||          Date"<<endl;
            list<Asset>::iterator ptr;
            for(ptr=head.begin();ptr!=head.end();ptr++)
            {
                cout<<ptr->asset_id<<" "<<ptr->asset_name<<" "<<FindEOL(ptr->purchase_date)<<endl;
                cout<<"----------------------------------------------------------"<<endl;
                
            }

        }
        int FindEOL(string s)
        {   
            int num=0;
            for(int i=6;i<=9;i++)
            {
                num*=10;
                num  = num + s[i]-'0';
            }
            num+=4;
            return num;
        }
        // helper funtion for asset.h
//--------------------------------------------------------------------------------------//
         bool number_cheacker(char ch)
            {
                if(ch >='0' && ch <='9')
                return 1;
                return 0;
            }
        string make_small_case(string s)
        {   string temp;
            for(int i=0;i<s.size();i++)
            {
                if(s[i]>='A' && s[i]<='Z')
                {
                    temp.push_back(s[i]-'A'+'a');
                } 
                else{
                    temp.push_back(s[i]);
                }   
            }
            return temp;
        }

        int Validation(string assetname, string purchasedate)
        {   
            vector<string> s;
            int flag=0;
            s.push_back("laptop");
            s.push_back("desktop");
            s.push_back("voip");
            for(int i=0;i<s.size();i++)
            {
                if(assetname==s[i])
                {  
                    flag=1;
                }
            }
            if(purchasedate.size()== 10)
            {
                for(int i=0;i<=1;i++)
                {    if(i==0 && purchasedate[i] > '3'  )
                        flag=0;
                     if(number_cheacker(purchasedate[i])==0)
                        flag=0;
                }
                if(purchasedate[0]=='3')
                {
                    if(purchasedate[1]>='2')
                        flag=0;
                }

                if(purchasedate[2]!='-')
                flag=0;
                for(int i=3;i<=4;i++)
                {   if(i==3 && purchasedate[i]> '2')
                        flag=0;
                    if(number_cheacker(purchasedate[i])==0)
                        flag=0;
                }
                if(purchasedate[5]!='-')
                flag=0;
                for(int i=6;i<=9;i++)
                {
                     if(number_cheacker(purchasedate[i])==0)
                        flag=0;
                }
            }
            else{
                flag=0;
            }
            return flag;
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
        void setTagged(string aid)    // this function use to set tagged and 1(asset status) in .csv  this is called by mainhelper.h in line 190
        {
            list<Asset>::iterator ptr;
            for( ptr= head.begin(); ptr!=head.end();ptr++)
            {
                //cout<<ptr->is_active<<" "<<ptr->tagging_status<<endl;
                if(aid==ptr->asset_id)
                {
                    ptr->is_active="1";
                    ptr->tagging_status="tagged";
                }
            }
        }
        void setDetag(string aid)
        {
            list<Asset>::iterator ptr;
            for(ptr= head.begin() ; ptr!=head.end();ptr++)
            {
                if(aid== (ptr->asset_id))
                {
                    ptr->is_active="0";
                    ptr->tagging_status="free";
                }
            }
        }
};