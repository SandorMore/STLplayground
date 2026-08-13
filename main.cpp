#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <forward_list>
#include <list>

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
	std::forward_list<int> flist = {10,20,30,40,50};	
	std::list<int> list = {1,2,3,4,5};

	std::generate_n(std::back_inserter(vec), 10, [n = 0] () mutable {return ++n;});
	
	std::cout << "Generated numbers are: ";
	print_iterable(vec.begin(), vec.end());

	//forward iterator
	std::cout << "Original forward_list: ";
	print_iterable(flist.begin(), flist.end());
	
	for(auto it = flist.begin(); it != flist.end(); ++it)
	{
		(*it)++;
	}

	std::cout << "Modified list: ";
	print_iterable(flist.begin(), flist.end());

	//bidirectional iterator
	std::cout << "Traversing the list forwards: ";
	for(std::list<int>::iterator it = list.begin(); it != list.end(); ++it)
	{
		std::cout << *it << " ";
	}
	std::cout << '\n';
	
	std::cout << "Traversing the list backwards: ";
	for(std::list<int>::reverse_iterator it = list.rbegin(); it != list.rend(); ++it)
	{
		std::cout << *it << " ";
	}
	std::cout << '\n';
	
	//random access iterator
	


	return 0;
}

