
#include <cstdio>

#include <fs.hpp>
#include <printer.hpp>
#include <test/Test.hpp>
#include <var.hpp>

#include "json.hpp"

class UnitTest : public test::Test {
public:
  UnitTest(var::StringView name) : test::Test(name) {}

  class JsonChild : public JsonValue {
  public:
    JsonChild() {}

    JsonChild(const json::JsonObject &object) : json::JsonValue(object) {}
    JsonChild &set_as_object() {
      *this = JsonObject();
      m_is_valid = is_valid();
      return *this;
    }

    bool m_is_valid;
  };

  bool execute_class_api_case() {

    JsonObject object;
    TEST_ASSERT(object.is_valid());
    object = JsonObject();
    TEST_ASSERT(object.is_valid());

    JsonValue value;
    TEST_ASSERT(value.is_valid() == false);
    value = JsonObject();
    TEST_ASSERT(value.is_valid());
    TEST_ASSERT(value.is_object());

    JsonChild child;
    TEST_ASSERT(child.is_valid() == false);
    TEST_ASSERT(child.set_as_object().is_valid());
    TEST_ASSERT(child.m_is_valid);

    TEST_ASSERT_RESULT(array_case());
    TEST_ASSERT_RESULT(object_case());
    TEST_ASSERT_RESULT(value_case());
    TEST_ASSERT_RESULT(document_case());
    TEST_ASSERT_RESULT(seek_case());

    return true;
  }

  bool seek_case() {
    JsonObject test_object;

    const JsonArray array
      = JsonArray()
          .append(JsonString("test"))
          .append(JsonInteger(1))
          .append(JsonTrue())
          .append(JsonObject().insert("config", JsonString("stm32")))
          .append(JsonFalse());

    JsonObject some_object
      = JsonObject().insert("config", JsonString("name")).insert("list", array);

    test_object.insert("config", JsonString("name"))
      .insert("arch", some_object)
      .insert("other", some_object)
      .insert("another", some_object);

    printer().object("testObject", test_object);

    const DataFile json_file
      = DataFile().write(JsonDocument().stringify(test_object)).seek(0).move();

    JsonObject arch_object
      = JsonDocument()
          .seek("/arch", json_file)
          .set_flags(JsonDocument::Flags::disable_eof_check)
          .load(json_file);

    printer().object("/arch", arch_object);
    TEST_ASSERT(arch_object.at("config").to_string_view() == "name");
    TEST_ASSERT(is_success());

    json_file.seek(0);
    JsonArray arch_array = JsonDocument()
                             .seek("/arch/list", json_file)
                             .set_flags(JsonDocument::Flags::disable_eof_check)
                             .load(json_file);

    printer().object("/arch/list", arch_array);
    TEST_ASSERT(arch_array.count() == array.count());
    TEST_ASSERT(is_success());

    {
      json_file.seek(0);
      JsonObject object = JsonDocument()
                            .seek("/arch/list/[3]", json_file)
                            .set_flags(JsonDocument::Flags::disable_eof_check)
                            .load(json_file);

      TEST_ASSERT(is_success());

      printer().object("/arch/list/[3]", object);
      TEST_ASSERT(object.at("config").to_string_view() == "stm32");
    }

    {
      json_file.seek(0);
      JsonObject object = JsonDocument()
                            .seek("/other/list/[3]", json_file)
                            .set_flags(JsonDocument::Flags::disable_eof_check)
                            .load(json_file);

      TEST_ASSERT(is_success());

      printer().object("/other/list/[3]", object);
      TEST_ASSERT(object.at("config").to_string_view() == "stm32");
    }

    {
      json_file.seek(0);
      JsonObject object = JsonDocument()
                            .seek("/another/list/[3]", json_file)
                            .set_flags(JsonDocument::Flags::disable_eof_check)
                            .load(json_file);

      TEST_ASSERT(is_success());

      printer().object("/another/list/[3]", object);
      TEST_ASSERT(object.at("config").to_string_view() == "stm32");
    }

    {
      json_file.seek(0);
      JsonObject object = JsonDocument()
                            .seek("/another/list/[9]", json_file)
                            .set_flags(JsonDocument::Flags::disable_eof_check)
                            .load(json_file);

      TEST_ASSERT(is_error());
      API_RESET_ERROR();
    }

    return true;
  }

