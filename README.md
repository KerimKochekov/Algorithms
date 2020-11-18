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

