#include<bits/stdc++.h>

const int maxn=1e5+10, inf=0x3f3f3f3f;

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

struct SGT
{
	int Max[maxn<<2],Min[maxn<<2];
	inline void pushup(int x)//�ϴ����
	{
		Max[x]=max(Max[x<<1],Max[x<<1|1]);
		Min[x]=min(Min[x<<1],Min[x<<1|1]);//��������˼
	}

	inline void Change(int x,int l,int r,int k,int v)//ȨֵΪ��ǰ�������һ�α�������ʱ��
	{
		if (l==r)
		{
			Max[x]=Min[x]=v;
			return ;
		}
		int mid=(l+r)>>1;
		if (k<=mid) Change(x<<1,l,mid,k,v);
		else Change(x<<1|1,mid+1,r,k,v);
		pushup(x);
	}

	inline int QueryL(int x,int l,int r,int v)
	{
		if (l==r) return Max[x]>=v ? l : 0;
		int mid=(l+r)>>1;
		if (Max[x<<1|1]>=v) return QueryL(x<<1|1,mid+1,r,v);//��ΪҪ�ҵ�ǰ�����һ���Ϸ���λ�ã�����Ҫ�������ұ�Щ
		else return QueryL(x<<1,l,mid,v);//��������Ϊ�Ҷ��ӵ�Ȩֵ�Ƿ�Ϸ�
	}

	inline int queryl(int x,int l,int r,int k,int v)//�ҵ��� k λ��ǰ�����һ�����ڵ��� v ��λ��
	{
		if (l==r) return Max[x]>=v ? l : 0;
		int mid=(l+r)>>1;
		if (k<=mid) return queryl(x<<1,l,mid,k,v);//ע���ж���������ǰ���������
		else
		{
			int t=queryl(x<<1|1,mid+1,r,k,v);
			if (t) return t;
			return QueryL(x<<1,l,mid,v);//������������߶������϶���
		}
	}

	inline int QueryR(int x,int l,int r,int v)
	{
		if (l==r) return Max[x]>=v ? l : 0;
		int mid=(l+r)>>1;
		if (Max[x<<1]>=v) return QueryR(x<<1,l,mid,v);//��ΪҪ�ҵ��󷽵�һ���Ϸ���λ�ã�����Ҫ���������Щ
		else return QueryR(x<<1|1,mid+1,r,v);//��������Ϊ����ӵ�Ȩֵ�Ƿ�Ϸ�
	}

	inline int queryr(int x,int l,int r,int k,int v)//�ҵ��� k λ�ú�ĵ�һ�����ڵ��� v ��λ��
	{
		if (l==r) return Max[x]>=v ? l : 0;
		int mid=(l+r)>>1;
		if (k>mid) return queryr(x<<1|1,mid+1,r,k,v);//ע���ж��������Һ󷽣����ұ�
		else
		{
			int t=queryr(x<<1,l,mid,k,v);
			if (t) return t;
			return QueryR(x<<1|1,mid+1,r,v);//������������߶������϶���
		}
	}

	inline int querymin(int x,int l,int r,int tl,int tr)//��ѯ [tl,tr] �������Сֵ
	{
		if (tl<=l && r<=tr) return Min[x];
		int mid=(l+r)>>1;
		int ans=inf;
		if (tl<=mid) chkMin(ans,querymin(x<<1,l,mid,tl,tr));
		if (tr>mid) chkMin(ans,querymin(x<<1|1,mid+1,r,tl,tr));//���д���ͱȽϳ����ˣ��´�Ҫ��д����
		return ans;
	}
} R, C;//row��col ����һ���߶����Ա��ѯ���伫ֵ

