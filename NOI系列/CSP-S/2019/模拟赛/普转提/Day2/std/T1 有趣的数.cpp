#include<bits/stdc++.h>

typedef long long ll;

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

ll bin[20];
int main()
{
	ll l,r; read(l), read(r);
	bin[0]=1;
	for (int i=1; i<=18; ++i) bin[i]=bin[i-1]*10;//10 �Ľ׳�
	ll ans=0;
	for (int i=0; i<=9; ++i)//����������
		for (int j=0; j<=9; ++j)//���������
		{
			if (i==j) continue;
			for (int k=3; k<=18; ++k)//ö���������λ��
				for (int t=1; t<=k; ++t)//�������ֵ�λ��
				{
					if ((t==k && !j) || (t^k && !i)) continue;
					ll num=0;//���������
					for (int p=1; p<=k; ++p)//�������ֵ�λ��
						if (p^t) num+=i*bin[p-1];
						else num+=j*bin[p-1];
					if (l<=num && num<=r) ++ans;//����������������Ϸ�
				}
		}
	write(ans,'\n');
	IO::flush();
	return 0;
}
