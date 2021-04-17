// The latest version of this library is available on GitHub;
// https://github.com/jjsheets/FacadeUI
// License text can be found at the end of this file.

#ifndef FACADE_CHECKBOX_H_INCLUDED
#define FACADE_CHECKBOX_H_INCLUDED

namespace facade {

  typedef std::function<void (
    const std::string &, // label text
    int, // x coordinate
    int, // y coordinate
    int, // width
    int, // height
    bool, // value (true = checked)
    display_state // display state of the checkbox
  )> checkbox_renderer;

  void initCheckbox();

  void setDefaultCheckboxRenderer(
    checkbox_renderer renderer);

  bool checkbox(
    const std::string &id,
    const std::string &label,
    int w,
    int h,
    bool val,
    bool disabled = false,
    checkbox_renderer renderer = nullptr);

  // Overloads

  bool checkbox(
    const std::string &id,
    const std::string &label,
    int w,
    bool val,
    bool disabled = false,
    checkbox_renderer renderer = nullptr);

  bool checkbox(
    const std::string &id,
    const std::string &label,
    bool val,
    bool disabled,
    checkbox_renderer renderer = nullptr);

  bool checkbox(
    const std::string &id,
    const std::string &label,
    bool val,
    checkbox_renderer renderer = nullptr);

}

#endif // FACADE_CHECKBOX_H_INCLUDED

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
