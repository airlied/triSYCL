#ifndef TRISYCL_SYCL_INFO_EVENT_HPP
#define TRISYCL_SYCL_INFO_EVENT_HPP

namespace cl {
namespace sycl {  
namespace info {

enum class event : unsigned int {
  command_execution_status,
  reference_count,
};

enum class event_command_status : unsigned int {
   submitted,
   running,
   complete
};

enum class event_profiling : unsigned int {
  command_submit,
  command_start,
  command_end,
};					   

TRISYCL_INFO_PARAM_TRAITS(info::event::command_execution_status, event_command_status)
TRISYCL_INFO_PARAM_TRAITS(info::event::reference_count, cl::sycl::cl_uint)

TRISYCL_INFO_PARAM_TRAITS(info::event_profiling::command_submit, cl::sycl::cl_ulong);
TRISYCL_INFO_PARAM_TRAITS(info::event_profiling::command_start, cl::sycl::cl_ulong);
TRISYCL_INFO_PARAM_TRAITS(info::event_profiling::command_end, cl::sycl::cl_ulong);

}
}
}
#endif
