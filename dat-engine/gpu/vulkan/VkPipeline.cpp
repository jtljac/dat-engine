#include "VkPipeline.h"

using namespace DatEngine::DatGPU::DatVk;

/* -------------------------------------------- */
/* Shader Stage                                 */
/* -------------------------------------------- */
PipelineBuilder&
PipelineBuilder::addShader(vk::ShaderStageFlagBits stage, vk::ShaderModule shader, const std::string& entrypoint) {
    shaderStages.push_back({{}, stage, shader, entrypoint.c_str()});

    return *this;
}

PipelineBuilder& PipelineBuilder::addShader(const vk::PipelineShaderStageCreateInfo& shaderStage) {
    shaderStages.push_back(shaderStage);

    return *this;
}

PipelineBuilder& PipelineBuilder::clearShaderStages() {
    shaderStages.clear();

    return *this;
}

/* -------------------------------------------- */
/* Vertex handling                              */
/* -------------------------------------------- */

PipelineBuilder& PipelineBuilder::setInputTopology(const vk::PrimitiveTopology topology) {
    inputAssembly.topology = topology;

    return *this;
}

PipelineBuilder& PipelineBuilder::setPolygonMode(const vk::PolygonMode polygonMode, const float lineWidth) {
    rasterizer.polygonMode = polygonMode;
    rasterizer.lineWidth = lineWidth;

    return *this;
}

PipelineBuilder& PipelineBuilder::setCullMode(const vk::CullModeFlags cullMode, const vk::FrontFace frontFace) {
    rasterizer.cullMode = cullMode;
    rasterizer.frontFace = frontFace;

    return *this;
}

/* -------------------------------------------- */
/* Blending                                     */
/* -------------------------------------------- */

PipelineBuilder& PipelineBuilder::disableBlending() {
    colorBlendAttachment.blendEnable = VK_FALSE;
    colorBlendAttachment.colorWriteMask = vk::ColorComponentFlagBits::eR | vk::ColorComponentFlagBits::eG
                                          | vk::ColorComponentFlagBits::eB | vk::ColorComponentFlagBits::eA;

    return *this;
}

PipelineBuilder& PipelineBuilder::enableBlendingAdditive() {
    colorBlendAttachment.colorWriteMask = vk::ColorComponentFlagBits::eR | vk::ColorComponentFlagBits::eG
                                          | vk::ColorComponentFlagBits::eB | vk::ColorComponentFlagBits::eA;
    colorBlendAttachment.blendEnable = VK_TRUE;
    colorBlendAttachment.srcColorBlendFactor = vk::BlendFactor::eSrcAlpha;
    colorBlendAttachment.dstColorBlendFactor = vk::BlendFactor::eOne;
    colorBlendAttachment.colorBlendOp = vk::BlendOp::eAdd;
    colorBlendAttachment.srcAlphaBlendFactor = vk::BlendFactor::eOne;
    colorBlendAttachment.dstAlphaBlendFactor = vk::BlendFactor::eZero;
    colorBlendAttachment.alphaBlendOp = vk::BlendOp::eAdd;

    return *this;
}

PipelineBuilder& PipelineBuilder::enableBlendingAlpha() {
    colorBlendAttachment.colorWriteMask = vk::ColorComponentFlagBits::eR | vk::ColorComponentFlagBits::eG
                                          | vk::ColorComponentFlagBits::eB | vk::ColorComponentFlagBits::eA;
    colorBlendAttachment.blendEnable = VK_TRUE;
    colorBlendAttachment.srcColorBlendFactor = vk::BlendFactor::eSrcAlpha;
    colorBlendAttachment.dstColorBlendFactor = vk::BlendFactor::eOneMinusSrcAlpha;
    colorBlendAttachment.colorBlendOp = vk::BlendOp::eAdd;
    colorBlendAttachment.srcAlphaBlendFactor = vk::BlendFactor::eOne;
    colorBlendAttachment.dstAlphaBlendFactor = vk::BlendFactor::eZero;
    colorBlendAttachment.alphaBlendOp = vk::BlendOp::eAdd;

    return *this;
}

/* -------------------------------------------- */
/* Colour, Depth, and Stencil Attachment        */
/* -------------------------------------------- */

PipelineBuilder& PipelineBuilder::addColourAttachmentFormat(const vk::Format format) {
    colourAttachmentFormats.push_back(format);

    return *this;
}

PipelineBuilder& PipelineBuilder::setDepthAttachmentFormat(const vk::Format format) {
    renderInfo.depthAttachmentFormat = format;

    return *this;
}

PipelineBuilder& PipelineBuilder::setStencilAttachmentFormat(const vk::Format format) {
    renderInfo.stencilAttachmentFormat = format;

    return *this;
}

PipelineBuilder& PipelineBuilder::clearColourAttachmentFormats() {
    colourAttachmentFormats.clear();

    return *this;
}

