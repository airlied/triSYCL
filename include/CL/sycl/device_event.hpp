#ifndef TRISYCL_SYCL_DEVICE_EVENT_HPP
#define TRISYCL_SYCL_DEVICE_EVENT_HPP

/** \file The OpenCL SYCL device_event<>

    Dave Airlie

    This file is distributed under the University of Illinois Open Source
    License. See LICENSE.TXT for details.
*/

namespace cl::sycl {

class device_event {

public:
  void wait() const {}
};

}
#endif
