//
// Created by Tyler Gilbert on 12/17/21.
//

#include "lvgl/AssetFile.hpp"

using namespace lvgl;

AssetFile::AssetFile(var::StringView path) {
  API_RETURN_IF_ERROR();
  var::PathString path_string(path);
  if( auto result = api()->fs_open(&m_handle, path_string.cstring(), LV_FS_MODE_RD); result != LV_FS_RES_OK ){
    API_RETURN_ASSIGN_ERROR("failed to open LV file", EINVAL);
  }
}

AssetFile::~AssetFile() {
  if( m_handle.file_d != nullptr ){
    api()->fs_close(&m_handle);
  }
}



int AssetFile::interface_lseek(int offset, int whence) const {
  const auto lv_whence = [](int whence) {
    switch (Whence(whence)) {
    case Whence::set:
      return LV_FS_SEEK_SET;
    case Whence::end:
      return LV_FS_SEEK_END;
    case Whence::current:
      return LV_FS_SEEK_CUR;
    };
    return LV_FS_SEEK_SET;
  }(whence);

  if( api()->fs_seek(&m_handle, offset, lv_whence) == LV_FS_RES_OK ){
    u32 location = 0;
    api()->fs_tell(&m_handle, &location);
    return location;
  }

  errno = EIO;
  return -1;
}

int AssetFile::interface_read(void *buf, int nbyte) const {
  u32 bytes = 0;
  if (api()->fs_read(&m_handle, buf, nbyte, &bytes) == LV_FS_RES_OK) {
    return bytes;
  }
  return -1;
}

int AssetFile::interface_write(const void *buf, int nbyte) const {
  errno = ENOTSUP;
  return -1;
}
