#ifndef TRISYCL_SYCL_INFO_QUEUE_HPP
#define TRISYCL_SYCL_INFO_QUEUE_HPP

/** \file The OpenCL SYCL queue information parameters

    Dave Airlie

    This file is distributed under the University of Illinois Open Source
    License. See LICENSE.TXT for details.
*/

#include "CL/sycl/id.hpp"
#include "CL/sycl/opencl_types.hpp"
#include "CL/sycl/info/param_traits.hpp"

namespace cl {
namespace sycl {

namespace info {

using queue_profiling = bool;

/** Queue information descriptors

    From specification C.4

    \todo unsigned int?

    \todo To be implemented
*/
enum class queue : int {
  context,
  device,
  reference_count,
};

TRISYCL_INFO_PARAM_TRAITS(queue::context, cl::sycl::context)
TRISYCL_INFO_PARAM_TRAITS(queue::device, cl::sycl::device)
TRISYCL_INFO_PARAM_TRAITS(queue::reference_count, cl::sycl::cl_uint)

}
/** Dummy example for get_info() on queue::context that would return a
    context

    \todo Describe all the types
*/

  
}
}

  
#endif
