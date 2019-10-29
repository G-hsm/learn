#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

#define mp std::make_pair
typedef long long ll;
typedef std::pair<ll, int> pli;
const int MaxN = 3e3 + 10;
const ll INF = 0x3f3f3f3f3f3f3f3fll;

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

int ver[MaxN << 1], edge[MaxN << 1], Next[MaxN << 1], head[MaxN], len;
inline void add(int x, int y, int z)
{
	ver[++ len] = y, edge[len] = z, Next[len] = head[x], head[x] = len;
}

int n, m, k, z[MaxN];
ll dist[MaxN];
bool vis[MaxN];
inline ll Dijkstra(ll l)
{
	for (int i = 1; i <= n; ++ i) dist[i] = INF, vis[i] = 0;
	std::priority_queue<pli, std::vector<pli>, std::greater<pli> >q;
	q.push(mp(0, 1)), dist[1] = 0;
	while (!q.empty())
	{
		int x = q.top().second;
		q.pop();
		if (vis[x]) continue;
		vis[x] = 1;
		for (int i = head[x]; i; i = Next[i])
		{
			int y = ver[i]; ll z = edge[i];
			if (chkMin(dist[y], dist[x] + max(z - l, 0ll))) q.push(mp(dist[y], y));
		}
	}
	return dist[n];
}

int main()//������˼·���ö�� m ���ߣ�����Ȩ��Ϊ max(z - l, 0ll)��������·���� kl �󣬶����е����ȡ min ��Ϊ��
{//����һ�������ܺ�д������Ҫ˼��Ϊʲô��ȷ��
	read(n, m, k);
	for (int i = 1, x, y; i <= m; ++ i) read(x, y, z[i]), add(x, y, z[i]), add(y, x, z[i]);
	ll ans = Dijkstra(0), l = 0;//�����˵�ǿ�������һ��·������ l ��Ϊ�� k ��ֵ��ʱ���ǵ�����ǰ k ���֮�͵�
	for (int i = 1; i <= m; ++ i) l = z[i], chkMin(ans, Dijkstra(l) + 1ll * k * l);//����ֻ���󲻻��С
	write(ans, '\n', true);
	IO::flush();
	return 0;
}
