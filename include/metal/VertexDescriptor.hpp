#ifndef METALPP_METAL_VERTEXDESCRIPTOR_HPP
#define METALPP_METAL_VERTEXDESCRIPTOR_HPP

namespace mtl
{
    class VertexDescriptor final: public ns::Object
    {
        inline static const auto cls = objc_lookUpClass("MTLVertexDescriptor");

    public:
        VertexDescriptor() noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, allocSel), initSel)}
        {
        }
    };
}

#endif
