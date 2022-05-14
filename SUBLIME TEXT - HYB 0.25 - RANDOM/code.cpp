#include <bits/stdc++.h>
#include <random>
using namespace std;

#define vvi             vector<vector<int>>
#define ld              long double
#define mod             1000000007
#define ff              first
#define ss              second
#define int             long long
#define pb              push_back
#define mp              make_pair
#define pii             pair<int,int>
#define vpii            vector<pair<int,int>>
#define all(x)          x.begin(),x.end()
#define sz(a)           (int)(a.size())
#define vi              vector<int>
#define setbits(x)      __builtin_popcountll(x)
#define zrobits(x)      __builtin_ctzll(x)
#define SS              stringstream
#define db(...)         __f(#__VA_ARGS__, __VA_ARGS__)

template <typename Arg1>
void __f(const char* name, Arg1&& arg1) { cerr << name << " : " << arg1 << '\n'; }
template <typename Arg1, typename... Args>
void __f(const char* names, Arg1&& arg1, Args&&... args) {
    const char* comma = strchr(names + 1, ',');
    cerr.write(names, comma - names) << " : " << arg1 << " | "; __f(comma + 1, args...);
}

static random_device rd;
static mt19937_64 rng(rd());

void FASTIO()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
}


int a[3000][3000];
vector<string> testcases;
vector<string> error_msg;
vector<pair<int, string>> doubts;
int num_of_bugs;
int matched;
map<string, int> line;
map<string, int> cond;
int line_cov[3000];
int cond_cov[3000];
int KK = 1;

int randomfunc(int j)
{
    return rand() % j;
}

bool num(string s)
{
    for (int i = 0; i < sz(s); i++)
        if (s[i] > '9' or s[i] < '0')
            return 0;
    return 1;
}

void reset()
{
    for (int i = 1; i <= 2000; i++)
        for (int j = 1; j <= 2000; j++)
            a[i][j] = 0;
}


vvi split(vvi x, int ptr = 1)
{
    vvi ans;

    for (vi v : x)
    {
        vi one;
        vi zero;

        for (int i : v)
        {
            if (a[ptr][i] == 1)
                one.pb(i);
            else
                zero.pb(i);
        }

        if (sz(one))
            ans.pb(one);

        if (sz(zero))
            ans.pb(zero);
    }

    return ans;
}

double calc_score(int j, vi &found, vvi before, ld w)
{
    int sc1 = 0;

    for (int i = 1; i <= num_of_bugs; i++)
    {
        if (a[j][i] == 1 and found[i] == 0)
        {
            sc1++;
        }
    }

    vvi now = split(before, j);
    int sc2 = sz(now) - sz(before);

    double ans = w * sc1 + (1 - w) * sc2;

    return ans;
}

void calc_APFD_NEW_METHOD(ld  w = 0.25)
{
    vi final;

    vi vis(sz(testcases) + 1, 0);
    vi found(num_of_bugs + 1, 0);

    vvi before, after;

    vi now;
    for (int i = 1; i <= num_of_bugs; i++)
        now.pb(i);

    before.pb(now);

    before = split(before, 1);
    vis[1] = 1;
    final.pb(1);

    for (int i = 2; i <= sz(testcases); i++)
    {
        vector<pair<double, int>> v;
        for (int j = 1; j <= sz(testcases); j++)
        {
            if (vis[j] == 0)
            {
                v.pb({calc_score(j, found, before, w), j});
            }
        }

        sort(all(v));
        int in = v.back().ss;

        before = split(before, in);

        for (int j = 1; j <= num_of_bugs; j++)
        {
            if (a[in][j] == 1)
            {
                found[j] = 1;
            }
        }

        vis[in] = 1;
        final.pb(in);
    }

    for (int i = 1; i <= sz(testcases); i++)
    {
        if (vis[i] == 0)
        {
            final.pb(i);
        }
    }

    vector<int> tf(num_of_bugs + 1, 0);
    int ptr = 0;

    for (int id : final)
    {
        ++ptr;

        for (int j = 1; j <= num_of_bugs; j++)
        {
            if (a[id][j] == 1 and tf[j] == 0)
            {
                tf[j] = ptr;
            }
        }
    }
    db(1);

    // APFD_C

    vi f(num_of_bugs + 1, 1);
    vi t(sz(testcases) + 1, 1);

    for (int i = 1; i <= num_of_bugs; i++)
    {
        f[i] = (i * i * i) % 5 + 1;
    }

    for (int i = 1; i <= num_of_bugs; i++)
    {
        t[i] = (i * i) % 5 + 1;
    }

    double num = 0.000;
    double den = 0.000;

    for (int i = 1; i <= num_of_bugs; i++)
    {
        double temp = 0;
        for (int j = tf[i]; j <= sz(testcases); j++)
        {
            temp += t[j];
        }
        temp -= 0.5000 * tf[i];
        num += temp * f[i];
    }
    //db(num);
    db(1);
    int sum_t = 0, sum_f = 0;
    for (int i = 1; i <= num_of_bugs; i++)
        sum_f += f[i];
    for (int i = 1; i <= sz(testcases); i++)
        sum_t += t[i];
    den = sum_f * sum_t;

    double APFD = (1.000) * num;
    APFD /= den;

    APFD *= KK;

    cout << "APFD_C : " << fixed << setprecision(10) << APFD << '\n';

    // APFD

    APFD = 1 + (0.5000 / sz(testcases));

    double sum = 0;

    for (int i = 1; i <= num_of_bugs; i++)
        sum += tf[i];

    sum *= 1.00000;
    db(1);
    sum /=  sz(testcases) * num_of_bugs;

    APFD -= sum;
    APFD *= KK;

    cout << "APFD : " <<  fixed << setprecision(10) << APFD << '\n';
}

void test_case()
{
    int nn, mm;
    cin >> nn >> mm;
    nn=317;
    mm=276;

    int &tc = nn;
    int &b = mm;

    vector <vector<int>> fm(tc, vector<int>(b, 0));
    srand(time(NULL));
    uniform_int_distribution<int> distribution(0, 1);
    for (int i = 0; i < tc; i++) for (int j = 0; j < b; j++) fm[i][j] = distribution(rng    );
    for (int i = 0; i < b; i++) {
        int flag = 0;
        for (int j = 0; j < tc; j++) {
            if (fm[j][i] == 1) flag = 1;
            if (flag) break;
        }
        if (!flag) {
            fm[rand() % tc][i] = 1;
        }
    }

    for (int i = 1; i <= nn; i++)
    {
        for (int j = 1; j <= mm; j++)
        {
            a[i][j] = fm[i - 1][j - 1];
        }
    }

    num_of_bugs = mm;
    testcases = vector<string> (nn);

    db(1, nn, mm);
    // assert(sz(testcases) == nn);

    cout << "RESULT FOR N = " << nn << " and M = " << mm << '\n';
    calc_APFD_NEW_METHOD();
    cout << '\n';
}

int32_t main()
{
    FASTIO();

    int t;
    t = 1;
    // cin >> t;

    for (int i = 1; i <= t; i++)
    {
        //cout << "Case #" << i << ": ";
        test_case();
    }
    return 0;
}
