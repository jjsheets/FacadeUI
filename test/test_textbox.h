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

#ifndef FACADE_TEST_TEXTBOX_H_INCLUDED
#define FACADE_TEST_TEXTBOX_H_INCLUDED

UTEST(textbox, noRenderer) {
  facade::init(2560);
  bool exceptionThrown = false;
  // Initialization complete
  facade::preFrame();
  facade::beginLayout(10, 15, 80);
    std::string text = "Textbox Content";
    unsigned int cursorStart = 0;
    unsigned int cursorEnd = 0;
    try {
      facade::textbox("test", text, cursorStart, cursorEnd);
    } catch (...) {
      exceptionThrown = true;
    }
    ASSERT_TRUE(exceptionThrown);
}

UTEST(textbox, defaultRenderer) {
  facade::init(2560);
  bool rendered = false;
  facade::setDefaultTextboxRenderer(
    [&](int x, int y, int w, int h, std::string text, unsigned int cursorStart, unsigned int cursorEnd, facade::display_state displayState) {
      rendered = true;
    }
  );
  // Initialization complete
  facade::preFrame();
  facade::beginLayout(10, 15, 80);
    std::string text = "Textbox Content";
    unsigned int cursorStart = 0;
    unsigned int cursorEnd = 0;
    facade::textbox("test", text, cursorStart, cursorEnd);
    ASSERT_TRUE(rendered);
}

UTEST(textbox, textboxRenderer) {
  facade::init(2560);
  bool rendered = false;
  // Initialization complete
  facade::preFrame();
  facade::beginLayout(10, 15, 80);
    std::string text = "Textbox Content";
    unsigned int cursorStart = 0;
    unsigned int cursorEnd = 0;
    facade::textbox("test", text, cursorStart, cursorEnd,
      [&](int x, int y, int w, int h, std::string text, unsigned int cursorStart, unsigned int cursorEnd, facade::display_state displayState) {
        rendered = true;
      }
    );
    ASSERT_TRUE(rendered);
}

UTEST(textbox, textboxRendererParameters) {
  facade::init(2560);
  // Initialization complete
  facade::preFrame();
  facade::beginLayout(10, 15, 80);
    std::string text = "Textbox Content";
    unsigned int cursorStart = 0;
    unsigned int cursorEnd = 0;
    facade::textbox("test", text, cursorStart, cursorEnd,
      [&](int x, int y, int w, int h, std::string text, unsigned int cursorStart, unsigned int cursorEnd, facade::display_state displayState) {
        ASSERT_TRUE(text == "Textbox Content");
        ASSERT_EQ(10, x);
        ASSERT_EQ(15, y);
        ASSERT_EQ(80, w);
        ASSERT_EQ(20, h);
        ASSERT_EQ(0u, cursorStart);
        ASSERT_EQ(0u, cursorEnd);
      }
    );
}

UTEST(textbox, textboxEnabled) {
  facade::init(2560);
  // Initialization complete
  facade::preFrame();
  facade::beginLayout(10, 15, 80);
    std::string text = "Textbox Content";
    unsigned int cursorStart = 0;
    unsigned int cursorEnd = 0;
    facade::textbox("test", text, cursorStart, cursorEnd,
      [&](int x, int y, int w, int h, std::string text, unsigned int cursorStart, unsigned int cursorEnd, facade::display_state displayState) {
        ASSERT_TRUE(displayState == facade::display_state::enabled);
      }
    );
}

UTEST(textbox, textboxHover) {
  facade::init(2560);
  // Initialization complete
  facade::setMouseXY(15, 20);
  facade::preFrame();
  facade::beginLayout(10, 15, 80);
    std::string text = "Textbox Content";
    unsigned int cursorStart = 0;
    unsigned int cursorEnd = 0;
    facade::textbox("test", text, cursorStart, cursorEnd,
      [&](int x, int y, int w, int h, std::string text, unsigned int cursorStart, unsigned int cursorEnd, facade::display_state displayState) {
        ASSERT_TRUE(displayState == facade::display_state::hovered);
      }
    );
}

UTEST(textbox, textboxPressed) {
  facade::init(2560);
  // Initialization complete
  facade::setMouseXY(15, 20);
  facade::preFrame();
  facade::beginLayout(10, 15, 80);
    std::string text = "Textbox Content";
    unsigned int cursorStart = 0;
    unsigned int cursorEnd = 0;
    facade::textbox("test", text, cursorStart, cursorEnd,
      [&](int x, int y, int w, int h, std::string text, unsigned int cursorStart, unsigned int cursorEnd, facade::display_state displayState) {
      }
    );
  facade::endLayout();
  facade::postFrame();

  facade::setLeftMouseButton(true);
  facade::preFrame();
  facade::beginLayout(10, 15, 80);
    facade::textbox("test", text, cursorStart, cursorEnd,
      [&](int x, int y, int w, int h, std::string text, unsigned int cursorStart, unsigned int cursorEnd, facade::display_state displayState) {
        ASSERT_TRUE(displayState == facade::display_state::pressed);
      }
    );
  facade::endLayout();
  facade::postFrame();

  // Make sure the button stays pressed even after moving the mouse out of the button boundary
  facade::setMouseXY(5, 5);
  facade::preFrame();
  facade::beginLayout(10, 15, 80);
    facade::textbox("test", text, cursorStart, cursorEnd,
      [&](int x, int y, int w, int h, std::string text, unsigned int cursorStart, unsigned int cursorEnd, facade::display_state displayState) {
        ASSERT_TRUE(displayState == facade::display_state::pressed);
      }
    );
}

UTEST(textbox, textboxDisabled) {
  facade::init(2560);
  // Initialization complete
  facade::preFrame();
  facade::beginLayout(10, 15, 80);
    std::string text = "Textbox Content";
    unsigned int cursorStart = 0;
    unsigned int cursorEnd = 0;
    facade::textbox("test", text, cursorStart, cursorEnd, true,
      [&](int x, int y, int w, int h, std::string text, unsigned int cursorStart, unsigned int cursorEnd, facade::display_state displayState) {
        ASSERT_TRUE(displayState == facade::display_state::disabled);
      }
    );
}

// Update this test to be able to correctly handle input of char32_t codepoints, with the output being utf8.
UTEST(textbox, textboxKeyboardInput) {
  facade::init(2560);
  std::string text = "";
  unsigned int cursorStart = 0;
  unsigned int cursorEnd = 0;
  facade::setDefaultTextboxRenderer(
    [&](int x, int y, int w, int h, std::string text, unsigned int cursorStart, unsigned int cursorEnd, facade::display_state displayState) {});
  // Initialization complete
  std::string goal = "Hello World!";
  for (auto &c : goal) {
    facade::setKeyChar(c);
    facade::preFrame();
    facade::beginLayout(10, 15, 80);
      facade::textbox("test", text, cursorStart, cursorEnd);
    facade::endLayout();
    facade::postFrame();
    std::cout << "  " << c << " : " << text << " (" << cursorStart << ", " << cursorEnd << ")" << std::endl;
  }
  ASSERT_TRUE(goal == text);
  ASSERT_EQ(goal.size(), cursorStart);
  ASSERT_EQ(goal.size(), cursorEnd);
}

#endif // FACADE_TEST_TEXTBOX_H_INCLUDED