// 3rd Party
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QVariant>
//#include <lv_examples/lv_examples.h>

#include <font/lv_font.h>

#include "lvgl/TabView.hpp"

// Local
#include "LvglImageProvider.hpp"
#include "LvglRenderer.hpp"

static lv_style_t style_title;
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

  lv::Object screen(lv_scr_act());
  lv::TabView tv(screen, lv::Direction::top, 70);

  // auto *tv = lv_tabview_create(lv_scr_act(), LV_DIR_TOP, 70);
  lv_obj_t *tab_btns = lv_tabview_get_tab_btns(tv.object());

  tv.add_tab("Profile").add_tab("Analytics").add_tab("Shop");

#if 0
  lv_obj_t *t1 = lv_tabview_add_tab(tv.object(), "Profile");
  lv_obj_t *t2 = lv_tabview_add_tab(tv.object(), "Analytics");
  lv_obj_t *t3 = lv_tabview_add_tab(tv.object(), "Shop");
#endif

  lv_style_init(&style_title);
  lv_style_set_text_font(&style_title, font_large);

  //lv_obj_t *panel2_title = lv_label_create(t1);
  //lv_label_set_text(panel2_title, "Your profile");
  //lv_obj_add_style(panel2_title, &style_title, 0);

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
