#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

typedef long long ll;
typedef unsigned long long ull;
const int MaxN = 1e5 + 10, mod = 1e9 + 7, inf = 0x3f3f3f3f;

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
	template <typename T> inline void write(T x, char str)
	{
		if (!x) *fe++ = 48;
		if (x < 0) *fe++ = '-', x = -x;
		T num = 0, ch[20];
		while (x) ch[++ num] = x % 10 + 48, x /= 10;
		while (num) *fe++ = ch[num --];
		*fe++ = str;
	}
}

using IO::read;
using IO::write;

template <typename T> inline bool chkMin(T &a, const T &b) { return a > b ? (a = b, true) : false; }
template <typename T> inline bool chkMax(T &a, const T &b) { return a < b ? (a = b, true) : false; }
template <typename T> inline T min(T a, T b) { return a < b ? a : b; }
template <typename T> inline T max(T a, T b) { return a > b ? a : b; }

inline int Quick_Power(int a, int b)
{
	int ans = 1;
	while (b)
	{
		if (b & 1) ans = ull(ans) * a % mod;
		a = ull(a) * a % mod, b >>= 1;
	}
	return ans;
}

int a[MaxN], b[MaxN], c[MaxN];
namespace SGT
{
	int a1[MaxN << 2], n1[MaxN << 2], a2[MaxN << 2], n2[MaxN << 2];
	int Min[MaxN << 2], Max[MaxN << 2], atag[MaxN << 2];
	inline void pushup(int x)
	{
		a1[x] = ull(a1[x << 1]) * a1[x << 1 | 1] % mod;
		n1[x] = n1[x << 1] + n1[x << 1 | 1];
		a2[x] = ull(a2[x << 1]) * a2[x << 1 | 1] % mod;
		n2[x] = n2[x << 1] + n2[x << 1 | 1];
		Min[x] = min(Min[x << 1], Min[x << 1 | 1]);
		Max[x] = max(Max[x << 1], Max[x << 1 | 1]);
	}

	inline void build(int x, int l, int r)
	{
		atag[x] = -1;
		if (l == r)
		{
			if (c[l] < b[l]) a1[x] = c[l], n1[x] = 1, a2[x] = 1, Min[x] = b[l];
			else a1[x] = 1, a2[x] = b[l], n2[x] = 1, Min[x] = inf;
			Max[x] = a[l];
			return ;
		}
		int mid = (l + r) >> 1;
		build(x << 1, l, mid);
		build(x << 1 | 1, mid + 1, r);
		pushup(x);
	}

	inline void pushdown(int x, int k)
	{
		atag[x] = k, a1[x] = Quick_Power(k, n1[x]);
	}

	inline void ChangeA(int x, int l, int r, int k, int v)
	{
		if (l == r)
		{
			Max[x] = v;
			return ;
		}
		if (atag[x] ^ -1) pushdown(x << 1, atag[x]), pushdown(x << 1 | 1, atag[x]), atag[x] = -1;
		int mid = (l + r) >> 1;
		if (k <= mid) ChangeA(x << 1, l, mid, k, v);
		else ChangeA(x << 1 | 1, mid + 1, r, k, v);
		pushup(x);
	}

	inline void ChangeB(int x, int l, int r, int k, int v, int c)
	{
		if (l == r)
		{
			chkMax(c, Max[x]);
			if (c < v) a1[x] = c, n1[x] = 1, a2[x] = 1, n2[x] = 0, Min[x]= v;
			else a1[x]= 1, n1[x] = 0, a2[x] = v, n2[x] = 1, Min[x] = inf;
			return ;
		}
		if (atag[x] ^ -1) pushdown(x << 1, atag[x]), pushdown(x << 1 | 1, atag[x]), atag[x] = -1;
		int mid = (l + r) >> 1;
		if (k <= mid) ChangeB(x << 1, l, mid, k, v, c);
		else ChangeB(x << 1 | 1, mid + 1, r, k, v, max(Max[x << 1], c));
		pushup(x);
	}

	inline void ChangeC(int x, int l, int r, int tl, int tr, int v)
	{
		if (tl > r || l > tr) return ;
		if (tl <= l && r <= tr && Min[x] > v)
		{
			pushdown(x, v);
			return ;
		}
		if (l == r)
		{
			a1[x] = 1, n1[x] = 0, a2[x] = b[l], n2[x] = 1, Min[x] = inf;
			return  ;
		}
		if (atag[x] ^ -1) pushdown(x << 1, atag[x]), pushdown(x << 1 | 1, atag[x]), atag[x] = -1;
		int mid = (l + r) >> 1;
		ChangeC(x << 1, l, mid, tl, tr, v);
		ChangeC(x << 1 | 1, mid + 1, r, tl, tr, v);
		pushup(x);
	}

