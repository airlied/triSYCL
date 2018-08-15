/* RUN: %{execute}%s

   Test some vec<> simple swizzles behaviour
*/
#define SYCL_SIMPLE_SWIZZLES
#include <CL/sycl.hpp>
#include <iostream>
#include <boost/test/minimal.hpp>

using namespace cl::sycl;

int test_main(int argc, char *argv[]) {
	vec<int, 3> v = {1, 2, 3};

	BOOST_CHECK(v.x() == 1);
	BOOST_CHECK(v.y() == 2);
	BOOST_CHECK(v.z() == 3);

	vec<int, 2> v2 = v.zy();
	BOOST_CHECK(v2.x() == 3);
	BOOST_CHECK(v2.y() == 2);

	v2 = v.rb();
	BOOST_CHECK(v2.x() == 1);
	BOOST_CHECK(v2.y() == 3);

	v.x() = 4;
	v.y() = 5;
	v.z() = 6;
	BOOST_CHECK(v.x() == 4);
	BOOST_CHECK(v.y() == 5);
	BOOST_CHECK(v.z() == 6);
	
	v2 = v.swizzle<1, 0>();
	BOOST_CHECK(v2.x() == 5);
	BOOST_CHECK(v2.y() == 4);

  return 0;
}
