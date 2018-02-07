#include <iostream>
#include <vector>

using namespace std;


template <class Type>
Type t_min( Type a, Type b ) {
    return a < b ? a : b;
}

template <class type>
int array_pos(type str, char ch){
    for(int i=0;i<str.size();i++){
        if(str[i] == ch){
            return i;
        }
    }
    return -1;
}

template <class Type, int size>
Type t_min2( const Type (&r_array)[size] )
{
    Type min_val = r_array[0];
    for ( int i = 1; i < size; ++i ){
        if ( r_array[i] < min_val )
            min_val = r_array[i];
    }
    return min_val;
}

template <typename Type, int size>
Type t_size(const Type (&array)[size])
{
    Type cnt = 0;
    for(int i=0;i<size;i++){
        cnt++;
    }
    return cnt;
}
int main()
{
    int a=1,b=2,c,ret;
    char ch1='b',arr[10]={1,2,3,4,5,6,7,8,9,10};
    int arr2[]={0,1,2,3,4,5,6,7,8,9,10,11,12,13};
    int arr3[10]={1,2,3,4,5,6,7,8,9,10};
    string s1="abc",s2="def",s3;
    vector<char> v1;

    v1.push_back(s1[0]);
    v1.push_back(s1[1]);
    v1.push_back(s1[2]);

    c=t_min(a,b);
    cout<<"c:"<<c<<endl;

    s3=t_min(s1,s2);
    cout<<"s3:"<<s3<<endl;

    cout<<"s1-b:"<<array_pos(s1,ch1)<<endl;
    cout<<"s2-b:"<<array_pos(s2,ch1)<<endl;
    cout<<"v1-b:"<<array_pos(v1,ch1)<<endl;

    ret = static_cast<int>(t_min2(arr));
    cout<<"v1-b2:"<<ret <<endl;
    ret = static_cast<int>(t_min2(arr2));
    cout<<"v1-b3:"<<ret <<endl;

    ret = static_cast<int>(t_size(arr));
    cout<<"v2-b1:"<<ret<<endl;

    return 0;
}
