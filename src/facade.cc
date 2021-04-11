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

void facade::beginLayout(int x, int y, int w, int rowHeight, int xSpacing, int ySpacing);
struct _layout;

// Anonymous namespace to hold the state and maintain it as local to this file only.
namespace {
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
  // state for a fully composed unicode codepoint as provided by the OS.
  char32_t state_key_char;
  // the following state is used to keep track of the last cursor control key sent.
  facade::control_code state_cursor_control;
  bool state_mod_shift;
  facade::get_clipboard_callback state_get_clipboard;
  facade::set_clipboard_callback state_set_clipboard;

  // Layout state
  std::stack<_layout*> layout_stack;
  _layout* curLayout;
}

void facade::init(int screenWidth) {
  state_mouse_x = 0;
  state_mouse_y = 0;
  state_mouse_left_down = false;
  state_mouse_middle_down = false;
  state_mouse_right_down = false;
  state_hover_item = "";
  state_active_item = "";
  state_get_clipboard = nullptr;
  state_set_clipboard = nullptr;
  while (!layout_stack.empty()) layout_stack.pop();
  facade::beginLayout(0, 0, screenWidth);
  facade::initButton();
  facade::initLabel();
  facade::initSlider();
  facade::initCheckbox();
  facade::initTextbox();
}

void facade::setMouseXY(int x, int y) {
  state_mouse_x = x;
  state_mouse_y = y;
}

int facade::getMouseX() {
  return state_mouse_x;
}

int facade::getMouseY() {
  return state_mouse_y;
}

void facade::setLeftMouseButton(bool down) {
  state_mouse_left_down = down;
}

void facade::setMiddleMouseButton(bool down) {
  state_mouse_middle_down = down;
}

void facade::setRightMouseButton(bool down) {
  state_mouse_right_down = down;
}

bool facade::getLeftMouseButton() {
  return state_mouse_left_down;
}

bool facade::getMiddleMouseButton() {
  return state_mouse_middle_down;
}

bool facade::getRightMouseButton() {
  return state_mouse_right_down;
}

bool facade::mouseInRegion(int x, int y, int w, int h) {
  return !(state_mouse_x < x ||
           state_mouse_y < y ||
           state_mouse_x >= x + w ||
           state_mouse_y >= y + h);
}

bool facade::isHoverItem(std::string id) {
  return state_hover_item == id;
}

void facade::setHoverItem(std::string id) {
  state_hover_item = id;
}

void facade::clearHoverItem() {
  state_hover_item = "";
}

bool facade::isActiveItem(std::string id) {
  return state_active_item == id;
}

bool facade::noActiveItem() {
  return state_active_item == "";
}

void facade::clearActiveItem() {
  state_active_item = "";
}

void facade::setActiveItem(std::string id) {
  state_active_item = id;
}

bool facade::isFocusItem(std::string id) {
  return state_focus_item == id;
}

bool facade::noFocusItem() {
  return state_focus_item == "";
}

void facade::clearFocusItem() {
  state_focus_item = "";
}

void facade::setFocusItem(std::string id) {
  state_focus_item = id;
}

void facade::focusPrevItem() {
  state_focus_item = state_previous_item;
}

void facade::setPreviousItem(std::string id) {
  state_previous_item = id;
}

bool facade::noKeyChar() {
  return state_key_char == U'\0';
}

bool facade::hasKeyChar() {
  return state_key_char != U'\0';
}

// TODO: Convert this to output a string of utf8 code units (bytes) representing the currently stored char32_t code point.
char32_t facade::getKeyChar() {
  return state_key_char;
}

void facade::clearKeyChar() {
  state_key_char = U'\0';
}

void facade::setKeyChar(char32_t code) {
  state_key_char = code;
}

facade::control_code facade::getControlCode() {
  auto cc = state_cursor_control;
  state_cursor_control = facade::control_code::nop;
  return cc;
}

void facade::setControlCode(facade::control_code code, bool shift) {
  state_cursor_control = code;
  state_mod_shift = shift;
}

bool facade::getModShift() {
  return state_mod_shift;
}

void facade::setClipboardCallback(facade::get_clipboard_callback get, facade::set_clipboard_callback set) {
  state_get_clipboard = get;
  state_set_clipboard = set;
}

std::string facade::getClipboardText() {
  if (!state_get_clipboard) {
    return "";
  }
  return state_get_clipboard();
}

void facade::setClipboardText(std::string new_clipboard) {
  if (state_set_clipboard) {
    state_set_clipboard(new_clipboard);
  }
}

// Frame handling functions.

// update input events outside of preFrame()/postFrame() pairs
void facade::preFrame() {
  clearHoverItem();
}

void facade::postFrame() {
  if (!state_mouse_left_down) {
    clearActiveItem();
  } else if (noActiveItem()) {
    state_active_item = "_unavailable";
  }
  clearKeyChar();
}

// layout functions, local variables, and structures

struct _layout {
  // base layout values that don't change after being initialized in beginLayout()
  int baseX;
  int baseY;
  int baseW;
  int rowHeight;
  int xSpacing;
  int ySpacing;
  // variables that update during use
  int indent;
  int x;
  int y;
  int h;
};

void facade::beginLayout(int x, int y, int w, int rowHeight, int xSpacing, int ySpacing) {
  // push a new curLayout to the stack after initializing it and make it available as curLayout.
  curLayout = new _layout();
  curLayout->baseX = x;
  curLayout->baseY = y;
  curLayout->baseW = w;
  curLayout->rowHeight = rowHeight;
  curLayout->xSpacing = xSpacing;
  curLayout->ySpacing = ySpacing;
  curLayout->indent = 0;
  curLayout->x = 0;
  curLayout->h = 0;
  layout_stack.push(curLayout);
}

void facade::endLayout() {
  // if the stack size is greater than 1, pop the top layout and discard it, then make curLayout reference the new top.
  // We never pop the original layout, because that was initialized during facade::init()
  if (layout_stack.size() > 1) {
    delete curLayout;
    layout_stack.pop();
    curLayout = layout_stack.top();
  }
}

void facade::indent(int w) {
  curLayout->indent += w;
  curLayout->indent = curLayout->indent < 0 ? 0 : curLayout->indent;
  curLayout->indent = curLayout->indent > curLayout->baseW / 2 ? curLayout->baseW / 2 : curLayout->indent;
}

void _newRow(int h) {
  curLayout->x = 0;
  curLayout->y += curLayout->ySpacing + h;
  curLayout->h = 0;
}

void facade::updateLayout(int& x, int& y, int& w, int& h, bool resizeW) {
  int availableWidth = curLayout->baseW - curLayout->x - curLayout->indent;
  x = curLayout->baseX + curLayout->x + curLayout->indent;
  y = curLayout->baseY + curLayout->y;
  h = h > 0 ? h : curLayout->rowHeight;
  curLayout->h = curLayout->h < h ? h : curLayout->h;
  if (resizeW) {
    w = availableWidth;
    _newRow(curLayout->h);
  } else {
    if (w > availableWidth) {
      _newRow(curLayout->h);
      x = curLayout->baseX + curLayout->x + curLayout->indent;
      y = curLayout->baseY + curLayout->y;
      availableWidth = curLayout->baseW - curLayout->x - curLayout->indent;
    }
    w = w > availableWidth ? availableWidth : w;
    curLayout->x += w + curLayout->xSpacing;
  }
}

#endif // FACADE_FACADE_CC_INCLUDED
