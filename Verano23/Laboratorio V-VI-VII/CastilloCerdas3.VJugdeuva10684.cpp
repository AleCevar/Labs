#include <iostream>
using namespace std;

//Problema 3: The Jackpot VJudge (Aceptado)
// https://vjudge.net/problem/UVA-10684
// https://vjudge.net/solution/47791699
// Complejidad: O(n)

int array[10000];

int main(){
    ios_base :: sync_with_stdio(false); cin.tie(0);
    int N;
    while(cin >> N && N){
        for(int i = 0; i < N; i++){
            cin >> array[i];
        }
        int maxStreak = 0, streak = 0;
        for(int i = 0; i < N; i++){
            streak+=array[i];
            maxStreak=max(maxStreak, streak);
            streak=max(streak, 0);
        }
        maxStreak = max(streak,maxStreak);
        if(!maxStreak) cout << "Losing streak" << ".\n";
        else cout << "The maximum winning streak is " << maxStreak << ".\n";
    }
}