// 3rd Party
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QVariant>
//#include <lv_examples/lv_examples.h>

#include <var.hpp>

#include <font/lv_font.h>

#include "lvgl/Button.hpp"
#include "lvgl/Label.hpp"
#include "lvgl/Slider.hpp"
#include "lvgl/TabView.hpp"

// Local
#include "LvglImageProvider.hpp"
#include "LvglRenderer.hpp"

using namespace lv;

static const lv_font_t *font_large;

int main(int argc, char *argv[]) {
  QGuiApplication app(argc, argv);
  QQmlApplicationEngine engine;
  LvglRenderer lvgl;
  auto *lvgl_image_provider = new LvglImageProvider(lvgl);

  engine.addImageProvider(
    "LvglImageProvider",
    lvgl_image_provider); // engine takes ownership

  /// lvgl_sim_qt_example
  // lv_demo_widgets();

  font_large = &lv_font_montserrat_12;

  lv::Style style = lv::Style().set_text_font(font_large);

  const auto tab_view = "tabview";
  static const auto brightness_slider = "brightness";

  API_PRINTF_TRACE_LINE();
  Container::active_screen().add(
      lv::TabView(tab_view, lv::Direction::top, 70)
        .add_tab(
          "Profile",
          lv::Container("ProfileContainer")
            .set_content_size(lv::Size(50_percent, 50_percent))
            .add(lv::Button(brightness_slider)
                   .add(lv::Label("buttonLabel")
                          .set_text("Button")
                          .set_alignment(Alignment::center))
                   .add_event_callback(
                     lv::EventCode::value_changed, nullptr,
                     [](lv_event_t *event) {
                       const auto value =
                         lv::Event(event).target().reinterpret<lv::Slider>()->get_value();
                       printf("slider value changed %d\n", value);

                       Container::active_screen()
                         .find_child("Hello1")
                         .reinterpret<lv::Label>()
                         ->set_text(var::NumberString(value).cstring());
                     }))
            .add(
              lv::Label("Hello1").set_text("Hello2").add_style(style).set_y(50_percent)))
        .add_tab("Analytics", lv::Label("Hello2").set_text("Hello2").add_style(style))
        .add_tab("Shopping", lv::Label("Hello3").set_text("Hello3").add_style(style)));
  API_PRINTF_TRACE_LINE();

  printf("Hello1 is %p\n", Container::active_screen().find_child("Hello1").object());
  printf("hello1 y is %d\n", Container::active_screen().find_child("Hello1").get_y());

  Container::active_screen().find_child(tab_view).reinterpret<TabView>()->get_tab(1).add(
    lv::Button("Hello5")
      .add_style(style)
      .set_y(10_percent)
      .set_size(Size(50_percent, 50_percent))
      .add_event_callback(lv::EventCode::clicked, nullptr, [](lv_event_t *event) {
        lv::Event(event).target().reinterpret<Button>()->set_y(100);
      }));
  API_PRINTF_TRACE_LINE();

#if 0
  lv::TabView tv(screen, lv::Direction::top, 70);

  // auto *tv = lv_tabview_create(lv_scr_act(), LV_DIR_TOP, 70);
  lv::ButtonMatrix tab_buttons = tv.get_tab_buttons();

  tv.add_tab("Profile").add_tab("Analytics").add_tab("Shop");

  lv::Object tab0 = tv.get_tab(0);

  lv::Style style = lv::Style().set_text_font(font_large);
  lv::Label panel_title =
      lv::Label(tab0).set_text("Hello World").add_style(style);
#endif
  const QUrl url(QStringLiteral("qrc:/main.qml"));
  engine.load(url);
  auto *window = qobject_cast<QQuickWindow *>(engine.rootObjects().value(0, nullptr));
  if (window == nullptr) {
    EXIT_FAILURE;
  }
  window->setProperty("width", QVariant(LvglRenderer::max_width));
  window->setProperty("height", QVariant(LvglRenderer::max_height));

  auto *timer = window->findChild<QObject *>("timer");
  timer->setProperty("interval", LvglRenderer::tick_perios_ms);

  lvgl_image_provider->setMouseArea(window->findChild<QObject *>("mouseArea"));

  return app.exec();
}
