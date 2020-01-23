//
//  polynomia.cpp
//  helloworld
//
//  Created by Apple on 2020/1/23.
//  Copyright © 2020 Apple. All rights reserved.
//


//大数乘法取模运算
//
//计算(a*b)%m的值，当a和b还有m都很大时，那么会溢出long long，虽然也可以采用字符串表示大数进行乘法后再取余得到结果，但未免稍显繁琐。
//
//二进制数也是满足十进制竖式乘法运算规律的，我们可以模拟二进制乘法竖式来计算(a*b)%m，因为其每次只相当于a乘2，再取模就不会溢出了；
//

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<vector>
using namespace std;
//#define long long ll
//计算(a*b)%m
long long muliti_mod(long long a,long long b,long long mod){
    long long result=0;
    while(b>0){
        if(b&1)
            result=(a+result)%mod;
        a=(a<<1)%mod;
        b>>=1;
    }
    return result;
}

//假设我们有整数a, b与除数m ,那么假设
//a % m = j , b % m = t , 有整数 i , s , 使
//a=im+jb=sm+t
//a=im+jb=sm+t
//
//所以有
//a⋅b=(im+j)⋅(sm+t)=ism2+jsm+itm+jt
//a⋅b=(im+j)⋅(sm+t)=ism2+jsm+itm+jt
//
//推出
//(a⋅b)modm=(ism2+jsm+itm+jt)modm=jtmodm=((amodm)(bmodm))modm
//(a⋅b)modm=(ism2+jsm+itm+jt)modm=jtmodm=((amodm)(bmodm))modm
//
//所以
//对于像7123456789%655367123456789%65536这样的大数幂模运算,我们可以把大数幂m拆分成形如m=m1+m2+...+mnm=m1+m2+...+mn这样的形式,那么nm=nm1+m2+...+mn=nm1nm2⋅...nmnnm=nm1+m2+...+mn=nm1nm2⋅...nmn,这样通过上面的公式我们就可以很容易算出大数幂了.
//因为
//abcmodm=((ab)⋅c)modm=(((ab)modm)(cmodm))modm=(((amodm)(bmodm)modm)(cmodm))modm
//abcmodm=((ab)⋅c)modm=(((ab)modm)(cmodm))modm=(((amodm)(bmodm)modm)(cmodm))modm
//
//依次类推既可.
//我们再考虑大数幂m要如何分解成形如m=m1+m2+...+mnm=m1+m2+...+mn的形式.
//观察211=21+2+8=21×20+1×21+0×22+1×23211=21+2+8=21×20+1×21+0×22+1×23.
//所以
//可以把大数幂m写成二进制,然后只取值为1的位,和这一位在二进制中从右到左的位数(从0开始计算),就可以得到这个大数幂的分解式了.
//
//
//————————————————
//版权声明：本文为CSDN博主「怪叔叔爱猫猫」的原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接及本声明。
//原文链接：https://blog.csdn.net/cain4578369/article/details/72724206
//

//计算pow(a,b)%mod
long long pow_mod(long long a,long long b,long long mod){
    long long result=1;
    while(b>0){
        if(b&1){
            result=muliti_mod(result, a, mod);
        }
        a=muliti_mod(a, a, mod);
        b>>=1;
    }
    return result;
}
vector<long long> factors;
long long n,m,a;
long long m_mod=1000000007;
long long fn(long long x){
    long long result=0;
    for(long long i=0;i<=m;i++){
        result+=muliti_mod(factors[i], pow_mod(x, i, m_mod), m_mod);
        result%=m_mod;
    }
    return result;
}
long long sn(long long n){
    long long result=0;
    for(long long i=0;i<=n;i++){
        result+=muliti_mod(pow_mod(a, i, m_mod), fn(i), m_mod);
        result%=m_mod;
    }
    return result;
}
int main(){
    //cin>>n>>m>>a;
    scanf("%lld %lld %lld\n",&n,&m,&a);
    for(long long i=0;i<=m;i++){
        long long t;
        //cin>>t;
        scanf("%lld ",&t);
        factors.push_back(t);
    }
    cout<<sn(n)<<endl;
}
