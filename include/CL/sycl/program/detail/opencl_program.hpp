#ifndef TRISYCL_SYCL_PROGRAM_DETAIL_OPENCL_PROGRAM_HPP
#define TRISYCL_SYCL_PROGRAM_DETAIL_OPENCL_PROGRAM_HPP

#include "CL/sycl/program/detail/program.hpp"
namespace cl {
namespace sycl {  
namespace detail {

class opencl_program : public detail::program,
		       public detail::singleton<opencl_program> {

  /// Return false since the program is not a SYCL host program
  bool is_host() const override {
    return false;
  }
};

}
}
}
#endif // TRISYCL_SYCL_PROGRAM_DETAIL_OPENCL_PROGRAM_HPP
