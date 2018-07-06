#ifndef TRISYCL_SYCL_EVENT_HPP
#define TRISYCL_SYCL_EVENT_HPP

/** \file The event class

    Ronan at keryell dot FR

    This file is distributed under the University of Illinois Open Source
    License. See LICENSE.TXT for details.
*/
#include "CL/sycl/info/event.hpp"
#include "CL/sycl/event/detail/event.hpp"

namespace cl {
namespace sycl {

class event : public detail::shared_ptr_implementation<event, detail::event> {

  cl_event cl;
public:

  event() = default;


/** \todo To be implemented */
  bool is_host() const { return false; }

  explicit event(cl_event clEvent) {}

  event(const event & rhs) {}

  cl_event get() {
    detail::unimplemented();
    return {};
  }

  vector_class<event> get_wait_list() {
    detail::unimplemented();
  }

  void wait() {
    detail::unimplemented();
  }
  static void wait(const vector_class<event> &eventList) {}

  void wait_and_throw() {
    detail::unimplemented();
  }

  static void wait_and_throw(const vector_class<event> &eventList) {}

  template <info::event param>
  inline auto get_info() const;

  template <info::event_profiling param>
  inline auto get_profiling_info() const;

};

template<>
inline auto event::get_info<info::event::command_execution_status>() const {
  return cl::sycl::info::event_command_status::submitted;
}

template<>
inline auto event::get_info<info::event::reference_count>() const {
    return static_cast<cl::sycl::cl_uint>(0);
}

template<>
inline auto event::get_profiling_info<info::event_profiling::command_submit>() const {
      return static_cast<cl::sycl::cl_ulong>(0);
}

template<>
inline auto event::get_profiling_info<info::event_profiling::command_start>() const {
      return static_cast<cl::sycl::cl_ulong>(0);
}

template<>
inline auto event::get_profiling_info<info::event_profiling::command_end>() const {
      return static_cast<cl::sycl::cl_ulong>(0);
}

  
}

}

namespace std {

template <> struct hash<cl::sycl::event> {

  auto operator()(const cl::sycl::event &e) const {
    // Forward the hashing to the implementation
    return e.hash();
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

#endif // TRISYCL_SYCL_EVENT_HPP
