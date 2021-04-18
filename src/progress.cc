// The latest version of this library is available on GitHub;
// https://github.com/jjsheets/FacadeUI
// License text can be found at the end of this file.

#ifndef FACADE_PROGRESS_CC_INCLUDED
#define FACADE_PROGRESS_CC_INCLUDED

#include "facade.h"

namespace {
  facade::progress_renderer state_default_progress_renderer;
}

void facade::initProgress()
{
  state_default_progress_renderer = nullptr;
}

void facade::setDefaultProgressRenderer(facade::progress_renderer renderer)
{
  state_default_progress_renderer = renderer;
}

double facade::progress(
  const std::string &label,
  facade::orientation type,
  int w,
  int l,
  double min,
  double max,
  double val,
  facade::progress_renderer renderer)
{
  int x = 0;
  int y = 0;
  w = w > 0 ? w : 20;
  if (type == facade::orientation::horizontal) {
    facade::controlBounds(x, y, l, w);
  } else {
    l = l > 0 ? l : 160;
    facade::controlBounds(x, y, w, l);
  }
  auto _renderer = renderer ? renderer : state_default_progress_renderer;
  _renderer(label, type, x, y, w, l, val);
  return val;
}

// Overloads

double facade::progress(
  const std::string &label,
  facade::orientation type,
  int l,
  double min,
  double max,
  double val,
  facade::progress_renderer renderer)
{
  return facade::progress(label, type, 0, l, min, max, val, renderer);
}

double facade::progress(
  const std::string &label,
  facade::orientation type,
  double min,
  double max,
  double val,
  facade::progress_renderer renderer)
{
  return facade::progress(label, type, 0, 0, min, max, val, renderer);
}

#endif // FACADE_SLIDER_CC_INCLUDED

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
