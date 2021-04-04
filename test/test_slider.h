// The latest version of this library is available on GitHub;
// https://github.com/jjsheets/FacadeUI

// This is free and unencumbered software released into the public domain.
//
// Anyone is free to copy, modify, publish, use, compile, sell, or
// distribute this software, either in source code form or as a compiled
// binary, for any purpose, commercial or non-commercial, and by any
// means.
//
// In jurisdictions that recognize copyright laws, the author or authors
// of this software dedicate any and all copyright interest in the
// software to the public domain. We make this dedication for the benefit
// of the public at large and to the detriment of our heirs and
// successors. We intend this dedication to be an overt act of
// relinquishment in perpetuity of all present and future rights to this
// software under copyright law.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
// OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.
//
// For more information, please refer to <http://unlicense.org/>

#ifndef FACADE_TEST_SLIDER_H_INCLUDED
#define FACADE_TEST_SLIDER_H_INCLUDED

UTEST(slider, noRenderer) {
  facade::init(2560);
  bool exceptionThrown = false;
  // Initialization complete
  facade::preFrame();
  facade::beginLayout(10, 15, 160);
    try {
      facade::slider("test", facade::slider_type::horizontal, 0.0, 100.0, 0.0);
    } catch (...) {
      exceptionThrown = true;
    }
    ASSERT_TRUE(exceptionThrown);
}

UTEST(slider, defaultRenderer) {
  facade::init(2560);
  bool rendered = false;
  facade::setDefaultSliderRenderer(
    [&](facade::slider_type type, int x, int y, int w, int l, double val, facade::display_state displayState) {
      rendered = true;
    }
  );
  // Initialization complete
  facade::preFrame();
  facade::beginLayout(10, 15, 160);
    facade::slider("test", facade::slider_type::horizontal, 0.0, 100.0, 0.0);
    ASSERT_TRUE(rendered);
}

UTEST(slider, sliderRenderer) {
  facade::init(2560);
  bool rendered = false;
  // Initialization complete
  facade::preFrame();
  facade::beginLayout(10, 15, 160);
    facade::slider("test", facade::slider_type::horizontal, 0.0, 100.0, 0.0,
      [&](facade::slider_type type, int x, int y, int w, int l, double val, facade::display_state displayState) {
        rendered = true;
      }
    );
    ASSERT_TRUE(rendered);
}

UTEST(slider, sliderRendererParameters) {
  facade::init(2560);
  // Initialization complete
  facade::preFrame();
  facade::beginLayout(10, 15, 160);
    facade::slider("test", facade::slider_type::horizontal, 0.0, 100.0, 0.0,
      [&](facade::slider_type type, int x, int y, int w, int l, double val, facade::display_state displayState) {
        ASSERT_TRUE(type == facade::slider_type::horizontal);
        ASSERT_EQ(x, 10);
        ASSERT_EQ(y, 15);
        ASSERT_EQ(w, 20);
        ASSERT_EQ(l, 160);
        ASSERT_EQ(val, 0.0);
      }
    );
  facade::endLayout();
  facade::postFrame();

  facade::preFrame();
  facade::beginLayout(10, 15, 160);
    facade::slider("test", facade::slider_type::vertical, 0.0, 100.0, 0.0,
      [&](facade::slider_type type, int x, int y, int w, int l, double val, facade::display_state displayState) {
        ASSERT_TRUE(type == facade::slider_type::vertical);
        ASSERT_EQ(x, 10);
        ASSERT_EQ(y, 15);
        ASSERT_EQ(w, 20);
        ASSERT_EQ(l, 160);
        ASSERT_EQ(val, 0.0);
      }
    );
}

UTEST(slider, sliderEnabled) {
  facade::init(2560);
  // Initialization complete
  facade::setMouseXY(5, 5);
  facade::preFrame();
  facade::beginLayout(10, 15, 160);
    facade::slider("test", facade::slider_type::horizontal, 0.0, 100.0, 0.0,
      [&](facade::slider_type type, int x, int y, int w, int l, double val, facade::display_state displayState) {
        ASSERT_TRUE(displayState == facade::display_state::enabled);
      }
    );
}

UTEST(slider, sliderHovered) {
  facade::init(2560);
  // Initialization complete
  facade::setMouseXY(80, 25);
  facade::preFrame();
  facade::beginLayout(10, 15, 160);
    facade::slider("test", facade::slider_type::horizontal, 0.0, 100.0, 0.0,
      [&](facade::slider_type type, int x, int y, int w, int l, double val, facade::display_state displayState) {
        ASSERT_TRUE(displayState == facade::display_state::hovered);
      }
    );
  facade::endLayout();
  facade::postFrame();

  facade::preFrame();
  facade::beginLayout(10, 15, 160);
    facade::slider("test", facade::slider_type::vertical, 0.0, 100.0, 0.0,
      [&](facade::slider_type type, int x, int y, int w, int l, double val, facade::display_state displayState) {
        ASSERT_FALSE(displayState == facade::display_state::hovered);
      }
    );
  facade::endLayout();
  facade::postFrame();

  facade::setMouseXY(20, 85);
  facade::preFrame();
  facade::beginLayout(10, 15, 160);
    facade::slider("test", facade::slider_type::horizontal, 0.0, 100.0, 0.0,
      [&](facade::slider_type type, int x, int y, int w, int l, double val, facade::display_state displayState) {
        ASSERT_FALSE(displayState == facade::display_state::hovered);
      }
    );
  facade::endLayout();
  facade::postFrame();

  facade::preFrame();
  facade::beginLayout(10, 15, 160);
    facade::slider("test", facade::slider_type::vertical, 0.0, 100.0, 0.0,
      [&](facade::slider_type type, int x, int y, int w, int l, double val, facade::display_state displayState) {
        ASSERT_TRUE(displayState == facade::display_state::hovered);
      }
    );
}

