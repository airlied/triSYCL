#ifndef TRISYCL_SYCL_INFO_EVENT_HPP
#define TRISYCL_SYCL_INFO_EVENT_HPP

namespace cl::sycl::info {

enum class event : unsigned int {
  command_execution_status,
  reference_count,
};

enum class event_command_status : unsigned int {
   submitted TRISYCL_SKIP_OPENCL(= CL_SUBMITTED),
   running TRISYCL_SKIP_OPENCL(= CL_RUNNING),
   complete TRISYCL_SKIP_OPENCL(= CL_COMPLETE)
};

enum class event_profiling : unsigned int {
  command_submit TRISYCL_SKIP_OPENCL(= CL_PROFILING_COMMAND_SUBMIT),
  command_start TRISYCL_SKIP_OPENCL(= CL_PROFILING_COMMAND_START),
  command_end TRISYCL_SKIP_OPENCL(= CL_PROFILING_COMMAND_END),
};

TRISYCL_INFO_PARAM_TRAITS(info::event::command_execution_status, event_command_status)
TRISYCL_INFO_PARAM_TRAITS(info::event::reference_count, cl::sycl::cl_uint)

TRISYCL_INFO_PARAM_TRAITS(info::event_profiling::command_submit, cl::sycl::cl_ulong);
TRISYCL_INFO_PARAM_TRAITS(info::event_profiling::command_start, cl::sycl::cl_ulong);
TRISYCL_INFO_PARAM_TRAITS(info::event_profiling::command_end, cl::sycl::cl_ulong);

}
#endif /* TRISYCL_SYCL_INFO_EVENT_HPP */
