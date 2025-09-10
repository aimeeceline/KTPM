#include <iostream>
using namespace std;

int f2(int x) { 
    if (x < 10)
        return 2 * x; 
    else if (x < 2)
        return -x; 
    else
        return 2 * x;
}

int main()
{
    int x,e;
    cin >> x >>e;
    cout <<"Expect:"<<e<<endl;
    cout <<"f2:"<< f2(x) << endl<< endl;
    return 0;
}