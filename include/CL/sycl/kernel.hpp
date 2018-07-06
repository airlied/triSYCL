#ifndef TRISYCL_SYCL_KERNEL_HPP
#define TRISYCL_SYCL_KERNEL_HPP

/** \file The OpenCL SYCL kernel

    Ronan at Keryell point FR

    This file is distributed under the University of Illinois Open Source
    License. See LICENSE.TXT for details.
*/

#ifdef TRISYCL_OPENCL
#include <boost/compute.hpp>
#endif

#include "CL/sycl/detail/debug.hpp"
#include "CL/sycl/detail/shared_ptr_implementation.hpp"
#include "CL/sycl/detail/unimplemented.hpp"
#include "CL/sycl/info/kernel.hpp"
#include "CL/sycl/kernel/detail/kernel.hpp"
#include "CL/sycl/program.hpp"
#ifdef TRISYCL_OPENCL
#include "CL/sycl/kernel/detail/opencl_kernel.hpp"
#endif

namespace cl {
namespace sycl {

/** \addtogroup execution Platforms, contexts, devices and queues
    @{
*/

/** SYCL kernel

    \todo To be implemented

    \todo Check specification
*/
class kernel
  /* Use the underlying kernel implementation that can be shared in
     the SYCL model */
  : public detail::shared_ptr_implementation<kernel, detail::kernel> {

  friend class program;
  // The type encapsulating the implementation
  using implementation_t = typename kernel::shared_ptr_implementation;

  // The handler class uses the implementation
  friend class handler;

  // Allows the comparison operation to access the implementation
  friend implementation_t;

 public:

  // Make the implementation member directly accessible in this class
  using implementation_t::implementation;

  /** The default object is not valid because there is no program or
      \code cl_kernel \endcode associated with it */
  kernel() = delete;

#ifdef TRISYCL_OPENCL
  /** Constructor for SYCL kernel class given an OpenCL kernel object
      with set arguments, valid for enqueuing

      Retains a reference to the \p cl_kernel object. The Caller
      should release the passed cl_kernel object when it is no longer
      needed.
  */
  kernel(cl_kernel k, const cl::sycl::context &syclContext) : kernel { boost::compute::kernel { k }, syclContext } {}


  /** Construct a kernel class instance using a boost::compute::kernel

      This is a triSYCL extension for boost::compute interoperation.

      Return synchronous errors via the SYCL exception class.
  */
  kernel(const boost::compute::kernel &k, const cl::sycl::context &syclContext)
    : implementation_t { detail::opencl_kernel::instance(k) } {}


  /** Return the OpenCL kernel object for this kernel

      Retains a reference to the returned cl_kernel object. Caller
      should release it when finished.
  */
  cl_kernel get() const {
    return implementation->get();
  }
#endif


  /** Query information from the kernel object using the
      info::kernel_info descriptor.
  */
  template <info::kernel param>
  inline auto get_info() const;

  template <info::kernel_work_group param>
  inline auto get_work_group_info(const device &dev) const;

};

template<>
inline auto kernel::get_info<info::kernel::function_name>() const {
  return string_class {};
}

template<>
inline auto kernel::get_info<info::kernel::num_args>() const {
  return 0;
}

template<>
inline auto kernel::get_info<info::kernel::reference_count>() const {
  return 0;
}

template<>
inline auto kernel::get_info<info::kernel::attributes>() const {
  return string_class {};
}

template<>
inline auto kernel::get_work_group_info<info::kernel_work_group::global_work_size>(const device &dev) const {
  return cl::sycl::range<3> { 128, 128, 128 };
}

template<>
inline auto kernel::get_work_group_info<info::kernel_work_group::work_group_size>(const device &dev) const {
  return 0;
}  

template<>
inline auto kernel::get_work_group_info<info::kernel_work_group::compile_work_group_size>(const device &dev) const {
  return cl::sycl::range<3> { 128, 128, 128 };
}

template<>
inline auto kernel::get_work_group_info<info::kernel_work_group::preferred_work_group_size_multiple>(const device &dev) const {
  return 0;
}

template<>
inline auto kernel::get_work_group_info<info::kernel_work_group::private_mem_size>(const device &dev) const {
  return 0;
}
/// @} End the execution Doxygen group

}
}


/* Inject a custom specialization of std::hash to have the buffer
   usable into an unordered associative container

   \todo Add this to the spec
*/
namespace std {

template <> struct hash<cl::sycl::kernel> {

  auto operator()(const cl::sycl::kernel &k) const {
    // Forward the hashing to the implementation
    return k.hash();
  }

};

}

/*
    # Some Emacs stuff:
    ### Local Variables:
    ### ispell-local-dictionary: "american"
    ### eval: (flyspell-prog-mode)
    ### End:
*/

#endif // TRISYCL_SYCL_KERNEL_HPP
