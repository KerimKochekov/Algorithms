#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <vector>

using namespace std;


//! Ìîäóëü 64-áèòíîãî ÷èñëà
long long abs (long long n)
{
	return n < 0 ? -n : n;
}

unsigned long long abs (unsigned long long n)
{
	return n;
}

//! Âîçâðàùàåò true, åñëè n ÷åòíîå
template <class T>
bool even (const T & n)
{
	// return n % 2 == 0;
	return (n & 1) == 0;
}

//! Äåëèò ÷èñëî íà 2
template <class T>
void bisect (T & n)
{
	// n /= 2;
	n >>= 1;
}

//! Óìíîæàåò ÷èñëî íà 2
template <class T>
void redouble (T & n)
{
	// n *= 2;
	n <<= 1;
}

//! Âîçâðàùàåò true, åñëè n - òî÷íûé êâàäðàò ïðîñòîãî ÷èñëà
template <class T>
bool perfect_square (const T & n)
{
	T sq = (T) ceil (sqrt ((double)n));
	return sq*sq == n;
}

//! Âû÷èñëÿåò êîðåíü èç ÷èñëà, îêðóãëÿÿ åãî âíèç
template <class T>
T sq_root (const T & n)
{
	return (T) floor (sqrt ((double) n));
}

//! Âîçâðàùàåò êîëè÷åñòâî áèò â ÷èñëå (ò.å. ìèíèìàëüíîå êîëè÷åñòâî áèò, êîòîðûìè ìîæíî ïðåäñòàâèòü äàííîå ÷èñëî)
template <class T>
unsigned bits_in_number (T n)
{
	if (n == 0)
		return 1;
	unsigned result = 0;
	while (n)
	{
		bisect (n);
		++result;
	}
	return result;
}

//! Âîçâðàùàåò çíà÷åíèå k-ãî áèòà ÷èñëà (áèòû íóìåðóþòñÿ ñ íóëÿ)
template <class T>
bool test_bit (const T & n, unsigned k)
{
	return (n & (T(1) << k)) != 0;
}

//! Óìíîæàåò a *= b (mod n)
template <class T>
void mulmod (T & a, T b, const T & n)
{
	// íàèâíàÿ âåðñèÿ, ãîäèòñÿ òîëüêî äëÿ äëèííîé àðèôìåòèêè
	a *= b;
	a %= n;
}

template <>
void mulmod (int & a, int b, const int & n)
{
	a = int( (((long long)a) * b) % n );
}

template <>
void mulmod (unsigned & a, unsigned b, const unsigned & n)
{
	a = unsigned( (((unsigned long long)a) * b) % n );
}

template <>
void mulmod (unsigned long long & a, unsigned long long b, const unsigned long long & n)
{
	// ñëîæíàÿ âåðñèÿ, îñíîâàííàÿ íà áèíàðíîì ðàçëîæåíèè ïðîèçâåäåíèÿ â ñóììó
	if (a >= n)
		a %= n;
	if (b >= n)
		b %= n;
	unsigned long long res = 0;
	while (b)
		if (!even (b))
		{
			res += a;
			while (res >= n)
				res -= n;
			--b;
		}
		else
		{
			redouble (a);
			while (a >= n)
				a -= n;
			bisect (b);
		}
	a = res;
}

template <>
void mulmod (long long & a, long long b, const long long & n)
{
	bool neg = false;
	if (a < 0)
	{
		neg = !neg;
		a = -a;
	}
	if (b < 0)
	{
		neg = !neg;
		b = -b;
	}
	unsigned long long aa = a;
	mulmod<unsigned long long> (aa, (unsigned long long)b, (unsigned long long)n);
	a = (long long)aa * (neg ? -1 : 1);
}


//! Âû÷èñëÿåò a^k (mod n). Èñïîëüçóåò áèíàðíîå âîçâåäåíèå â ñòåïåíü
template <class T, class T2>
T powmod (T a, T2 k, const T & n)
{
	T res = 1;
	while (k)
		if (!even (k))
		{
			mulmod (res, a, n);
			--k;
		}
		else
		{
			mulmod (a, a, n);
			bisect (k);
		}
	return res;
}

