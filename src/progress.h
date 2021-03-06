// The latest version of this library is available on GitHub;
// https://github.com/jjsheets/FacadeUI
// License text can be found at the end of this file.

#ifndef FACADE_PROGRESS_H_INCLUDED
#define FACADE_PROGRESS_H_INCLUDED

namespace facade {

  typedef std::function<void (
    const std::string &, // progress text
    orientation, // either facade::horizontal or facade::vertical
    int, // x coordinate
    int, // y coordinate
    int, // width
    int, // height
    double // progress percentage
  )> progress_renderer;

  void initProgress();

  void setDefaultProgressRenderer(
    progress_renderer renderer);

  double progress(
    const std::string &label,
    orientation type,
    int w,
    int l,
    double min,
    double max,
    double val,
    progress_renderer renderer = nullptr);

// Overloads

  double progress(
    const std::string &label,
    orientation type,
    int l,
    double min,
    double max,
    double val,
    progress_renderer renderer = nullptr);

  double progress(
    const std::string &label,
    orientation type,
    double min,
    double max,
    double val,
    progress_renderer renderer = nullptr);

}

#endif // FACADE_PROGRESS_H_INCLUDED

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
