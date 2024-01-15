#include <iostream>
using namespace std;

int ab(int a,int b){
    return (a > b)? a-b : b-a;
}

int main(){
    int t; cin >> t;
    while(t--){
        int x=10000,b,a,y1,y2;
        for(int i = 0; i < 4; i++){
            cin >> a >> b;
            if(x == 10000){
                x = a;
                y1 = b;
            }
            else if(x == a){
                y2 = b;
            }
        }
        cout << ab(y1,y2)*ab(y1,y2)  << '\n';
    }    
    return 0;
}