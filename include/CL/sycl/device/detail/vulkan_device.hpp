#ifndef TRISYCL_SYCL_DEVICE_DETAIL_VULKAN_DEVICE_HPP
#define TRISYCL_SYCL_DEVICE_DETAIL_VULKAN_DEVICE_HPP

namespace cl::sycl::detail {

class vulkan_device : public detail::device {

  VkDevice vkdev;
public:


};

}

#endif
