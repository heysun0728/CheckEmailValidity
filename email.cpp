#include <bits/stdc++.h>
#include <windows.h>
using namespace std;
struct Email {
    string name;
    string domain;
};
bool HaveWord(string s,int i){//判斷符號前後有沒有文字
    if(!(isalpha(s[i-1])||isdigit(s[i-1])))return false;
    if(!(isalpha(s[i+1])||isdigit(s[i+1])))return false;
    return true;
}
int IsValidEmail(string s){//回傳0:valid 其餘:invalid
    int mouseCount,i;
    mouseCount=0;
    for(i=0;i<s.size();i++){
        //判斷@有沒有多個
        if(s[i]=='@'){
            if(mouseCount==1)return 1;
            if(!HaveWord(s,i))return 2;
            mouseCount++;
            continue;
        }
        //判斷.前後有沒有文字
        if(s[i]=='.'){
            if(!HaveWord(s,i))return 3;
            continue;
        }
        //判斷有沒有非法字元
        if(!isalpha(s[i])&&!isdigit(s[i])&&s[i]!='_')return (int)s[i];
    }
    //若沒有@
    if(mouseCount==0)return 4;
    return 0;
}
string lower(string p){//string to lowercase
    int i=0;
    for(i=0;i<p.size();i++){
        if(p[i]>='A'&&p[i]<='Z'){
            p[i]=tolower(p[i]);
        }
    }
    return p;
}
bool cmpByUser(Email &p,Email &q){
    return (lower(p.name).compare(lower(q.name))<0);
}
bool cmpByUserDomain(Email &p,Email &q){
    if(lower(p.domain).compare(lower(q.domain))==0){
        return (lower(p.name).compare(lower(q.name))<0);
    }
    return (lower(p.domain).compare(lower(q.domain))<0);
}
void print(vector<Email> e){//印出結果
    for(auto &i:e){
        cout<<i.name<<"@"<<i.domain<<endl;
    }
}
int main(){
    //freopen("email.in","r",stdin);
    HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE );
    int n,i;
    string s;
    Email e;
    vector<Email> valid;
    cin>>n;
    getline(cin,s);
    while(n--){
        getline(cin,s);
        cout<<setw(25)<<left<<s;
        int result=IsValidEmail(s);
        if(result==0){
            SetConsoleTextAttribute ( h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            cout<<" valid "<<endl;
            //製作成EMail struct形式
            i=s.find('@');
            e.name.assign(s,0,i);
            e.domain.assign(s,i+1,s.size()-i);
            valid.push_back(e);
        }else{
            SetConsoleTextAttribute ( h, FOREGROUND_RED | FOREGROUND_INTENSITY );
            cout<<" invalid ";
            SetConsoleTextAttribute ( h, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            if(result==1) cout<<"(too many @)";
            else if(result==2) cout<<"(@前後沒有英文或數字)";
            else if(result==3) cout<<"(.前後沒有英文或數字)";
            else if(result==4) cout<<"(don't have @)";
            else printf("(invalid character%c)",result);
            cout<<endl;
        }
        SetConsoleTextAttribute ( h, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }
    //print result
    if(!valid.empty()){
        cout<<endl;
        cout<<"------------------------------------------"<<endl;
        cout<<"(i)User:"<<endl;
        sort(valid.begin(),valid.end(),cmpByUser);
        print(valid);
        cout<<endl;
        cout<<"(ii)Domain+User:"<<endl;
        sort(valid.begin(),valid.end(),cmpByUserDomain);
        print(valid);
    }
    return 0;
}
