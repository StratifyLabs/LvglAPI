//
// Created by Tyler Gilbert on 11/26/21.
//

#if defined __lodepng || 1

#include "lodepng.h"
#include <stdlib.h>

#include "lvgl_api.h"

/**
 * If the display is not in 32 bit format (ARGB888) then covert the image to the current
 * color depth
 * @param img the ARGB888 image
 * @param px_cnt number of pixels in `img`
 */
static void convert_color_depth(uint8_t *img, uint32_t px_cnt) {
#if LV_COLOR_DEPTH == 32
  lv_color32_t *img_argb = (lv_color32_t *)img;
  lv_color_t c;
  lv_color_t *img_c = (lv_color_t *)img;
  uint32_t i;
  for (i = 0; i < px_cnt; i++) {
    c = lv_color_make(img_argb[i].ch.red, img_argb[i].ch.green, img_argb[i].ch.blue);
    img_c[i].ch.red = c.ch.blue;
    img_c[i].ch.blue = c.ch.red;
  }
#elif LV_COLOR_DEPTH == 16
  lv_color32_t *img_argb = (lv_color32_t *)img;
  lv_color_t c;
  uint32_t i;
  for (i = 0; i < px_cnt; i++) {
    c = lv_color_make(img_argb[i].ch.blue, img_argb[i].ch.green, img_argb[i].ch.red);
    img[i * 3 + 2] = img_argb[i].ch.alpha;
    img[i * 3 + 1] = c.full >> 8;
    img[i * 3 + 0] = c.full & 0xFF;
  }
#elif LV_COLOR_DEPTH == 8
  lv_color32_t *img_argb = (lv_color32_t *)img;
  lv_color_t c;
  uint32_t i;
  for (i = 0; i < px_cnt; i++) {
    c = lv_color_make(img_argb[i].ch.red, img_argb[i].ch.green, img_argb[i].ch.blue);
    img[i * 2 + 1] = img_argb[i].ch.alpha;
    img[i * 2 + 0] = c.full;
  }
#elif LV_COLOR_DEPTH == 1
  lv_color32_t *img_argb = (lv_color32_t *)img;
  uint8_t b;
  uint32_t i;
  for (i = 0; i < px_cnt; i++) {
    b = img_argb[i].ch.red | img_argb[i].ch.green | img_argb[i].ch.blue;
    img[i * 2 + 1] = img_argb[i].ch.alpha;
    img[i * 2 + 0] = b > 128 ? 1 : 0;
  }
#endif
}

/**
 * Get info about a PNG image
 * @param src can be file name or pointer to a C array
 * @param header store the info here
 * @return LV_RES_OK: no error; LV_RES_INV: can't get the info
 */
static lv_res_t decoder_info(
  struct _lv_img_decoder_t *decoder,
  const void *src,
  lv_img_header_t *header) {
  (void)decoder;                                    /*Unused*/
  lv_img_src_t src_type = lv_img_src_get_type(src); /*Get the source type*/

  /*If it's a PNG file...*/
  if (src_type == LV_IMG_SRC_FILE) {
    const char *fn = src;
    if (!strcmp(&fn[strlen(fn) - 3], "png")) { /*Check the extension*/

      /* Read the width and height from the file. They have a constant location:
       * [16..23]: width
       * [24..27]: height
       */
      uint32_t size[2];
      lv_fs_file_t f;
      lv_fs_res_t res = lv_fs_open(&f, fn, LV_FS_MODE_RD);
      if (res != LV_FS_RES_OK)
        return LV_RES_INV;
      lv_fs_seek(&f, 16, LV_FS_SEEK_SET);
      uint32_t rn;
      lv_fs_read(&f, &size, 8, &rn);
      if (rn != 8)
        return LV_RES_INV;
      lv_fs_close(&f);
      /*Save the data in the header*/
      header->always_zero = 0;
      header->cf = LV_IMG_CF_RAW_ALPHA;
      /*The width and height are stored in Big endian format so convert them to little
       * endian*/
      header->w =
        (lv_coord_t)((size[0] & 0xff000000) >> 24) + ((size[0] & 0x00ff0000) >> 8);
      header->h =
        (lv_coord_t)((size[1] & 0xff000000) >> 24) + ((size[1] & 0x00ff0000) >> 8);
      return LV_RES_OK;
    }
  }
  /*If it's a PNG file in a  C array...*/
  else if (src_type == LV_IMG_SRC_VARIABLE) {
    const lv_img_dsc_t *img_dsc = src;
    header->always_zero = 0;
    header->cf = img_dsc->header.cf; /*Save the color format*/
    header->w = img_dsc->header.w;   /*Save the color width*/
    header->h = img_dsc->header.h;   /*Save the color height*/
    return LV_RES_OK;
  }

  return LV_RES_INV; /*If didn't succeeded earlier then it's an error*/
}

