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
        container.set_layout(LV_LAYOUT_FLEX)
          .set_flex_align(FlexAlign::center, FlexAlign::center, FlexAlign::center)
          .set_flex_flow(FlexFlow::row_wrap)
          .add<Meter>(Meter::Create("Meter").configure([](Meter &meter, void *) {
            meter.remove_style(Part::indicator);
            auto scale0 = meter.add_scale();
            meter
              .set_size(Size(200,200))
              .set_scale_ticks(
                scale0, Meter::Tick().set_count(11).set_width(2).set_length(30).set_color(
                          Color::get_palette(Palette::grey)))
              .set_scale_major_ticks(
                scale0, Meter::Tick()
                          .set_skip_minor_count(2)
                          .set_label_gap(40)
                          .set_length(10)
                          .set_color(Color::get_palette(
                            Palette::grey)))
              .set_scale_range(scale0, Meter::ScaleRange());

            auto indicator0 = meter.add_arc(scale0, 10, Color::get_palette(Palette::green), 0);

            meter.set_indicator_end_value(indicator0, 50);

          }))
          .add<Calendar>(Calendar::Create("Calendar"))
          .add<Arc>(Arc::Create("Arc"))
          .add<Bar>(
            Bar::Create("Bar").configure([](Bar &bar, void *) { bar.set_width(75); }))
          .add<Roller>(Roller::Create("roller").configure([](Roller &roller, void *) {
            roller
              .set_options(
                "January\nFebruary\nMarch\nApril\nMay\nJune\nJuly\nAugust\nSeptember\nOctober\nNovember\nDecember")
              .set_visible_row_count(5)
              .set_size(Size(LV_SIZE_CONTENT, 150));
          }))
          .add<Label>(
            Label::Create("HelloLabel1")
              .configure(
                style,
                [](Label &label, void *context) {
                  Style *style = reinterpret_cast<Style *>(context);
                  label.set_text("Hello Label X").add_style(*style).update_layout();
                }))
          .add<Label>(Label::Create("HelloLabel2"))
          .add<Spinner>(Spinner::Create("Spinner").configure(
            [](Spinner &spinner, void *) { spinner.align(Alignment::center); }))
          .add<Slider>(Slider::Create("Slider").configure([](Slider &slider, void *) {
            slider.set_height(12).set_width(150).add_event_callback(
              EventCode::value_changed, nullptr, [](lv_event_t *ev) {
                const auto value = Event(ev).target().cast<Slider>()->get_value();
                Container::active_screen().find("Bar").cast<Bar>()->set_value(value);
              });
          }));

        container.find("HelloLabel2").cast<Label>()->set_text("Hello Label 2").set_y(100);
      })
    .add_tab(
      "KeyboardTab",
      [](Container &container) {
        container
          .add<TextArea>(
            TextArea::Create("TextArea").configure([](TextArea &text_area, void *) {
              text_area.set_size(Size(100_percent, 50_percent));
            }))
          .add<Keyboard>(
            Keyboard::Create("Keyboard").configure([](Keyboard &keyboard, void *) {
              auto text_area = *(keyboard.get_parent().find("TextArea").cast<TextArea>());
              keyboard.set_text_area(text_area);
            }));
      })
    .add_tab("ChartTab", [](Container &container) {
      container.add<Chart>(Chart::Create("Chart").configure([](Chart &chart, void *) {
        chart.set_size(Size(100_percent, 100_percent)).set_type(Chart::Type::bar);
        auto series = chart.add_series(
          Color::get_palette(Palette::amber), Chart::Axis::primary_y);
        chart.set_point_count(10)
          .set_next_value(series, 5)
          .set_next_value(series, 10)
          .set_next_value(series, 15)
          .set_next_value(series, 3)
          .set_next_value(series, 20)
          .set_next_value(series, 8)
          .set_next_value(series, 11)
          .set_x_start_point(series, 0);
      }));
    });

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
