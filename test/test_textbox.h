// The latest version of this library is available on GitHub;
// https://github.com/jjsheets/FacadeUI
// License text can be found at the end of this file.

#ifndef FACADE_TEST_TEXTBOX_H_INCLUDED
#define FACADE_TEST_TEXTBOX_H_INCLUDED

UTEST(textbox, noRenderer) {
  facade::init(2560);
  bool exceptionThrown = false;
  // Initialization complete
  facade::preFrame();
  facade::beginLayout(10, 15, 80);
    std::string text = "Textbox Content";
    try {
      facade::textbox("test", text);
    } catch (...) {
      exceptionThrown = true;
    }
    ASSERT_TRUE(exceptionThrown);
}

UTEST(textbox, defaultRenderer) {
  facade::init(2560);
  bool rendered = false;
  facade::setDefaultTextboxRenderer(
    [&](int x, int y, int w, int h, std::string text, unsigned int _cursorStart, unsigned int _cursorEnd, facade::display_state displayState) {
      rendered = true;
    }
  );
  // Initialization complete
  facade::preFrame();
  facade::beginLayout(10, 15, 80);
    std::string text = "Textbox Content";
    facade::textbox("test", text);
    ASSERT_TRUE(rendered);
}

UTEST(textbox, textboxRenderer) {
  facade::init(2560);
  bool rendered = false;
  // Initialization complete
  facade::preFrame();
  facade::beginLayout(10, 15, 80);
    std::string text = "Textbox Content";
    facade::textbox("test", text,
      [&](int x, int y, int w, int h, std::string text, unsigned int _cursorStart, unsigned int _cursorEnd, facade::display_state displayState) {
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
    facade::textbox("test", text,
      [&](int x, int y, int w, int h, std::string text, unsigned int _cursorStart, unsigned int _cursorEnd, facade::display_state displayState) {
        ASSERT_TRUE(text == "Textbox Content");
        ASSERT_EQ(10, x);
        ASSERT_EQ(15, y);
        ASSERT_EQ(80, w);
        ASSERT_EQ(20, h);
        ASSERT_EQ(0u, _cursorStart);
        ASSERT_EQ(0u, _cursorEnd);
      }
    );
}

UTEST(textbox, textboxEnabled) {
  facade::init(2560);
  // Initialization complete
  facade::preFrame();
  facade::beginLayout(10, 15, 80);
    std::string text = "Textbox Content";
    facade::textbox("test", text,
      [&](int x, int y, int w, int h, std::string text, unsigned int _cursorStart, unsigned int _cursorEnd, facade::display_state displayState) {
        ASSERT_TRUE(displayState == facade::display_state::pressed); // this will be pressed because it will automatically grab the focus.
      }
    );
    facade::textbox("test2", text,
      [&](int x, int y, int w, int h, std::string text, unsigned int _cursorStart, unsigned int _cursorEnd, facade::display_state displayState) {
        ASSERT_TRUE(displayState == facade::display_state::enabled);
      }
    );
}

UTEST(textbox, textboxHover) {
  facade::init(2560);
  // Initialization complete
  facade::setMouseXY(15, 50);
  facade::preFrame();
  facade::beginLayout(10, 15, 80);
    std::string text = "Textbox Content";
    facade::textbox("test", text,
      [&](int x, int y, int w, int h, std::string text, unsigned int _cursorStart, unsigned int _cursorEnd, facade::display_state displayState) {
        ASSERT_TRUE(displayState == facade::display_state::pressed); // this will be pressed because it will automatically grab the focus.
      }
    );
    facade::textbox("test2", text,
      [&](int x, int y, int w, int h, std::string text, unsigned int _cursorStart, unsigned int _cursorEnd, facade::display_state displayState) {
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
    facade::textbox("test", text,
      [&](int x, int y, int w, int h, std::string text, unsigned int _cursorStart, unsigned int _cursorEnd, facade::display_state displayState) {
      }
    );
  facade::endLayout();
  facade::postFrame();

  facade::setLeftMouseButton(true);
  facade::preFrame();
  facade::beginLayout(10, 15, 80);
    facade::textbox("test", text,
      [&](int x, int y, int w, int h, std::string text, unsigned int _cursorStart, unsigned int _cursorEnd, facade::display_state displayState) {
        ASSERT_TRUE(displayState == facade::display_state::pressed);
      }
    );
  facade::endLayout();
  facade::postFrame();
  // Make sure the button stays pressed even after moving the mouse out of the button boundary
  facade::setMouseXY(5, 5);
  facade::preFrame();
  facade::beginLayout(10, 15, 80);
    facade::textbox("test", text,
      [&](int x, int y, int w, int h, std::string text, unsigned int _cursorStart, unsigned int _cursorEnd, facade::display_state displayState) {
        ASSERT_TRUE(displayState == facade::display_state::pressed);
      }
    );
}

UTEST(textbox, textboxDisabled) {
  facade::init(2560);
  std::string text = "Textbox Content";
  facade::setDefaultTextboxRenderer(
    [&](int x, int y, int w, int h, std::string text, unsigned int _cursorStart, unsigned int _cursorEnd, facade::display_state displayState) {
      ASSERT_TRUE(displayState == facade::display_state::disabled);
    });
  // Initialization complete
  // This should not change the text at all.
  facade::setKeyChar('0');
  facade::preFrame();
  facade::beginLayout(10, 15, 80);
    facade::textbox("test", text, true);
  facade::endLayout();
  facade::postFrame();
  ASSERT_TRUE("Textbox Content" == text);
  ASSERT_TRUE(facade::noFocusItem());
}

UTEST(textbox, textboxKeyboardInput) {
  facade::init(2560);
  std::string text = "";
  facade::setDefaultTextboxRenderer(
    [&](int x, int y, int w, int h, std::string text, unsigned int _cursorStart, unsigned int _cursorEnd, facade::display_state displayState) {});
  // Initialization complete
  std::string goal = "Hello World!";
  for (auto &c : goal) {
    facade::setKeyChar(c);
    facade::preFrame();
    facade::beginLayout(10, 15, 80);
      facade::textbox("test", text);
    facade::endLayout();
    facade::postFrame();
  }
  ASSERT_TRUE(goal == text);
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
  ASSERT_TRUE(validUtf8(text));
  // a full merseene twister is overkill for testing this, but what the heck.
  std::random_device r;
  std::mt19937 rng(r());
  std::uniform_int_distribution<> dis(0, 1);
  facade::setDefaultTextboxRenderer(
    [&](int x, int y, int w, int h, std::string text, unsigned int _cursorStart, unsigned int _cursorEnd, facade::display_state displayState) {});
  // Initialization complete
  // test this 10 times in a row.
  unsigned int direction;
  for (unsigned int t = 0; t < 1000; t++) {
    for (unsigned int i = 0; i < 100; i++) {
      direction = dis(rng);
      try {
        facade::setControlCode(direction ? facade::left : facade::right, false);
        facade::preFrame();
        facade::beginLayout(10, 15, 80);
          facade::textbox("test", text);
        facade::endLayout();
        facade::postFrame();
      } catch (std::out_of_range &_oor) {
        std::cout << (direction ? "left, " : "right, ");
        std::cout << t << ", " << i << ", " << text << std::endl;
        ASSERT_TRUE(false);
      }
      try {
        facade::setKeyChar('0');
        facade::preFrame();
        facade::beginLayout(10, 15, 80);
          facade::textbox("test", text);
        facade::endLayout();
        facade::postFrame();
      } catch (std::out_of_range &_oor) {
        std::cout << (direction ? "left, " : "right, ");
        std::cout << t << ", " << i << ", " << text << std::endl;
        ASSERT_TRUE(false);
      }
    }
    ASSERT_TRUE(validUtf8(text));
    text = "ði ıntəˈnæʃənəl fəˈnɛtık əsoʊsiˈeıʃn";
    facade::clearFocusItem();
  }
}

UTEST(textbox, textboxClipboard) {
  facade::init(2560);
  std::string text = "Hello World!";
  std::string clipboard = "Goodbye";
  facade::setDefaultTextboxRenderer(
    [&](int x, int y, int w, int h, std::string text, unsigned int _cursorStart, unsigned int _cursorEnd, facade::display_state displayState) {});
  facade::setClipboardCallback(
    [&]() -> std::string {
      return clipboard;
    },
    [&](std::string newClipboard) {
      clipboard = newClipboard;
    });
  // Initialization complete
  // Select Hello
  for (unsigned int i = 0; i < 5; i++) {
    facade::setControlCode(facade::right, true);
    facade::preFrame();
    facade::beginLayout(10, 15, 80);
      facade::textbox("test", text);
    facade::endLayout();
    facade::postFrame();
  }
  // Paste in Goodbye;
  facade::setControlCode(facade::paste, false);
  facade::preFrame();
  facade::beginLayout(10, 15, 80);
    facade::textbox("test", text);
  facade::endLayout();
  facade::postFrame();
  ASSERT_TRUE(text == "Goodbye World!");
  // Clear clipboard externally to test cut operation
  clipboard = "";
  // Select Goodbye, this time using the Home control code
  facade::setControlCode(facade::home, true);
  facade::preFrame();
  facade::beginLayout(10, 15, 80);
    facade::textbox("test", text);
  facade::endLayout();
  facade::postFrame();
  // Cut Goodbye
  facade::setControlCode(facade::cut, false);
  facade::preFrame();
  facade::beginLayout(10, 15, 80);
    facade::textbox("test", text);
  facade::endLayout();
  facade::postFrame();
  ASSERT_TRUE(text == " World!");
  ASSERT_TRUE(clipboard == "Goodbye");
  // Paste it back in...
  facade::setControlCode(facade::paste, false);
  facade::preFrame();
  facade::beginLayout(10, 15, 80);
    facade::textbox("test", text);
  facade::endLayout();
  facade::postFrame();
  // Select " World!" with shift end
  // Cut Goodbye
  facade::setControlCode(facade::end, true);
  facade::preFrame();
  facade::beginLayout(10, 15, 80);
    facade::textbox("test", text);
  facade::endLayout();
  facade::postFrame();
  // Copy it
  facade::setControlCode(facade::copy, false);
  facade::preFrame();
  facade::beginLayout(10, 15, 80);
    facade::textbox("test", text);
  facade::endLayout();
  facade::postFrame();
  // paste it, which should be equivalent to just heading the cursor to the end
  facade::setControlCode(facade::paste, false);
  facade::preFrame();
  facade::beginLayout(10, 15, 80);
    facade::textbox("test", text);
  facade::endLayout();
  facade::postFrame();
  // Paste again...
  facade::setControlCode(facade::paste, false);
  facade::preFrame();
  facade::beginLayout(10, 15, 80);
    facade::textbox("test", text);
  facade::endLayout();
  facade::postFrame();
  // Verify results
  ASSERT_TRUE(text == "Goodbye World! World!");
}

UTEST(textbox, textboxCursorMovement) {
  facade::init(2560);
  std::string text = "12345";
  facade::setDefaultTextboxRenderer(
    [&](int x, int y, int w, int h, std::string text, unsigned int _cursorStart, unsigned int _cursorEnd, facade::display_state displayState) {});
  // Initialization complete
  facade::setControlCode(facade::left, false);
  facade::preFrame();
  facade::beginLayout(10, 15, 80);
    facade::textbox("test", text);
  facade::endLayout();
  facade::postFrame();
  facade::setControlCode(facade::down, false);
  facade::preFrame();
  facade::beginLayout(10, 15, 80);
    facade::textbox("test", text);
  facade::endLayout();
  facade::postFrame();
  facade::setControlCode(facade::up, false);
  facade::preFrame();
  facade::beginLayout(10, 15, 80);
    facade::textbox("test", text);
  facade::endLayout();
  facade::postFrame();
  facade::setControlCode(facade::pagedown, false);
  facade::preFrame();
  facade::beginLayout(10, 15, 80);
    facade::textbox("test", text);
  facade::endLayout();
  facade::postFrame();
  facade::setControlCode(facade::pageup, false);
  facade::preFrame();
  facade::beginLayout(10, 15, 80);
    facade::textbox("test", text);
  facade::endLayout();
  facade::postFrame();
  facade::setControlCode(facade::end, false);
  facade::preFrame();
  facade::beginLayout(10, 15, 80);
    facade::textbox("test", text);
  facade::endLayout();
  facade::postFrame();
  facade::setControlCode(facade::home, false);
  facade::preFrame();
  facade::beginLayout(10, 15, 80);
    facade::textbox("test", text);
  facade::endLayout();
  facade::postFrame();
  facade::setControlCode(facade::end, false);
  facade::preFrame();
  facade::beginLayout(10, 15, 80);
    facade::textbox("test", text);
  facade::endLayout();
  facade::postFrame();
  facade::setControlCode(facade::right, false);
  facade::preFrame();
  facade::beginLayout(10, 15, 80);
    facade::textbox("test", text);
  facade::endLayout();
  facade::postFrame();
}

UTEST(textbox, textboxTab) {
  facade::init(2560);
  std::string text = "";
  facade::setDefaultTextboxRenderer(
    [&](int x, int y, int w, int h, std::string text, unsigned int _cursorStart, unsigned int _cursorEnd, facade::display_state displayState) {});
  // Initialization complete
  facade::preFrame();
  facade::beginLayout(10, 15, 80);
    facade::textbox("test1", text);
    facade::textbox("test2", text);
  facade::endLayout();
  facade::postFrame();
  ASSERT_TRUE(facade::isFocused("test1"));
  facade::setControlCode(facade::tab, false);
  facade::preFrame();
  facade::beginLayout(10, 15, 80);
    facade::textbox("test1", text);
    facade::textbox("test2", text);
  facade::endLayout();
  facade::postFrame();
  ASSERT_TRUE(facade::isFocused("test2"));
  facade::setControlCode(facade::tab, false);
  facade::preFrame();
  facade::beginLayout(10, 15, 80);
    facade::textbox("test1", text);
    facade::textbox("test2", text);
  facade::endLayout();
  facade::postFrame();
  // there should be no focus item now, which means the first focus aware control in the next frame will grab focus.
  ASSERT_TRUE(facade::noFocusItem());
  facade::setControlCode(facade::tab, true);
  facade::preFrame();
  facade::beginLayout(10, 15, 80);
    facade::textbox("test1", text);
    facade::textbox("test2", text);
  facade::endLayout();
  facade::postFrame();
  // here the shift-tab should have picked up the previous frame's last focus aware control and focus on it.
  ASSERT_TRUE(facade::isFocused("test2"));
  facade::setControlCode(facade::tab, true);
  facade::preFrame();
  facade::beginLayout(10, 15, 80);
    facade::textbox("test1", text);
    facade::textbox("test2", text);
  facade::endLayout();
  facade::postFrame();
  ASSERT_TRUE(facade::isFocused("test1"));
}

UTEST(textbox, textboxDeletion) {
  facade::init(2560);
  std::string text = "JUNKJust This.JUNK";
  facade::setDefaultTextboxRenderer(
    [&](int x, int y, int w, int h, std::string text, unsigned int _cursorStart, unsigned int _cursorEnd, facade::display_state displayState) {});
  // Initialization complete
  facade::preFrame();
  facade::beginLayout(10, 15, 80);
    facade::textbox("test", text);
  facade::endLayout();
  facade::postFrame();
  facade::setControlCode(facade::del, false);
  facade::preFrame();
  facade::beginLayout(10, 15, 80);
    facade::textbox("test", text);
  facade::endLayout();
  facade::postFrame();
  ASSERT_TRUE("UNKJust This.JUNK" == text);
  // shift select the first three characters...
  for (int i = 0; i < 3; i++) {
    facade::setControlCode(facade::right, true);
    facade::preFrame();
    facade::beginLayout(10, 15, 80);
      facade::textbox("test", text);
    facade::endLayout();
    facade::postFrame();
  }
  // then delete.
  facade::setControlCode(facade::del, false);
  facade::preFrame();
  facade::beginLayout(10, 15, 80);
    facade::textbox("test", text);
  facade::endLayout();
  facade::postFrame();
  ASSERT_TRUE("Just This.JUNK" == text);
  // a backspace at the beginning should do nothing.
  facade::setControlCode(facade::backspace, false);
  facade::preFrame();
  facade::beginLayout(10, 15, 80);
    facade::textbox("test", text);
  facade::endLayout();
  facade::postFrame();
  ASSERT_TRUE("Just This.JUNK" == text);
  // Head to the end
  facade::setControlCode(facade::end, false);
  facade::preFrame();
  facade::beginLayout(10, 15, 80);
    facade::textbox("test", text);
  facade::endLayout();
  facade::postFrame();
  // a delete at the end should also do nothing.
  facade::setControlCode(facade::del, false);
  facade::preFrame();
  facade::beginLayout(10, 15, 80);
    facade::textbox("test", text);
  facade::endLayout();
  facade::postFrame();
  ASSERT_TRUE("Just This.JUNK" == text);
  // a backspace should work though
  facade::setControlCode(facade::backspace, false);
  facade::preFrame();
  facade::beginLayout(10, 15, 80);
    facade::textbox("test", text);
  facade::endLayout();
  facade::postFrame();
  ASSERT_TRUE("Just This.JUN" == text);
  // shift select the last three characters...
  for (int i = 0; i < 3; i++) {
    facade::setControlCode(facade::left, true);
    facade::preFrame();
    facade::beginLayout(10, 15, 80);
      facade::textbox("test", text);
    facade::endLayout();
    facade::postFrame();
  }
  // then backspace.
  facade::setControlCode(facade::backspace, false);
  facade::preFrame();
  facade::beginLayout(10, 15, 80);
    facade::textbox("test", text);
  facade::endLayout();
  facade::postFrame();
  ASSERT_TRUE("Just This." == text);
}

#endif // FACADE_TEST_TEXTBOX_H_INCLUDED

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
