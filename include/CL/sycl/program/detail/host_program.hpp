#ifndef TRISYCL_SYCL_PROGRAM_DETAIL_HOST_PROGRAM_HPP
#define TRISYCL_SYCL_PROGRAM_DETAIL_HOST_PROGRAM_HPP

#include "CL/sycl/program/detail/program.hpp"
namespace cl {
namespace sycl {  
namespace detail {

class host_program : public detail::program,
		     public detail::singleton<host_program> {

  /// Return true since the program is a SYCL host program
  bool is_host() const override {
    return true;
  }
};

}
}
}
#endif // TRISYCL_SYCL_PROGRAM_DETAIL_HOST_PROGRAM_HPP
