#include <stdio.h>
#include "student.pb.h"

using namespace std;
using namespace class_college;

int main()
{
    studend stu1;
    stu1.set_id(11);
    stu1.set_name("jack");

    cout<<stu1.id()<<endl;
    return 0;
}