PipelineBuilder& PipelineBuilder::clearDepthAttachmentFormat() {
    renderInfo.depthAttachmentFormat = vk::Format::eUndefined;

    return *this;
}

PipelineBuilder& PipelineBuilder::clearStencilAttachmentFormat() {
    renderInfo.stencilAttachmentFormat = vk::Format::eUndefined;

    return *this;
}

PipelineBuilder& PipelineBuilder::clearColourDepthStencilAttachmentFormats() {
    clearColourAttachmentFormats();
    clearDepthAttachmentFormat();
    clearStencilAttachmentFormat();

    return *this;
}

/* -------------------------------------------- */
/* Depth & Stencil testing                      */
/* -------------------------------------------- */

PipelineBuilder& PipelineBuilder::disableDepthTest() {
    depthStencil.depthTestEnable = VK_FALSE;
    depthStencil.depthWriteEnable = VK_FALSE;
    depthStencil.depthCompareOp = vk::CompareOp::eNever;
    depthStencil.depthBoundsTestEnable = VK_FALSE;
    depthStencil.minDepthBounds = 0.f;
    depthStencil.maxDepthBounds = 1.f;

    return *this;
}

PipelineBuilder& PipelineBuilder::enableDepthTest(const bool depthWriteEnable, const vk::CompareOp depthCompareOp) {
    depthStencil.depthTestEnable = VK_TRUE;
    depthStencil.depthWriteEnable = depthWriteEnable;
    depthStencil.depthCompareOp = depthCompareOp;
    depthStencil.depthBoundsTestEnable = VK_FALSE;
    depthStencil.stencilTestEnable = VK_FALSE;
    depthStencil.front = vk::StencilOpState();
    depthStencil.back = vk::StencilOpState();
    depthStencil.minDepthBounds = 0.f;
    depthStencil.maxDepthBounds = 1.f;

    return *this;
}

PipelineBuilder& PipelineBuilder::disableStencilTest() {
    depthStencil.stencilTestEnable = VK_FALSE;
    depthStencil.front = vk::StencilOp::eZero;
    depthStencil.back = vk::StencilOp::eZero;

    return *this;
}
PipelineBuilder& PipelineBuilder::enableStencilTest(const vk::StencilOpState& front, const vk::StencilOpState& back) {
    depthStencil.stencilTestEnable = VK_TRUE;
    depthStencil.front = front;
    depthStencil.back = back;

    return *this;
}

/* -------------------------------------------- */
/* Direct Setters                               */
/* -------------------------------------------- */

PipelineBuilder& PipelineBuilder::setInputAssembly(const vk::PipelineInputAssemblyStateCreateInfo& inputAssembly) {
    this->inputAssembly = inputAssembly;
    return *this;
}

PipelineBuilder& PipelineBuilder::setRasterizer(const vk::PipelineRasterizationStateCreateInfo& rasterizer) {
    this->rasterizer = rasterizer;
    return *this;
}

PipelineBuilder& PipelineBuilder::setColorBlendAttachment(const vk::PipelineColorBlendAttachmentState& colorBlendAttachment) {
    this->colorBlendAttachment = colorBlendAttachment;
    return *this;
}

PipelineBuilder& PipelineBuilder::setMultisampling(const vk::PipelineMultisampleStateCreateInfo& multisampling) {
    this->multisampling = multisampling;
    return *this;
}

PipelineBuilder& PipelineBuilder::setPipelineLayout(const vk::PipelineLayout pipelineLayout) {
    this->pipelineLayout = pipelineLayout;
    return *this;
}

PipelineBuilder& PipelineBuilder::setDepthStencil(const vk::PipelineDepthStencilStateCreateInfo& depthStencil) {
    this->depthStencil = depthStencil;
    return *this;
}

PipelineBuilder& PipelineBuilder::setRenderInfo(const vk::PipelineRenderingCreateInfo& renderInfo) {
    this->renderInfo = renderInfo;
    return *this;
}

/* -------------------------------------------- */
/* Build & Reset                                */
/* -------------------------------------------- */

PipelineBuilder& PipelineBuilder::clear() {
    inputAssembly = vk::PipelineInputAssemblyStateCreateInfo();
    rasterizer = vk::PipelineRasterizationStateCreateInfo();
    colorBlendAttachment = vk::PipelineColorBlendAttachmentState();
    multisampling = vk::PipelineMultisampleStateCreateInfo(
            {},
            vk::SampleCountFlagBits::e1,
            VK_FALSE,
            1.0f,
            nullptr,
            VK_FALSE,
            VK_FALSE
    );
    pipelineLayout = VK_NULL_HANDLE;
    depthStencil = vk::PipelineDepthStencilStateCreateInfo();
    renderInfo = vk::PipelineRenderingCreateInfo();

    clearShaderStages();
    clearColourAttachmentFormats();

    return *this;
}
vk::Pipeline PipelineBuilder::build() {
    vk::PipelineViewportStateCreateInfo viewportState = {};
    // TODO:
}
