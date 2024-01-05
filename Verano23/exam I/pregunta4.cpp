#include <bits/stdc++.h>
using namespace std;

typedef vector<char> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;

vector<vii> memo;

int multi(int a, int b){
    return memo[a][b].first * memo[a][b].second;
}

ii newHouse(vector<vi> array){
    memo.assign(array.size(),vii(array[0].size()));
    if(array[0][0] == '*') memo[0][0] = {0,0};
    else memo[0][0] = {1,1};
    ii res = {0,0};
    for(int i = 1; i < array.size(); i++) {
        if(array[i][0] != '*')memo[i][0] = {memo[i-1][0].first+1,1};    
        else memo[i][0] = {0,0};
        if(multi(i,0) > res.first*res.second)res = memo[i][0];
    }
    for(int i = 1; i < array[0].size(); i++) {
        if(array[0][i] != '*')memo[0][i] = {1,memo[0][i-1].second+1};    
        else memo[0][i] = {0,0};
        if(multi(0,i) > res.first*res.second)res = memo[0][i];
    }
    for(int i = 1; i < array.size(); i++){
        for(int j = 1; j < array[0].size(); j++){
            int up = multi(i-1,j), le = multi(i,j-1), di = multi(i-1,j-1); 
            if(!up && !le && !di) memo[i][j] = {1,1};
            else {
                if(di== 0||le==0||up==0){
                    if(up >= le) memo[i][j] = {memo[i-1][j].first+1,1};
                    else memo[i][j] = {1,memo[i][j-1].second+1};
                }else memo[i][j] = {memo[i][j-1].first,memo[i-1][j].second};     
            }
            if(multi(i,j) > res.first*res.second)res = memo[i][j]; 
        }
    }
    return res = {res.second,res.first}; 
}