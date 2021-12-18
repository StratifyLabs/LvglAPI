#include <fcntl.h>
#include <unistd.h>

#if defined __win32
#include "dirent_windows.h"
#define posix_open _open
#define posix_close _close
#define posix_read _read
#define posix_write _write
#define posix_lseek _lseek
#else
#include <dirent.h>
#define posix_open open
#define posix_close close
#define posix_read read
#define posix_write write
#define posix_lseek lseek
#endif

#include "lvgl.h"
#include "lvgl_api.h"

static bool lvgl_api_fs_ready_cb(struct _lv_fs_drv_t *drv) {
  MCU_UNUSED_ARGUMENT(drv);
  return true;
}

#if defined __win32
#define OTHER_OPTIONS O_BINARY
#else
#define OTHER_OPTIONS 0
#endif

static void *
lvgl_api_fs_open_cb(struct _lv_fs_drv_t *drv, const char *path, lv_fs_mode_t mode) {
  MCU_UNUSED_ARGUMENT(drv);
  const int f_mode =
    (mode == LV_FS_MODE_WR) ? OTHER_OPTIONS | O_RDWR : OTHER_OPTIONS | O_RDONLY;

  ssize_t fd = (ssize_t)posix_open(path, f_mode);
  return (void *)fd;
}

static lv_fs_res_t lvgl_api_fs_close_cb(struct _lv_fs_drv_t *drv, void *file_p) {
  MCU_UNUSED_ARGUMENT(drv);
  const int fd = (ssize_t)file_p;
  posix_close(fd);
  return LV_FS_RES_OK;
}

static lv_fs_res_t lvgl_api_fs_read_cb(
  struct _lv_fs_drv_t *drv,
  void *file_p,
  void *buf,
  uint32_t btr,
  uint32_t *br) {
  MCU_UNUSED_ARGUMENT(drv);
  const int fd = (ssize_t)file_p;
  const int result = posix_read(fd, buf, btr);
  if (result > 0) {
    *br = result;
    return LV_FS_RES_OK;
  }

  return LV_FS_RES_FS_ERR;
}
static lv_fs_res_t lvgl_api_fs_write_cb(
  struct _lv_fs_drv_t *drv,
  void *file_p,
  const void *buf,
  uint32_t btw,
  uint32_t *bw) {
  MCU_UNUSED_ARGUMENT(drv);
  const int fd = (ssize_t)file_p;

  const int result = posix_write(fd, buf, btw);
  if (result > 0) {
    *bw = result;
    return LV_FS_RES_OK;
  }

  return LV_FS_RES_FS_ERR;
}
static lv_fs_res_t lvgl_api_fs_seek_cb(
  struct _lv_fs_drv_t *drv,
  void *file_p,
  uint32_t pos,
  lv_fs_whence_t whence) {
  MCU_UNUSED_ARGUMENT(drv);
  const int fd = (ssize_t)file_p;
  const int fwhence = (whence == LV_FS_SEEK_CUR)
                        ? SEEK_CUR
                        : (whence == LV_FS_SEEK_SET ? SEEK_SET : (SEEK_END));
  posix_lseek(fd, pos, fwhence);
  return LV_FS_RES_OK;
}
static lv_fs_res_t
lvgl_api_fs_tell_cb(struct _lv_fs_drv_t *drv, void *file_p, uint32_t *pos_p) {
  MCU_UNUSED_ARGUMENT(drv);
  const int fd = (ssize_t)file_p;
  *pos_p = posix_lseek(fd, 0, SEEK_CUR);
  return LV_FS_RES_OK;
}

static void *lvgl_api_fs_dir_open_cb(struct _lv_fs_drv_t *drv, const char *path) {
  MCU_UNUSED_ARGUMENT(drv);
  return opendir(path);
}
static lv_fs_res_t
lvgl_api_fs_dir_read_cb(struct _lv_fs_drv_t *drv, void *rddir_p, char *fn) {
  MCU_UNUSED_ARGUMENT(drv);
  struct dirent entry;
  struct dirent *result;
  readdir_r(rddir_p, &entry, &result);
  strncpy(fn, entry.d_name, 256);
  return LV_FS_RES_OK;
}

