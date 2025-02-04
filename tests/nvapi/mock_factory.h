#pragma once

#include "nvapi_tests_private.h"
#include "../../src/nvapi/nvapi_resource_factory.h"
#include "../mocks/vulkan_mocks.h"
#include "../mocks/dxgi_mocks.h"
#include "../mocks/nvml_mocks.h"
#include "../mocks/lfx_mocks.h"

using namespace trompeloeil;

class MockFactory final : public dxvk::NvapiResourceFactory {

  public:
    MockFactory(
        std::unique_ptr<DXGIDxvkFactoryMock> dxgiFactory1Mock,
        std::unique_ptr<VkMock> vkMock,
        std::unique_ptr<NvmlMock> nvmlMock,
        std::unique_ptr<LfxMock> lfxMock)
        : m_dxgiFactoryMock(std::move(dxgiFactory1Mock)),
          m_vkMock(std::move(vkMock)),
          m_nvmlMock(std::move(nvmlMock)),
          m_lfxMock(std::move(lfxMock)) {};

    dxvk::Com<IDXGIFactory1> CreateDXGIFactory1() override {
        return m_dxgiFactoryMock.get();
    };

    std::unique_ptr<dxvk::Vk> CreateVulkan(dxvk::Com<IDXGIFactory1>& dxgiFactory) override {
        return std::move(m_vkMock);
    }

    std::unique_ptr<dxvk::Vk> CreateVulkan(const char*) override {
        return std::move(m_vkMock);
    }

    std::unique_ptr<dxvk::Nvml> CreateNvml() override {
        return std::move(m_nvmlMock);
    }

    std::unique_ptr<dxvk::Lfx> CreateLfx() override {
        return std::move(m_lfxMock);
    }

    [[nodiscard]] DXGIDxvkFactoryMock* GetDXGIDxvkFactoryMock() const {
        return m_dxgiFactoryMock.get();
    }

  private:
    std::unique_ptr<DXGIDxvkFactoryMock> m_dxgiFactoryMock;
    std::unique_ptr<VkMock> m_vkMock;
    std::unique_ptr<NvmlMock> m_nvmlMock;
    std::unique_ptr<LfxMock> m_lfxMock;
};
