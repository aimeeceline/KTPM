#include <iostream>
#include <cmath>  
using namespace std;

    int f3(int x) {
        if (log(x * x * cos(x)) < 3 * x) 
            return 2 * x;
        else
            return 2 * x;
}

int main()
{
    int x,e;
    cin >> x >> e;
    cout <<"Expect:"<<e<<endl;
    cout <<"f3:"<< f3(x) << endl<< endl;
    return 0;
}