#pragma once
#include<iostream>
using namespace std; 
class utlity{
    public:
    void AssetTaggingAdminMenu()
    {
    cout<<"0 for exit."<<endl;
    cout<<"1 for TagAsset. "<<endl;
    cout<<"2 for DeTagAsset."<<endl;
    cout<<"3 Search Tagging Information of Asset."<<endl;
}
    void getch()
    {
        char ch;
        cout<<"press character key and enter to continue."<<endl;
        cin>>ch;
    }
    void main_menu()
    {
        cout<<"Enter 1 for Log In."<<endl;
        cout<<"Enter 2 for EXIT. "<<endl;
    }
    void employee_main_menu()
    {   cout<<"YOU LOGIN AS EMPLOYEE."<<endl;
        cout<<"Press respective button for their operation. "<<endl;
        cout<<"1 for view the tagged asset(s). "<<endl;
        cout<<"2 for make a request for an asset."<<endl;
        cout<<"3 for view the asset request status."<<endl;
        cout<<"4 for Logout."<<endl;
    }
    void admin_main_menu()
    {   cout<<"YOU LOGIN AS ADMIN."<<endl;
        cout<<"Press respective button for their operation. "<<endl;
        cout<<"1 for add, update, search and remove an asset (Laptop/ Desktops/ VOIP)."<<endl ;
        cout<<"2 for add, update, search and remove an employee. "<<endl;
        cout<<"3 for tag , detag and SearchTaggingInfo."<<endl;
        cout<<"4 for view the list of tagged assets and the respective users information."<<endl;
        cout<<"5 for view all the EOL assets."<<endl;
        cout<<"6 for Logout. "<<endl;
    }
    void Asset_Admin_Menu()
    {   
        cout<<"Press respective button for their operation. "<<endl;
        cout<<"0 for Exit. "<<endl;
        cout<<"1 for add asset. "<<endl;
        cout<<"2 for update asset. "<<endl;
        cout<<"3 for remove asset. "<<endl;
        cout<<"4 for search asset. "<<endl;
        cout<<"5 for status of Asset (press 0 or 1). "<<endl;
        cout<<"6 for list of asset in free pool."<<endl;
    }
    void Employee_Admin_Menu()
    {   cout<<"0 for Exit."<<endl;
        cout<<"1 for add Employee."<<endl;
        cout<<"2 for Update Employee."<<endl;
        cout<<"3 for Delet Employee."<<endl;
        cout<<"4 for Searching Employee. "<<endl;
    }
    
};