static lv_fs_res_t lvgl_api_fs_dir_close_cb(struct _lv_fs_drv_t *drv, void *rddir_p) {
  MCU_UNUSED_ARGUMENT(drv);
  closedir(rddir_p);
  return LV_FS_RES_OK;
}

static lv_fs_drv_t drv;

void lvgl_api_initialize_filesystem() {

  lv_fs_drv_init(&drv); /*Basic initialization*/

  drv.letter = 'S';                    /*An uppercase letter to identify the drive */
  drv.ready_cb = lvgl_api_fs_ready_cb; /*Callback to tell if the drive is ready to use */
  drv.open_cb = lvgl_api_fs_open_cb;   /*Callback to open a file */
  drv.close_cb = lvgl_api_fs_close_cb; /*Callback to close a file */
  drv.read_cb = lvgl_api_fs_read_cb;   /*Callback to read a file */
  drv.write_cb = lvgl_api_fs_write_cb; /*Callback to write a file */
  drv.seek_cb = lvgl_api_fs_seek_cb;   /*Callback to seek in a file (Move cursor) */
  drv.tell_cb = lvgl_api_fs_tell_cb;   /*Callback to tell the cursor position  */

  drv.dir_open_cb =
    lvgl_api_fs_dir_open_cb; /*Callback to open directory to read its content */
  drv.dir_read_cb = lvgl_api_fs_dir_read_cb;   /*Callback to read a directory's content */
  drv.dir_close_cb = lvgl_api_fs_dir_close_cb; /*Callback to close a directory */

  drv.user_data = NULL; /*Any custom data if required*/

  lv_fs_drv_register(&drv); /*Finally register the drive*/
}


static void *
lvgl_api_assetfs_open_cb(struct _lv_fs_drv_t *drv, const char *path, lv_fs_mode_t mode) {
  const lvgl_assetfs_header_t *config = drv->user_data;
  printf("open file %s\n", path);
  for (size_t i = 0; i < config->count; i++) {
    const lvgl_assetfs_dirent_t *entry = config->entries + i;
    if (strncmp(path, entry->name, LVGL_ASSETFS_NAME_MAX) == 0) {
      // it's a match
      lvgl_api_assetfs_file_t *result = lv_mem_alloc(sizeof(lvgl_api_assetfs_file_t));
      if (result == NULL) {
        printf("alloc failed\n");
        return NULL;
      }
      result->entry = entry;
      result->seek_offset = 0;
      printf("return entry\n");
      return result;
    }
  }
  printf("not found\n");
  return NULL;
}

static lv_fs_res_t lvgl_api_assetfs_close_cb(struct _lv_fs_drv_t *drv, void *file_p) {
  MCU_UNUSED_ARGUMENT(drv);
  if (file_p != NULL) {
    lv_mem_free(file_p);
  }
  return LV_FS_RES_OK;
}

static lv_fs_res_t lvgl_api_assetfs_read_cb(
  struct _lv_fs_drv_t *drv,
  void *file_p,
  void *buf,
  uint32_t btr,
  uint32_t *br) {
  MCU_UNUSED_ARGUMENT(drv);
  // const assetfs_dirent_t * entry = file_p;
  lvgl_api_assetfs_file_t *file = file_p;
  const char *start = (char *)(drv->user_data) + file->entry->start;
  const size_t offset = file->seek_offset;

  const size_t end = offset + btr;
  const size_t bytes_ready = end < file->entry->size ? btr : file->entry->size - offset;

  memcpy(buf, start + offset, bytes_ready);
  file->seek_offset += bytes_ready;
  *br = bytes_ready;

  return LV_FS_RES_OK;
}

static lv_fs_res_t lvgl_api_assetfs_write_cb(
  struct _lv_fs_drv_t *drv,
  void *file_p,
  const void *buf,
  uint32_t btw,
  uint32_t *bw) {
  MCU_UNUSED_ARGUMENT(drv);
  MCU_UNUSED_ARGUMENT(file_p);
  MCU_UNUSED_ARGUMENT(buf);
  MCU_UNUSED_ARGUMENT(btw);
  MCU_UNUSED_ARGUMENT(bw);
  return LV_FS_RES_NOT_IMP;
}

