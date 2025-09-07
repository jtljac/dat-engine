#pragma once

#include <vector>
#include "VkStub.h"

namespace DatEngine::DatGPU::DatVk {
    class PipelineBuilder {
    public:
        vk::Device device;

        std::vector<vk::PipelineShaderStageCreateInfo> shaderStages;
        std::vector<vk::Format> colourAttachmentFormats;
        vk::PipelineInputAssemblyStateCreateInfo inputAssembly;
        vk::PipelineRasterizationStateCreateInfo rasterizer;
        vk::PipelineColorBlendAttachmentState colorBlendAttachment;
        vk::PipelineMultisampleStateCreateInfo multisampling;
        vk::PipelineLayout pipelineLayout;
        vk::PipelineDepthStencilStateCreateInfo depthStencil;
        vk::PipelineRenderingCreateInfo renderInfo;

        PipelineBuilder(const vk::Device device) : device(device) {
            clear();
        };

        /**
         * Add a shader module to the pipeline
         *
         * @param stage The stage the shader module will execute at
         * @param shader The shader module to add to the pipeline
         * @param entrypoint The name of the entrypoint function in the shader module
         * @return The PipelineBuilder for chaining
         */
        PipelineBuilder& addShader(vk::ShaderStageFlagBits stage, vk::ShaderModule shader, const std::string& entrypoint = "main");

        /**
         *Add a complete PipelineShaderStageCreateInfo to the pipeline
         *
         * @return The PipelineBuilder for chaining
         */
        PipelineBuilder& addShader(const vk::PipelineShaderStageCreateInfo& shaderStage);

        /**
         * Remove all the shader stages from the pipeline
         *
         * @return The PipelineBuilder for chaining
         */
        PipelineBuilder& clearShaderStages();

        /**
         * Set the topology of vertices consumed by the pipeline
         *
         * @param topology The topology
         * @return The PipelineBuilder for chaining
         */
        PipelineBuilder& setInputTopology(vk::PrimitiveTopology topology);

        /**
         * Set the polygon mode used when consuming vertices
         *
         * @param polygonMode The polygon mode
         * @param lineWidth The width of the line when the polygon mode is vk::PolygonMode::eLine
         * @return The PipelineBuilder for chaining
         */
        PipelineBuilder& setPolygonMode(vk::PolygonMode polygonMode, float lineWidth = 1.f);

        /**
         * Set which orientation of faces are culled when drawing triangles
         *
         * @param cullMode Which faces to cull
         * @param frontFace Which faces to treat as the "front face"
         * @return The PipelineBuilder for chaining
         */
        PipelineBuilder& setCullMode(vk::CullModeFlags cullMode, vk::FrontFace frontFace);

        /**
         * Disable blending for the pipeline
         *
         * @return The PipelineBuilder for chaining
         */
        PipelineBuilder& disableBlending();

        /**
         * Enable additive blending for the pipeline
         *
         * @code outColor = srcColor.rgb * srcColor.a + dstColor.rgb * 1.0@endcode
         *
         * @return The PipelineBuilder for chaining
         */
        PipelineBuilder& enableBlendingAdditive();

        /**
         * Enable alpha blending for the pipeline
         *
         * @code outColor = srcColor.rgb * srcColor.a + dstColor.rgb * (1.0 - srcColor.a)@endcode
         *
         * @return The PipelineBuilder for chaining
         */
        PipelineBuilder& enableBlendingAlpha();

        /**
         * Add a new colour attachment to the pipeline
         *
         * @param format A format to add to the colour attachments
         * @return The PipelineBuilder for chaining
         */
        PipelineBuilder& addColourAttachmentFormat(vk::Format format);

        /**
         * Set the format used for the depth attachment in the pipeline
         *
         * @param format the format to use for the depth attachment
         * @return The PipelineBuilder for chaining
         */
        PipelineBuilder& setDepthAttachmentFormat(vk::Format format);

        /**
         * Set the format used for the stencil attachment in the pipeline
         *
         * @param format the format to use for the stencil attachment
         * @return The PipelineBuilder for chaining
         */
        PipelineBuilder& setStencilAttachmentFormat(vk::Format format);

        /**
         * Clear the configured colour attachments from the pipeline
         *
         * @return The PipelineBuilder for chaining
         */
        PipelineBuilder& clearColourAttachmentFormats();

