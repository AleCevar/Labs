#include <iostream>
#include <vector>
using namespace std;

int main(){
    int t;
    cin >> t;
    while(t--){
        int n,a,x,r,m1 = INT32_MIN,m2 = INT32_MAX;
        cin >> n;
        vector<int> ar;
        while(n--){
            cin >> a >> x;
            if(a == 1) m1 = max(m1,x);
            if(a == 2) m2 = min(m2,x);
            if(a == 3) ar.push_back(x);
        }
        r = m2 - m1 + 1;
        for(int i = 0; i < ar.size(); i++)
            if(ar[i] <= m2 && ar[i] >= m1) r--;
        if(r < 0) {
            cout << 0 <<'\n';
            continue;
        }
        if(m2 == m1 && !r) {
            cout << r << '\n';
            continue;
        }
        cout << r << '\n';
    }
}