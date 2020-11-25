# Tricks
1) Sum-Xor property <br>
![](https://latex.codecogs.com/gif.latex?a&plus;b%20%3D%20a%20%5Coplus%20b%20&plus;%202%28a%5CAnd%20b%29) <br>
![](https://latex.codecogs.com/gif.latex?a&plus;b%3Da%5Cvert%20b%20&plus;%20a%5CAnd%20b) <br>
![](https://latex.codecogs.com/gif.latex?a%20%5Coplus%20b%20%3D%20a%5Cvert%20b%20-%20a%5CAnd%20b) <br>

2) Any even number greater than 2 can be split into two prime numbers

3) Pragmas
```
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
```

4) find all B that B is submask of A
```(B = A; B > 0; --B, B&=A);```

5) find all D that A is submask of D
```for (D = A; D < (1 << n); ++D, D |= A)```

6) Rotate board 45 degree by (x,y) -> (x+y,y-x), so Manhattan distance between two points would be max(|x1-x2|,|y1-y2|)

7) Find any x,y such that ax+by=gcd(a,b) for given two integers a and b with EEA(Extended Euclidean Algorithm )
```
int gcd(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int d = gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}
```

8) There is no assumption that n1 and n2 are coprime. Find an integer x that satisfies:<br>
![](https://espresso.codeforces.com/bb121fa59f669935e3b01fd4dd0e9278e3e33fa8.png) <br>
Answer: ![](https://espresso.codeforces.com/5c24e7d9eb7072de51e66f33018c45b316cc1318.png), where d=gcd(n1,n2) and x' from EEA we can find (x', y') such that n1x' + n2y' = d
