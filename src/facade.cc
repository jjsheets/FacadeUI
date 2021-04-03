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

int state_mouse_x;
int state_mouse_y;
bool state_mouse_left_down;
bool state_mouse_middle_down;
bool state_mouse_right_down;
std::u8string state_hover_item;
std::u8string state_active_item;

// Layout state
struct _layout;
std::stack<_layout*> layout_stack;
_layout* curLayout;
void facade::beginLayout(int x, int y, int w, int rowHeight, int xSpacing, int ySpacing);

void facade::init(int screenWidth) {
  state_mouse_x = 0;
  state_mouse_y = 0;
  state_mouse_left_down = false;
  state_mouse_middle_down = false;
  state_mouse_right_down = false;
  state_hover_item = u8"";
  state_active_item = u8"";
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

bool facade::isHoverItem(std::u8string id) {
  return state_hover_item == id;
}

void facade::setHoverItem(std::u8string id) {
  state_hover_item = id;
}

void facade::clearHoverItem() {
  state_hover_item = u8"";
}

bool facade::isActiveItem(std::u8string id) {
  return state_active_item == id;
}

bool facade::noActiveItem() {
  return state_active_item == u8"";
}

void facade::clearActiveItem() {
  state_active_item = u8"";
}

void facade::setActiveItem(std::u8string id) {
  state_active_item = id;
}

void facade::preFrame() {
  clearHoverItem();
}

void facade::postFrame() {
  if (!state_mouse_left_down) {
    clearActiveItem();
  } else if (noActiveItem()) {
    state_active_item = u8"_unavailable";
  }
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
