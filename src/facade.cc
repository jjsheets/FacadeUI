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

#ifndef JJSHEETS_FACADE_CC_INCLUDED
#define JJSHEETS_FACADE_CC_INCLUDED

struct _facade_state {
  int mouse_x;
  int mouse_y;
  bool mouse_left_down;
  bool mouse_middle_down;
  bool mouse_right_down;
  void* hover_item;
  void* active_item;
};

struct _facade_state _cur_state = {
  .mouse_x = 0,
  .mouse_y = 0,
  .mouse_left_down = false,
  .mouse_middle_down = false,
  .mouse_right_down = false,
  .hover_item = nullptr,
  .active_item = nullptr
};

void setMouseXY(int _x, int _y) {
  _cur_state.mouse_x = _x;
  _cur_state.mouse_y = _y;
}

void setLeftMouseButton(bool _down) {
  _cur_state.mouse_left_down = _down;
}

void setMiddleMouseButton(bool _down) {
  _cur_state.mouse_middle_down = _down;
}

void setRightMouseButton(bool _down) {
  _cur_state.mouse_right_down = _down;
}

#endif // JJSHEETS_FACADE_CC_INCLUDED
