#include <bits/stdc++.h>

#define file(s) freopen(s ".in", "r", stdin), freopen(s ".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

typedef long long ll;
const int MaxN = 1e5 + 10, MaxM = 10;

namespace IO
{
	#define Grt ch = getchar()
	char buf[1 << 15], *fs, *ft;
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
	#undef Grt

	template <typename T, typename... Args>
	inline void read(T &x, Args &...args) { read(x); read(args...); }

	char Out[1 << 24], *fe = Out;
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

int a[MaxM], b[MaxM], c[MaxM], d[MaxM];
bool judge()
{
	for (int i = 1, x, t; i <= 3; ++ i)
	{
		t = 1;
		for (int j = 1; j <= 3; ++ j)
		{
			if (i + j > 3) x = i + j - 3;//多出来的回到头上
			else x = i + j;
			if (a[x] != b[j]) t = 0;//实现判断顺序的功能
		}
		if (t) return true;
	}
	return false;
}

int cnt, len;
int main()
{
	read(c[1]), read(c[2]), read(c[4]), read(c[3]);
	read(d[1]), read(d[2]), read(d[4]), read(d[3]);//顺时针输入
	for (int i = 1; i <= 4; ++ i)
	{
		if (!c[i]) ++ cnt;
		else a[++ len] = c[i];
	}
	len = 0;
	for (int i = 1; i <= 4; ++ i)
		if (d[i]) b[++ len] = d[i];//制造顺序字符串
	bool flag = false;
	if (cnt == 2 || cnt == 3 || cnt == 4) flag = true;
	else if (cnt == 1) flag = judge();
	else
	{
		if (c[1] == d[1] && c[2] == d[2] && c[3] == d[3] && c[4] == d[4]) flag = true;
		else flag = false;
	}
	puts(flag == true ? "Yes" : "No");
	return 0;
}
