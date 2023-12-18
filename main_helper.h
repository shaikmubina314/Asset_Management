#include<iostream>
#include"utility.h"
#include"asset.h"
#include"Employee.h"
#include"AssetTagging.h"
#pragma once
using namespace std;
void main_funtion_asset_caller()
{
      
        
        utlity utlity_obj;
        
        AssetDataOperations asset_obj;
        AssetTaggingDataOpeations assetTaggingObject;
        int ch;
        do{
            //cout << "\033[2J\033[1;1H";
            utlity_obj.Asset_Admin_Menu();
            cin>>ch;
            switch (ch)
                {
                                    case 1:     // start of asset opration 
                                        {
                                            if(asset_obj.AddAssetHelper())
                                                cout<<"ASSET is Added Sucessful! "<<endl;
                                            else{
                                                cout<<"ASSET ADDING IS FAILED "<<endl;
                                            }
                                        }
                                        break;
                                    case 2:
                                        {
                                            if(asset_obj.UpdateAssetHelper())
                                            {
                                                cout<<"update is sucessful!"<<endl;
                                            }
                                            else{
                                                cout<<"UPDATE FAILED DUE TO WRONG INPUT!"<<endl;
                                            }
                                        }
                                        break;
                                    case 3:
                                        {
                                             cout<<"Enter Asset ID for Delete Asset ";
                                                string s;
                                                cin>>s;
                                            if(asset_obj.DeleteAssetHelper(s))
                                            {   
                                                cout<<"Delete is sucessful ! "<<endl;
                                                assetTaggingObject.removeAssetAndEmployee(s);
                                            }
                                            else{
                                                    cout<<"Delete is failed ! "<<endl;
                                                }
                                        }
                                        break;
                                    case 4:
                                        {
                                            if(asset_obj.SearchAssetHelper()){ }
                                            else{ cout<<"Details are not found ! "<<endl; }
                                        }
                                        break;
                                    case 5:
                                        {
                                        if(asset_obj.GetAssetsHelper()){}
                                        else{
                                        cout<<"Wrong INPUT"<<endl;
                                        }
                                        }
                                        break;
                                    case 6:
                                        {
                                            asset_obj.ViewFreePool();
                                        }
                                        break;
                                    default:
                                        break;
                    }// end of switch
        }while(ch!=0);
                               

}
void EmployeeAdminCaller()
{
     int i;
     utlity obj;
    EmployeeDataOpeations Employee_object;
    do{
       cout << "\033[2J\033[1;1H"; 
        obj.Employee_Admin_Menu();
        cin>>i;
        switch (i)
        {
        case 1:
            if(Employee_object.AddEmployeeHelper())
            {
                cout<<"Employee details added !"<<endl;
            }
            else{
                cout<<"Employee details Not added !"<<endl;
            }
            break;
        case 2:
            {
                if(Employee_object.UpdateEmployeeHelper())
                {
                    cout<<"Update is Done"<<endl;
                }
                else{
                    cout<<"Update is Failed !!! "<<endl;
                }
            }
            break;
        case 3:
            {   
                string intEmployeeID=Employee_object.DeleteEmployeeHelper();

                if(intEmployeeID=="0")
                {  
                     cout<<"Something went Wrong TRY AGIN !"<<endl;
                     
                }
                else{
                    AssetTaggingDataOpeations obj1; 
                    string assetID=obj1.getAssetID(intEmployeeID);
                    obj1.RemoveEmployeeDetailsFromAssetTagging(intEmployeeID);

                    AssetDataOperations obj2;
                    obj2.setDetag(assetID);
                    cout<<"Deletion is done !! "<<endl;
                    obj.getch();
    
                }
            }
            break;
        case 4:
            {
                if(Employee_object.SearchEmployeeHelper())
                {

                }
                else{
                    cout<<"Details are not Found ! "<<endl;
                }
            }
            break;
        default:
            break;
        }
        //obj.getch();
    }while(i!=0);
   
}

void AssetTggingCaller()
{
    int i;
    utlity obj1;

    AssetTaggingDataOpeations obj;
    do{
        obj1.AssetTaggingAdminMenu();
        cin>>i;
        switch (i)
        {
        case 1:
           { 
            string intEmployeeID,intAssetID,strAssetTaggingDate;
            cout<<"enter AssetID "<<endl;
            cin>>intAssetID;
            cout<<"Enter employeeID "<<endl;
            cin>>intEmployeeID;
            cout<<"Enter asset tagging Date"<<endl;
            cin>>strAssetTaggingDate;
            int f1=0;
            AssetDataOperations assetObject;
            Asset assetobj=assetObject.SearchAsset(intAssetID);
            if(assetobj.asset_id==intAssetID)
            { 
                f1=1;
            }
            int f2=0;
            EmployeeDataOpeations employeeObject;
            Employee  EmployeeNode=employeeObject.SearchEmployee(intEmployeeID);
            if(EmployeeNode.Employee_ID==intEmployeeID)
            {
                f2=1;
            }
            if(f1==1 && f2==1)
            {   

                obj.TagAssetHelper(intAssetID,intEmployeeID,strAssetTaggingDate);
                
                assetObject.setTagged(intAssetID);
                //cout<<intAssetID<<"---------------- "<<endl;
            }
            else{
                cout<<"failed"<<endl;
            }
           }
            
            break;
        case 2:
            {
                string intEmployeeID,intAssetID,strReleaseDate;
            
                cout<<"enter AssetID "<<endl;
                cin>>intAssetID;
                cout<<"Enter employeeID "<<endl;
                cin>>intEmployeeID;
                cout<<"Enter asset De tagging Date " <<endl;
                cin>>strReleaseDate;
                
                if(1)
                {   AssetDataOperations assetobj;
                    assetobj.setDetag(intAssetID);
                    obj.DeTagAssetHelper(intAssetID,strReleaseDate);
                    cout<<"sucess!! "<<endl;
                }
                else{
                    cout<<"failed"<<endl;
                    }
            }
            break;
        case 3:
            obj.SearchTaggingInfo();
            break;
        default:
            break;
        }

    }while(i!=0);

}


void ViewListAssetEmployeeDetails()
{
    AssetTaggingDataOpeations obj;
    EmployeeDataOpeations obj2;
    list<AssetTagging>::iterator Aptr= obj.ll_asset_tagging.begin();
    list<Employee>::iterator Eptr=obj2.LLEmployeeObject.begin();
    for( Aptr= obj.ll_asset_tagging.begin(); Aptr!=obj.ll_asset_tagging.end();Aptr++)
    {   
        //cout<<Aptr->AssetID<<endl;
        
        for(Eptr=obj2.LLEmployeeObject.begin();Eptr!=obj2.LLEmployeeObject.end();Eptr++)
        {
             if((Aptr->EmployeeID)==(Eptr->Employee_ID))
                    {
                        cout<<"--------------------------------------"<<endl;
                        cout<<"Employee deatils are who assine Asset "<<endl;
                        cout<<"Asset ID : "<<Aptr->AssetID<<endl;
                        cout<<"Employee ID : "<<Eptr->Employee_ID<<endl;
                        cout<<"First name : "<<Eptr->First_Name<<endl;
                        cout<<"Last name : "<<Eptr->Last_Name<<endl;
                        cout<<"Joining Date : "<<Eptr->Joining_Date<<endl;
                        cout<<"Location : "<<Eptr->Location<<endl;
                        cout<<"Desiganation : "<<Eptr->Designation<<endl;
                    }
        }
        
    }
}

void EOLCaller()
{
    AssetDataOperations obj;
    obj.printEOL();
}