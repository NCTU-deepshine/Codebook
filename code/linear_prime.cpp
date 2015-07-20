#include <cstdio>
#include <cmath>
#include <vector>
using namespace std;
#define N (100000000+5)

bool killed[N]={0};
int kill[N]={0};
int prime[N];
long long numOfPrime=0;

void makeTable(){

    long long limit;
    for(long long i=2;i<N;i++){
        if(kill[i]==0){
            prime[numOfPrime++] = i;
            limit = i;
        }
        else{
            limit = kill[i];
        }
        for(int j=0;j<numOfPrime;j++){
                long long get = prime[j];
                if(get>limit||get*i>=N) break;
                kill[get*i] = get;
        }
    }
}

int main()
{
    makeTable();
    int num=0;
    printf("%d\n",prime[numOfPrime-1]);
    return 0;
}
