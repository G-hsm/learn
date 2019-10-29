#include<bits/stdc++.h>

typedef long long ll;
const int maxn=1e5+10;
const ll INF=0x3f3f3f3f3f3f3f3fll;

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

struct Orz{int w,s,p;}o[maxn];
inline bool cmp(Orz a,Orz b)//����������෴������ν��
{
	return a.w>b.w || (a.w==b.w && a.p<b.p);
}

ll f[2][250][250];//f[i][a][b]��ʾ������������ǰ i ���ˣ�Ŀǰ�Ѿ��� a ��������ˣ����� b ����ֻ���鳤����С����
int main()
{
	int n,kk;read(n);read(kk);
	for (int i=1; i<=n; ++i) read(o[i].w),read(o[i].s),read(o[i].p);
	if (kk<<1>n) return puts("-1"),0;//��Ҫ��Ƹ���˳�������ӦƸ���ˣ��޽�

	for (int i=1; i<=n; ++i)
	{
		if (o[i].p==2) o[i].p=3;
		else if (o[i].p==3) o[i].p=2;
	}
	std::sort(o+1,o+n+1,cmp);//���վ���ֵ�Ӵ�С�����鳤����Ա��˳������
	memset(f,0x3f,sizeof(f));//��ֵ
	f[0][0][0]=0;
	int x=1;//��������
	for (int i=1; i<=n; ++i)
	{
		int lim1=min(i>>1,kk);//�Ѿ������ı߽磨����ֵ��
		for (int j=0; j<=lim1; ++j)
		{
			int lim2=min(i-(j<<1),kk-j);//��Ҫ��õ���ı߽磨����ֵ��
			for (int k=0; k<=lim2; ++k) f[x][j][k]=INF;
		}
		lim1=min((i-1)>>1,kk);//�Ѿ������ı߽磨ת�ƣ�
		for (int j=0; j<=lim1; ++j)
		{
			int lim2=min(i-1-(j<<1),kk-j);//��Ҫ��õ���ı߽磨ת�ƣ�
			for (int k=0; k<=lim2; ++k)
			{
				if (o[i].p==1 && j+k+1<=kk) chkMin(f[x][j][k+1],f[x^1][j][k]+o[i].s);//�鳤�ֻ�ܶ࿪һ����
				else if (o[i].p==2)
				{
					if (j+k+1<=kk) chkMin(f[x][j][k+1],f[x^1][j][k]+o[i].s);//��Ա����Ϳ����Ƕ࿪һ�����
					if (k>0) chkMin(f[x][j+1][k-1],f[x^1][j][k]+o[i].s);//����ȥ���ǰû����õ���
				}
				else if (o[i].p==3 && k>0) chkMin(f[x][j+1][k-1],f[x^1][j][k]+o[i].s);//ͨ����������ǰû����õ���
				chkMin(f[x][j][k],f[x^1][j][k]);//Ҳ��������������һ�Σ���û��ԭ�ȵķ����Ĵ���С
			}
		}
		x^=1;
	}
	if (f[x^1][kk][0]==INF) f[x^1][kk][0]=-1;//�޽�
	write(f[x^1][kk][0],'\n');
	IO::flush();
	return 0;
}
