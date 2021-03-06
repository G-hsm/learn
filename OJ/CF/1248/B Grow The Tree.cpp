#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

const int MaxN = 1e5 + 10;

namespace IO
{
	#define G ch = getchar()
	char buf[1<<15], *fs, *ft;
	inline char getc() { return ft == fs && (ft = (fs = buf) + fread(buf, 1, 1 << 15, stdin), ft == fs) ? 0 : *fs ++; }
	template <typename T> inline void read(T &x)
	{
		x = 0;
		T f = 1, G;
		while (!isdigit(ch) && ch ^ '-') G;
		if (ch == '-') f = -1, G;
		while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), G;
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

int a[MaxN];//仔细想想的话，此题很水
int main()//原问题模型为：将一个序列分成两部分，两部分的大小最多差为 1，求最大两部分的和的平方和
{
	int n; read(n);
	for (int i = 1; i <= n; ++ i) read(a[i]);
	std::sort(a + 1, a + n + 1);//所以先排个序
	int m = n >> 1, sumc = 0, sumr = 0;//利用下取整，正好满足条件
	for (int i = 1; i <= m; ++ i) sumc += a[i];//前一半划分成一个部分
	for (int i = m + 1; i <= n; ++ i) sumr += a[i];//后一半划分成一个部分
	write(1ll * sumc * sumc + 1ll * sumr * sumr, '\n', true);
	IO::flush();
	return 0;
}
