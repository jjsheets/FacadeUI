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

#ifndef FACADE_TEST_CHECKBOX_H_INCLUDED
#define FACADE_TEST_CHECKBOX_H_INCLUDED

UTEST(checkbox, noRenderer) {
  facade::init(2560);
  facade::initCheckbox();
  bool exceptionThrown = false;
  bool val = false;
  // Initialization complete
  facade::preFrame();
  try {
    facade::checkbox(u8"test", u8"Checkbox Label", 10, 15, 80, 20, val);
  } catch (...) {
    exceptionThrown = true;
  }
  ASSERT_TRUE(exceptionThrown);
}

UTEST(checkbox, defaultRenderer) {
  facade::init(2560);
  facade::initCheckbox();
  bool rendered = false;
  bool val = false;
  // Initialization complete
  facade::preFrame();
  facade::setDefaultCheckboxRenderer(
    [&](std::u8string label, int x, int y, int w, int h, bool val, facade::display_state displayState) {
      rendered = true;
    }
  );
  facade::checkbox(u8"test", u8"Checkbox Label", 10, 15, 80, 20, val);
  ASSERT_TRUE(rendered);
}

UTEST(checkbox, checkboxRenderer) {
  facade::init(2560);
  facade::initCheckbox();
  bool rendered = false;
  bool val = false;
  // Initialization complete
  facade::preFrame();
  facade::checkbox(u8"test", u8"Checkbox Label", 10, 15, 80, 20, val, false,
    [&](std::u8string label, int x, int y, int w, int h, bool val, facade::display_state displayState) {
      rendered = true;
    }
  );
  ASSERT_TRUE(rendered);
}

UTEST(checkbox, checkboxRendererParameters) {
  facade::init(2560);
  facade::initCheckbox();
  bool val = false;
  // Initialization complete
  facade::preFrame();
  facade::checkbox(u8"test", u8"Checkbox Label", 10, 15, 80, 20, val, false,
    [&](std::u8string label, int x, int y, int w, int h, bool val, facade::display_state displayState) {
      ASSERT_TRUE(label == u8"Checkbox Label");
      ASSERT_EQ(x, 10);
      ASSERT_EQ(y, 15);
      ASSERT_EQ(w, 80);
      ASSERT_EQ(h, 20);
      ASSERT_FALSE(val);
    }
  );
}

UTEST(checkbox, checkboxEnabled) {
  facade::init(2560);
  facade::initCheckbox();
  bool val = false;
  // Initialization complete
  facade::setMouseXY(5, 5);
  facade::preFrame();
  facade::checkbox(u8"test", u8"Checkbox Label", 10, 15, 80, 20, val, false,
    [&](std::u8string label, int x, int y, int w, int h, bool val, facade::display_state displayState) {
      ASSERT_TRUE(displayState == facade::display_state::enabled);
    }
  );
}

UTEST(checkbox, checkboxHover) {
  facade::init(2560);
  facade::initCheckbox();
  bool val = false;
  // Initialization complete
  facade::setMouseXY(15, 20);
  facade::preFrame();
  facade::checkbox(u8"test", u8"Checkbox Label", 10, 15, 80, 20, val, false,
    [&](std::u8string label, int x, int y, int w, int h, bool val, facade::display_state displayState) {
      ASSERT_TRUE(displayState == facade::display_state::hovered);
    }
  );
}

UTEST(checkbox, checkboxPressed) {
  facade::init(2560);
  facade::initCheckbox();
  bool val = false;
  // Initialization complete
  facade::setMouseXY(15, 20);
  facade::preFrame();
  facade::checkbox(u8"test", u8"Checkbox Label", 10, 15, 80, 20, val, false,
    [&](std::u8string label, int x, int y, int w, int h, bool val, facade::display_state displayState) {
    }
  );
  facade::postFrame();

  facade::setLeftMouseButton(true);
  facade::preFrame();
  facade::checkbox(u8"test", u8"Checkbox Label", 10, 15, 80, 20, val, false,
    [&](std::u8string label, int x, int y, int w, int h, bool val, facade::display_state displayState) {
      ASSERT_TRUE(displayState == facade::display_state::pressed);
    }
  );
  facade::postFrame();

  // Make sure the button stays pressed even after moving the mouse out of the button boundary
  facade::setMouseXY(5, 5);
  facade::preFrame();
  facade::checkbox(u8"test", u8"Checkbox Label", 10, 15, 80, 20, val, false,
    [&](std::u8string label, int x, int y, int w, int h, bool val, facade::display_state displayState) {
      ASSERT_TRUE(displayState == facade::display_state::pressed);
    }
  );
}

UTEST(checkbox, checkboxDisabled) {
  facade::init(2560);
  facade::initCheckbox();
  bool val = false;
  // Initialization complete
  facade::checkbox(u8"test", u8"Checkbox Label", 10, 15, 80, 20, val, true,
    [&](std::u8string label, int x, int y, int w, int h, bool val, facade::display_state displayState) {
      ASSERT_TRUE(displayState == facade::display_state::disabled);
    }
  );
}

UTEST(checkbox, checkboxClicked) {
  facade::init(2560);
  facade::initCheckbox();
  auto renderer = [&](std::u8string label, int x, int y, int w, int h, bool val, facade::display_state displayState) {};
  bool val = false;
  // Initialization complete
  facade::setMouseXY(15, 20);
  facade::preFrame();
  val = facade::checkbox(u8"test", u8"Checkbox Label", 10, 15, 80, 20, val, false, renderer);
  facade::postFrame();

  facade::setLeftMouseButton(true);
  facade::preFrame();
  val = facade::checkbox(u8"test", u8"Checkbox Label", 10, 15, 80, 20, val, false, renderer);
  facade::postFrame();

  facade::setLeftMouseButton(false);
  facade::preFrame();
  val = facade::checkbox(u8"test", u8"Checkbox Label", 10, 15, 80, 20, val, false, renderer);
  ASSERT_TRUE(val);
  facade::postFrame();

  facade::setLeftMouseButton(true);
  facade::preFrame();
  val = facade::checkbox(u8"test", u8"Checkbox Label", 10, 15, 80, 20, val, false, renderer);
  facade::postFrame();

  facade::setLeftMouseButton(false);
  facade::preFrame();
  val = facade::checkbox(u8"test", u8"Checkbox Label", 10, 15, 80, 20, val, false, renderer);
  ASSERT_FALSE(val);
}

#endif // FACADE_TEST_CHECKBOX_H_INCLUDED
