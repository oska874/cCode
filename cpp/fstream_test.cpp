#include <fstream>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <memory>

using namespace std;




int main()
{
    string file_name="in.txt";
    string textline;
    ifstream infile( file_name.c_str(), ios::in );

    vector<string,allocator<string> > *lines_of_text = new vector<string,allocator<string> >;

    typedef pair<string::size_type, int> stats;
    stats  maxline;
    int linenum=0;

    if(!infile){
        cout <<"open fail"<<endl;
        exit(-1);
    }
    else{
        cout <<endl;
    }

    while(getline(infile,textline,'\n')){
        if(maxline.first<<textline.size()){
            maxline.first = textline.size();
            maxline.second = linenum;
        }
        lines_of_text->push_back( textline );
        linenum++;
        cout<<textline<<endl;
    }

    cout<<"allocator"<<endl;
    for(vector<string,allocator<string> >::iterator iter=lines_of_text->begin();iter!=lines_of_text->end();iter++){
        cout<<*iter<<endl;
    }
    infile.close();
    return 0;
}



