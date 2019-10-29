#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

const int MaxN = 1e5 + 10, MaxM = 3e5 + 10, inf = 0x3f3f3f3f;

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

#define Yes (*IO::fe++ = 'Y', *IO::fe++ = 'e', *IO::fe++ = 's', *IO::fe++ = '\n')
#define No (*IO::fe++ = 'N', *IO::fe++ = 'o', *IO::fe++ = '\n')

struct Orz
{
	int x, y, z;
	inline bool operator < (const Orz &a) const//���������
	{
		return z > a.z;
	}
} e[MaxM];

int fa[MaxN];
inline int get(int x)//ѹ��·����������һ���ӣ�����
{
	return fa[x] == x ? x : fa[x] = get(fa[x]);
}

int ver[MaxM << 1], edge[MaxM << 1], Next[MaxM << 1], head[MaxN], len;
inline void add(int x, int y, int z)
{
	ver[++ len] = y, edge[len] = z, Next[len] = head[x], head[x] = len;
}

namespace lca//�����ǻ������ lca��һ���ģ����ǵõ�ʱ�� hl ���˺ó�ʱ�䣬һֱд���ԣ�������Ҳֻ�ܴ����￴���Լ��ɳ���
{
	int dep[MaxN], f[MaxN][21], w[MaxN][21];
	bool vis[MaxN];
	inline void dfs(int x)
	{
		vis[x] = 1;//�ǵñ�ǣ�Ҫ�� O(n) �ĸ��ӶȾͱ���� O(n^2)��T ��
		for (int i = 1; i <= 20; ++ i)
		{
			f[x][i] = f[f[x][i - 1]][i - 1];
			w[x][i] = min(w[x][i - 1], w[f[x][i - 1]][i - 1]);
		}
		for (int i = head[x]; i; i = Next[i])
		{
			int y = ver[i];
			if (y == f[x][0]) continue;
			f[y][0] = x;
			w[y][0] = edge[i];
			dep[y] = dep[x] + 1;
			dfs(y);
		}
	}

	inline int LCA(int x, int y)
	{
		int ans = inf;
		if (dep[x] > dep[y]) std::swap(x, y);
		for (int i = 20; i >= 0; -- i)
			if (dep[y] - (1 << i) >= dep[x]) chkMin(ans, w[y][i]), y = f[y][i];
		if (x == y) return ans;
		for (int i = 20; i >= 0; -- i)
			if (f[x][i] ^ f[y][i]) chkMin(ans, min(w[x][i], w[y][i])), x = f[x][i], y = f[y][i];
		chkMin(ans, min(w[x][0], w[y][0]));
		return ans;
	}
}

using lca::vis;
using lca::dfs;
using lca::LCA;

int main()//������Ŀ�ĵ�һ�ۣ������ǻ����䣬Ȼ�������룬���� IOI ��ת�᲻�����ô��Ȼ�ɣ�Ȼ���벻�������������
{//д���Ǹ�ɶ���о�û˵һ����Ȼ������֮�µ㿪 duyi �� code��Ȼ�����̹ص���Ϊɶ����Ϊ��һ�۾Ϳ�������ǻ�����
	int n, m, Q; read(n, m, Q);//Ȼ�����д��󣬽���ȥ���㣬�±ƣ����򿪿���ϸ�ڣ�Ŷ�����˱�� vis[i]���� w �� 0x3f
	for (int i = 1; i <= m; ++ i) read(e[i].x, e[i]. y, e[i].z);//Ȼ���ֱ����ˣ�����԰ɣ�Ӧ��û������Ѿ��Ȼ�����ֲ�
	std::sort(e + 1, e + m + 1);
	for (int i = 1; i <= n; ++ i) fa[i] = i;
	for (int i = 1; i <= m; ++ i)//�ֲУ��ո�д��˼·ûɾ��ֱ�Ӹ��ˣ������������д���� Q���ֲ���һֱ����
	{
		int x = get(e[i].x), y = get(e[i].y);
		if (x == y) continue;
		fa[x] = y;
		add(e[i].x, e[i].y, e[i].z), add(e[i].y, e[i].x, e[i].z);
	}
	memset(lca::w, 0x3f, sizeof(lca::w));
	for (int i = 1; i <= n; ++ i)
		if (!vis[i]) dfs(i);
	for (int i = 1, x, y, z; i <= Q; ++ i)
	{
		read(x, y, z);
		if (get(x) != get(y)) { No; continue; }//x �޷����� y
		if (LCA(x, y) >= z) Yes;//x -> y ��·���ϵ���СȨֵ���� z����������
		else No;
	}
	IO::flush();
	return 0;
}
