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

#ifndef FACADE_BUTTON_CC_INCLUDED
#define FACADE_BUTTON_CC_INCLUDED

#include "facade.h"

namespace {
  facade::textbox_renderer state_default_textbox_renderer;
}

void facade::initTextbox() {
  state_default_textbox_renderer = nullptr;
  facade::clearFocusItem();
}

static std::string _to_utf8(const char32_t code, unsigned &l) {
  std::string s = "";
  if (code <= 0x7F) {
    l = 1;
    s.reserve(l);
    s.push_back(code);
  } else if (code <= 0x7FF) {
    l = 2;
    s.reserve(l);
    s.push_back(0xC0 | (code >> 6));
    s.push_back(0x80 | (code & 0x3F));
  } else if (code <= 0xFFFF) {
    l = 3;
    s.reserve(l);
    s.push_back(0xE0 | (code >> 12));
    s.push_back(0x80 | ((code >> 6) & 0x3F));
    s.push_back(0x80 | (code & 0x3F));
  } else if (code <= 0x10FFFF) {
    l = 4;
    s.reserve(l);
    s.push_back(0xF0 | (code >> 18));
    s.push_back(0x80 | ((code >> 12) & 0x3F));
    s.push_back(0x80 | ((code >> 6) & 0x3F));
    s.push_back(0x80 | (code & 0x3F));
  } else {
    l = 0;
  }
  return s;
}

static unsigned int _utf8_forward_codepoint_length(const std::string &s, unsigned int cursor) {
  if (cursor == s.length()) {
    return 0;
  }
  char c = s[cursor];
  if ((c & 0x80) == 0x00) {
    return 1;
  } else if ((c & 0xE0) == 0xC0) {
    return 2;
  } else if ((c & 0xF0) == 0xE0) {
    return 3;
  } else if ((c & 0xF8) == 0xF0) {
    return 4;
  }
  throw "Invalid initial UTF-8 code unit";
}

static unsigned int _utf8_reverse_codepoint_length(const std::string &s, unsigned int cursor) {
  if (cursor == 0) {
    return 0;
  }
  for (auto c = cursor - 1; c >= 0; c--) {
    if ((s[c] & 0xC0) != 0x80) {
      return cursor - c;
    }
    if (c == 0) {
      throw "No valid codepoint found";
    }
  }
}

void facade::textbox(std::string id, std::string &text, unsigned int &cursorStart, unsigned int &cursorEnd, int w, int h, bool disabled,
    facade::textbox_renderer renderer) {
  int x = 0;
  int y = 0;
  facade::updateLayout(x, y, w, h, w == 0);
  // check/update hover and active.
  if (!disabled && facade::mouseInRegion(x, y, w, h)) {
    facade::setHoverItem(id);
    if (facade::noActiveItem() && facade::getLeftMouseButton()) {
      facade::setActiveItem(id);
    }
  }
  if (! disabled) {
    // Deal with cursor movement
    switch (facade::getControlCode()) {
      case facade::control_code::home:
      cursorStart = 0;
      cursorEnd = cursorStart;
      break;
      case facade::control_code::end:
      cursorStart = text.length();
      cursorEnd = cursorStart;
      break;
      case facade::control_code::left:
      cursorStart -= _utf8_reverse_codepoint_length(text, cursorStart);
      cursorEnd = cursorStart;
      break;
      case facade::control_code::right:
      cursorStart += _utf8_forward_codepoint_length(text, cursorStart);
      cursorEnd = cursorStart;
      break;
      default:
      break;
    }
    // Deal with keyboard text input
    if (facade::hasKeyChar()) {
      unsigned l = 0;
      text.insert(cursorStart, _to_utf8(facade::getKeyChar(), l));
      cursorStart = cursorStart + l;
      cursorEnd = cursorStart;
    }
  }
  // render the textbox
  auto _renderer = renderer ? renderer : state_default_textbox_renderer;
  if (!_renderer) {
    throw "No textbox renderer provided.";
  }
  if (disabled) {
    _renderer(x, y, w, h, text, cursorStart, cursorEnd, facade::display_state::disabled);
  } else if (facade::getLeftMouseButton() && facade::isActiveItem(id)) {
    _renderer(x, y, w, h, text, cursorStart, cursorEnd, facade::display_state::pressed);
  } else if (facade::isHoverItem(id)) {
    _renderer(x, y, w, h, text, cursorStart, cursorEnd, facade::display_state::hovered);
  } else {
    _renderer(x, y, w, h, text, cursorStart, cursorEnd, facade::display_state::enabled);
  }

}

void facade::textbox(std::string id, std::string &text, unsigned int &cursorStart, unsigned int &cursorEnd, int w, bool disabled,
    facade::textbox_renderer renderer) {
  facade::textbox(id, text, cursorStart, cursorEnd, w, 0, disabled, renderer);
}

void facade::textbox(std::string id, std::string &text, unsigned int &cursorStart, unsigned int &cursorEnd, bool disabled,
    facade::textbox_renderer renderer) {
  facade::textbox(id, text, cursorStart, cursorEnd, 0, 0, disabled, renderer);
}

void facade::textbox(std::string id, std::string &text, unsigned int &cursorStart, unsigned int &cursorEnd,
    facade::textbox_renderer renderer) {
  facade::textbox(id, text, cursorStart, cursorEnd, 0, 0, false, renderer);
}

void facade::setDefaultTextboxRenderer(facade::textbox_renderer renderer) {
  state_default_textbox_renderer = renderer;
}

#endif // FACADE_Button_CC_INCLUDED
