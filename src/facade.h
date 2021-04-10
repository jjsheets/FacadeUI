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
#include <string>

namespace facade {

  // Widgets can have four display states: enabled, hovered, pressed, and disabled.
  // States for input focusing and draggable buttons are currently not planned.
  enum class display_state {
    enabled,
    hovered,
    pressed,
    disabled
  };

  // control codes for text entry
  enum class control_code {
    tab,
    shift_tab,
    home,
    end,
    del,
    backspace,
    pageup,
    pagedown,
    enter,
    left,
    right,
    up,
    down,
    cut,
    copy,
    paste,
    nop
  };

  void init(int screenWidth);
  void setMouseXY(int _x, int _y);
  int getMouseX();
  int getMouseY();
  void setLeftMouseButton(bool _down);
  void setMiddleMouseButton(bool _down);
  void setRightMouseButton(bool _down);
  bool getLeftMouseButton();
  bool getMiddleMouseButton();
  bool getRightMouseButton();
  bool mouseInRegion(int x, int y, int w, int h);
  bool isHoverItem(std::string id);
  void setHoverItem(std::string id);
  void clearHoverItem();
  bool isActiveItem(std::string id);
  bool noActiveItem();
  void setActiveItem(std::string id);
  void clearActiveItem();
  bool isFocusItem(std::string id);
  bool noFocusItem();
  void clearFocusItem();
  void setFocusItem(std::string id);
  void focusPrevItem();
  void setPreviousItem(std::string id);
  bool noKeyChar();
  bool hasKeyChar();
  char32_t getKeyChar();
  void clearKeyChar();
  void setKeyChar(char32_t code);
  control_code getControlCode();
  void setControlCode(control_code code, bool shift);
  bool getModShift();
  void preFrame();
  void postFrame();
  void beginLayout(int x, int y, int w, int rowHeight = 20, int xSpacing = 4, int ySpacing = 4);
  void endLayout();
  void indent(int w);
  void updateLayout(int& x, int& y, int& w, int& h, bool resizeW = true);

}

// Include widget headers

#include "button.h"
#include "label.h"
#include "slider.h"
#include "checkbox.h"
#include "textbox.h" // single line text entry
//#include "editbox.h" // multi-line text entry
//#include "colorwheel.h"

// Include complex widgets

//#include "uiconsole.h" // a traditional console system for a game, with layout of text sourced from a log (ideally with the capacity to scroll up) as well as a spot to enter debug/cheat commands

// Include rendering primitives

//#include "renderprims.h" // basic rendering primitives which can be used by custom renderers to achieve a desired styling to widgets
//#include "defaultrenderers.h" // default renderers which provide reasonable default rendering of all implemented widgets.

#endif // FACADE_FACADE_H_INCLUDED
