#ifndef JANSSON_API_H
#define JANSSON_API_H

#include <sdk/api.h>

#include "jansson.h"

#ifdef __cplusplus
extern "C" {
#endif

#define JANSSON_API_T 1

typedef struct {
  api_t sos_api;
  json_t *(*create_object)();
  json_t *(*create_array)();
  json_t *(*create_string)(const char *value);
  json_t *(*create_stringn)(const char *value, size_t len);
  json_t *(*create_string_nocheck)(const char *value);
  json_t *(*create_stringn_nocheck)(const char *value, size_t len);
  json_t *(*create_integer)(json_int_t value);
  json_t *(*create_real)(double value);
  json_t *(*create_true)();
  json_t *(*create_false)();
  json_t *(*create_null)();

  void (*remove)(json_t *json);

  /* getters, setters, manipulation */

  void (*object_seed)(size_t seed);
  size_t (*object_size)(const json_t *object);
  json_t *(*object_get)(const json_t *object, const char *key);
  int (*object_set)(json_t *object, const char *key, json_t *value);
  int (*object_del)(json_t *object, const char *key);
  int (*object_clear)(json_t *object);
  int (*object_update)(json_t *object, json_t *other);
  int (*object_update_existing)(json_t *object, json_t *other);
  int (*object_update_missing)(json_t *object, json_t *other);
  void *(*object_iter)(json_t *object);
  void *(*object_iter_at)(json_t *object, const char *key);
  void *(*object_key_to_iter)(const char *key);
  void *(*object_iter_next)(json_t *object, void *iter);
  const char *(*object_iter_key)(void *iter);
  json_t *(*object_iter_value)(void *iter);
  int (*object_iter_set_new)(json_t *object, void *iter, json_t *value);

  size_t (*array_size)(const json_t *array);
  json_t *(*array_get)(const json_t *array, size_t index);
  int (*array_set)(json_t *array, size_t index, json_t *value);
  int (*array_append)(json_t *array, json_t *value);
  int (*array_insert)(json_t *array, size_t index, json_t *value);
  int (*array_remove)(json_t *array, size_t index);
  int (*array_clear)(json_t *array);
  int (*array_extend)(json_t *array, json_t *other);

  const char *(*string_value)(const json_t *string);
  size_t (*string_length)(const json_t *string);
  json_int_t (*integer_value)(const json_t *integer);
  double (*real_value)(const json_t *real);
  double (*number_value)(const json_t *json);

  int (*string_set)(json_t *string, const char *value);
  int (*string_setn)(json_t *string, const char *value, size_t len);
  int (*string_set_nocheck)(json_t *string, const char *value);
  int (*string_setn_nocheck)(json_t *string, const char *value, size_t len);
  int (*integer_set)(json_t *integer, json_int_t value);
  int (*real_set)(json_t *real, double value);

  /* pack, unpack */

  json_t *(*pack)(const char *fmt, ...);
  json_t *(*pack_ex)(json_error_t *error, size_t flags, const char *fmt, ...);
  json_t *(
    *vpack_ex)(json_error_t *error, size_t flags, const char *fmt, va_list ap);

  int (*unpack)(json_t *root, const char *fmt, ...);
  int (*unpack_ex)(
    json_t *root,
    json_error_t *error,
    size_t flags,
    const char *fmt,
    ...);
  int (*vunpack_ex)(
    json_t *root,
    json_error_t *error,
    size_t flags,
    const char *fmt,
    va_list ap);

  /* sprintf */

  json_t *(*sprintf)(const char *fmt, ...);
  json_t *(*vsprintf)(const char *fmt, va_list ap);

  /* equality */

  int (*equal)(const json_t *value1, const json_t *value2);

  /* copying */

  json_t *(*copy)(json_t *value);
  json_t *(*deep_copy)(const json_t *value);

  /* decoding */

  json_t *(*loads)(const char *input, size_t flags, json_error_t *error);
  json_t *(*loadb)(
    const char *buffer,
    size_t buflen,
    size_t flags,
    json_error_t *error);
  json_t *(*loadf)(FILE *input, size_t flags, json_error_t *error);
  json_t *(*loadfd)(int input, size_t flags, json_error_t *error);
  json_t *(*load_file)(const char *path, size_t flags, json_error_t *error);
  json_t *(*load_callback)(
    json_load_callback_t callback,
    void *data,
    size_t flags,
    json_error_t *error);

  /* encoding */

  char *(*dumps)(const json_t *json, size_t flags);
  size_t (*dumpb)(const json_t *json, char *buffer, size_t size, size_t flags);
  int (*dumpf)(const json_t *json, FILE *output, size_t flags);
  int (*dumpfd)(const json_t *json, int output, size_t flags);
  int (*dump_file)(const json_t *json, const char *path, size_t flags);
  int (*dump_callback)(
    const json_t *json,
    json_dump_callback_t callback,
    void *data,
    size_t flags);

  /* utility */
  void (*decref)(json_t *json);
  void (*decrefp)(json_t **json);
  json_t *(*incref)(json_t *json);

} jansson_api_t;

extern const jansson_api_t jansson_api;

#if defined __link
#define JANSSON_API_REQUEST &jansson_api
#else
enum {
	JANSSON_API_REQUEST = MCU_API_REQUEST_CODE('j','s','o','n')
};
#endif

#ifdef __cplusplus
}
#endif

#endif // JANSSON_API_H
