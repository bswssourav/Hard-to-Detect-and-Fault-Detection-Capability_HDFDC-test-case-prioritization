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
int testcases = 276;
vector<string> error_msg;
vector<pair<int, string>> doubts;
int num_of_bugs = 398;

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
printf("Fm Done\n");
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

// this algo lies -
void calc_APFD()
{
	vector<pair<double,int>> order;
printf("Entering\n");
	for(int i = 1; i <= testcases; i++)
	{

		double cost = (i * i * i + i) % 10;
		double cnt = 0;
		for(int j = 1; j <= num_of_bugs; j++)
		{
			if(a[i][j] == 1)
				cnt++;
		}

		cnt = cnt * 1.0000;
		cnt /= num_of_bugs;
		cost = cost * 1.0000;
		cost /= 10;

		order.pb({cost + 10 * cnt, i});
	}

	sort(all(order));
	reverse(all(order));

	vi final;
printf("Calculating\n");
	for(auto p : order)
	{
		final.pb(p.ss);
	}

	vector<int> tf(num_of_bugs + 1, 0);

	int ptr = 0;

	for(int id : final)
	{
		++ptr;

		for(int j = 1; j <= num_of_bugs; j++)
		{
			if(a[id][j] == 1 and tf[j] == 0)
			{
				tf[j] = ptr;
			}
		}
	}


	// APFD_C
printf("Calculating\n");
	vi f(num_of_bugs + 1, 1);
	vi t(testcases + 1, 1);

	for(int i = 1; i <= num_of_bugs; i++)
	{
		f[i] = (i * i * i) % 5 + 1;
	}

	for(int i = 1; i <= num_of_bugs; i++)
	{
		t[i] = (i * i) % 5 + 1;
	}

	double num = 0.000;
	double den = 0.000;

	for(int i = 1; i <= num_of_bugs; i++)
	{
		double temp = 0;
		for(int j = tf[i]; j <= testcases; j++)
		{
			temp += t[j];
		}
		temp -= 0.5000 * tf[i];
		num += temp * f[i];
	}
	//db(num);
printf("Calculating\n");
	int sum_t = 0, sum_f = 0;
	for(int i = 1; i <= num_of_bugs; i++)
		sum_f += f[i];
	for(int i = 1; i <= testcases; i++)
		sum_t += t[i];
	den = sum_f * sum_t;

	double APFD = (1.000) * num;
	APFD /= den;

	cout << "APFD_C : " << fixed << setprecision(10) << APFD << '\n';

	// APFD

	APFD = 1 + (0.5000 / testcases);
printf("Apfd calcu\n");
	double sum = 0;

	for(int i = 1; i <= num_of_bugs; i++)
		sum += tf[i];

	sum *= 1.00000;

	sum /= 	testcases * num_of_bugs;

	APFD -= sum;
printf("Calculation done\n");
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

	calc_APFD();

	cout << fixed << setprecision(10) << "The time is " << getCurrentTime() << '\n';
	return 0;
}
