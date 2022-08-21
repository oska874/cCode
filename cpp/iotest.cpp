#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    string sx;
    ofstream outfile("out.txt");
    ifstream infile("in.txt");
    if(!outfile || !infile){
        cerr<<"in/out file fail"<<endl;
    }
    else{
        do{
            infile>>sx;
            outfile<<sx<<endl;
        }while(!infile.eof());
    }


    return 0;
}
