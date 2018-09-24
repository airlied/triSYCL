#ifndef TRISYCL_SYCL_QUEUE_DETAIL_VULKAN_QUEUE_HPP
#define TRISYCL_SYCL_QUEUE_DETAIL_VULKAN_QUEUE_HPP

namespace cl::sycl::detail {

class vulkan_queue : public detail::queue,
		       detail::debug<vulkan_queue> {


};

}
#endif // TRISYCL_SYCL_QUEUE_DETAIL_VULKAN_QUEUE_HPP
