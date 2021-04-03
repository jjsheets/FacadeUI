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
    std::u8string text = u8"Textbox Content";
    int cursorStart = 0;
    int cursorEnd = 0;
    try {
      facade::textbox(u8"test", text, cursorStart, cursorEnd);
    } catch (...) {
      exceptionThrown = true;
    }
    ASSERT_TRUE(exceptionThrown);
}

UTEST(textbox, defaultRenderer) {
  facade::init(2560);
  bool rendered = false;
  facade::setDefaultTextboxRenderer(
    [&](int x, int y, int w, int h, std::u8string text, int cursorStart, int cursorEnd, facade::display_state displayState) {
      rendered = true;
    }
  );
  // Initialization complete
  facade::preFrame();
  facade::beginLayout(10, 15, 80);
    std::u8string text = u8"Textbox Content";
    int cursorStart = 0;
    int cursorEnd = 0;
    facade::textbox(u8"test", text, cursorStart, cursorEnd);
    ASSERT_TRUE(rendered);
}

UTEST(textbox, textboxRenderer) {
  facade::init(2560);
  bool rendered = false;
  // Initialization complete
  facade::preFrame();
  facade::beginLayout(10, 15, 80);
    std::u8string text = u8"Textbox Content";
    int cursorStart = 0;
    int cursorEnd = 0;
    facade::textbox(u8"test", text, cursorStart, cursorEnd,
      [&](int x, int y, int w, int h, std::u8string text, int cursorStart, int cursorEnd, facade::display_state displayState) {
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
    std::u8string text = u8"Textbox Content";
    int cursorStart = 0;
    int cursorEnd = 0;
    facade::textbox(u8"test", text, cursorStart, cursorEnd,
      [&](int x, int y, int w, int h, std::u8string text, int cursorStart, int cursorEnd, facade::display_state displayState) {
        ASSERT_TRUE(text == u8"Textbox Content");
        ASSERT_EQ(10, x);
        ASSERT_EQ(15, y);
        ASSERT_EQ(80, w);
        ASSERT_EQ(20, h);
        ASSERT_EQ(0, cursorStart);
        ASSERT_EQ(0, cursorEnd);
      }
    );
}

UTEST(textbox, textboxEnabled) {
  facade::init(2560);
  // Initialization complete
  facade::preFrame();
  facade::beginLayout(10, 15, 80);
    std::u8string text = u8"Textbox Content";
    int cursorStart = 0;
    int cursorEnd = 0;
    facade::textbox(u8"test", text, cursorStart, cursorEnd,
      [&](int x, int y, int w, int h, std::u8string text, int cursorStart, int cursorEnd, facade::display_state displayState) {
        ASSERT_TRUE(displayState == facade::display_state::enabled);
      }
    );
}

#endif // FACADE_TEST_TEXTBOX_H_INCLUDED