//! Ïåðåâîäèò ÷èñëî n â ôîðìó q*2^p
template <class T>
void transform_num (T n, T & p, T & q)
{
	T p_res = 0;
	while (even (n))
	{
		++p_res;
		bisect (n);
	}
	p = p_res;
	q = n;
}

//! Àëãîðèòì Åâêëèäà
template <class T, class T2>
T gcd (const T & a, const T2 & b)
{
	return (a == 0) ? b : gcd (b % a, a);
}

//! Âû÷èñëÿåò jacobi(a,b)
template <class T>
T jacobi (T a, T b)
{

#pragma warning (push)
#pragma warning (disable: 4146)

	if (a == 0)
		return 0;
	if (a == 1)
		return 1;
	
	if (a < 0)
		if ((b & 2) == 0)
			return jacobi (-a, b);
		else
			return - jacobi (-a, b);
	
	T e, a1;
	transform_num (a, e, a1);
	
	T s;
	if (even (e) || (b & 7) == 1 || (b & 7) == 7)
		s = 1;
	else
		s = -1;
	if ((b & 3) == 3 && (a1 & 3) == 3)
		s = -s;
	if (a1 == 1)
		return s;
	return s * jacobi (b % a1, a1);

#pragma warning (pop)

}

//! Âû÷èñëÿåò pi(b) ïåðâûõ ïðîñòûõ ÷èñåë. Âîçâðàùàåò ññûëêó íà âåêòîð ñ ïðîñòûìè (â âåêòîðå ìîæåò îêàçàòüñÿ áîëüøå ïðîñòûõ, ÷åì íàäî) è â pi - pi(b)
template <class T, class T2>
const std::vector<T> & get_primes (const T & b, T2 & pi)
{

	static std::vector<T> primes;
	static T counted_b;

	// åñëè ðåçóëüòàò óæå áûë âû÷èñëåí ðàíåå, âîçâðàùàåì åãî, èíà÷å äîâû÷èñëÿåì ïðîñòûå
	if (counted_b >= b)
		pi = T2 (std::upper_bound (primes.begin(), primes.end(), b) - primes.begin());
	else
	{
	
		// ÷èñëî 2 îáðàáàòûâàåì îòäåëüíî
		if (counted_b == 0)
		{
			primes.push_back (2);
			counted_b = 2;
		}

		// òåïåðü îáðàáàòûâàåì âñå íå÷¸òíûå, ïîêà íå íàáåð¸ì íóæíîå êîëè÷åñòâî ïðîñòûõ
		T first = counted_b == 2 ? 3 : primes.back()+2;
		for (T cur=first; cur<=b; ++++cur)
		{
			bool cur_is_prime = true;
			for (std::vector<T>::const_iterator iter = primes.begin(), end = primes.end();
				iter != end; ++iter)
			{
				const T & div = *iter;
				if (div * div > cur)
					break;
				if (cur % div == 0)
				{
					cur_is_prime = false;
					break;
				}
			}
			if (cur_is_prime)
				primes.push_back (cur);
		}
		
		counted_b = b;
		pi = (T2) primes.size();

	}
	
	return primes;

}

