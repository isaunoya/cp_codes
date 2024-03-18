/*
 * j.cpp
 * Copyright (C) 2022 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU AGPLv3+ license.
 */

#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>

#include <map>
#include <queue>
#include <vector>
#include <algorithm>

typedef const int cint;
typedef long long ll;
typedef unsigned long long ull;

inline bool isdigit( const char cur ) { return cur >= '0' && cur <= '9'; }/*{{{*/
template <class T> 
T Max( T a, T b ) { return a > b? a: b; }
template <class T> 
T Min( T a, T b ) { return a < b? a: b; }
template <class T> 
void chk_Max( T &a, T b ) { if( b > a ) a = b; }
template <class T> 
void chk_Min( T &a, T b ) { if( b < a ) a = b; }
template <typename T>
T read() { 
	T sum = 0, fl = 1; 
	char ch = getchar();
	for (; isdigit(ch) == 0; ch = getchar())
		if (ch == '-') fl = -1;
	for (; isdigit(ch); ch = getchar()) sum = sum * 10 + ch - '0';
	return sum * fl;
}
template <class T> 
T pow( T a, int p ) {
	T res = 1;
	while( p ) {
		if( p & 1 ) 
			res = res * a;
		a = a * a;
		p >>= 1;
	}
	return res;
}/*}}}*/

const int INF = 0x3f3f3f3f;

int main() {
#ifdef woshiluo
	freopen( "j.in", "r", stdin );
	freopen( "j.out", "w", stdout );
#endif
	int32_t T = read<int>();
	while( T -- ) {
		const int32_t n = read<int32_t>();
		const int32_t k = read<int32_t>();

		int64_t sum = 0;
		std::map<int32_t, int32_t> limit;
		std::map<int32_t, int32_t> pool;
		std::vector<int32_t> a(n);
		for( auto &x: a ) {
			x = read<int32_t>();
			pool[x] ++;
			sum += x;
		}

		std::sort( a.begin(), a.end() );
		for( int i = 0; i < k; i ++ ) {
			const int32_t x = read<int>();
			const int32_t y = read<int>();
			if( !limit.count(x) ) 
				limit[x] = y;
			else
				chk_Min( limit[x], y );
		}

		std::vector<int32_t> banned;
		for( auto &pair: limit ) {
			if( pair.second == 0 ) 
				banned.push_back( pair.first );
		}
		banned.push_back(INF);

		int end = 0;
		std::deque<std::pair<int32_t, int32_t>> list;
		for( auto &x: a ) {
			int32_t nxt_banned = *std::lower_bound( banned.begin(), banned.end(), end );
			while( nxt_banned < x ) {
				end = nxt_banned + 1;
				list.resize(0);
				nxt_banned = *std::lower_bound( banned.begin(), banned.end(), end );
			}

			while( end <= x ) {
				if( limit.count(end) ) {
					list.push_back(std::make_pair( end, limit[end] ));
					end += 1;
				}
				else {
					list.push_back(std::make_pair( end, INF ));
					break;
				}
			}

			while( list.size() && list.front().second == 0 ) 
				list.pop_front();

			if( list.empty() ) {
				sum = 0;
				break;
			}

			sum -= list.front().first;
			list.front().second --;
			while( list.size() && list.front().second == 0 ) 
				list.pop_front();

		}

		if( sum & 1 ) {
			printf( "Pico\n" );
		}
		else {
			printf( "FuuFuu\n" );
		}
	}
}
