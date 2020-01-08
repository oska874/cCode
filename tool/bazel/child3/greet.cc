#include <iostream>
#include <string>

#include "absl/strings/str_cat.h"
#include "absl/strings/string_view.h"

using std::string;
using std::cout;
using std::endl;

string Greet(absl::string_view person) {
    return absl::StrCat("Hello ", person);
}

int main(){
    cout << Greet("world") << endl;
    cout << Greet("ChrisZZ") << endl;

    return 0;
}