  bool array_case() {

    JsonArray array = JsonArray()
                        .append(JsonString("string"))
                        .append(JsonInteger(5))
                        .append(JsonReal(2.5f))
                        .append(JsonTrue())
                        .append(JsonFalse())
                        .append(JsonNull());

    TEST_ASSERT(array.insert(1, JsonString("at1")).at(1).to_string() == "at1");

    return true;
  }

  bool document_case() {

    {
      JsonObject object = JsonObject()
                            .insert("string", JsonString("string"))
                            .insert("integerString", JsonString("100"))
                            .insert("integer", JsonInteger(10))
                            .insert("integerZero", JsonInteger(0))
                            .insert("real", JsonReal(2.2f))
                            .insert("realString", JsonString("2.2f"))
                            .insert("realZero", JsonReal(0.0f))
                            .insert("true", JsonTrue())
                            .insert("false", JsonFalse())
                            .insert("null", JsonNull())
                            .insert("trueString", JsonString("true"))
                            .insert_bool("boolTrue", true)
                            .insert_bool("boolFalse", false)
                            .insert(
                              "array",
                              JsonArray()
                                .append(JsonString("string"))
                                .append(JsonInteger(5))
                                .append(JsonReal(2.5f))
                                .append(JsonTrue())
                                .append(JsonFalse())
                                .append(JsonNull()));

      TEST_ASSERT(JsonDocument()
                    .save(object, File(File::IsOverwrite::yes, "test.json"))
                    .is_success());

      {
        JsonObject load_object
          = JsonDocument().load(File("test.json", OpenMode::read_only()));

        TEST_ASSERT(is_success());
        TEST_ASSERT(load_object.is_object());
      }

      {
        JsonObject load_object
          = JsonDocument()
              .load(File("test2.json", OpenMode::read_only()))
              .to_object();
        API_RESET_ERROR();
        TEST_ASSERT(load_object.is_valid() == false);
        TEST_ASSERT(load_object.is_object() == false);
        TEST_ASSERT(load_object.is_empty() == true);
      }
    }
    return true;
  }

  bool value_case() {
    TEST_ASSERT(JsonString().assign("test").is_string());
    TEST_ASSERT(JsonInteger().assign("10").to_integer() == 10);
    TEST_ASSERT(JsonReal().assign("2.5").to_real() == 2.5f);
    TEST_ASSERT(JsonReal().assign("2.5f").to_real() == 2.5f);

    {
      TEST_ASSERT(JsonValue().is_valid() == false);
      TEST_ASSERT(JsonObject().is_valid() == true);
      TEST_ASSERT(JsonObject().is_object() == true);
      TEST_ASSERT(JsonArray().is_valid() == true);
      TEST_ASSERT(JsonArray().is_array() == true);
      TEST_ASSERT(JsonString().is_valid() == true);
      TEST_ASSERT(JsonString().is_string() == true);
      TEST_ASSERT(JsonInteger().is_valid() == true);
      TEST_ASSERT(JsonInteger().is_integer() == true);
      TEST_ASSERT(JsonReal().is_valid() == true);
      TEST_ASSERT(JsonReal().is_real() == true);
      TEST_ASSERT(JsonTrue().is_valid() == true);
      TEST_ASSERT(JsonTrue().is_true() == true);
      TEST_ASSERT(JsonFalse().is_valid() == true);
      TEST_ASSERT(JsonFalse().is_false() == true);
      TEST_ASSERT(JsonNull().is_valid() == true);
      TEST_ASSERT(JsonNull().is_null() == true);
    }

    return true;
  }

