/** \file Test that the local accessor provides uninitialized memory
    like uninitialized buffers


   RUN: %{execute}%s

*/
#include <cstdlib>

#include <CL/sycl.hpp>

#include <boost/test/minimal.hpp>

struct explosive_type {

  int value;

  // An explosive default constructor
  explosive_type() {
    std::terminate();
  }

  // Initialize value
  explosive_type(decltype(value) v) : value { v } {}

  // Behave like "value" itself through this implicit reference conversion
  operator decltype(value)& () { return value; }

};

using namespace cl::sycl;

int test_main(int argc, char *argv[]) {
  queue my_queue;
  constexpr int size = 10;

  buffer<explosive_type> output { size };

  my_queue.submit([&](handler &cgh) {
      auto out_access = output.get_access<access::mode::discard_write>(cgh);
      cl::sycl::accessor<explosive_type,
                         1,
                         access::mode::read_write,
                         access::target::local> lds { size, cgh };
      cgh.parallel_for<class init>(size,
                                   [=] (int i) {
                                     lds[i] = i;
                                     out_access[i] = lds[i];
                                   });
    });

  auto o = output.get_access<access::mode::read>();

  // Check the computation above
  for (int i = 0; i != size; i++)
    BOOST_CHECK(o[i] == i);

  return 0;
}