//! Òðèâèàëüíàÿ ïðîâåðêà n íà ïðîñòîòó, ïåðåáèðàþòñÿ âñå äåëèòåëè äî m. Ðåçóëüòàò: 1 - åñëè n òî÷íî ïðîñòîå, p - åãî íàéäåííûé äåëèòåëü, 0 - åñëè íåèçâåñòíî, ÿâëÿåòñÿ ëè n ïðîñòûì èëè íåò
template <class T, class T2>
T2 prime_div_trivial (const T & n, T2 m)
{
	
	// ñíà÷àëà ïðîâåðÿåì òðèâèàëüíûå ñëó÷àè
	if (n == 2 || n == 3)
		return 1;
	if (n < 2)
		return 0;
	if (even (n))
		return 2;

	// ãåíåðèðóåì ïðîñòûå îò 3 äî m
	T2 pi;
	const vector<T2> & primes = get_primes (m, pi);

	// äåëèì íà âñå ïðîñòûå
	for (std::vector<T2>::const_iterator iter=primes.begin(), end=primes.end();
		iter!=end; ++iter)
	{
		const T2 & div = *iter;
		if (div * div > n)
			break;
		else
			if (n % div == 0)
				return div;
	}
	
	if (n < m*m)
		return 1;
	return 0;

}

//! Óñèëåííûé àëãîðèòì Ìèëëåðà-Ðàáèíà ïðîâåðêè n íà ïðîñòîòó ïî áàçèñó b
template <class T, class T2>
bool miller_rabin (T n, T2 b)
{

	// ñíà÷àëà ïðîâåðÿåì òðèâèàëüíûå ñëó÷àè
	if (n == 2)
		return true;
	if (n < 2 || even (n))
		return false;

	// ïðîâåðÿåì, ÷òî n è b âçàèìíî ïðîñòû (èíà÷å ýòî ïðèâåäåò ê îøèáêå)
	// åñëè îíè íå âçàèìíî ïðîñòû, òî ëèáî n íå ïðîñòî, ëèáî íóæíî óâåëè÷èòü b
	if (b < 2)
		b = 2;
	for (T g; (g = gcd (n, b)) != 1; ++b)
		if (n > g)
			return false;

	// ðàçëàãàåì n-1 = q*2^p
	T n_1 = n;
	--n_1;
	T p, q;
	transform_num (n_1, p, q);

	// âû÷èñëÿåì b^q mod n, åñëè îíî ðàâíî 1 èëè n-1, òî n, âåðîÿòíî, ïðîñòîå
	T rem = powmod (T(b), q, n);
	if (rem == 1 || rem == n_1)
		return true;

	// òåïåðü âû÷èñëÿåì b^2q, b^4q, ... , b^((n-1)/2)
	// åñëè êàêîå-ëèáî èç íèõ ðàâíî n-1, òî n, âåðîÿòíî, ïðîñòîå
	for (T i=1; i<p; i++)
	{
		mulmod (rem, rem, n);
		if (rem == n_1)
			return true;
	}

	return false;

}

