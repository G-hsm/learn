#include<bits/stdc++.h>

const int maxn=505,maxk=1e3+10;

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

template<typename T>inline bool chkMin(T &a,const T &b) { return a>b ? (a=b, true) : false; }
template<typename T>inline bool chkMax(T &a,const T &b) { return a<b ? (a=b, true) : false; }
template<typename T>inline T min(T a,T b) { return a<b ? a : b; }
template<typename T>inline T max(T a,T b) { return a>b ? a : b; }

struct Orz{int in,out,w,s,v;}o[maxn];
inline bool cmp(Orz a,Orz b)
{
	return a.out<b.out || (a.out==b.out && a.in>b.in);
}

int f[maxn][maxk],g[maxk];//��ʾ i �Լ� i ������Ʒ������ʱ�����������Ϊ j ʱ���������
int main()
{
	int n,S,nowt=0,noww=0;
	read(n);read(S);
	for (int i=1; i<=n; ++i) read(o[i].in),read(o[i].out),read(o[i].w),read(o[i].s),read(o[i].v);
	o[++n]=(Orz){0,n<<1,0,S,0};
	std::sort(o+1,o+n+1,cmp);//��������ʱ���С�����ţ���������ȥʱ��Ӵ�С�ţ�����֤�����Ʒ�Ϸ�����Ʒһ������ǰ��

	for (int i=1; i<=n; ++i)//ö����Ʒ
		for (int w=o[i].w; w<=S; ++w)//ö�ٿռ䣨�Ѿ��Ž������
		{
			nowt=o[i].in;//���ڵ�ʱ��
			g[nowt]=0;//��ʾʱ�� i ֮ǰ��Ʒ���������
			noww=min(w-o[i].w,o[i].s);//�����������������涨
			for (int j=1; j<i; ++j)//ö�� i �������Ʒ
				if (o[j].in>=o[i].in)
				{
					while (nowt<o[j].out) ++nowt, g[nowt]=g[nowt-1];
					chkMax(g[nowt],g[o[j].in]+f[j][noww]);//������������
				}
			f[i][w]=g[nowt]+o[i].v;//�������ó�������ü�ֵ
		}
	write(f[n][S],'\n');
	IO::flush();
	return 0;
}
