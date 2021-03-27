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

#ifndef FACADE_TEST_BUTTON_H_INCLUDED
#define FACADE_TEST_BUTTON_H_INCLUDED

UTEST(button, noRenderer) {
  facade::init();
  facade::initButton();
  bool exceptionThrown = false;
  // Initialization complete
  facade::preFrame();
  try {
    facade::button(u8"test", u8"Button Label", 10, 15, 80, 20);
  } catch (...) {
    exceptionThrown = true;
  }
  ASSERT_TRUE(exceptionThrown);
}

UTEST(button, defaultRenderer) {
  facade::init();
  facade::initButton();
  bool rendered = false;
  // Initialization complete
  facade::preFrame();
  facade::setDefaultButtonRenderer(
    [&](std::u8string label, int x, int y, int w, int h, facade::button_display_state buttonState) {
      rendered = true;
    }
  );
  facade::button(u8"test", u8"Button Label", 10, 15, 80, 20);
  ASSERT_TRUE(rendered);
}

UTEST(button, buttonRenderer) {
  facade::init();
  facade::initButton();
  bool rendered = false;
  // Initialization complete
  facade::preFrame();
  facade::button(u8"test", u8"Button Label", 10, 15, 80, 20, false,
    [&](std::u8string label, int x, int y, int w, int h, facade::button_display_state buttonState) {
      rendered = true;
    }
  );
  ASSERT_TRUE(rendered);
}

UTEST(button, buttonRendererParameters) {
  facade::init();
  facade::initButton();
  bool rendered = false;
  // Initialization complete
  facade::preFrame();
  facade::button(u8"test", u8"Button Label", 10, 15, 80, 20, false,
    [&](std::u8string label, int x, int y, int w, int h, facade::button_display_state buttonState) {
      ASSERT_TRUE(label == u8"Button Label");
      ASSERT_EQ(x, 10);
      ASSERT_EQ(y, 15);
      ASSERT_EQ(w, 80);
      ASSERT_EQ(h, 20);
    }
  );
}

UTEST(button, buttonEnabled) {
  facade::init();
  facade::initButton();
  // Initialization complete
  facade::setMouseXY(5, 5);
  facade::preFrame();
  facade::button(u8"test", u8"Button Label", 10, 15, 80, 20, false,
    [&](std::u8string label, int x, int y, int w, int h, facade::button_display_state buttonState) {
      ASSERT_TRUE(buttonState == facade::button_display_state::enabled);
    }
  );
}

UTEST(button, buttonHover) {
  facade::init();
  facade::initButton();
  // Initialization complete
  facade::setMouseXY(15, 20);
  facade::preFrame();
  facade::button(u8"test", u8"Button Label", 10, 15, 80, 20, false,
    [&](std::u8string label, int x, int y, int w, int h, facade::button_display_state buttonState) {
      ASSERT_TRUE(buttonState == facade::button_display_state::hovered);
    }
  );
}

UTEST(button, buttonPressed) {
  facade::init();
  facade::initButton();
  // Initialization complete
  facade::setMouseXY(15, 20);
  facade::preFrame();
  facade::button(u8"test", u8"Button Label", 10, 15, 80, 20, false,
    [&](std::u8string label, int x, int y, int w, int h, facade::button_display_state buttonState) {
    }
  );
  facade::postFrame();

  facade::setLeftMouseButton(true);
  facade::preFrame();
  facade::button(u8"test", u8"Button Label", 10, 15, 80, 20, false,
    [&](std::u8string label, int x, int y, int w, int h, facade::button_display_state buttonState) {
      ASSERT_TRUE(buttonState == facade::button_display_state::pressed);
    }
  );
  facade::postFrame();

  // Make sure the button stays pressed even after moving the mouse out of the button boundary
  facade::setMouseXY(5, 5);
  facade::preFrame();
  facade::button(u8"test", u8"Button Label", 10, 15, 80, 20, false,
    [&](std::u8string label, int x, int y, int w, int h, facade::button_display_state buttonState) {
      ASSERT_TRUE(buttonState == facade::button_display_state::pressed);
    }
  );
}

UTEST(button, buttonDisabled) {
  facade::init();
  facade::initButton();
  // Initialization complete
  facade::button(u8"test", u8"Button Label", 10, 15, 80, 20, true,
    [&](std::u8string label, int x, int y, int w, int h, facade::button_display_state buttonState) {
      ASSERT_TRUE(buttonState == facade::button_display_state::disabled);
    }
  );
}

UTEST(button, buttonClicked) {
  facade::init();
  facade::initButton();
  auto renderer = [&](std::u8string label, int x, int y, int w, int h, facade::button_display_state buttonState) {};
  // Initialization complete
  facade::setMouseXY(15, 20);
  facade::preFrame();
  ASSERT_FALSE(facade::button(u8"test", u8"Button Label", 10, 15, 80, 20, false, renderer));
  facade::postFrame();

  facade::setLeftMouseButton(true);
  facade::preFrame();
  ASSERT_FALSE(facade::button(u8"test", u8"Button Label", 10, 15, 80, 20, false, renderer));
  facade::postFrame();

  facade::setLeftMouseButton(false);
  facade::preFrame();
  ASSERT_TRUE(facade::button(u8"test", u8"Button Label", 10, 15, 80, 20, false, renderer));
}

#endif // FACADE_TEST_BUTTON_H_INCLUDED
