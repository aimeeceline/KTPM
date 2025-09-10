#include <iostream>
using namespace std;

    int f1(int x){ 
        if (x > 10)
            return 2 * x; else
        return -x;
    }
int main()
{
    int x,e;
    cin >> x >>e;
    cout <<"Expect:"<<e<<endl;
    cout <<"f1:"<< f1(x) << endl<< endl;
    return 0;
}