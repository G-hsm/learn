#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

const int MaxN = 1e3 + 10, MaxW = 1e6 + 10, mod = 987654321;//���ģ��������˼

namespace IO
{
	#define Grt ch = getchar()
	char buf[1<<15], *fs, *ft;
	inline char getc() { return ft == fs && (ft = (fs = buf) + fread(buf, 1, 1 << 15, stdin), ft == fs) ? 0 : *fs ++; }
	template <typename T> inline void read(T &x)
	{
		x = 0;
		T f = 1, Grt;
		while (!isdigit(ch) && ch ^ '-') Grt;
		if (ch == '-') f = -1, Grt;
		while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), Grt;
		x *= f;
	}

	template <typename T, typename... Args>
	inline void read(T &x, Args &...args) { read(x); read(args...); }

	char Out[1<<24], *fe = Out;
	inline void flush() { fwrite(Out, 1, fe - Out, stdout); fe = Out; }
	template <typename T> inline void write(T x, char str, bool fl)
	{
		if (!x) *fe++ = 48;
		if (x < 0) *fe++ = '-', x = -x;
		T num = 0, ch[20];
		while (x) ch[++ num] = x % 10 + 48, x /= 10;
		while (num) *fe++ = ch[num --];
		if (fl) *fe++ = str;
	}
}

using IO::read;
using IO::write;

template <typename T> inline bool chkMin(T &a, const T &b) { return a > b ? (a = b, true) : false; }
template <typename T> inline bool chkMax(T &a, const T &b) { return a < b ? (a = b, true) : false; }
template <typename T> inline T min(T a, T b) { return a < b ? a : b; }
template <typename T> inline T max(T a, T b) { return a > b ? a : b; }

int a[MaxN], f[MaxN], n;
int prime[MaxW], sum[MaxN], cnt;
bool isnopr[MaxW];
inline void Pre()
{
	isnopr[1] = 1;//����ɸ��Ҫ���˰� 1 ���޳���
	for (int i = 2; i <= sum[n]; ++ i)//ֵ���Ͻ磺1e6���ܺ��룬ֻ��д��������
	{
		if (!isnopr[i]) prime[++ cnt] = i;
		for (int j = 1, x; j <= cnt && (x = i * prime[j]) <= sum[n]; ++ j)
		{
			isnopr[x] = 1;
			if (i % prime[j] == 0) break;//��ǰ�������Ͻ��е� i ��Լ����ʱ�򣬾�˵�� x �Ѿ����������ˣ�ֹͣ��һ��ѭ��
		}//����һ��������ʼ��һ�ֵ��ж�
	}
}

int main()//�� f[i] ��ʾǰ i ��ʯͷ����ɵĺϷ����еķ�����
{//������ôת�ƣ����ǿ��Ժϲ��ģ�һ���Ϸ��������е��������������ǵ���˵ֻҪǰ i �����ĺ���������f[i] �϶���...
	read(n);//���䲻ֹ 1~i ��һ�֣���ô����ö����˵� j ��ֻҪ j-1~i ��һ���������֮��Ϊ��������ô f[i]=��f[j]
	for (int i = 1; i <= n; ++ i) read(a[i]), sum[i] = sum[i - 1] + a[i];//����ĺ���Ҫ O(1) �жϣ�������Ȼǰ׺��
	Pre(), f[0] = 1;
	for (int i = 1; i <= n; ++ i)
		for (int j = 1; j <= i; ++ j)//Ȼ�� O(n^2) ö�����Ҷ˵��ˣ���Ҫ�ﵽ O(1) �ж�������ֻ��ʵ������ɸ
			if (!isnopr[sum[i] - sum[j - 1]]) (f[i] += f[j - 1]) %= mod;
	write(f[n], '\n', true);//�����ܸ��Ӷ��� O(n^2)
	IO::flush();
	return 0;
}