  bool object_case() {

    Printer::Object po(printer(), "object");
    {
      JsonObject object = JsonObject()
                            .insert("string", JsonString("string"))
                            .insert("integerString", JsonString("100"))
                            .insert("integer", JsonInteger(10))
                            .insert("integerZero", JsonInteger(0))
                            .insert("real", JsonReal(2.2f))
                            .insert("realString", JsonString("2.2f"))
                            .insert("realZero", JsonReal(0.0f))
                            .insert("true", JsonTrue())
                            .insert("false", JsonFalse())
                            .insert("null", JsonNull())
                            .insert("trueString", JsonString("true"))
                            .insert(
                              "array",
                              JsonArray()
                                .append(JsonString("string"))
                                .append(JsonInteger(5))
                                .append(JsonReal(2.5f))
                                .append(JsonTrue())
                                .append(JsonFalse())
                                .append(JsonNull()));

      const auto key_list = object.get_key_list();

      TEST_ASSERT(key_list.count() == 12);
      TEST_ASSERT(key_list.find("string") == "string");
      TEST_ASSERT(key_list.find("integerString") == "integerString");
      TEST_ASSERT(key_list.find("integer") == "integer");
      TEST_ASSERT(key_list.find("integerZero") == ("integerZero"));
      TEST_ASSERT(key_list.find("real") == "real");

      TEST_ASSERT(key_list.find("realString") == "realString");
      TEST_ASSERT(key_list.find("realZero") == "realZero");
      TEST_ASSERT(key_list.find("true") == "true");
      TEST_ASSERT(key_list.find("false") == "false");
      TEST_ASSERT(key_list.find("null") == "null");
      TEST_ASSERT(key_list.find("trueString") == "trueString");
      TEST_ASSERT(key_list.find("array") == "array");

      printer().object("object", object);

      TEST_ASSERT(object.at("string").to_cstring() == StringView("string"));
      TEST_ASSERT(object.at("string").to_string() == StringView("string"));
      TEST_ASSERT(object.at("string").to_integer() == 0);
      TEST_ASSERT(object.at("string").to_bool() == false);
      TEST_ASSERT(object.at("string").to_real() == 0.0f);
      TEST_ASSERT(object.at("integerString").to_integer() == 100);
      TEST_ASSERT(object.at("integerString").to_real() == 100.0f);
      TEST_ASSERT(object.at("integerString").to_cstring() == StringView("100"));
      TEST_ASSERT(object.at("integerString").to_string() == StringView("100"));
      TEST_ASSERT(object.at("integer").to_integer() == 10);
      TEST_ASSERT(object.at("integer").to_real() == 10.0f);
      TEST_ASSERT(object.at("real").to_real() == 2.2f);
      TEST_ASSERT(object.at("real").to_integer() == 2);
      TEST_ASSERT(object.at("realString").to_real() == 2.2f);
      TEST_ASSERT(object.at("realString").to_cstring() == StringView("2.2f"));
      TEST_ASSERT(object.at("realString").to_integer() == 2);
      TEST_ASSERT(object.at("true").to_bool() == true);
      TEST_ASSERT(object.at("false").to_bool() == false);
      TEST_ASSERT(object.at("null").to_bool() == false);
      TEST_ASSERT(object.at("trueString").to_bool() == true);
      TEST_ASSERT(object.at("string").to_bool() == false);
      TEST_ASSERT(
        object.at("array").to_array().at(0).to_cstring()
        == StringView("string"));
      TEST_ASSERT(object.at("array").to_array().at(1).to_integer() == 5);
      TEST_ASSERT(object.at("array").to_array().at(2).to_real() == 2.5f);
      TEST_ASSERT(object.at("array").to_array().at(3).to_bool() == true);
      TEST_ASSERT(object.at("array").to_array().at(4).to_bool() == false);
      TEST_ASSERT(object.at("array").to_array().at(5).is_null() == true);
    }
    return true;
  }

private:
};
