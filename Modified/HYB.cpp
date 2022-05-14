#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>
#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>

using namespace std;

#define vvi             vector<vector<int>>
#define ld              long double
#define mod             1000000007
#define ff              first
#define ss              second
#define int            	long long
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
int KK = 1;

void FASTIO()
{
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
}

clock_t startTime;


// time reqd
double getCurrentTime() {
	return (double)(clock() - startTime) / CLOCKS_PER_SEC;
}

vector<vector<int>> a;
int testcases = 1300;
vector<string> error_msg;
vector<pair<int, string>> doubts;
int num_of_bugs = 450;

// FM
void createFM()
{
	srand(time(0));

	// cin >> testcases >> num_of_bugs;

	a = vector<vector<int>> (testcases + 1, vector<int> (num_of_bugs + 1, 0));

	for(int i = 1; i <= testcases; i++) {
		for(int j = 1; j <= num_of_bugs; j++) {
			a[i][j] = rand() % 2;
		}
	}

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


// prints the FM
void print_FM()
{
	for (int i = 1; i <= testcases; i++)
	{
		for (int j = 1; j <= num_of_bugs; j++)
		{
			cout << a[i][j];

			if (j != num_of_bugs)
				cout << " ";
		}

		cout << '\n';
	}
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

// this algo lies -
void calc_APFD_NEW_METHOD(ld  w = 0.25)
{
    vi final;

    vi vis(testcases + 1, 0);
    vi found(num_of_bugs + 1, 0);

    vvi before, after;

    vi now;
    for (int i = 1; i <= num_of_bugs; i++)
        now.pb(i);

    before.pb(now);

    before = split(before, 1);
    vis[1] = 1;
    final.pb(1);

    for (int i = 2; i <= testcases; i++)
    {
        vector<pair<double, int>> v;
        for (int j = 1; j <= testcases; j++)
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

    for (int i = 1; i <= testcases; i++)
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
    vi t(testcases + 1, 1);

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
        for (int j = tf[i]; j <= testcases; j++)
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
    for (int i = 1; i <= testcases; i++)
        sum_t += t[i];
    den = sum_f * sum_t;

    double APFD = (1.000) * num;
    APFD /= den;

    APFD *= KK;

    cout << "APFD_C : " << fixed << setprecision(10) << APFD << '\n';

    // APFD

    APFD = 1 + (0.5000 / testcases);

    double sum = 0;

    for (int i = 1; i <= num_of_bugs; i++)
        sum += tf[i];

    sum *= 1.00000;
    db(1);
    sum /=  testcases * num_of_bugs;

    APFD -= sum;
    APFD *= KK;

    cout << "APFD : " <<  fixed << setprecision(10) << APFD << '\n';
}

int32_t main()
{

	startTime = clock();

	//FASTIO();

	createFM();

	cout << "BUGS : " << num_of_bugs << '\n';
	cout << "TESTCASES : " << testcases << '\n';

	//print_FM();

	calc_APFD_NEW_METHOD();

	cout << fixed << setprecision(10) << "The time is " << getCurrentTime() << '\n';
	return 0;
}
