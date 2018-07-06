#ifndef TRISYCL_SYCL_PROGRAM_DETAIL_HOST_PROGRAM_HPP
#define TRISYCL_SYCL_PROGRAM_DETAIL_HOST_PROGRAM_HPP

#include "CL/sycl/program/detail/program.hpp"
namespace cl {
namespace sycl {  
namespace detail {

class host_program : public detail::program {

#ifdef TRISYCL_OPENCL
  cl_program get() const override {
    throw non_cl_error("The host queue has no OpenCL command queue");
  }
#endif
  /// Return true since the program is a SYCL host program
  bool is_host() const override {
    return true;
  }

  cl::sycl::cl_uint get_reference_count() const override {
    return 0;
  }
};

}
}
}
#endif // TRISYCL_SYCL_PROGRAM_DETAIL_HOST_PROGRAM_HPP