/**
 * Open a PNG image and return the decided image
 * @param src can be file name or pointer to a C array
 * @param style style of the image object (unused now but certain formats might use it)
 * @return pointer to the decoded image or  `LV_IMG_DECODER_OPEN_FAIL` if failed
 */
static lv_res_t decoder_open(lv_img_decoder_t *decoder, lv_img_decoder_dsc_t *dsc) {

  (void)decoder;  /*Unused*/
  uint32_t error; /*For the return values of PNG decoder functions*/

  uint8_t *img_data = NULL;

  /*If it's a PNG file...*/
  if (dsc->src_type == LV_IMG_SRC_FILE) {
    const char *fn = dsc->src;

    if (!strcmp(&fn[strlen(fn) - 3], "png")) { /*Check the extension*/

      /*Load the PNG file into buffer. It's still compressed (not decoded)*/
      const unsigned char *png_data; /*Pointer to the loaded data. Same as the original file
                                  just loaded into the RAM*/
      size_t png_data_size;    /*Size of `png_data` in bytes*/


      lv_fs_file_t f;
      lv_fs_res_t res = lv_fs_open(&f, fn, LV_FS_MODE_RD);
      lv_fs_drv_t *drv = lv_fs_get_drv(fn[0]);

      int needs_free = 0;
      if (drv->user_data != NULL) {
        // drv data is already in memory
        lvgl_api_assetfs_file_t *file = f.file_d;
        png_data = (const unsigned char *)(drv->user_data) + file->entry->start;
        png_data_size = file->entry->size;
      } else {
        //TODO need to load the file from memory

      }

      lv_fs_close(&f);


      /*Decode the PNG image*/
      uint32_t png_width;  /*Will be the width of the decoded image*/
      uint32_t png_height; /*Will be the width of the decoded image*/

      /*Decode the loaded image in ARGB8888 */
      error =
        lodepng_decode32(&img_data, &png_width, &png_height, png_data, png_data_size);
      if (needs_free) {
        lv_mem_free(png_data); /*Free the loaded file*/
      }
      if (error) {
        LV_LOG_WARN("error %u: %s\n", error, lodepng_error_text(error));
        return LV_RES_INV;
      }

      /*Convert the image to the system's color depth*/
      convert_color_depth(img_data, png_width * png_height);
      dsc->img_data = img_data;
      return LV_RES_OK; /*The image is fully decoded. Return with its pointer*/
    }
  }

  return LV_RES_INV; /*If not returned earlier then it failed*/
}

lv_res_t decoder_read_line(
  struct _lv_img_decoder_t *decoder,
  struct _lv_img_decoder_dsc_t *dsc,
  lv_coord_t x,
  lv_coord_t y,
  lv_coord_t len,
  uint8_t *buf) {
  printf("%s():%d\n", __FUNCTION__, __LINE__);
  return LV_RES_OK; /*Return with its pointer*/
}

/**
 * Free the allocated resources
 */
static void decoder_close(lv_img_decoder_t *decoder, lv_img_decoder_dsc_t *dsc) {
  LV_UNUSED(decoder); /*Unused*/

  if (dsc->img_data) {
    free(dsc->img_data);
    dsc->img_data = NULL;
  }
}

void lvgl_api_initialize_png_decoder() {
  lv_img_decoder_t *dec = lv_img_decoder_create();
  lv_img_decoder_set_info_cb(dec, decoder_info);
  lv_img_decoder_set_open_cb(dec, decoder_open);
  lv_img_decoder_set_close_cb(dec, decoder_close);
  lv_img_decoder_set_read_line_cb(dec, decoder_read_line);
}

#endif