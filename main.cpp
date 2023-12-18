#include<iostream>
#include"utility.h"
#include "log_In_Class.h"
#include "main_helper.h"
#include"AssetRequests.h"
using namespace std;

int main()
{ 
     
    //login obj;
    utlity utlity_obj;                              // utility class object is created 
    char ch;
    do{
        cout << "\033[2J\033[1;1H";
        utlity_obj.main_menu();                    // utility main_menu() function called 
        cin>>ch;
        if(ch=='1')
        {   //ch='2';
            string userID,password;
            cout<<"Enter UserID : ";
            cin>>userID;
            cout<<"Enter Password : ";
            cin>>password;
            //AssetDataOperations assetdataopration_object;
            AuthenticationOperations obj;                     // AuthenticationOperations class object
            string status=obj.Login(userID,password);
            string asset_name;
            string purchasedate;
            Asset x;
            if(status[0]=='1' )
            {   
                if(status[1]=='E')
                {    cout << "\033[2J\033[1;1H";
                    AssetRequestDataOpeations objOfRequest;          // from AssetRequests.h  
                    AssetTaggingDataOpeations  taggingObj;
                    int choice;
                    do{
                        utlity_obj.employee_main_menu();
                        cin>>choice;
                        switch (choice)                             // employee switch 
                        {   
                            
                            case 1:
                                taggingObj.EmployeeCanViewTaggedAsset(userID);
                                break;
                            case 2:
                                {
                                    int f=taggingObj.taggedAsset(userID);
                                    if(f==0)
                                    {
                                        objOfRequest.RequestAssetHelper(userID);
                                        cout<<"request is raised "<<endl;
                                    }
                                    else{
                                        
                                            try {
                                                    throw MyCustomException(f);
                                                }
                                            catch (MyCustomException mce) 
                                                {   
                                            
                                                    if(mce.what()==1)
                                                    {
                                                        cout<<"InvalidTaggingException"<<endl;
                                                    }
                                                    
                                                }

                                        }
                                }
                                break;
                            case 3:
                                objOfRequest.RequestStatus(userID);
                                break;
                            case 4:
                                if(obj.Logout(userID))
                                    cout<<"Log Out Successful !"<<endl;
                                break;    
                            default:
                                cout<<"WRONG INPUT "<<endl;
                                break;
                        }
                    }while(choice!=4);
                }
                else if(status[1]=='A')                          // admin switch
                {
                    
                    
                    int choise;
                    do{ 
                        cout << "\033[2J\033[1;1H";
                        utlity_obj.admin_main_menu();
                        cin>>choise;
                        switch(choise)
                        {   cin>>choise;
                            case 1:
                                main_funtion_asset_caller();
                                utlity_obj.getch();
                                break;
                            case 2:
                                EmployeeAdminCaller();
                                utlity_obj.getch();
                                break;     
                            case 3:
                                AssetTggingCaller();
                                utlity_obj.getch();
                                break;
                            case 4:
                               ViewListAssetEmployeeDetails();
                                utlity_obj.getch();
                                break;
                            case 5:
                                EOLCaller();
                                utlity_obj.getch();
                                break;
                            case 6:
                            {
                                if(obj.Logout(userID))
                                    cout<<"Log Out Successful !"<<endl;
                            }
                                break; 
                            default:
                                cout<<"WRONG INPUT "<<endl;
                                utlity_obj.getch();
                        }
                    }while(choise!=6); 
                    
                }
                utlity_obj.getch();
            }
            else{
                cout<<"Wrong login credentials";
                utlity_obj.getch();
                }   
        }
    }while(ch!='2');
    return 0;
}