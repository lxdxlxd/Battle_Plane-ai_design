#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
using namespace std;

int main(int argc, char *argv[]){
    fstream in;
    in.open("result3.txt");
    int num=0;
    int maxn=0;
    int minn=100;
    int sum=0;
    double accu=0;
    int n=0;
    stringstream ss(argv[1]);
    int x;
    ss>>x;
    while(in>>num){
        n++;
        sum+=num;
        maxn=max(maxn, num);
        minn=min(minn,num);
        if(n==x) break;
    }
    double m=(double)sum/n;
    in.close();
    in.open("result.txt");
    for(int i=0;i<n;++i){
        in>>num;
        accu+=(num-m)*(num-m);
    }
    double v=accu/n;
    cout<<n<<" "<<setprecision(7)<<m<<" "<<v<<" "<<maxn<<" "<<minn<<endl;
}

