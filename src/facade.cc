// The latest version of this library is available on GitHub;
// https://github.com/jjsheets/FacadeUI
// License text can be found at the end of this file.

#ifndef FACADE_FACADE_CC_INCLUDED
#define FACADE_FACADE_CC_INCLUDED

#include "facade.h"
#include <stack>
#include <iostream>

// Anonymous namespace so state is local to this file only.
namespace {
  struct _layout;
  // Mouse controlling state
  int state_mouse_x;
  int state_mouse_y;
  bool state_mouse_left_down;
  bool state_mouse_middle_down;
  bool state_mouse_right_down;
  std::string state_hover_item;
  std::string state_active_item;

  // Keyboard controlling state
  std::string state_focus_item;
  std::string state_previous_item;
  char32_t state_key_char;
  facade::control_op state_control_op;
  bool state_mod_shift;
  unsigned int state_cursorStart;
  unsigned int state_cursorEnd;

  // Clipboard callbacks
  facade::clipboard_content_callback state_clipboard_content;
  facade::clip_content_callback state_clip_content;

  // Layout state
  std::stack<_layout*> layout_stack;
  _layout *curLayout;
}

void facade::init(
  int screenWidth)
{
  state_mouse_x = 0;
  state_mouse_y = 0;
  state_mouse_left_down = false;
  state_mouse_middle_down = false;
  state_mouse_right_down = false;
  state_hover_item = "";
  state_active_item = "";
  state_focus_item = "";
  state_clipboard_content = nullptr;
  state_clip_content = nullptr;
  while (!layout_stack.empty()) {
    layout_stack.pop();
  }
  facade::beginLayout(0, 0, screenWidth);
  facade::initButton();
  facade::initLabel();
  facade::initPanel();
  facade::initSlider();
  facade::initProgress();
  facade::initCheckbox();
  facade::initTextbox();
}

void facade::setMouseXY(
  int x,
  int y)
{
  state_mouse_x = x;
  state_mouse_y = y;
}

int facade::getMouseX()
{
  return state_mouse_x;
}

int facade::getMouseY()
{
  return state_mouse_y;
}

void facade::setLeftMouseButton(
  bool down)
{
  state_mouse_left_down = down;
}

void facade::setMiddleMouseButton(
  bool down)
{
  state_mouse_middle_down = down;
}

void facade::setRightMouseButton(
  bool down)
{
  state_mouse_right_down = down;
}

bool facade::leftMouseDown()
{
  return state_mouse_left_down;
}

bool facade::middleMouseDown()
{
  return state_mouse_middle_down;
}

bool facade::rightMouseDown()
{
  return state_mouse_right_down;
}

bool facade::mouseInRegion(
  int x,
  int y,
  int w,
  int h)
{
  return !(state_mouse_x < x ||
           state_mouse_y < y ||
           state_mouse_x >= x + w ||
           state_mouse_y >= y + h);
}

bool facade::isHovered(
  const std::string &id)
{
  return state_hover_item == id;
}

void facade::setHoverItem(
  const std::string &id)
{
  state_hover_item = id;
}

void facade::clearHoverItem()
{
  state_hover_item = "";
}

bool facade::isActive(
  const std::string &id)
{
  return state_active_item == id;
}

bool facade::noActiveItem()
{
  return state_active_item == "";
}

void facade::clearActiveItem()
{
  state_active_item = "";
}

bool facade::clicked(
  const std::string &id)
{
  return
    !facade::leftMouseDown()
    && facade::isHovered(id)
    && facade::isActive(id);
}

void facade::setActiveItem(
  const std::string &id)
{
  state_active_item = id;
}

bool facade::isFocused(
  const std::string &id)
{
  return state_focus_item == id;
}

bool facade::noFocusItem()
{
  return state_focus_item == "";
}

void facade::clearFocusItem()
{
  facade::focus("");
}

void facade::focus(
  const std::string &id)
{
  state_focus_item = id;
  state_cursorStart = 0;
  state_cursorEnd = 0;
}

void facade::focusPrevItem()
{
  facade::focus(state_previous_item);
}