UTEST(slider, sliderPressed) {
  facade::init(2560);
  // Initialization complete
  facade::setMouseXY(80, 25);
  facade::preFrame();
    facade::beginLayout(10, 15, 160);
    facade::slider("test", facade::slider_type::horizontal, 0.0, 100.0, 0.0,
      [&](facade::slider_type type, int x, int y, int w, int l, double val, facade::display_state displayState) {
      }
    );
  facade::endLayout();
  facade::postFrame();

  facade::setLeftMouseButton(true);
  facade::preFrame();
  facade::beginLayout(10, 15, 160);
    facade::slider("test", facade::slider_type::horizontal, 0.0, 100.0, 0.0,
      [&](facade::slider_type type, int x, int y, int w, int l, double val, facade::display_state displayState) {
        ASSERT_TRUE(displayState == facade::display_state::pressed);
      }
    );
    facade::endLayout();
  facade::postFrame();

  facade::setMouseXY(20, 85);
  facade::preFrame();
  facade::beginLayout(10, 15, 160);
    facade::slider("test", facade::slider_type::horizontal, 0.0, 100.0, 0.0,
      [&](facade::slider_type type, int x, int y, int w, int l, double val, facade::display_state displayState) {
        ASSERT_TRUE(displayState == facade::display_state::pressed);
      }
    );
}

UTEST(slider, sliderFunctionality) {
  facade::init(2560);
  auto val = 50.0;
  auto renderer = [&](facade::slider_type type, int x, int y, int w, int l, double val, facade::display_state displayState) {};
  // Initialization complete
  facade::setMouseXY(5, 25);
  facade::preFrame();
    facade::beginLayout(10, 15, 160);
    val = facade::slider("test", facade::slider_type::horizontal, 50.0, 100.0, val, renderer);
    ASSERT_EQ(50.0, val);
  facade::endLayout();
  facade::postFrame();

  facade::setMouseXY(90, 25);
  facade::preFrame();
  facade::beginLayout(10, 15, 160);
    val = facade::slider("test", facade::slider_type::horizontal, 50.0, 100.0, val, renderer);
    ASSERT_EQ(50.0, val);
  facade::endLayout();
  facade::postFrame();

  facade::setLeftMouseButton(true);
  facade::preFrame();
  facade::beginLayout(10, 15, 160);
    val = facade::slider("test", facade::slider_type::horizontal, 50.0, 100.0, val, renderer);
    ASSERT_EQ(75.0, val);
  facade::endLayout();
  facade::postFrame();

  facade::setMouseXY(5, 25);
  facade::preFrame();
  facade::beginLayout(10, 15, 160);
    val = facade::slider("test", facade::slider_type::horizontal, 50.0, 100.0, val, renderer);
    ASSERT_EQ(50.0, val);
  facade::endLayout();
  facade::postFrame();

  facade::setMouseXY(500, 25);
  facade::preFrame();
  facade::beginLayout(10, 15, 160);
    val = facade::slider("test", facade::slider_type::horizontal, 50.0, 100.0, val, renderer);
    ASSERT_EQ(100.0, val);
  facade::endLayout();
  facade::postFrame();

  facade::setMouseXY(20, 25);
  facade::preFrame();
  facade::beginLayout(10, 15, 160);
    val = facade::slider("test", facade::slider_type::horizontal, 50.0, 100.0, val, renderer);
    ASSERT_EQ(50.0, val);
  facade::endLayout();
  facade::postFrame();

  facade::setMouseXY(21, 25);
  facade::preFrame();
  facade::beginLayout(10, 15, 160);
    val = facade::slider("test", facade::slider_type::horizontal, 50.0, 100.0, val, renderer);
    ASSERT_EQ(50.0 + 0.5 / 1.4, val);
  facade::endLayout();
  facade::postFrame();

  facade::setMouseXY(159, 25);
  facade::preFrame();
  facade::beginLayout(10, 15, 160);
    val = facade::slider("test", facade::slider_type::horizontal, 50.0, 100.0, val, renderer);
    ASSERT_EQ(100.0 - 0.5 / 1.4, val);
  facade::endLayout();
  facade::postFrame();

  facade::setMouseXY(160, 25);
  facade::preFrame();
  facade::beginLayout(10, 15, 160);
    val = facade::slider("test", facade::slider_type::horizontal, 50.0, 100.0, val, renderer);
    ASSERT_EQ(100.0, val);
}

#endif // FACADE_TEST_SLIDER_H_INCLUDED
