#ifndef TRISYCL_SYCL_QUEUE_DETAIL_QUEUE_TAIL_HPP
#define TRISYCL_SYCL_QUEUE_DETAIL_QUEUE_TAIL_HPP

/** \file The ending part of of the OpenCL SYCL context

    This is here to break a dependence between context and device_selector

    Dave Airlie

    This file is distributed under the University of Illinois Open Source
    License. See LICENSE.TXT for details.
*/

namespace cl {
namespace sycl {

/* has to be inline as it references default_selector */
inline queue::queue(const property_list &propList) : queue(default_selector {}, propList) {}

inline queue::queue(const async_handler asyncHandler, const property_list &propList) : queue(default_selector {}, asyncHandler, propList) {}

}
}
/*
    # Some Emacs stuff:
    ### Local Variables:
    ### ispell-local-dictionary: "american"
    ### eval: (flyspell-prog-mode)
    ### End:
*/

#endif // TRISYCL_SYCL_QUEUE_DETAIL_QUEUE_TAIL_HPP
