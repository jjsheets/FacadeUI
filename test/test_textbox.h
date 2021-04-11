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
  }
  ASSERT_TRUE(goal == text);
  ASSERT_EQ(goal.size(), cursorStart);
  ASSERT_EQ(goal.size(), cursorEnd);
}

bool validUtf8(std::string &data) {
  unsigned int count = 0;
  for (unsigned char c : data) {
    if (count > 0) {
      if ((c >> 6) != 0b10) {
        return false;
      }
      count--;
    } else {
      if ((c >> 5) == 0b110) {
        count = 1;
      } else if ((c >> 4) == 0b1110) {
        count = 2;
      } else if ((c >> 3) == 0b11110) {
        count = 3;
      } else if ((c >> 7) != 0) {
        return false;
      }
    }
  }
  return count == 0;
}

UTEST(textbox, textboxCursorValidity) {
  facade::init(2560);
  std::string text = "ði ıntəˈnæʃənəl fəˈnɛtık əsoʊsiˈeıʃn";
  unsigned int cursorStart = 0;
  unsigned int cursorEnd = 0;
  ASSERT_TRUE(validUtf8(text));
  // a full merseene twister is overkill for testing this, but what the heck.
  std::random_device r;
  std::mt19937 rng(r());
  std::uniform_int_distribution<> dis(0, 1);
  facade::setDefaultTextboxRenderer(
    [&](int x, int y, int w, int h, std::string text, unsigned int cursorStart, unsigned int cursorEnd, facade::display_state displayState) {});
  // Initialization complete
  // test this 10 times in a row.
  unsigned int direction;
  for (unsigned int t = 0; t < 1000; t++) {
    for (unsigned int i = 0; i < 100; i++) {
      direction = dis(rng);
      facade::setControlCode(direction ? facade::control_code::left : facade::control_code::right, false);
      facade::preFrame();
      facade::beginLayout(10, 15, 80);
        facade::textbox("test", text, cursorStart, cursorEnd);
      facade::endLayout();
      facade::postFrame();
      facade::setKeyChar('0');
      facade::preFrame();
      facade::beginLayout(10, 15, 80);
        facade::textbox("test", text, cursorStart, cursorEnd);
      facade::endLayout();
      facade::postFrame();
    }
    ASSERT_TRUE(validUtf8(text));
    text = "ði ıntəˈnæʃənəl fəˈnɛtık əsoʊsiˈeıʃn";
    cursorStart = 0;
    cursorEnd = 0;
  }
}

UTEST(textbox, textboxClipboard) {
  facade::init(2560);
  std::string text = "Hello World!";
  unsigned int cursorStart = 0;
  unsigned int cursorEnd = 0;
  facade::setDefaultTextboxRenderer(
    [&](int x, int y, int w, int h, std::string text, unsigned int cursorStart, unsigned int cursorEnd, facade::display_state displayState) {});
  facade::setClipboardCallback([&]() -> std::string {
    return "Goodbye";
  });
  // Initialization complete
  for (unsigned int i = 0; i < 5; i++) {
    facade::setControlCode(facade::control_code::right, true);
    facade::preFrame();
    facade::beginLayout(10, 15, 80);
      facade::textbox("test", text, cursorStart, cursorEnd);
    facade::endLayout();
    facade::postFrame();
  }
  facade::setControlCode(facade::control_code::paste, false);
  facade::preFrame();
  facade::beginLayout(10, 15, 80);
    facade::textbox("test", text, cursorStart, cursorEnd);
  facade::endLayout();
  facade::postFrame();
  ASSERT_TRUE(text == "Goodbye World!");
}

#endif // FACADE_TEST_TEXTBOX_H_INCLUDED
