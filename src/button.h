// The latest version of this library is available on GitHub;
// https://github.com/jjsheets/FacadeUI
// License text can be found at the end of this file.

#ifndef FACADE_BUTTON_H_INCLUDED
#define FACADE_BUTTON_H_INCLUDED

namespace facade {

  typedef std::function<void (
    const std::string &, // label text
    int, // x coordinate
    int, // y coordinate
    int, // width
    int, // height
    display_state // display state of the button
  )> button_renderer;

  void initButton();

  void setDefaultButtonRenderer(
    button_renderer renderer);

  bool button(
    const std::string &id,
    const std::string &label,
    int w,
    int h,
    bool disabled = false,
    button_renderer renderer = nullptr);

  // Overloads

  bool button(
    const std::string &id,
    const std::string &label,
    int w,
    bool disabled,
    button_renderer renderer = nullptr);

  bool button(
    const std::string &id,
    const std::string &label,
    bool disabled,
    button_renderer renderer = nullptr);

  bool button(
    const std::string &id,
    const std::string &label,
    button_renderer renderer = nullptr);

  bool button(
    const std::string &id,
    const std::string &label,
    int w,
    button_renderer renderer = nullptr);

}

#endif // FACADE_BUTTON_H_INCLUDED

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
