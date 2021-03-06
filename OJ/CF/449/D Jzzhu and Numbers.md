# title

[CF449D](https://www.luogu.org/problem/CF449D)

Description

>给出一个长度为 $n$ 的序列 $a_1,a_2...a_n$ 。
>
>求构造出一个序列 $i_1 \le i_2 \le ... \le i_k$ 使得 $a_{i_1}\&a_{i_2}\&...\&a_{i_k}=0$ 。求方案数模 $10^9+7$ 。
>
>也就是从 $\{a_i\}$ 里面选出一个非空子集使这些数按位与起来为 $0$ 。

# analysis

这不是普转提的第四题吗？不得不防啊。

这也是一个新的知识点，高维前缀和。

从最开始的说起：

一维前缀和：

```cpp
for (int i=1; i<=n; ++i) a[i]+=a[i-1];
```

二维前缀和：

```cpp
for (int i=1; i<=n; ++i)
    for (int j=1; j<=n; ++j) a[i][j]+=a[i-1][j]+a[i][j-1]-a[i-1][j-1];
```

也可以写成这样：

```cpp
for (int i=1; i<=n; ++i)
    for (int j=1; j<=n; ++j) a[i][j]+=a[i-1][j];
for (int i=1; i<=n; ++i)
    for (int j=1; j<=n; ++j) a[i][j]+=a[i][j-1];
```

好像第二种写法有些麻烦？别急，看三维的：

```cpp
for (int i=1; i<=n; ++i)
    for (int j=1; j<=n; ++j)
        for (int k=1; k<=n; ++k)
            a[i][j][k]+=a[i-1][j][k]+a[i][j-1][k]+a[i][j][k-1]
        			-a[i][j-1][k-1]-a[i-1][j][k-1]-a[i-1][j-1][k]
        			+a[i-1][j-1][k-1];
```

换成第二种来写一下：

```cpp
for (int i=1; i<=n; ++i)
    for (int j=1; j<=n; ++j)
        for (int k=1; k<=n; ++k) a[i][j][k]+=a[i-1][j][k];
for (int i=1; i<=n; ++i)
    for (int j=1; j<=n; ++j)
        for (int k=1; k<=n; ++k) a[i][j][k]+=a[i][j-1][k];
for (int i=1; i<=n; ++i)
    for (int j=1; j<=n; ++j)
        for (int k=1; k<=n; ++k) a[i][j][k]+=a[i][j][k-1];
```

分析一下：对于三维前缀和，第一种写法的复杂度是 $O(8N^3)$ ，而第二种写法的复杂度为 $O(3N^3)$ ，快了很多。

而且随着维度增高，第二种写法的愈发加大。

最后的解决方法便是高维前缀和，第一层循环从低到高枚举二进制位数，第二层循环从 $1$ 到 $n$ 枚举所有元素（下面给出本题中的高维前缀和 $code$ ）：

 ```cpp
for (int i=0; i<=20; ++i)
	for (int j=1; j<=maxn; ++j)
		if (j&(1<<i)) f[j^(1<<i)]+=f[j];
 ```

对于本题而言，最后的方案数为： $2^{n-1}-至少1位为1+至少2位为1-至少3位为1...$ 。

根据上道题的经验，设 $f[x]$ 表示包含 $i$ 这个状态的数的个数。

然后枚举所有可能的有 $1$ 的情况：$ans=2^{n-1}-\sum(-1)^{|S|}*2^{f[i]-1}$ 。其中 $|S|$ 表示这种状态 $i$ 中含 $1$ 的个数。

$f[x]$ 就用刚才的高维前缀和解决就好了，然后应该就没了。

# code

```cpp
#include<bits/stdc++.h>

typedef long long ll;
const int maxn=1e6,mod=1e9+7;

namespace IO
{
	char buf[1<<15],*fs,*ft;
	inline char getc() { return (ft==fs&&(ft=(fs=buf)+fread(buf,1,1<<15,stdin),ft==fs))?0:*fs++; }
	template<typename T>inline void read(T &x)
	{
		x=0;
		T f=1, ch=getchar();
		while (!isdigit(ch) && ch^'-') ch=getchar();
		if (ch=='-') f=-1, ch=getchar();
		while (isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
		x*=f;
	}

	char Out[1<<24],*fe=Out;
	inline void flush() { fwrite(Out,1,fe-Out,stdout); fe=Out; }
	template<typename T>inline void write(T x,char str)
	{
		if (!x) *fe++=48;
		if (x<0) *fe++='-', x=-x;
		T num=0, ch[20];
		while (x) ch[++num]=x%10+48, x/=10;
		while (num) *fe++=ch[num--];
		*fe++=str;
	}
}

using IO::read;
using IO::write;

int p[maxn+10],f[maxn+10];
int main()
{
	int n;read(n);
	for (int i=1,x; i<=n; ++i) read(x), ++f[x];
	p[0]=1;
	for (int i=1; i<=maxn; ++i) p[i]=1ll*p[i-1]*2%mod;

	for (int i=0; i<=20; ++i)
		for (int j=1; j<=maxn; ++j)
			if (j&(1<<i)) (f[j^(1<<i)]+=f[j])%=mod;
	int ans=0;
	for (int i=0; i<=maxn; ++i)
	{
		int opt=1;
		for (int j=0; j<=20; ++j)
			if (i&(1<<j)) opt=-opt;
		ans=(ans+(1ll*opt*(p[f[i]]-1)%mod)+mod)%mod;
	}
	write(ans,'\n');
	IO::flush();
	return 0;
}
```
