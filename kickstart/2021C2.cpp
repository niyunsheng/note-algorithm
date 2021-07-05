#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
#define min(x,y) (x<y?x:y)
#define max(x,y) (x>y?x:y)
using namespace std;
#define MAXN 1000005
int main(){
    freopen("in.txt","r",stdin);
    long long T,G;
    bool is_prime[MAXN];
    vector<long long> prime;
    memset(is_prime,1,MAXN);
    for(long long i=3;i<MAXN;i+=2){
        if(is_prime[i]){
            prime.push_back(i);
            for(long long j=i*2;j<MAXN;j+=i){
                is_prime[j] = false;
            }
        }
    }
    long long ans;
    long long rank_prime;
    scanf("%lld",&T);
    for(long long i=1;i<=T;i++){
        scanf("%lld",&G);
        ans = 1;
        rank_prime = 0;
        while(G%2==0)G/=2;
        while(G!=1){
            long long tmp=1;
            while(G%prime[rank_prime]==0){G/=prime[rank_prime];tmp++;}
            rank_prime++;
            ans *= tmp;
            printf("%lld %lld %lld\n",G,tmp,rank_prime);
        }
        printf("Case #%lld: %lld\n",i,ans);
    }
    return 0;
}