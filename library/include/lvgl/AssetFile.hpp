//
// Created by Tyler Gilbert on 12/17/21.
//

#ifndef LVGLAPI_LVGL_ASSETFILE_HPP
#define LVGLAPI_LVGL_ASSETFILE_HPP

#include <algorithm>

#include <fs/File.hpp>

#include "Types.hpp"

namespace lvgl {

class AssetFile : public fs::FileObject, public Api {

public:
  AssetFile(var::StringView path);
  ~AssetFile();

  AssetFile(const AssetFile&) = delete;
  AssetFile& operator=(const AssetFile&) = delete;

  AssetFile(AssetFile&&a){
    std::swap(m_handle,a.m_handle);
  }

  AssetFile& operator=(AssetFile&&a){
    std::swap(m_handle,a.m_handle);
    return *this;
  }

private:

  mutable lv_fs_file_t m_handle{};

  int interface_ioctl(int request, void *argument) const override {
    return fake_ioctl(request, argument);
  }
  int interface_lseek(int offset, int whence) const override;
  int interface_read(void *buf, int nbyte) const override;
  int interface_write(const void *buf, int nbyte) const override;
};

} // namespace lvgl

#endif // LVGLAPI_LVGL_ASSETFILE_HPP
