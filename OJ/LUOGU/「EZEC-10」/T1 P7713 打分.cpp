#include <bits/stdc++.h>

#define file(s) freopen(s ".in", "r", stdin), freopen(s ".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

typedef long long ll;
const int MaxN = 1e5 + 10, MaxM = 101;

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

ll ans, sum, maxs, a[MaxN];
int main()
{
	int n; ll m;
	read(n), read(m);
	for (int i = 1; i <= n; ++ i) read(a[i]);
	std::sort(a + 1, a + n + 1);
	for (int i = 2; i <= n; ++ i) sum += a[i];
	maxs = a[n] * (n - 1);	
	if (sum + m <= maxs) ans = sum + m - a[n];
	else
	{
		ll tmp = sum + m - maxs;
		ans = maxs - a[n] + tmp * (n - 2) / (n - 1);//先乘后除 AC，先除后乘 WA
	}
	write(ans, '\n', true);
	IO::flush();
	return 0;
}