void facade::setPreviousItem(
  const std::string &id)
{
  state_previous_item = id;
}

bool facade::noKeyChar()
{
  return state_key_char == U'\0';
}

bool facade::hasKeyChar()
{
  return state_key_char != U'\0';
}

char32_t facade::getKeyChar()
{
  return state_key_char;
}

void facade::clearKeyChar()
{
  state_key_char = U'\0';
}

void facade::setKeyChar(
  char32_t code)
{
  state_key_char = code;
}

void facade::setControlCode(
  facade::control_op code,
  bool shift)
{
  state_control_op = code;
  state_mod_shift = shift;
}

bool facade::getModShift()
{
  return state_mod_shift;
}

void facade::setClipboardCallback(
  facade::clipboard_content_callback get,
  facade::clip_content_callback set)
{
  state_clipboard_content = get;
  state_clip_content = set;
}

std::string facade::clipboardText()
{
  if (!state_clipboard_content) {
    return "";
  }
  return state_clipboard_content();
}

void facade::clipboardText(
  std::string new_clipboard)
{
  if (state_clip_content) {
    state_clip_content(new_clipboard);
  }
}

static std::string _utf8(
  const char32_t code)
{
  std::string s = "";
  if (code <= 0x7F) {
    s.reserve(1);
    s.push_back(code);
  } else if (code <= 0x7FF) {
    s.reserve(2);
    s.push_back(0xC0 | (code >> 6));
    s.push_back(0x80 | (code & 0x3F));
  } else if (code <= 0xFFFF) {
    s.reserve(3);
    s.push_back(0xE0 | (code >> 12));
    s.push_back(0x80 | ((code >> 6) & 0x3F));
    s.push_back(0x80 | (code & 0x3F));
  } else if (code <= 0x10FFFF) {
    s.reserve(4);
    s.push_back(0xF0 | (code >> 18));
    s.push_back(0x80 | ((code >> 12) & 0x3F));
    s.push_back(0x80 | ((code >> 6) & 0x3F));
    s.push_back(0x80 | (code & 0x3F));
  }
  return s;
}

