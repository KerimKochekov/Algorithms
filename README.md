# Lambda operator (applicable beyond C++11)
Inner-function in Function
```cpp
	auto function = [](auto x){
		return ...;
	};
```
Boolean Comporator
```cpp
    sort(q, q + n, [&](int A, int B) { return A < B; });
```

# Techniques
1) Sum-Xor property <br>
$a + b = a \oplus b + 2 (a \land b)$ <br>
$a + b = a | b + a \land b$ <br>
$a \oplus b = a | b - a \land b$

3) Conjecture: Any even number greater than 2 can be split into two prime numbers

4) Pragmas for speedup
```
#pragma GCC optimize ("O3")
#pragma GCC optimize ("unroll-loops")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
```

4) find all B that B is submask of A
```(B = A; B > 0; --B, B&=A);```

5) find all D that A is submask of D
```for (D = A; D < (1 << n); ++D, D |= A)```

6) Rotate board 45 degree by $(x,y) \rightarrow (x+y,y-x)$, so [Manhattan distance](https://simple.wikipedia.org/wiki/Manhattan_distance) between two points would be $max(|x1-x2|, |y1-y2|)$.

7) Find any x,y such that $ax + by = gcd(a,b)$ for given two non-negative integers a and b with [Extended Euclidean Algorithm](https://cp-algorithms.com/algebra/extended-euclid-algorithm.html#algorithm)


8) There is no assumption that n1 and n2 are coprime. Find an integer x that satisfies:
- $x \equiv a_1 (mod n_1)$
- $x \equiv a_2 (mod n_2)$

where $d = gcd(n1,n2)$ and $(x', y')$ is retrieved with help of EEA to find $n1x' + n2y' = d$.

9) $gcd(lcm(x, y_1), lcm(x, y_2), \dots, lcm(x, y_k)) = lcm(x, gcd(y1, y2, \dots, y_k))$
10) $lcm(gcd(x, y_1), gcd(x, y_2), \dots, gcd(x, y_k)) = gcd(x, lcm(y1, y2, \dots, y_k))$
11) For any $x \geq y$ the $gcd(x, y) = gcd(x - y, y)$, which can be extended for multiple arguments $gcd(x, y, z, \dots) = gcd(x-y, y, z, \dots)$
   
