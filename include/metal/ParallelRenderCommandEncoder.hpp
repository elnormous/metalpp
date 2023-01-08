#ifndef METALPP_METAL_PARALLELRENDERCOMMANDENCODER_HPP
#define METALPP_METAL_PARALLELRENDERCOMMANDENCODER_HPP

#include <os/availability.h>
#include "../objc/Runtime.hpp"
#include "CommandEncoder.hpp"
#include "RenderCommandEncoder.hpp"
#include "RenderPass.hpp"

namespace mtl
{
    class ParallelRenderCommandEncoder final: public CommandEncoder
    {
    public:
        METALPP_PRIVATE_SEL(renderCommandEncoder, "renderCommandEncoder");
        METALPP_PRIVATE_SEL(setColorStoreAction_atIndex_, "setColorStoreAction:atIndex:");
        METALPP_PRIVATE_SEL(setDepthStoreAction_, "setDepthStoreAction:");
        METALPP_PRIVATE_SEL(setStencilStoreAction_, "setStencilStoreAction:");
        METALPP_PRIVATE_SEL(setColorStoreActionOptions_atIndex_, "setColorStoreActionOptions:atIndex:");
        METALPP_PRIVATE_SEL(setDepthStoreActionOptions_, "setDepthStoreActionOptions:");
        METALPP_PRIVATE_SEL(setStencilStoreActionOptions_, "setStencilStoreActionOptions:");

        using CommandEncoder::CommandEncoder;
        using CommandEncoder::operator=;

        ParallelRenderCommandEncoder() = delete;

        [[nodiscard]] auto renderCommandEncoder() noexcept
        {
            return RenderCommandEncoder{sendMessage<id>(METALPP_SEL(renderCommandEncoder))};
        }

        void setColorStoreAction(const StoreAction storeAction,const ns::UInteger colorAttachmentIndex) noexcept API_AVAILABLE(macos(10.12), ios(10.0))
        {
            sendMessage(METALPP_SEL(setColorStoreAction_atIndex_), storeAction, colorAttachmentIndex);
        }

        void setDepthStoreAction(const StoreAction storeAction) noexcept API_AVAILABLE(macos(10.12), ios(10.0))
        {
            sendMessage(METALPP_SEL(setDepthStoreAction_), storeAction);
        }

        void setStencilStoreAction(const StoreAction storeAction) noexcept API_AVAILABLE(macos(10.12), ios(10.0))
        {
            sendMessage(METALPP_SEL(setStencilStoreAction_), storeAction);
        }

        void setColorStoreActionOptions(const StoreActionOptions storeActionOptions, const ns::UInteger colorAttachmentIndex) noexcept API_AVAILABLE(macos(10.13), ios(11.0))
        {
            sendMessage(METALPP_SEL(setColorStoreActionOptions_atIndex_), storeActionOptions, colorAttachmentIndex);
        }

        void setDepthStoreActionOptions(const StoreActionOptions storeActionOptions) noexcept API_AVAILABLE(macos(10.13), ios(11.0))
        {
            sendMessage(METALPP_SEL(setDepthStoreActionOptions_), storeActionOptions);
        }

        void setStencilStoreActionOptions(const StoreActionOptions storeActionOptions) noexcept API_AVAILABLE(macos(10.13), ios(11.0))
        {
            sendMessage(METALPP_SEL(setStencilStoreActionOptions_), storeActionOptions);
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));
}

#endif
