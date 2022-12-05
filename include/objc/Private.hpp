#ifndef METALPP_OBJC_PRIVATE_HPP
#define METALPP_OBJC_PRIVATE_HPP

#define METALPP_PRIVATE_VISIBILITY __attribute__((visibility("hidden")))
#define METALPP_PRIVATE_CLS(name) static inline const auto cls METALPP_PRIVATE_VISIBILITY = objc_lookUpClass(name)
#define METALPP_PRIVATE_SEL(selector, name) static inline const auto selector_##selector METALPP_PRIVATE_VISIBILITY = sel_registerName(name)
#define METALPP_SEL(selector) selector_##selector

#endif
