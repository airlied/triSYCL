#ifndef TRISYCL_SYCL_PROPERTY_LIST_HPP
#define TRISYCL_SYCL_PROPERTY_LIST_HPP

#include "CL/sycl/detail/all_true.hpp"

namespace cl {
namespace sycl {

class property_list {

public:
  template<typename... propsT,
	   typename = std::enable_if_t<detail::all_true<std::is_convertible<propsT, detail::property>::value ...>::value>>
  property_list(propsT... props) {
  }
};

}
}
#endif
