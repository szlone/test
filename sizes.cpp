#include <iostream>
#include <cstddef>
using std::cout;


int main(int argc, char * argv[])
{
	cout << "bool:" << sizeof(bool) << "\n"  // 1
		<< "char:" << sizeof(char) << "\n"  // 1
		<< "wchar_t:" << sizeof(wchar_t) << "\n"  // 4
		<< "short:" << sizeof(short) << "\n"  // 2
		<< "int:" << sizeof(int) << "\n"  // 4
		<< "unsigned:" << sizeof(unsigned) << "\n"  // 4
		<< "long:" << sizeof(long) << "\n"  // 8
		<< "long long:" << sizeof(long long) << "\n"  // 8
		<< "float:" << sizeof(float) << "\n"  // 4
		<< "double:" << sizeof(double) << "\n"  // 8
		<< "long double:" << sizeof(long double) << "\n"  // 16
//		<< "__float128: " << sizeof(__float128) << "\n"
		<< "int *:" << sizeof(int *) << "\n"  // 8
		<< "double *:" << sizeof(double *) << "\n"  // 8
		<< "size_t:" << sizeof(size_t) << "\n"  // 8
		<< "ptrdiff_t:" << sizeof(ptrdiff_t) << "\n";  // 8
	return 0;
}
