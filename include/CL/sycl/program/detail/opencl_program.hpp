#ifndef TRISYCL_SYCL_PROGRAM_DETAIL_OPENCL_PROGRAM_HPP
#define TRISYCL_SYCL_PROGRAM_DETAIL_OPENCL_PROGRAM_HPP

#include "CL/sycl/program/detail/program.hpp"
namespace cl {
namespace sycl {  
namespace detail {

class opencl_program : public detail::program,
		       public detail::singleton<opencl_program> {

};

}
}
}
#endif // TRISYCL_SYCL_PROGRAM_DETAIL_OPENCL_PROGRAM_HPP
