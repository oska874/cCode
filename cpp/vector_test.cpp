#include <vector>
#include <algorithm>
#include <iostream>
#include <list>
#include <iterator>
using namespace std;

int main()
{
    vector<string> xx;
    vector<string>::iterator iter;

    list<int> ilist;
    list<int>::iterator iter2 ;
    const list<int>::iterator iter3 = ilist.begin();

    int ary[]={0,1,2,3,4,5,6};
    vector<int> a_v(ary,ary+5);
    vector<int>::iterator temp;
    vector<int> av2=a_v;

    for(vector<int>::iterator i=av2.begin();i!=av2.end();i++){
        cout << *i <<endl;
    }
    for(vector<int>::iterator i=av2.end()-1;i!=av2.begin()-1;i--){
        cout << *i <<endl;
    }
    cout << "pop_back"<<endl;
    for(vector<int>::iterator i=av2.end();i!=av2.begin();i--){
        cout << *i <<endl;
    }
    av2.pop_back();
    for(vector<int>::iterator i=av2.end();i!=av2.begin();i--){
        cout << *i <<endl;
    }
    cout <<"end"<<endl;
    

    for(vector<int>::iterator i=a_v.end();i!=a_v.begin();i--){
        cout << *i<<endl;
    }
    cout<<"find 5"<<endl;
    temp=find(a_v.begin(),a_v.end(),5);
    cout<<*temp<<endl;
    cout<<"find 8"<<endl;
    temp=find(a_v.begin(),a_v.end(),8);
    cout<<*temp<<endl;
    cout<<"end"<<endl;
    



    xx.push_back("back");
    xx.push_back("front");

    for(iter = xx.begin();iter!=xx.end();iter++){
        cout<<*iter<<endl;
    }

    ilist.push_back(1);
    ilist.push_front(0);
    for(iter2 = ilist.begin();iter2!=ilist.end();iter2++){
        cout<<*iter2<<endl;
    }
    ilist.insert(iter2,99);
    for(iter2 = ilist.begin();iter2!=ilist.end();iter2++){
        cout<<*iter2<<endl;
    }
    cout<<"erase ilist[0]"<<endl;
    ilist.erase(ilist.begin());
    for(iter2 = ilist.begin();iter2!=ilist.end();iter2++){
        cout<<*iter2<<endl;
    }
    cout<<"erase ilist all"<<endl;
    ilist.erase(ilist.begin(),ilist.end());
    for(iter2 = ilist.begin();iter2!=ilist.end();iter2++){
        cout<<*iter2<<endl;
    }
    cout<<"endl"<<endl;


    return 0;
}
    
