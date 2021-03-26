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

facade::init(facade::_state* state) {
  state->mouse_x = 0;
  state->mouse_y = 0;
  state->mouse_left_down = false;
  state->mouse_middle_down = false;
  state->mouse_right_down = false;
  state->hover_item = nullptr;
  state->active_item = nullptr;
}

void facade::setMouseXY(facade::_state* state, int x, int y) {
  state->mouse_x = x;
  state->mouse_y = y;
}

void facade::setLeftMouseButton(facade::_state* state, bool down) {
  state->mouse_left_down = down;
}

void facade::setMiddleMouseButton(facade::_state* state, bool down) {
  state->mouse_middle_down = down;
}

void facade::setRightMouseButton(facade::_state* state, bool down) {
  state->mouse_right_down = down;
}

bool facade::mouseInRegion(facade::_state* state, int x, int y, int w, int h) {
  return !(state->mouse_x < x ||
           state->mouse_y < y ||
           state->mouse_x >= x + w ||
           state->mouse_y >= y + h);
}

#endif // FACADE_FACADE_CC_INCLUDED
