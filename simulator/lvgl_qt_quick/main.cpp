// 3rd Party
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QVariant>
//#include <lv_examples/lv_examples.h>

#include <font/lv_font.h>

#include "lvgl/Label.hpp"
#include "lvgl/Slider.hpp"
#include "lvgl/TabView.hpp"

// Local
#include "LvglImageProvider.hpp"
#include "LvglRenderer.hpp"

static const lv_font_t *font_large;

int main(int argc, char *argv[]) {
  QGuiApplication app(argc, argv);
  QQmlApplicationEngine engine;
  LvglRenderer lvgl;
  auto *lvgl_image_provider = new LvglImageProvider(lvgl);

  engine.addImageProvider("LvglImageProvider",
                          lvgl_image_provider); // engine takes ownership

  /// lvgl_sim_qt_example
  // lv_demo_widgets();

  font_large = &lv_font_montserrat_12;

  lv::Style style = lv::Style().set_text_font(font_large);

  lv::Object(lv_scr_act())
      .add(lv::TabView(lv::Direction::top, 70)
               .add_tab(
                   "Profile",
                   lv::Container()
                       .set_content_height(lv_pct(50))
                       .set_content_width(lv_pct(50))

                       .add(lv::Slider(lv::Object())
                                .set_width(400)
                                .set_height(12)
                                .set_x(200))
                       .add(lv::Label().set_text("Hello2").add_style(style).set_y(100)))
               .add_tab("Analytics",
                        lv::Label().set_text("Hello2").add_style(style))
               .add_tab("Shopping",
                        lv::Label().set_text("Hello3").add_style(style)));

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
  auto *window =
      qobject_cast<QQuickWindow *>(engine.rootObjects().value(0, nullptr));
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