	inline int find(int x, int l, int r, int v)
	{
		if (Max[x] <= v) return r + 1;
		int res = -1;
		while (l ^ r)
		{
			int mid = (l + r) >> 1;
			if (max(Max[x << 1], res) > v) x = x << 1, r = mid;
			else chkMax(res, Max[x << 1]), x = x << 1 | 1, l = mid + 1;
		}
		return l;
	}

	inline int Query(int x, int l, int r, int v)
	{
		int ans = -1;
		while (l ^ r)
		{
			int mid = (l + r) >> 1;
			if (v <= mid) x = x << 1, r = mid;
			else chkMax(ans, Max[x << 1]), x = x << 1 | 1, l = mid + 1;
		}
		return max(ans, Max[x]);
	}
}

using SGT::build;
using SGT::ChangeA;
using SGT::ChangeB;
using SGT::ChangeC;
using SGT::Query;
using SGT::find;
using SGT::a1;
using SGT::a2;

int main()
{
	int n, q; read(n, q);
	for (int i = 1; i <= n; ++ i) read(a[i]), c[i] = max(c[i - 1], a[i]);
	for (int i = 1; i <= n; ++ i) read(b[i]);
	build(1, 1, n);
	for (int i = 1, opt, x, y; i <= q; ++ i)
	{
		read(opt, x, y);
		if (opt == 0)
		{
			int t = Query(1, 1, n, x);
			ChangeA(1, 1, n, x, y);
			if (y <= t) { write(ull(a1[1]) * a2[1] % mod, '\n'); continue; }
			t = find(1, 1, n, y) - 1;
			ChangeC(1, 1, n, x, t, y);
		}
		else b[x] = y, ChangeB(1, 1, n, x, y, -1);
		write(ull(a1[1]) * a2[1] % mod, '\n');
	}
	IO::flush();
	return 0;
}
//
//首先，设C中关键点为C[i]!=C[i-1]的i（1也是关键点）
//
//整个C序列被这些关键点划分成了一些段，段内部C值都是相等的
//
//每一次修改A都越改越大，因此会删掉一些关键点，然后加入O(1)个关键点（大概理解一下。。）；那么，总共加入关键点的数量是O(n+q)级别的，总共删除关键点的数量也是O(n+q)级别的
//
//设一个势能函数，函数的值是序列中有多少个位置的C<B
//
//修改A的时候，由于任何位置的C都不会越改越小，势能函数会减少这样一个值：这一次修改过程中有多少个位置由C<B变为C>=B
//
//每一次单点修改B，最多使得势能函数增加1，因此，可以设计一个算法，使得修改A的时候，复杂度与“这一次修改过程中有多少个位置由C<B变为C>=B”有关，这样复杂度就是对的
//
//每一次修改A的时候，相当于对于C做一些区间修改（根据上面的结论，所有操作的区间修改总次数是O(n+q)的；要找到这个修改的区间的话，可以用另外一个数据结构维护；貌似为了减小代码复杂度，这个也可以直接在下面线段树的基础上实现，就每个节点多记一个区间内A的最大值ma）每次区间修改，大概可以这样用线段树维护一下：
//
//线段树每个节点存：区间内所有C<B的位置的C的积a1；区间内C<B的位置的个数n1；区间内所有C>=B的位置的B的积a2；区间内C>=B的位置的个数n2；区间内所有C<B的位置的B的最小值mi（没有则设为INF）；
//
//区间修改的懒标记；这样的话，区间修改C的时候，dfs线段树（设要将区间[l,r]内的C都改为y）；首先，只走与[l,r]交集不为空的区间；走到不被[l,r]包含的区间的时候直接递归下去，回溯的时候更新节点信息；走到被[l,r]包含的区间的时候，当且仅当它的mi<=y时，说明区间内存在点由C<B变为C>=B，继续递归下去，回溯的时候更新节点信息；否则打个懒标记就走，不要递归下去
//
//这样的复杂度就是$O((n+q)log^2n)$（第二个log是由于区间修改打懒标记以及pushdown的时候更新a1需要快速幂）
