#ifndef TRISYCL_SYCL_PROGRAM_DETAIL_OPENCL_PROGRAM_HPP
#define TRISYCL_SYCL_PROGRAM_DETAIL_OPENCL_PROGRAM_HPP

#include "CL/sycl/program/detail/program.hpp"
namespace cl {
namespace sycl {  
namespace detail {

class opencl_program : public detail::program {

public:
  boost::compute::program p;

  opencl_program(cl_program clp) : p(clp) {}

  opencl_program() {}
  
  /// Return the cl_program of the underlying OpenCL program
  cl_program get() const override {
    return p.get();
  }
  
  /// Return false since the program is not a SYCL host program
  bool is_host() const override {
    return false;
  }

  cl::sycl::cl_uint get_reference_count() const override {
    return p.get_info<CL_PROGRAM_REFERENCE_COUNT>();
  }
};

}
}
}
#endif // TRISYCL_SYCL_PROGRAM_DETAIL_OPENCL_PROGRAM_HPP
