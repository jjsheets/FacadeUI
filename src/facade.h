// The latest version of this library is available on GitHub;
// https://github.com/jjsheets/FacadeUI
// License text can be found at the end of this file.

#ifndef FACADE_FACADE_H_INCLUDED
#define FACADE_FACADE_H_INCLUDED

#include <functional>
#include <string>

namespace facade {

  typedef std::function<std::string ()> clipboard_content_callback;

  typedef std::function<void (
    std::string
  )> clip_content_callback;

  typedef std::function<void (
    std::string &,
    unsigned int &,
    unsigned int &
  )> control_op;

  void init(
    int screenWidth);

  void setMouseXY(
    int _x,
    int _y);

  int getMouseX();

  int getMouseY();

  void setLeftMouseButton(
    bool _down);

  void setMiddleMouseButton(
    bool _down);

  void setRightMouseButton(
    bool _down);

  bool leftMouseDown();

  bool middleMouseDown();

  bool rightMouseDown();

  bool mouseInRegion(
    int x,
    int y,
    int w,
    int h);

  bool isHovered(
    const std::string &id);

  void setHoverItem(
    const std::string &id);

  void clearHoverItem();

  bool isActive(
    const std::string &id);

  bool noActiveItem();

  void setActiveItem(
    const std::string &id);

  void clearActiveItem();

  bool clicked(
    const std::string &id);

  bool isFocused(
    const std::string &id);

  bool noFocusItem();

  void clearFocusItem();

  void focus(
    const std::string &id);

  void focusPrevItem();

  void setPreviousItem(
    const std::string &id);

  bool noKeyChar();

  bool hasKeyChar();

  char32_t getKeyChar();

  void clearKeyChar();

  void setKeyChar(
    char32_t code);

  void setControlCode(
    control_op code,
    bool shift);

  bool getModShift();

  void setClipboardCallback(
    clipboard_content_callback get,
    clip_content_callback set);

  std::string clipboardText();

  void clipboardText(
    std::string);

  void tab(
    std::string &text,
    unsigned int &cursorStart,
    unsigned int &cursorEnd);

  void home(
    std::string &text,
    unsigned int &cursorStart,
    unsigned int &cursorEnd);

  void pageup(
    std::string &text,
    unsigned int &cursorStart,
    unsigned int &cursorEnd);

  void up(
    std::string &text,
    unsigned int &cursorStart,
    unsigned int &cursorEnd);

  void end(
    std::string &text,
    unsigned int &cursorStart,
    unsigned int &cursorEnd);

  void pagedown(
    std::string &text,
    unsigned int &cursorStart,
    unsigned int &cursorEnd);

  void down(
    std::string &text,
    unsigned int &cursorStart,
    unsigned int &cursorEnd);

  void del(
    std::string &text,
    unsigned int &cursorStart,
    unsigned int &cursorEnd);

  void backspace(
    std::string &text,
    unsigned int &cursorStart,
    unsigned int &cursorEnd);

  void left(
    std::string &text,
    unsigned int &cursorStart,
    unsigned int &cursorEnd);

  void right(
    std::string &text,
    unsigned int &cursorStart,
    unsigned int &cursorEnd);

  void paste(
    std::string &text,
    unsigned int &cursorStart,
    unsigned int &cursorEnd);

  void cut(
    std::string &text,
    unsigned int &cursorStart,
    unsigned int &cursorEnd);

  void copy(
    std::string &text,
    unsigned int &cursorStart,
    unsigned int &cursorEnd);

  void handleKeyboardEditing(
    std::string &text,
    unsigned int &cursorStart,
    unsigned int &cursorEnd);

  void preFrame();

  void postFrame();

  enum class display_state {
    enabled,
    hovered,
    pressed,
    disabled
  };

  display_state displayState(
    const std::string &id,
    bool disabled);

  void beginLayout(
    int x,
    int y,
    int w,
    int rowHeight = 20,
    int xSpacing = 4,
    int ySpacing = 4);

  void endLayout();

  void indent(
    int w);

  void controlBounds(
    int& x,
    int& y,
    int& w,
    int& h);

  void updateControlState(
    const std::string &id,
    int x,
    int y,
    int w,
    int h,
    bool disabled,
    bool focusAwareControl = false);

  enum class orientation {
    horizontal,
    vertical
  };

}

// Include standard widget headers

#include "button.h"
#include "label.h"
#include "slider.h"
#include "progress.h"
#include "checkbox.h"
#include "textbox.h"
#include "panel.h"

#endif // FACADE_FACADE_H_INCLUDED

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
