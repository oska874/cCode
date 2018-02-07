#include <iostream>
using namespace std;

class testC{
friend ostream& operator<<( ostream&,const testC& );
public:
    testC(int a,int b,int c){A=a;B=b;C=c;}
    testC(){}
	mutable int A;
    void set(int a,int b){A=a;B=b;}
    void show() const {cout<<"show testC"<<endl;}
private :
	int B;
protected:
    int C;
};

class testCd:public testC{
public:
    void get();
    void set(int a,int b){A=a;C=b;}
};

void testCd::get()
{
    cout<<this->A<<endl;
    //cout<<this->B<<endl;
    cout<<this->C<<endl;
}

ostream& operator<< ( ostream& os, const testC& s )
{
	os << "<" << s.A<< "," << s.B<< ">";
	return os;
}

int main()
{
    testC test;
    test.set(1,2);
    cout<<test<<endl;
//    cout<<test.B<<endl;//wrong
    
    testCd test2;
    test2.set(3,4);

    cout<<test2<<endl;
    cout<<"-------------------------"<<endl;
    test2.get();

    const testC test3(1,2,3);
    test3.show();
    test3.A=5;
    return 0;
}
