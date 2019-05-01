#include <cstdio>
#include <algorithm>
#include <tuple>
#include <utility>
#include <vector>

static const int MAXM = 10000;
static const int MAXN = 501;

static int m;
static int n[MAXM], *a[MAXM];

static std::vector<int> vals;
static std::vector<std::tuple<int, int, int *>> poss;

// Cyclic doubly-linked list implementation
struct list_node {
    int val;
    struct list_node *prev, *next;

    list_node(int val = 0) : val(val) { }

    // Inserts <n> after <this>.
    inline void insert(list_node *n)
    {
        this->next->prev = n;
        n->next = this->next;
        this->next = n;
        n->prev = this;
    }

    // Removes <this>.
    // Does not release memory so the node can be reused.
    inline void remove()
    {
        this->prev->next = this->next;
        this->next->prev = this->prev;
    }
};
#define list_each(__ls, __val) \
    (list_node *__n = (__ls)->next; ((__val) = __n->val), (__n != (__ls)); __n = __n->next)

static int t[MAXM];
static list_node head[MAXN * 2 + 1];  // next - first, prev - last
static list_node *node[MAXM];

static int ans[MAXM] = { 0 };

namespace fio {

static const int BUFSZ = 9876;
static char buf[BUFSZ];
static int bufptr = BUFSZ - 1;

inline void flush()
{
    fread(buf, BUFSZ, 1, stdin);
    bufptr = -1;
}

inline char getchar()
{
    if (bufptr == BUFSZ - 1) flush();
    return buf[++bufptr];
}

inline int read_int()
{
    char ch;
    int ret = 0;
    while ((ch = getchar()) < '0' || ch > '9') ;
    ret = ch - '0';
    while ((ch = getchar()) >= '0' && ch <= '9') ret = ret * 10 + ch - '0';
    return ret;
}

} // namespace fio

int main()
{
    m = fio::read_int();
    poss.reserve(m * MAXN);
    for (int i = 0; i < m; ++i) {
        n[i] = fio::read_int();
        a[i] = new int[n[i]];
        for (int j = 0; j < n[i]; ++j) {
            a[i][j] = fio::read_int();
            poss.push_back({a[i][j], i, &a[i][j]});
        }
    }

    // Discretization
    std::vector<std::pair<int, int>> diffs;
    std::sort(poss.begin(), poss.end(),
        [] (const std::tuple<int, int, int *> &a, const std::tuple<int, int, int *> &b) {
            return std::get<0>(a) < std::get<0>(b);
        });
    vals.reserve(poss.size());
    for (auto p : poss) {
        if (vals.empty() || std::get<0>(p) != vals.back())
            vals.push_back(std::get<0>(p));
        *std::get<2>(p) = vals.size() - 1;
        diffs.push_back({std::get<0>(p), std::get<1>(p)});
    }

    for (int i = 0; i < MAXN * 2 + 1; ++i)
        head[i].next = head[i].prev = &head[i];

    for (int i = 0; i < m; ++i) {
        t[i] = -n[i];
        node[i] = new list_node(i);
        head[MAXN - n[i]].insert(node[i]);
    }

    std::sort(diffs.begin(), diffs.end());
    for (auto d : diffs) {
        int i = d.second;
        int v = d.first + i + 2;
        node[i]->remove();
        t[i] += 2;
        head[MAXN + t[i]].insert(node[i]);
        // t[i] == 0 is considered here, because
        // the answer will be updated twice in the loop below,
        // resulting in the change being cancelled out
        if (t[i] == 0 || t[i] == 1) ans[i] ^= (v + i);
        int j;
        for list_each(&head[MAXN - t[i] + 1], j) {
            ans[i] ^= (v + j);
            ans[j] ^= (v + j);
        }
        for list_each(&head[MAXN - t[i]], j) {
            ans[i] ^= (v + j);
            ans[j] ^= (v + j);
        }
    }

    for (int i = 0; i < m; ++i) printf("%d\n", ans[i]);

    return 0;
}