int row[maxn], col[maxn], n, m, Q;
inline int ask(int a,int b,int c,int d,int v)
{
	if (a==c && b==d) return 0;//ͬһ���㣬0 ������
	if ( (row[a]<v && col[b]<v) || (row[c]<v && col[d]<v) ) return -1;//����һ��������ж��� ban
	if ( (row[a]>=v && col[b]>=v) || (row[c]>=v && col[d]>=v) ) return abs(a-c)+abs(b-d);//ֻҪһ������������о�û�б� ban����Ϊ�����پ���
	//�������������������ϣ���ô����������������ǣ��к�������һ���� ban
	bool v1=(row[a]>=v), v2=(row[c]>=v);//����ȷ�����������������һ��Ԫ�ر� ban
	if (v1^v2) return abs(a-c)+abs(b-d);//һ��������Ǻõģ�һ��������Ǻõģ����Դ���һ�������پ���·������ͼ��֪
	//�������˵���������һ���ģ�Ҫô���б� ban��Ҫô���б� ban
	if (v1)//�б� ban
	{
		if (a>c) std::swap(a,c);
		if (R.querymin(1,1,n,a,c)>=v) return abs(a-c)+abs(b-d);//[a,c] ������ı�������ʱ��Ҳ�Ϸ��Ļ�����һ���н�

		if (b>d) std::swap(b,d);
		if (C.Max[1]<v) return -1;////����������������ʱ�䲻�Ϸ���˵��û��һ�������ĺϷ��У�ּ�ڲ鿴��ת���Ƿ����

		int t=C.queryr(1,1,m,b,v);//�ҵ��� b λ�ú�ĵ�һ�����ڵ��� v ��λ��
		if (t && t<=d) return abs(a-c)+abs(b-d);//�����λ���ںϷ�������
		int ans=inf;
		t=C.queryl(1,1,m,b,v);//��������ת��
		if (t) chkMin(ans,abs(a-c)+abs(b-t)+abs(d-t));
		t=C.queryr(1,1,m,d,v);//��������ת��
		if (t) chkMin(ans,abs(a-c)+abs(b-t)+abs(d-t));
		return ans<inf ? ans : -1;
	}
	else//�б� ban
	{
		if (b>d) std::swap(b,d);
		if (C.querymin(1,1,m,b,d)>=v) return abs(a-c)+abs(b-d);//[b,d] ������ı�������ʱ��Ҳ�Ϸ��Ļ�����һ���н�

		if (a>c) std::swap(a,c);
		if (R.Max[1]<v) return -1;//����������������ʱ�䲻�Ϸ���˵��û��һ�������ĺϷ��У�ּ�ڲ鿴��ת���Ƿ����

		int t=R.queryr(1,1,n,a,v);//�ҵ��� a λ�ú�ĵ�һ�����ڵ��� v ��λ��
		if (t && t<=c) return abs(a-c)+abs(b-d);//�����λ���ںϷ�������
		int ans=inf;
		t=R.queryl(1,1,n,a,v);//��������ת��
		if (t) chkMin(ans,abs(b-d)+abs(a-t)+abs(c-t));
		t=R.queryr(1,1,n,c,v);//��������ת��
		if (t) chkMin(ans,abs(b-d)+abs(a-t)+abs(c-t));
		return ans<inf ? ans : -1;
	}
}

int main()
{
	read(n), read(m), read(Q);
	for (int i=1,opt; i<=Q; ++i)
	{
		read(opt);
		if (opt==1)//�е��޸�
		{
			int x;read(x);
			row[x]=i;
			R.Change(1,1,n,x,i);
		}
		else if (opt==2)//�е��޸�
		{
			int x;read(x);
			col[x]=i;
			C.Change(1,1,m,x,i);
		}
		else//��ѯ��
		{
			int a,b,c,d,v;
			read(a), read(b), read(c), read(d), read(v);
			write(ask(a,b,c,d,max(0,i-v)),'\n');//Ϊ��������ݵ�ֵΪ max(0,(i-v))
		}//Ե�ɣ���ǰ row ��ֵ = ��ǰʱ�� i -�����һ�α�������ʱ�� row[x]����ĿҪ��i-row[x]<=v���� rox[x]>=i-v
	}
	IO::flush();
	return 0;
}
