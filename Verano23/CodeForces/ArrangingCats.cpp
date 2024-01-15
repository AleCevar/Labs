#include <iostream>
using namespace std;

int main(){
    int t; cin >> t;
    while(t--){
        int a,falta=0,dispo=0,cambi=0;
        string s1, s2;
        cin >> a >> s1 >> s2;
        for(int i = 0; i < a; i++){
            if(s1[i] == '1' && s2[i] == '0'){
                if(!falta) dispo++;
                else{
                    falta--;
                    cambi++;
                }
            }
            if(s1[i] == '0' && s2[i] == '1'){
                if(!dispo) falta++;
                else{
                    cambi++;
                    dispo--;
                }
            }
        }
        if(falta) cambi+=falta;
        if(dispo) cambi+=dispo;
        cout << cambi << '\n';
    }
    return 0;
}