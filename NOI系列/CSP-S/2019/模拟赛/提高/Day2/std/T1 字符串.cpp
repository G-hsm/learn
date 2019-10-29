#include<bits/stdc++.h>

const int maxn=3e5+10;

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

int p[maxn];
char s[maxn],t[maxn];
int main()
{
	int n,m;read(n);read(m);
	scanf("%s",s+1), scanf("%s",t+1);
	for (int i=1, j=1; i<=m; ++i)
	{
		while (j<=n && s[j]!=t[i]) ++j;//ѡ���һ���� Ti һ������ Ti ����ƥ��
		if (j==n+1) return puts("-1"),0;//����ĩβ��û�У��޽�
		p[i]=j++;//Ti ��ƥ��λ��Ϊ Sj
	}
	for (int i=m, j=n; j>1; --j)
	{
		if (s[j]==s[j-1]) continue;//�Ӻ���ǰ��˳�����ο��� S ��������������������ĸ��ͬ��λ��
		while (i>0 && p[i]>j) --i;//pj~i ��һ��ǰ׺�����ƶ�
		if (!i) return puts("-1"),0;//ͬ��
		p[i]=j;//����Ϊ i �� i+1 ֮һ���Ӷ�ʹ�� i ��������
		if (t[i]==s[j-1]) p[i]=--j;
	}
	for (int i=1; i<=m; ++i) write(p[i],' ');
	IO::flush();
	return 0;
}
