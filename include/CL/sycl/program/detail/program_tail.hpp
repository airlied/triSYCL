#ifndef TRISYCL_SYCL_PROGRAM_DETAIL_PROGRAM_TAIL_HPP
#define TRISYCL_SYCL_PROGRAM_DETAIL_PROGRAM_TAIL_HPP

/** \file The ending part of of OpenCL SYCL device

    This is here to break a dependence between device and device_selector

    Ronan at Keryell point FR

    This file is distributed under the University of Illinois Open Source
    License. See LICENSE.TXT for details.
*/

namespace cl {
namespace sycl {

/** \addtogroup execution Platforms, contexts, devices and queues
    @{
*/
template<typename kernelT>
inline cl::sycl::kernel program::get_kernel() const
{
  return cl::sycl::kernel { nullptr, get_context() };
  //  return *(kernels.at(NULL));
}
  
inline cl::sycl::kernel program::get_kernel(string_class kernelName) const
{
  return cl::sycl::kernel { nullptr, get_context() };
  //  return *(kernels.at(NULL));
}

/*
    # Some Emacs stuff:
    ### Local Variables:
    ### ispell-local-dictionary: "american"
    ### eval: (flyspell-prog-mode)
    ### End:
*/
}
}
#endif // TRISYCL_SYCL_PROGRAM_DETAIL_PROGRAM_TAIL_HPP
