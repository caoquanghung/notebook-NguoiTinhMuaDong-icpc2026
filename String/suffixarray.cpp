#include<bits/stdc++.h>
using namespace std;
const int N = 300005;
string s;
int p[N],c[N],n,i,k,cnt[N],pos[N],p_new[N],c_new[N],t;
pair<char, int>a[N];
pair<int, int>pre,now;
void count_sort(){
    for(i=0;i<n;i++)cnt[c[i]]++;
    pos[0]=0;
    for(i=1;i<n;i++)pos[i]=pos[i-1]+cnt[i-1];
    for(i=0;i<n;i++){
        p_new[pos[c[p[i]]]]=p[i];
        pos[c[p[i]]]++;
    }
    for(i=0;i<n;i++){
        p[i]=p_new[i];
        cnt[i]=0;
    }
}
void setup(){
    for(i=0;i<n;i++)a[i]={s[i],i};
    sort(a,a+n);
    for(i=0;i<n;i++)p[i]=a[i].second;
    for(i=1;i<n;i++){
        if(a[i].first==a[i-1].first)c[p[i]]=c[p[i-1]];
        else c[p[i]]=c[p[i-1]]+1;
    }
    while((1<<k)<n){
        for(i=0;i<n;i++)p[i]=(p[i]-(1<<k)+n)%n;
        count_sort();
        c_new[p[0]]=0;
        for(i=1;i<n;i++){
            pre={c[p[i-1]],c[(p[i-1]+(1<<k))%n]};
            now={c[p[i]],c[(p[i]+(1<<k))%n]};
            if(now==pre)c_new[p[i]]=c_new[p[i-1]];
            else c_new[p[i]]=c_new[p[i-1]]+1;
        }
        for(i=0;i<n;i++)c[i]=c_new[i];
        k++;
    }
}
main(){
    cin>>s;
    s+='$';
    n=s.size();
    setup();
    for(int i = 0; i < n; ++i)
        cout << p[i] << ' ';
} 
