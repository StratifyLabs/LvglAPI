// 3rd Party
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QVariant>
//#include <lv_examples/lv_examples.h>

#include <var.hpp>

#include <font/lv_font.h>

#include "lvgl.hpp"

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

  lvgl_api_initialize();

  font_large = &lv_font_montserrat_28;

  Font font_large(&lv_font_montserrat_28);

  Font loaded_font("S./roboto_l_36.font");

  printf("roboto font is %p\n", loaded_font.font());

  const auto tab_view = "tabview";

  Style style;

  style.set_text_font(loaded_font);

  auto screen = Container::active_screen();

  screen.add<TabView>(TabView::Create(tab_view).set_size(10_percent))
    .find(tab_view)
    .cast<TabView>()
    ->add_tab(
      "Hello", &style,
      [](Container &container, void *context) {
        Style *style = reinterpret_cast<Style *>(context);
        printf("style font is %p\n", style->style()->v_p.value1.ptr);
        container.set_layout(LV_LAYOUT_FLEX)
          .set_flex_align(FlexAlign::center, FlexAlign::center, FlexAlign::center)
          .set_flex_flow(FlexFlow::row_wrap)
          .add<Arc>(Arc::Create("Arc"))
          .add<Roller>(
            Roller::Create("roller").configure([](Roller &roller, void *) {
              roller.set_options("January\nFebruary\nMarch\nApril\nMay\nJune\nJuly\nAugust\nSeptember\nOctober\nNovember\nDecember")
                .set_visible_row_count(5).set_size(Size(LV_SIZE_CONTENT, 150));
            }))
          .add<Label>(
            Label::Create("HelloLabel1").set_context(style).configure([](Label &label, void * context) {
              Style * style = reinterpret_cast<Style*>(context);
              printf("style font is %p\n", style->style()->v_p.value1.ptr);

              label.set_text("Hello Label X").add_style(*style).update_layout();
            }))
          .add<Label>(Label::Create("HelloLabel2"))
          .add<Spinner>(Spinner::Create("Spinner").configure(
            [](Spinner &spinner, void *) { spinner.align(Alignment::center); }))
          .find("HelloLabel1")
          .cast<Label>()
          ->set_text("Hello Label 1")
          //.add_style(*style)
          ;

        container.find("HelloLabel2").cast<Label>()->set_text("Hello Label 2").set_y(100);
      })
    .add_tab("World");

#if 0
  screen.add<TabView>(TabView::Create(tab_view).set_size(10_percent).set_context(&style).set_initialize(
    [](TabView &tv, void *context) {
      tv.add_tab("Profile")
        .add_tab<Label>(
          "Analytics", Label::Create("Hello World")
                         .set_context(context)
                         .set_initialize([](Label &label, void *context) {
                           Style *style = reinterpret_cast<Style *>(context);
                           label.set_text("Hello Analytics").add_style(*style);
                         }))
        .add_tab("Shop")
        .add_content<Label>(
          0, Label::Create("ProfileLabel").set_initialize([](Label &label, void *) {
            label.set_text("Hello").align(Alignment::center);
          }))
        .add_content<Slider>(
          0, Slider::Create("slider").set_initialize([](Slider &slider, void *) {
            slider.align(Alignment::top_middle)
              .set_range(Range(0, 100))
              .add_event_callback(EventCode::value_changed, nullptr, [](lv_event_t *ev) {
                auto screen = Container::active_screen();
                Event event(ev);
                const auto range = event.target().reinterpret<Slider>()->get_range();
                const auto value = event.target().reinterpret<Slider>()->get_value();
                printf("Range is %d / %d\n", range.minimum(), range.maximum());

                screen.find("ProgressBar").reinterpret<Bar>()->set_value(value);
              });
          }))
        .add_content<Bar>(0, Bar::Create("ProgressBar").set_initialize([](Bar &bar, void *) {
                            bar.align(Alignment::bottom_middle);
                          }));
    }));
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
