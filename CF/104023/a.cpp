/*
 * c.cpp
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
#include <cstring>

#include <map>
#include <string>
#include <iostream>
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

const int mod = 1e9 + 7;

struct ModInt {/*{{{*/
	int cur;
	ModInt( ll _cur = 0 ) { cur = ( ( ( _cur % mod ) + mod ) % mod ); }

	inline ModInt operator+ ( const ModInt &b ) const { return ( cur + b.cur ) % mod; }
	inline ModInt operator- ( const ModInt &b ) const { return ( ( ( cur - b.cur ) % mod ) + mod ) % mod; }
	inline ModInt operator* ( const ModInt &b ) const { return ( 1LL * cur * b.cur ) % mod; }
	inline ModInt operator/ ( const ModInt &b ) const { return ( 1LL * cur * pow( b, mod - 2 ).cur ) % mod; }

	inline void operator+= ( const ModInt &b ) { (*this) = (*this) + b; }
	inline void operator-= ( const ModInt &b ) { (*this) = (*this) - b; }
	inline void operator*= ( const ModInt &b ) { (*this) = (*this) * b; }
	inline void operator/= ( const ModInt &b ) { (*this) = (*this) / b; }

	inline void output( const char end = '\n' ) { printf( "%d%c", cur, end ); }
};/*}}}*/

const int K = 10;

std::map<std::string, bool> winner;
// std::map<std::string, int> pos;

int winner_cnt[K], pos_cnt[K];

int main() {
#ifdef woshiluo
	freopen( "a.in", "r", stdin );
	freopen( "a.out", "w", stdout );
#endif
	cint n = read<int>();
	for( int i = 1; i <= n; i ++ ) {
		for( int j = 1; j <= 5; j ++ ) {
			std::string input;
			std::cin >> input;
			winner[input] = true;
		}
	}

	cint m = read<int>();
	for( int i = 1; i <= m; i ++ ) {
		int p;
		std::string input;

		std::cin >> input >> p;
		if( winner.count(input) )
			winner_cnt[p] ++;
		else
			pos_cnt[p] ++;
	}

	auto check = [&] () {
		bool flag = true;
		for( int i = 1; i <= 5; i ++ ) {
			flag &= ( pos_cnt[i] + winner_cnt[i] != 0 );
		}
		return flag;
	};

	auto find_main = [&] () {
		int res = -1;
		for( int i = 1; i <= 5; i ++ ) {
			if( winner_cnt[i] && !pos_cnt[i] ) 
				return i;
			if( winner_cnt[i] && pos_cnt[i] ) 
				res = i;
		}

		return res;
	};

	auto try_minus = [&] ( const int cur ) {
		if( pos_cnt[cur] ) 
			pos_cnt[cur] --;
		else
			winner_cnt[cur] --;
	};

	int cnt = 0;
	while(1) {
		if( !check() ) 
			break;

		int p = find_main();

		if( p == -1 )
			break;

		winner_cnt[p] --;

		cnt ++;

		for( int i = 1; i <= 5; i ++ ) 
			if( i != p )
				try_minus(i);
	}

	printf( "%d\n", cnt );
}
