#include <bits/stdc++.h>
using namespace std;
const string NAME = "FKAND";
const string task = "test";
const int nTest = 111;
mt19937 rd(chrono::steady_clock::now().time_since_epoch().count());
#define rand rd
#define ll long long
ll Rand(ll l, ll r)
{
    if(l > r)
        return r;
    return l + 1LL * rd() % (r - l + 1);
}
int main()
{
    srand(time(NULL));
    for (int iTest = 1; iTest <= nTest; iTest++)
    {
        ofstream inp((task + ".inp").c_str());
        inp.close();
        system((NAME + ".exe").c_str());
        system((NAME + "_brute.exe").c_str());
        if (system(("fc " + task + ".out " + task + ".ans").c_str()) != 0)
        {
            cout << "Test #" << iTest << ": WRONG!\n";
            return 0;
        }
        cout << "Test #" << iTest << ": CORRECT!\n";
    }
    return 0;
}