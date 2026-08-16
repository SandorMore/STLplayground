#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <forward_list>
#include <list>

template<typename T>
class CustomAllocator
{
public:
	using value_type = T;

	CustomAllocator() noexcept {}

	template<typename U>
	CustomAllocator(const CustomAllocator<U>&) noexcept;

	T* allocate(size_t n) noexcept 
	{
		std::cout << "Allocating" << "\n";
		return static_cast<T*>(::operator new(n * sizeof(T)));
	}

	void deallocate(T* p, size_t n) noexcept
	{
		std::cout << "Deallocating" << "\n";
		::operator delete(p);
	}

	template<typename U, typename... Args>
	void construct(U *p, Args&&... args)
	{
		std::cout << "Constructing" << "\n";
		new (p) U(std::forward<Args>(args)...);
	}

	template<typename U>
	void destroy(U* p)
	{
		std::cout << "Destroying" << "\n";
		p->~U();
	}

};

class SquareIterator 
{
public:
	using iterator_category = std::random_access_iterator_tag;
	using value_type = int;
	using difference_type = std::ptrdiff_t;

	explicit SquareIterator(int* _ptr) : ptr{_ptr} {}

	value_type operator*() const
	{
		return (*ptr) * (*ptr);
	}

	int* operator->() const
	{
		return ptr;
	}
	
	//prefix increment
	SquareIterator& operator++()
	{
		++ptr;
		return *this;
	}

	//postfix increment
	SquareIterator operator++(int)
	{
		SquareIterator tmp = *this;
		++ptr;
		return tmp;
	}
	
	SquareIterator& operator+=(difference_type diff)
	{
		ptr += diff;
		return *this;
	}

	SquareIterator operator+(difference_type diff) const 
	{
		return SquareIterator(ptr + diff);
	}

	value_type operator[](difference_type diff)
	{
		return *(ptr + diff) * *(ptr + diff);
	}
	
	bool operator!=(const SquareIterator& other)
	{
		return this->ptr != other.ptr;
	}

private:
	int* ptr;
};


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
	
	std::vector<int> _vec = {1,2,3,4,5};

	SquareIterator begin{_vec.data()};
	SquareIterator end{_vec.data() + vec.size()};


	for(auto it = begin; it != end; ++it)
	{
		std::cout << *it << " ";
	}
	
	std::cout << '\n';


	std::vector<int, CustomAllocator<int>> customvec;
	
	for(size_t i {}; i < 10; ++i)
	{
		customvec.push_back(i);
	}

	std::cout << "Clearing the vector";
	customvec.clear();

	return 0;
}
