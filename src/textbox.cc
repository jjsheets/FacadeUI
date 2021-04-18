// The latest version of this library is available on GitHub;
// https://github.com/jjsheets/FacadeUI
// License text can be found at the end of this file.

#ifndef FACADE_BUTTON_CC_INCLUDED
#define FACADE_BUTTON_CC_INCLUDED

#include "facade.h"

namespace {
  facade::textbox_renderer state_default_textbox_renderer;
}

void facade::initTextbox()
{
  facade::setDefaultTextboxRenderer(nullptr);
}

void facade::setDefaultTextboxRenderer(
  facade::textbox_renderer renderer)
{
  state_default_textbox_renderer = renderer;
}

void facade::textbox(
  const std::string &id,
  std::string &text,
  unsigned int &cursorStart,
  unsigned int &cursorEnd,
  int w,
  int h,
  bool disabled,
  facade::textbox_renderer renderer)
{
  int x = 0;
  int y = 0;
  facade::controlBounds(x, y, w, h);
  facade::updateControlState(id, x, y, w, h, disabled, true);
  if (!disabled && facade::clicked(id)) {
    facade::focus(id);
  }
  if (facade::isFocused(id) && !disabled) {
    facade::handleKeyboardEditing(text, cursorStart, cursorEnd);
  }
  auto _renderer = renderer ? renderer : state_default_textbox_renderer;
  _renderer(x, y, w, h, text, cursorStart, cursorEnd,
    facade::displayState(id, disabled));
  if (!disabled) {
    facade::setPreviousItem(id);
  }
}

// Overloads

void facade::textbox(
  const std::string &id,
  std::string &text,
  unsigned int &cursorStart,
  unsigned int &cursorEnd,
  int w,
  bool disabled,
  facade::textbox_renderer renderer)
{
  facade::textbox(id, text, cursorStart, cursorEnd, w, 0, disabled, renderer);
}

void facade::textbox(
  const std::string &id,
  std::string &text,
  unsigned int &cursorStart,
  unsigned int &cursorEnd,
  bool disabled,
  facade::textbox_renderer renderer)
{
  facade::textbox(id, text, cursorStart, cursorEnd, 0, 0, disabled, renderer);
}

void facade::textbox(
  const std::string &id,
  std::string &text,
  unsigned int &cursorStart,
  unsigned int &cursorEnd,
  facade::textbox_renderer renderer)
{
  facade::textbox(id, text, cursorStart, cursorEnd, 0, 0, false, renderer);
}

#endif // FACADE_Button_CC_INCLUDED

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
