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
int testcases = 1310;
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


// prints the FM
void print_FM()
{
    printf("fm creation\n");
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
void calc_APFD_LINE()
{
     printf("APfd started\n");
	vpii order;
    srand(time(0));

	long long line_cov[testcases + 1];
	for(int i = 1; i <= testcases; i++) {
		line_cov[i] = rand() % 1000;
	}
	for(int i = 1; i <= testcases; i++)
	{
		order.pb({line_cov[i], i});
	}

	sort(all(order));
	reverse(all(order));

	vi final;

	for(pii p : order)
		final.pb(p.ss);
printf("APfd middle1\n");

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
printf("APfd middle2\n");
	double APFD = 1 + (0.5000 / testcases);
    printf("apfd done \n");
	double sum = 0;

	for(int i = 1; i <= num_of_bugs; i++)
		sum += tf[i];

	sum *= 1.00000;

	sum /= 	testcases * num_of_bugs;

	APFD -= sum;
printf("APfd completed\n");
	cout << fixed << setprecision(10) << APFD << '\n';
}


int32_t main()
{

	startTime = clock();

	//FASTIO();

	createFM();

	cout << "BUGS : " << num_of_bugs << '\n';
	cout << "TESTCASES : " << testcases << '\n';

	//print_FM();

	calc_APFD_LINE();

	cout << fixed << setprecision(10) << "The time is " << getCurrentTime() << '\n';
	return 0;
}
