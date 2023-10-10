#include "bits/stdc++.h"
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;

typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update>ordered_set;
int main(){
	ordered_set s;
	s.insert(5);
	*s.find_by_order(0);
	s.order_of_key(0); //number of values in set smaller than k
}
