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
  facade::control_code state_cursor_control;
  bool state_mod_shift;

  // Clipboard callbacks
  facade::get_clipboard_callback state_get_clipboard;
  facade::set_clipboard_callback state_set_clipboard;

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
  state_get_clipboard = nullptr;
  state_set_clipboard = nullptr;
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
  return !facade::leftMouseDown() && facade::isHovered(id) && facade::isActive(id);
}

void facade::setActiveItem(
  const std::string &id)
{
  state_active_item = id;
}

bool facade::isFocusItem(
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
  state_focus_item = "";
}

void facade::setFocusItem(
  const std::string &id)
{
  state_focus_item = id;
}

void facade::focusPrevItem()
{
  state_focus_item = state_previous_item;
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

facade::control_code facade::getControlCode()
{
  auto cc = state_cursor_control;
  state_cursor_control = facade::control_code::nop;
  return cc;
}

void facade::setControlCode(
  facade::control_code code,
  bool shift)
{
  state_cursor_control = code;
  state_mod_shift = shift;
}

bool facade::getModShift()
{
  return state_mod_shift;
}

void facade::setClipboardCallback(
  facade::get_clipboard_callback get,
  facade::set_clipboard_callback set)
{
  state_get_clipboard = get;
  state_set_clipboard = set;
}

std::string facade::getClipboardText()
{
  if (!state_get_clipboard) {
    return "";
  }
  return state_get_clipboard();
}

void facade::setClipboardText(
  std::string new_clipboard)
{
  if (state_set_clipboard) {
    state_set_clipboard(new_clipboard);
  }
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
  } else if (facade::leftMouseDown() && facade::isActive(id)) {
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
    // base layout values that don't change after being initialized in beginLayout()
    int baseX;
    int baseY;
    int baseW;
    int rowHeight;
    int xSpacing;
    int ySpacing;
    // variables that update during use
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
  int &h,
  bool resizeW)
{
  curLayout->updateXY(x, y);
  curLayout->updateHeight(h);
  if (resizeW) {
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
    facade::setFocusItem(id);
  }
}

#endif // FACADE_FACADE_CC_INCLUDED