//! Óñèëåííûé àëãîðèòì Ëóêàñà-Ñåëôðèäæà ïðîâåðêè n íà ïðîñòîòó. Èñïîëüçóåòñÿ óñèëåííûé àëãîðèòì Ëóêàñà ñ ïàðàìåòðàìè Ñåëôðèäæà. Ðàáîòàåò òîëüêî ñ çíàêîâûìè òèïàìè!!! Âòîðîé ïàðàìåòð unused íå èñïîëüçóåòñÿ, îí òîëüêî äàåò òèï
template <class T, class T2>
bool lucas_selfridge (const T & n, T2 unused)
{

	// ñíà÷àëà ïðîâåðÿåì òðèâèàëüíûå ñëó÷àè
	if (n == 2)
		return true;
	if (n < 2 || even (n))
		return false;

	// ïðîâåðÿåì, ÷òî n íå ÿâëÿåòñÿ òî÷íûì êâàäðàòîì, èíà÷å àëãîðèòì äàñò îøèáêó
	if (perfect_square (n))
		return false;

	// àëãîðèòì Ñåëôðèäæà: íàõîäèì ïåðâîå ÷èñëî d òàêîå, ÷òî:
	// jacobi(d,n)=-1 è îíî ïðèíàäëåæèò ðÿäó { 5,-7,9,-11,13,... }
	T2 dd;
	for (T2 d_abs = 5, d_sign = 1; ; d_sign = -d_sign, ++++d_abs)
	{
		dd = d_abs * d_sign;
		T g = gcd (n, d_abs);
		if (1 < g && g < n)
			// íàøëè äåëèòåëü - d_abs
			return false;
		if (jacobi (T(dd), n) == -1)
			break;
	}

	// ïàðàìåòðû Ñåëôðèäæà
	T2
		p = 1,
		q = (p*p - dd) / 4;
	
	// ðàçëàãàåì n+1 = d*2^s
	T n_1 = n;
	++n_1;
	T s, d;
	transform_num (n_1, s, d);

	// àëãîðèòì Ëóêàñà
	T
		u = 1,
		v = p,
		u2m = 1,
		v2m = p,
		qm = q,
		qm2 = q*2,
		qkd = q;
	for (unsigned bit = 1, bits = bits_in_number(d); bit < bits; bit++)
	{
		mulmod (u2m, v2m, n);
		mulmod (v2m, v2m, n);
		while (v2m < qm2)
			v2m += n;
		v2m -= qm2;
		mulmod (qm, qm, n);
		qm2 = qm;
		redouble (qm2);
		if (test_bit (d, bit))
		{
			T t1, t2;
			t1 = u2m;
			mulmod (t1, v, n);
			t2 = v2m;
			mulmod (t2, u, n);
			
			T t3, t4;
			t3 = v2m;
			mulmod (t3, v, n);
			t4 = u2m;
			mulmod (t4, u, n);
			mulmod (t4, (T)dd, n);

			u = t1 + t2;
			if (!even (u))
				u += n;
			bisect (u);
			u %= n;

			v = t3 + t4;
			if (!even (v))
				v += n;
			bisect (v);
			v %= n;
			mulmod (qkd, qm, n);
		}
	}

	// òî÷íî ïðîñòîå (èëè ïñåâäî-ïðîñòîå)
	if (u == 0 || v == 0)
		return true;

	// äîïîëíèòåëüíûå ïðîâåðêè, èíà÷å íåêîòîðûå ñîñòàâíûå ÷èñëà "ïðåâðàòÿòñÿ" â ïðîñòûå
	T qkd2 = qkd;
	redouble (qkd2);
	for (T2 r = 1; r < s; ++r)
	{
		mulmod (v, v, n);
		v -= qkd2;
		if (v < 0) v += n;
		if (v < 0) v += n;
		if (v >= n) v -= n;
		if (v >= n) v -= n;
		if (v == 0)
			return true;
		if (r < s-1)
		{
			mulmod (qkd, qkd, n);
			qkd2 = qkd;
			redouble (qkd2);
		}
	}

	return false;

}

//! Àëãîðèòì Áýéëè-Ïîìåðàíñ-Ñåëôðèäæ-Âàãñòàôô (BPSW) ïðîâåðêè n íà ïðîñòîòó
template <class T>
bool baillie_pomerance_selfridge_wagstaff (T n)
{

	// ñíà÷àëà ïðîâåðÿåì íà òðèâèàëüíûå äåëèòåëè - äî 29
	int div = prime_div_trivial (n, 29);
	if (div == 1)
		return true;
	if (div > 1)
		return false;
	// åñëè div == 0, òî íà òðèâèàëüíûå äåëèòåëè n íå äåëèòñÿ

	// òåñò Ìèëëåðà-Ðàáèíà ïî áàçèñó 2
	if (!miller_rabin (n, 2))
		return false;

	// óñèëåííûé òåñò Ëóêàñà-Ñåëôðèäæà
	return lucas_selfridge (n, 0);

}

//! Àëãîðèòì Áýéëè-Ïîìåðàíñ-Ñåëôðèäæ-Âàãñòàôô (BPSW) ïðîâåðêè n íà ïðîñòîòó
template <class T>
bool isprime (T n)
{
	return baillie_pomerance_selfridge_wagstaff (n);
}

