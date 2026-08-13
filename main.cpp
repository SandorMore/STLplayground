#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>

template<typename _Iter>
void print_iterable(_Iter begin, _Iter end)
{
	for(;begin != end;++begin)
	{
		std::cout << *begin << ' '; 
	}
	std::cout << '\n';
}



int main(int argc, char** argv)
{
	std::vector<int>vec;
	
	std::generate_n(std::back_inserter(vec), 10, [n = 0] () mutable {return ++n;});
	
	print_iterable(vec.begin(), vec.end());

	return 0;
}