static lv_fs_res_t lvgl_api_assetfs_seek_cb(
  struct _lv_fs_drv_t *drv,
  void *file_p,
  uint32_t pos,
  lv_fs_whence_t whence) {

  MCU_UNUSED_ARGUMENT(drv);

  lvgl_api_assetfs_file_t *file = file_p;
  if (whence == LV_FS_SEEK_CUR) {
    file->seek_offset += pos;
  } else if (whence == LV_FS_SEEK_SET) {
    file->seek_offset = pos;
  } else {
    file->seek_offset = file->entry->size;
  }

  if (file->seek_offset > file->entry->size) {
    file->seek_offset = file->entry->size;
  }

  return LV_FS_RES_OK;
}
static lv_fs_res_t
lvgl_api_assetfs_tell_cb(struct _lv_fs_drv_t *drv, void *file_p, uint32_t *pos_p) {
  MCU_UNUSED_ARGUMENT(drv);
  lvgl_api_assetfs_file_t *file = file_p;
  *pos_p = file->seek_offset;
  return LV_FS_RES_OK;
}

static void *lvgl_api_assetfs_dir_open_cb(struct _lv_fs_drv_t *drv, const char *path) {
  MCU_UNUSED_ARGUMENT(drv);
  MCU_UNUSED_ARGUMENT(path);
  return NULL;
}
static lv_fs_res_t
lvgl_api_assetfs_dir_read_cb(struct _lv_fs_drv_t *drv, void *rddir_p, char *fn) {
  MCU_UNUSED_ARGUMENT(drv);
  MCU_UNUSED_ARGUMENT(rddir_p);
  MCU_UNUSED_ARGUMENT(fn);
  return LV_FS_RES_NOT_IMP;
}

static lv_fs_res_t
lvgl_api_assetfs_dir_close_cb(struct _lv_fs_drv_t *drv, void *rddir_p) {
  MCU_UNUSED_ARGUMENT(drv);
  MCU_UNUSED_ARGUMENT(rddir_p);
  return LV_FS_RES_NOT_IMP;
}

static bool lvgl_api_assetfs_ready_cb(struct _lv_fs_drv_t *drv) {
  MCU_UNUSED_ARGUMENT(drv);
  return true;
}

void lvgl_api_mount_asset_filesystem(const void *assetfs, lv_fs_drv_t *drv, char letter) {
  lv_fs_drv_init(drv); /*Basic initialization*/

  drv->letter = letter; /*An uppercase letter to identify the drive */
  drv->ready_cb =
    lvgl_api_assetfs_ready_cb; /*Callback to tell if the drive is ready to use */
  drv->open_cb = lvgl_api_assetfs_open_cb;   /*Callback to open a file */
  drv->close_cb = lvgl_api_assetfs_close_cb; /*Callback to close a file */
  drv->read_cb = lvgl_api_assetfs_read_cb;   /*Callback to read a file */
  drv->write_cb = lvgl_api_assetfs_write_cb; /*Callback to write a file */
  drv->seek_cb = lvgl_api_assetfs_seek_cb;   /*Callback to seek in a file (Move cursor) */
  drv->tell_cb = lvgl_api_assetfs_tell_cb;   /*Callback to tell the cursor position  */

  drv->dir_open_cb =
    lvgl_api_assetfs_dir_open_cb; /*Callback to open directory to read its content */
  drv->dir_read_cb =
    lvgl_api_assetfs_dir_read_cb; /*Callback to read a directory's content */
  drv->dir_close_cb = lvgl_api_assetfs_dir_close_cb; /*Callback to close a directory */

  printf("Mount assetfs at %p\n", assetfs);
  drv->user_data = (void *)assetfs; /*Any custom data if required*/
  lv_fs_drv_register(drv);          /*Finally register the drive*/
}