//! Ìåòîä Ïîëëàðäà p-1 ôàêòîðèçàöèè ÷èñëà. Ôóíêöèÿ âîçâðàùàåò íàéäåííûé äåëèòåëü ÷èñëà èëè 1, åñëè íè÷åãî íå íàéäåíî
template <class T>
T pollard_p_1 (T n)
{
	// ïàðàìåòðû àëãîðèòìà, ñóùåñòâåííî âëèÿþò íà ïðîèçâîäèòåëüíîñòü è êà÷åñòâî ïîèñêà
	const T b = 13;
	const T q[] = { 2, 3, 5, 7, 11, 13 };

	// íåñêîëüêî ïîïûòîê àëãîðèòìà
	T a = 5 % n;
	for (int j=0; j<10; j++)
	{

		// èùåì òàêîå a, êîòîðîå âçàèìíî ïðîñòî ñ n
		while (gcd (a, n) != 1)
		{
			mulmod (a, a, n);
			a += 3;
			a %= n;
		}

		// âû÷èñëÿåì a^M
		for (size_t i = 0; i < sizeof q / sizeof q[0]; i++)
		{
			T qq = q[i];
			T e = (T) floor (log ((double)b) / log ((double)qq));
			T aa = powmod (a, powmod (qq, e, n), n);
			if (aa == 0)
				continue;
			
			// ïðîâåðÿåì, íå íàéäåí ëè îòâåò
			T g = gcd (aa-1, n);
			if (1 < g && g < n)
				return g;
		}

	}

	// åñëè íè÷åãî íå íàøëè
	return 1;

}

//! Ìåòîä Ïîëëàðäà RHO ôàêòîðèçàöèè ÷èñëà. Âîçâðàùàåò åãî íàéäåííûé äåëèòåëü èëè 1, åñëè íè÷åãî íå áûëî íàéäåíî
template <class T>
T pollard_rho (T n, unsigned iterations_count = 100000)
{
	T
		b0 = rand() % n,
		b1 = b0,
		g;
	mulmod (b1, b1, n);
	if (++b1 == n)
		b1 = 0;
	g = gcd (abs (b1 - b0), n);
	for (unsigned count=0; count<iterations_count && (g == 1 || g == n); count++)
	{
		mulmod (b0, b0, n);
		if (++b0 == n)
			b0 = 0;
		mulmod (b1, b1, n);
		++b1;
		mulmod (b1, b1, n);
		if (++b1 == n)
			b1 = 0;
		g = gcd (abs (b1 - b0), n);
	}
	return g;
}

//! Ìåòîä Ïîëëàðäà-Áåíòà ôàêòîðèçàöèè ÷èñëà. Âîçâðàùàåò åãî íàéäåííûé äåëèòåëü èëè 1, åñëè íè÷åãî íå áûëî íàéäåíî
template <class T>
T pollard_bent (T n, unsigned iterations_count = 19)
{
	T
		b0 = rand() % n,
		b1 = (b0*b0 + 2) % n,
		a = b1;
	for (unsigned iteration=0, series_len=1; iteration<iterations_count; iteration++, series_len*=2)
	{
		T g = gcd (b1-b0, n);
		for (unsigned len=0; len<series_len && (g==1 && g==n); len++)
		{
			b1 = (b1*b1 + 2) % n;
			g = gcd (abs(b1-b0), n);
		}
		b0 = a;
		a = b1;
		if (g != 1 && g != n)
			return g;
	}
	return 1;
}

