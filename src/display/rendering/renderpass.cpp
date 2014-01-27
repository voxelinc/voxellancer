#include "renderpass.h"

RenderPass::RenderPass(std::string name):
    m_name(name)
{

}

const std::string& RenderPass::name() const
{
    return m_name;
}