        /**
         * Clear the configured depth attachment from the pipeline
         *
         * @return The PipelineBuilder for chaining
         */
        PipelineBuilder& clearDepthAttachmentFormat();

        /**
         * Clear the configured stencil attachment from the pipeline
         *
         * @return The PipelineBuilder for chaining
         */
        PipelineBuilder& clearStencilAttachmentFormat();

        /**
         * Clear the configured colour, depth, and stencil attachments from the pipeline
         *
         * @return The PipelineBuilder for chaining
         */
        PipelineBuilder& clearColourDepthStencilAttachmentFormats();

        /**
         * Disable depth testing for this pipeline
         *
         * @return The PipelineBuilder for chaining
         */
        PipelineBuilder& disableDepthTest();

        /**
         * Enable depth testing for this pipeline
         *
         * @param depthWriteEnable Whether this pipeline writes new values to the depth buffer
         * @param depthCompareOp The operation used to depth test
         * @return The PipelineBuilder for chaining
         */
        PipelineBuilder& enableDepthTest(bool depthWriteEnable, vk::CompareOp depthCompareOp);

        /**
         * Disable stencil testing for this pipeline
         *
         * @return The PipelineBuilder for chaining
         */
        PipelineBuilder& disableStencilTest();

        /**
         * Enable stencil testing for this pipeline
         *
         * @param front The stencil operations for front faces
         * @param back The stencil operations for back faces
         * @return The PipelineBuilder for chaining
         */
        PipelineBuilder& enableStencilTest(const vk::StencilOpState& front, const vk::StencilOpState& back);

        /**
         * Set the pipeline inputAssembly to a pre-configured PipelineInputAssemblyStateCreateInfo
         *
         * @param inputAssembly The new inputAssemblyCreateInfo
         * @return The PipelineBuilder for chaining
         */
        PipelineBuilder& setInputAssembly(const vk::PipelineInputAssemblyStateCreateInfo& inputAssembly);

        /**
         * Set the pipeline rasterizer to a pre-configured PipelineRasterizationStateCreateInfo
         *
         * @param rasterizer The new RasterizationStateCreateInfo
         * @return The PipelineBuilder for chaining
         */
        PipelineBuilder& setRasterizer(const vk::PipelineRasterizationStateCreateInfo& rasterizer);

        /**
         * Set the pipeline colorBlendAttachment to a pre-configured PipelineColorBlendAttachmentState
         *
         * @param colorBlendAttachment The new ColorBlendAttachmentState
         * @return The PipelineBuilder for chaining
         */
        PipelineBuilder& setColorBlendAttachment(const vk::PipelineColorBlendAttachmentState& colorBlendAttachment);

        /**
         * Set the pipeline multisampling to a pre-configured PipelineMultisampleStateCreateInfo
         *
         * @param multisampling The new MultisampleStateCreateInfo
         * @return The PipelineBuilder for chaining
         */
        PipelineBuilder& setMultisampling(const vk::PipelineMultisampleStateCreateInfo& multisampling);

        /**
         * Set the pipelineLayout to a pre-configured PipelineLayout
         *
         * @param pipelineLayout The new Layout
         * @return The PipelineBuilder for chaining
         */
        PipelineBuilder& setPipelineLayout(vk::PipelineLayout pipelineLayout);

        /**
         * Set the pipeline depthStencil to a pre-configured PipelineDepthStencilStateCreateInfo
         *
         * @param depthStencil The new DepthStencilStateCreateInfo
         * @return The PipelineBuilder for chaining
         */
        PipelineBuilder& setDepthStencil(const vk::PipelineDepthStencilStateCreateInfo& depthStencil);

        /**
         * Set the pipeline renderInfo to a pre-configured PipelineRenderingCreateInfo
         *
         * @param renderInfo The new PipelineRenderingCreateInfo
         * @return The PipelineBuilder for chaining
         */
        PipelineBuilder& setRenderInfo(const vk::PipelineRenderingCreateInfo& renderInfo);

        /**
         * Reset the pipeline builder to the defaults
         *
         * @return The PipelineBuilder for chaining
         */
        PipelineBuilder& clear();

        /**
         * Build the Pipeline from the given config
         *
         * @return A new pipeline
         */
        vk::Pipeline build();
    };
}