static unsigned int _utf8RightCodepointLength(
  const std::string &s,
  unsigned int cursor)
{
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

static unsigned int _utf8LeftCodepointLength(
  const std::string &s,
  unsigned int cursor)
{
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

static std::string _editTextState(
  const std::string &text,
  unsigned int _cursorStart,
  unsigned int _cursorEnd)
{
  if (_cursorStart <= _cursorEnd) {
    return text.substr(_cursorStart, _cursorEnd - _cursorStart);
  } else {
    return text.substr(_cursorEnd, _cursorStart - _cursorEnd);
  }
}

static void _editTextState(
  std::string &text,
  unsigned int &_cursorStart,
  unsigned int &_cursorEnd,
  const std::string &replacement)
{
  if (_cursorStart <= _cursorEnd) {
    text.replace(_cursorStart, _cursorEnd - _cursorStart, replacement);
    _cursorStart = _cursorStart + replacement.length();
    _cursorEnd = _cursorStart;
  } else {
    text.replace(_cursorEnd, _cursorStart - _cursorEnd, replacement);
    _cursorStart = _cursorEnd + replacement.length();
    _cursorEnd = _cursorStart;
  }
}

static void _moveCursorTo(
  unsigned int &_cursorStart,
  unsigned int &_cursorEnd,
  unsigned int pos)
{
  _cursorEnd = pos;
  if (!facade::getModShift()) {
    _cursorStart = _cursorEnd;
  }
}

static void _moveCursorBy(
  unsigned int &_cursorStart,
  unsigned int &_cursorEnd,
  unsigned int dist)
{
  _cursorEnd += dist;
  if (!facade::getModShift()) {
    _cursorStart = _cursorEnd;
  }
}

void facade::tab(
  std::string &text,
  unsigned int &_cursorStart,
  unsigned int &_cursorEnd)
{
  if (facade::getModShift()) {
    facade::focusPrevItem();
  } else {
    facade::clearFocusItem();
  }
}

void facade::home(
  std::string &text,
  unsigned int &_cursorStart,
  unsigned int &_cursorEnd)
{
  _moveCursorTo(_cursorStart, _cursorEnd, 0);
}

void facade::pageup(
  std::string &text,
  unsigned int &_cursorStart,
  unsigned int &_cursorEnd)
{
  // TODO: When coding the multiline, adjust this so it does an actual pageup
  _moveCursorTo(_cursorStart, _cursorEnd, 0);
}

void facade::up(
  std::string &text,
  unsigned int &_cursorStart,
  unsigned int &_cursorEnd)
{
  // TODO: When coding the multiline, adjust this so it does an actual up
  _moveCursorTo(_cursorStart, _cursorEnd, 0);
}

void facade::end(
  std::string &text,
  unsigned int &_cursorStart,
  unsigned int &_cursorEnd)
{
  _moveCursorTo(_cursorStart, _cursorEnd, text.length());
}

void facade::pagedown(
  std::string &text,
  unsigned int &_cursorStart,
  unsigned int &_cursorEnd)
{
  // TODO: When coding the multiline, adjust this so it does an actual pagedown
  _moveCursorTo(_cursorStart, _cursorEnd, text.length());
}

void facade::down(
  std::string &text,
  unsigned int &_cursorStart,
  unsigned int &_cursorEnd)
{
  // TODO: When coding the multiline, adjust this so it does an actual down
  _moveCursorTo(_cursorStart, _cursorEnd, text.length());
}

void facade::del(
  std::string &text,
  unsigned int &_cursorStart,
  unsigned int &_cursorEnd)
{
  if (_cursorStart == _cursorEnd) {
    _cursorEnd +=_utf8RightCodepointLength(text, _cursorStart);
  }
  _editTextState(text, _cursorStart, _cursorEnd, "");
}

void facade::backspace(
  std::string &text,
  unsigned int &_cursorStart,
  unsigned int &_cursorEnd)
{
  if (_cursorStart == _cursorEnd) {
    _cursorEnd -=_utf8LeftCodepointLength(text, _cursorStart);
  }
  _editTextState(text, _cursorStart, _cursorEnd, "");
}

void facade::left(
  std::string &text,
  unsigned int &_cursorStart,
  unsigned int &_cursorEnd)
{
  _moveCursorBy(_cursorStart, _cursorEnd,
    -_utf8LeftCodepointLength(text, _cursorStart));
}

void facade::right(
  std::string &text,
  unsigned int &_cursorStart,
  unsigned int &_cursorEnd)
{
  _moveCursorBy(_cursorStart, _cursorEnd,
    _utf8RightCodepointLength(text, _cursorStart));
}

void facade::paste(
  std::string &text,
  unsigned int &_cursorStart,
  unsigned int &_cursorEnd)
{
  _editTextState(text, _cursorStart, _cursorEnd, facade::clipboardText());
}

void facade::cut(
  std::string &text,
  unsigned int &_cursorStart,
  unsigned int &_cursorEnd)
{
  facade::clipboardText(_editTextState(text, _cursorStart, _cursorEnd));
  _editTextState(text, _cursorStart, _cursorEnd, "");
}

void facade::copy(
  std::string &text,
  unsigned int &_cursorStart,
  unsigned int &_cursorEnd)
{
  facade::clipboardText(_editTextState(text, _cursorStart, _cursorEnd));
}

void facade::handleKeyboardEditing(
  std::string &text)
{
  if (state_control_op) {
    state_control_op(text, state_cursorStart, state_cursorEnd);
    state_control_op = nullptr;
  } else {
    if (facade::hasKeyChar()) {
      _editTextState(text, state_cursorStart, state_cursorEnd, _utf8(facade::getKeyChar()));
    }
  }
}

unsigned int facade::cursorStart()
{
  return state_cursorStart;
}

unsigned int facade::cursorEnd()
{
  return state_cursorEnd;
}

// Frame handling functions.

void facade::preFrame()
{
  clearHoverItem();
}

void facade::postFrame()
{
  if (!state_mouse_left_down) {
    clearActiveItem();
  } else if (noActiveItem()) {
    state_active_item = "_unavailable";
  }
  clearKeyChar();
}

facade::display_state facade::displayState(
  const std::string &id,
  bool disabled)
{
  if (disabled) {
    return facade::display_state::disabled;
  } else if ((facade::leftMouseDown() && facade::isActive(id))
           || facade::isFocused(id)) {
    return facade::display_state::pressed;
  } else if (facade::isHovered(id)) {
    return facade::display_state::hovered;
  } else {
    return facade::display_state::enabled;
  }
}

// layout functions, local variables, and structures

// make sure this isn't exposed outside this file.
namespace {
  struct _layout {
    int baseX;
    int baseY;
    int baseW;
    int rowHeight;
    int xSpacing;
    int ySpacing;
    // variables that update during use follow
    int indentation;
    int x;
    int y;
    int h;

    _layout(
      int _x,
      int _y,
      int _w,
      int _rowHeight,
      int _xSpacing,
      int _ySpacing);

    void indent(
      int w);

    void newRow();
    int availableWidth();
    void updateXY(
      int &_x,
      int &_y);
    void updateHeight(
      int &_h);
    void adjustX(
      int _w);
  };

  _layout::_layout(
    int _x,
    int _y,
    int _w,
    int _rowHeight,
    int _xSpacing,
    int _ySpacing):
  baseX(_x), baseY(_y), baseW(_w), rowHeight(_rowHeight), xSpacing(_xSpacing),
  ySpacing(_ySpacing), indentation(0), x(0), y(0), h(0)
  {};

  void _layout::indent(
    int _w)
  {
    indentation = std::clamp(indentation + _w, 0, baseW / 2);
  };

  void _layout::newRow()
  {
    x = 0;
    y += ySpacing + h;
    h = 0;
  }

  int _layout::availableWidth()
  {
    return baseW - x - indentation;
  }

  void _layout::updateXY(
    int &_x,
    int &_y)
  {
    _x = baseX + x + indentation;
    _y = baseY + y;
  }

  void _layout::updateHeight(
    int &_h)
  {
    if (_h == 0) {
      _h = rowHeight;
    }
    if (h < _h) {
      h = _h;
    }
  }

  void _layout::adjustX(
    int _w)
  {
    x += _w + xSpacing;
  }
}

void facade::beginLayout(
  int x,
  int y,
  int w,
  int rowHeight,
  int xSpacing,
  int ySpacing)
{
  curLayout = new _layout(x, y, w, rowHeight, xSpacing, ySpacing);
  layout_stack.push(curLayout);
}

void facade::endLayout() {
  // NOTE: The bottom of the stack is the screen space layout.
  //       Don't get rid of it.
  if (layout_stack.size() > 1) {
    delete curLayout;
    layout_stack.pop();
    curLayout = layout_stack.top();
  }
}

void facade::indent(
  int w)
{
  curLayout->indent(w);
}

void facade::controlBounds(
  int &x,
  int &y,
  int &w,
  int &h)
{
  curLayout->updateXY(x, y);
  curLayout->updateHeight(h);
  if (w == 0) {
    w = curLayout->availableWidth();
    curLayout->newRow();
  } else {
    if (w > curLayout->availableWidth()) {
      curLayout->newRow();
      curLayout->updateXY(x, y);
    }
    // the above can change the return value of availableWidth() so test again
    if (w > curLayout->availableWidth()) {
      w = curLayout->availableWidth();
    }
    curLayout->adjustX(w);
  }
}

void facade::updateControlState(
  const std::string &id,
  int x,
  int y,
  int w,
  int h,
  bool disabled,
  bool focusAwareControl)
{
  if (!disabled && facade::mouseInRegion(x, y, w, h)) {
    facade::setHoverItem(id);
    if (facade::noActiveItem() && facade::leftMouseDown()) {
      facade::setActiveItem(id);
    }
  }
  if (focusAwareControl && facade::noFocusItem() && !disabled) {
    facade::focus(id);
  }
}

#endif // FACADE_FACADE_CC_INCLUDED

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