//! Ìåòîä Ïîëëàðäà Monte-Carlo ôàêòîðèçàöèè ÷èñëà. Âîçâðàùàåò åãî íàéäåííûé äåëèòåëü èëè 1, åñëè íè÷åãî íå áûëî íàéäåíî
template <class T>
T pollard_monte_carlo (T n, unsigned m = 100)
{
	T b = rand() % (m-2) + 2;

	static std::vector<T> primes;
	static T m_max;
	if (primes.empty())
		primes.push_back (3);
	if (m_max < m)
	{
		m_max = m;
		for (T prime=5; prime<=m; ++++prime)
		{
			bool is_prime = true;
			for (std::vector<T>::const_iterator iter=primes.begin(), end=primes.end();
				iter!=end; ++iter)
			{
				T div = *iter;
				if (div*div > prime)
					break;
				if (prime % div == 0)
				{
					is_prime = false;
					break;
				}
			}
			if (is_prime)
				primes.push_back (prime);
		}
	}

	T g = 1;
	for (size_t i=0; i<primes.size() && g==1; i++)
	{
		T cur = primes[i];
		while (cur <= n)
			cur *= primes[i];
		cur /= primes[i];
		b = powmod (b, cur, n);
		g = gcd (abs(b-1), n);
		if (g == n)
			g = 1;
	}

	return g;
}

//! Ìåòîä Ôåðìà ôàêòîðèçàöèè ÷èñëà. Ðàáîòàåò â õóäøåì ñëó÷àå çà O(sqrt(n)). Âîçâðàùàåò íàéäåííûé äåëèòåëü. Âòîðîé ïàðàìåòð äîëæåí áûòü òîãî æå òèïà, ÷òî è ïåðâûé, òîëüêî signed
template <class T, class T2>
T ferma (const T & n, T2 unused)
{
	T2
		x = sq_root (n),
		y = 0,
		r = x*x - y*y - n;
	for (;;)
		if (r == 0)
			return x!=y ? x-y : x+y;
		else
			if (r > 0)
			{
				r -= y+y+1;
				++y;
			}
			else
			{
				r += x+x+1;
				++x;
			}
}

//! Ðåêóðñèâíàÿ ôàêòîðèçàöèÿ ÷èñëà. Ïîñëåäíèé ïàðàìåòð äîëæåí áûòü òîãî æå òèïà, ÷òî è ïåðâûé, òîëüêî signed. Èñïîëüçóåò òåñò BPSW, ìåòîä Ôåðìà, ìåòîä Ïîëëàðäà RHO, ìåòîä Ïîëëàðäà-Áåíòà, ìåòîä Ïîëëàðäà Monte-Carlo
template <class T, class T2>
void factorize (const T & n, std::map<T,unsigned> & result, T2 unused)
{
	if (n == 1)
		;
	else
		// ïðîâåðÿåì, íå ïðîñòîå ëè ÷èñëî
		if (isprime (n))
			++result[n];
		else
			// åñëè ÷èñëî äîñòàòî÷íî ìàëåíüêîå, òî åãî ðàçëàãàåì ïðîñòûì ïåðåáîðîì
			if (n < 1000*1000)
			{
				T div = prime_div_trivial (n, 1000);
				++result[div];
				factorize (n / div, result, unused);
			}
			else
			{
				// ÷èñëî áîëüøîå, çàïóñêàåì íà íåì àëãîðèòìû ôàêòîðèçàöèè
				T div;
				// ñíà÷àëà èäóò áûñòðûå àëãîðèòìû Ïîëëàðäà
				div = pollard_monte_carlo (n);
				if (div == 1)
					div = pollard_rho (n);
				if (div == 1)
					div = pollard_p_1 (n);
				if (div == 1)
					div = pollard_bent (n);
				// åñëè àëãîðèòìû Ïîëëàðäà íè÷åãî íå äàëè, òî çàïóñêàåì àëãîðèòì Ôåðìà, êîòîðûé ãàðàíòèðîâàííî íàõîäèò äåëèòåëü
				if (div == 1)
					div = ferma (n, unused);
				// ðåêóðñèâíî îáðàáàòûâàåì íàéäåííûå ìíîæèòåëè
				factorize (div, result, unused);
				factorize (n / div, result, unused);
			}
}


int main()
{
	typedef long long base;

	base n;
	cin >> n;

	map <base, unsigned> m;
	factorize (n, m, (long long) 0);

	for (map <base, unsigned>::iterator i=m.begin(); i!=m.end(); ++i)
		cout << i->first << ' ' << i->second << endl;

}
