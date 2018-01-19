#include <iostream>
#include <string>
#include <iterator>
#include <vector>
using namespace std;

int main()
{
    // 将输入流 iterator 绑定到标准输入上
    istream_iterator<string> infile( cin );
    // 标记流结束位置的输入流 iterator
    istream_iterator<string> eos;
    // 利用通过 cin 输入的值初始化 svec
    vector<string> svec( infile, eos );
    // 处理 svec
    for(vector<string>::iterator iter=svec.begin();iter!=svec.end();iter++){
        cout << *iter<<endl;
    }
    return 0;
}
