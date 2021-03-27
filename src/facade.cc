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

int state_mouse_x;
int state_mouse_y;
bool state_mouse_left_down;
bool state_mouse_middle_down;
bool state_mouse_right_down;
void* state_hover_item;
void* state_active_item;

void facade::init() {
  state_mouse_x = 0;
  state_mouse_y = 0;
  state_mouse_left_down = false;
  state_mouse_middle_down = false;
  state_mouse_right_down = false;
  state_hover_item = nullptr;
  state_active_item = nullptr;
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

bool facade::isHoverItem(void* id) {
  return state_hover_item == id;
}

void facade::setHoverItem(void* id) {
  state_hover_item = id;
}

bool facade::isActiveItem(void* id) {
  return state_active_item == id;
}

void facade::setActiveItem(void* id) {
  state_active_item = id;
}

void facade::preFrame() {
  state_hover_item = nullptr;
}

void facade::postFrame() {
  if (!state_mouse_left_down) {
    state_active_item = nullptr;
  } else if (!state_active_item) {
    state_active_item = (void*)("_unavailable");
  }
}

#endif // FACADE_FACADE_CC_INCLUDED
