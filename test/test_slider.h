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
  facade::init();
  facade::initSlider();
  bool exceptionThrown = false;
  // Initialization complete
  facade::preFrame();
  try {
    facade::slider(u8"test", facade::slider_type::horizontal, 10, 15, 20, 160, 0.0, 100.0, 0.0);
  } catch (...) {
    exceptionThrown = true;
  }
  ASSERT_TRUE(exceptionThrown);
}

UTEST(slider, defaultRenderer) {
  facade::init();
  facade::initSlider();
  bool rendered = false;
  // Initialization complete
  facade::preFrame();
  facade::setDefaultSliderRenderer(
    [&](facade::slider_type type, int x, int y, int w, int l, double val, facade::display_state displayState) {
      rendered = true;
    }
  );
  facade::slider(u8"test", facade::slider_type::horizontal, 10, 15, 20, 160, 0.0, 100.0, 0.0);
  ASSERT_TRUE(rendered);
}

UTEST(slider, sliderRenderer) {
  facade::init();
  facade::initSlider();
  bool rendered = false;
  // Initialization complete
  facade::preFrame();
  facade::slider(u8"test", facade::slider_type::horizontal, 10, 15, 20, 160, 0.0, 100.0, 0.0,
    [&](facade::slider_type type, int x, int y, int w, int l, double val, facade::display_state displayState) {
      rendered = true;
    }
  );
  ASSERT_TRUE(rendered);
}

UTEST(slider, sliderRendererParameters) {
  facade::init();
  facade::initSlider();
  // Initialization complete
  facade::preFrame();
  facade::slider(u8"test", facade::slider_type::horizontal, 10, 15, 20, 160, 0.0, 100.0, 0.0,
    [&](facade::slider_type type, int x, int y, int w, int l, double val, facade::display_state displayState) {
      ASSERT_TRUE(type == facade::slider_type::horizontal);
      ASSERT_EQ(x, 10);
      ASSERT_EQ(y, 15);
      ASSERT_EQ(w, 20);
      ASSERT_EQ(l, 160);
      ASSERT_EQ(val, 0.0);
    }
  );
}

UTEST(slider, sliderEnabled) {
  facade::init();
  facade::initSlider();
  // Initialization complete
  facade::setMouseXY(5, 5);
  facade::preFrame();
  facade::slider(u8"test", facade::slider_type::horizontal, 10, 15, 20, 160, 0.0, 100.0, 0.0,
    [&](facade::slider_type type, int x, int y, int w, int l, double val, facade::display_state displayState) {
      ASSERT_TRUE(displayState == facade::display_state::enabled);
    }
  );
}

#endif // FACADE_TEST_SLIDER_H_INCLUDED
