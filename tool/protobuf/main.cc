#include <stdio.h>
#include <fstream>
#include "student.pb.h"

using namespace std;
using namespace class_college;


int main(int argc, char *argv[])
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    studend stu1;
    stu1.set_id(11);
    stu1.set_name("jack");
    stu1.add_score(95.5);
    stu1.add_score(88.3);

    cout<<stu1.id()<<endl;

    string stu1_str;
    stu1.SerializePartialToString(&stu1_str);
    cout<<stu1_str<<endl;
    studend stu1_des;
    stu1_des.ParseFromString(stu1_str);
    cout<<stu1_des.id()<<endl;

    fstream output(argv[1], ios::out | ios::trunc | ios::binary);
    stu1.SerializeToOstream(&output);

    google::protobuf::ShutdownProtobufLibrary();//optional
    return 0;
}