#include<string>
#include<iostream>
using namespace std;
 void FindEOL(string s)
{   
    int c=s[9]-'0';
    int d=s[8]-'0';
    d=d*10+c+4;
    char s1=d/10+'0';
    char v=d%10 + '0';
    s[8]=s1;
    s[9]=v;
    cout<<s;
}
int main()
{

    FindEOL("25-12-2027");
    return 0;
}