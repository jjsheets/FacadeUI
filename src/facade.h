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

#ifndef FACADE_FACADE_H_INCLUDED
#define FACADE_FACADE_H_INCLUDED

#include <functional>

namespace facade {

  struct _state;

  void init(_state* _state);
  void setMouseXY(_state* _state, int _x, int _y);
  void setLeftMouseButton(_state* _state, bool _down);
  void setMiddleMouseButton(_state* _state, bool _down);
  void setRightMouseButton(_state* _state, bool _down);
  bool mouseInRegion(_state* state, int x, int y, int w, int h);

  // Buttons can have four display states: enabled, hovered, pressed, and disabled.
  // States for input focusing and draggable buttons are currently not planned.
  enum button_display_state {
    enabled,
    hovered,
    pressed,
    disabled
  };
  // Buttons also support a rendering function, which allows for custom rendering of buttons
  typedef std::function<void (int, int, int, int, button_display_state)> button_renderer;

  bool button(_state* state, void* id, int x, int y, int w, int h, bool disabled = false, button_renderer renderer = nullptr);
  void setDefaultButtonRenderer(_state* state, button_renderer renderer);

  struct _state {
    int mouse_x;
    int mouse_y;
    bool mouse_left_down;
    bool mouse_middle_down;
    bool mouse_right_down;
    void* hover_item;
    void* active_item;
    button_renderer default_button_renderer;
  };
}

#endif // FACADE_FACADE_H_INCLUDED
