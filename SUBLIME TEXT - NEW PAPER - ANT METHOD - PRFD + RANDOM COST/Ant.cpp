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


int a[3000][3000];
vector<string> testcases;
vector<string> error_msg;
vector<pair<int, string>> doubts;
int num_of_bugs;
int matched;
map<string,int> line;
map<string,int> cond;
int line_cov[3000];
int cond_cov[3000];

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

void print_FM(int bugs, int testcases)
{
	for (int i = 1; i <= testcases; i++)
	{
		for (int j = 1; j <= bugs; j++)
		{
			cout << a[i][j];

			if (j != bugs)
				cout << " ";
		}

		cout << '\n';
	}
}


void calc_APFD()
{
	vector<pair<double,int>> order;

	for(int i = 1; i <= sz(testcases); i++)
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

	vi f(num_of_bugs + 1, 1);
	vi t(sz(testcases) + 1, 1);

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
		for(int j = tf[i]; j <= sz(testcases); j++)
		{
			temp += t[j];
		}
		temp -= 0.5000 * tf[i];
		num += temp * f[i];
	}
	//db(num);

	int sum_t = 0, sum_f = 0;
	for(int i = 1; i <= num_of_bugs; i++)
		sum_f += f[i];
	for(int i = 1; i <= sz(testcases); i++)
		sum_t += t[i];
	den = sum_f * sum_t;

	double APFD = (1.000) * num;
	APFD /= den;

	cout << "APFD_C : " << fixed << setprecision(10) << APFD << '\n';

	// APFD

	APFD = 1 + (0.5000 / sz(testcases));

	double sum = 0;

	for(int i = 1; i <= num_of_bugs; i++)
		sum += tf[i];

	sum *= 1.00000;

	sum /= 	sz(testcases) * num_of_bugs;

	APFD -= sum;

	cout << "APFD : " <<  fixed << setprecision(10) << APFD << '\n';
}

int find_index(string s)
{
	vi found;

	for (int i = 0; i < sz(testcases); i++)
	{
		bool done = 0;

		for (int j = 0; j + sz(testcases[i]) <= sz(s) and !done; j++)
		{
			if (s.substr(j, sz(testcases[i])) == testcases[i])
			{
				found.pb(i);
				done = 1;
			}	
		}
	}

	if(sz(found) > 1)
	{
		int len = 0;

		for(int ind : found)
			len = max(len, sz(testcases[ind]));

		for(int ind : found)
		{
			if(len == sz(testcases[ind]))
				return ind;
		}
	}

	if(sz(found) == 0)
	{
		//cout << s << '\n';
		return 0;
	}

	// if(sz(found) != 1)
	// {	
	// 	cout << " :: " << sz(found) << '\n';
	// 	cout << s << '\n';
	// 	cout << "matched : \n";

	// 	for (int i = 0; i < sz(testcases); i++)
	// 	{
	// 		bool done = 0;

	// 		for (int j = 0; j + sz(testcases[i]) <= sz(s) and !done; j++)
	// 		{
	// 			if (s.substr(j, sz(testcases[i])) == testcases[i])
	// 			{
	// 				found.pb(i);
	// 				cout << "hello : " << testcases[i] << '\n';
	// 				done = 1;
	// 			}
	// 		}
	// 	}

	// 	return 0;
	// }

	return found[0];
}

void read_testcases()
{
	testcases.clear();
	num_of_bugs = 0;

	string s;

	while (cin >> s)
	{
		if (s == "done")
			break;

		testcases.pb(s);
	}

	for (string &s : testcases)
	{
		s = s.substr(0, sz(s) - 5);
		// cout << s << '\n';
	}

	int ptr = 0;

	for (string &s : testcases)
	{
		int in = -1;

		string id = "";

		for(int i = 0; i < sz(s); i++)
		{
			if(s.substr(i, 5) == "lang3")
			{
				for(int j = i + 6; j < sz(s); j++)
				{
					if(s[j] == '/')
						break;
					id += s[j];
				}

				break;
			}
		}

		ptr++;
		line_cov[ptr] = line[id];
		cond_cov[ptr] = cond[id];

		for (int i = 0; i < sz(s); i++)
		{
			if (s[i] == '/')
			{
				in = i;
			}
		}

		if (in == -1)
			continue;

		int siz = sz(s) - (in + 1) + 1;
		s = s.substr(in + 1, siz);
	}

	

	// for(string s : testcases)
	// {
	// 	ptr++;

	// 	cout << ptr << " " << s << '\n';
	// }
}


void read_errors()
{
	error_msg.clear();
	num_of_bugs = 0;
	matched = 0;

	string s;

	while (cin >> s)
	{
		error_msg.pb(s);
	}

	vector<string> nw;

	for (string s : error_msg)
	{
		if (s == "Failing" or s == "tests:")
			continue;

		if (sz(s) == 1 and !num(s))
		{
			continue;
		}

		nw.pb(s);
	}

	error_msg = nw;

	doubts.clear();

	int in = 0;
	int t = 0;

	while (in < sz(error_msg))
	{
		if (error_msg[in] == "NEW_CODE")
		{
			t++;
			in++;
		}
		else
		{
			break;
		}

		if (in < sz(error_msg) and error_msg[in] == "NEW_CODE")
		{
			continue;
		}

		int siz = stoi(error_msg[in]);
		int st = in + 1;
		int en = in + siz + 1;

		for (int i = st; i < en; i++)
		{
			int ind = find_index(error_msg[i]);

			if (ind == 0)
			{
				// cout << error_msg[i] << '\n';
				doubts.pb({t, error_msg[i]});
				// return;
			}
			else
			{
				matched++;
				a[ind][t] = 1;
			}
		}

		in = in + siz + 1;
	}

	num_of_bugs = t;

}

void read_coverage()
{
	line.clear();
	cond.clear();

	string s;

	while(1)
	{
		cin >> s;

		if(s == "done")
			break;

		if(s == "NEW_CODE")
			continue;

		string name = s;

		if(sz(s) >= 5 and s.substr(sz(s) - 5, 5) == ".java")
		{
			s = s.substr(0, sz(s) - 5);
		}

		name = s;

		cin >> s;

		if(s == "done")
			break;

		if(s == "NEW_CODE")
			continue;

		vector<string> temp(17);
		for(string &it : temp)
			cin >> it;

		line[name] += stoi(temp[4]);
		cond[name] += stoi(temp[10]);
	}
}

void test_case()
{

	reset();

	// read_coverage();

	read_testcases();

	read_errors();


	// int debug = find_index("org.apache.commons.lang.NumberUtilsTest::testLang457", v);
	// cout << debug << '\n';
	// return;


	cout << "BUGS : " << num_of_bugs << '\n';
	cout << "TESTCASES : " << sz(testcases) << '\n';
	cout << "MATCHED : " << matched << '\n';
	cout << "ERROR : " << sz(doubts) << '\n';

	// cout << sz(doubts) << " " << sahi << '\n';

	// for(auto it : doubts)
	// {
	// 	cout << it.ff << " " << it.ss << '\n';
	// }


	//print_FM(num_of_bugs, sz(testcases));
	// calc_APFD();
	// calc_APFD_LINE();
	// calc_APFD_COND();
	calc_APFD();
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