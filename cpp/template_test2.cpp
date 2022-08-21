#include <numeric>
#include <list>
#include <functional>
#include <iostream>
using namespace std;
/*
 * * 输出为:
 * accumulate()
 * operating on values {1,2,3,4}
 * result with default addition: 10
 * result with plus<int> function object: 10
 * */
int main()
{
    int ia[] = { 1, 2, 3, 4 };
    list<int> ilist( ia, ia+4 );
    int i1_result = accumulate(&ia[0], &ia[4], 10);
    int i0_result = accumulate(&ia[0], &ia[4], 0);
    int ilist_res = accumulate(ilist.begin(), ilist.end(), 0, plus<int>() );
    cout << "accumulate()\n"
        << "operating on values {1,2,3,4}\n"
        << "result with 0 addition: "
        << i0_result << "\n"
        << "result with 1 addition: "
        << i1_result << "\n"
        << "result with plus<int> function object: "
        << ilist_res
        << endl;
}

