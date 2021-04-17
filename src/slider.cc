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

#ifndef FACADE_SLIDER_CC_INCLUDED
#define FACADE_SLIDER_CC_INCLUDED

#include "facade.h"

namespace {
  facade::slider_renderer state_default_slider_renderer;
}

void facade::initSlider()
{
  facade::setDefaultSliderRenderer(nullptr);
}

void facade::setDefaultSliderRenderer(
  facade::slider_renderer renderer)
{
  state_default_slider_renderer = renderer;
}

double facade::slider(
  const std::string &id,
  facade::orientation type,
  int w,
  int l,
  double min,
  double max,
  double val,
  bool disabled,
  facade::slider_renderer renderer)
{
  int x = 0;
  int y = 0;
  w = w > 0 ? w : 20;
  if (type == facade::orientation::horizontal) {
    facade::controlBounds(x, y, l, w, l == 0);
  } else {
    l = l > 0 ? l : 160;
    facade::controlBounds(x, y, w, l, w == 0);
  }
  const int regionW = type == facade::orientation::horizontal ? l : w;
  const int regionH = type == facade::orientation::horizontal ? w : l;
  facade::updateControlState(id, x, y, regionW, regionH, disabled);
  if (!disabled && facade::isActive(id)) {
    int mouseOffset;
    if (type == facade::orientation::horizontal) {
      mouseOffset = std::clamp(facade::getMouseX() - x - w / 2, 0, l - w);
    } else {
      mouseOffset = std::clamp(facade::getMouseY() - y - w / 2, 0, l - w);
    }
    val = min + (mouseOffset * (max - min)) / (l - w);
  }
  auto _renderer = renderer ? renderer : state_default_slider_renderer;
  _renderer(type, x, y, w, l, val, facade::displayState(id, disabled));
  return val;
}

// Overloads

double facade::slider(
  const std::string &id,
  facade::orientation type,
  int l,
  double min,
  double max,
  double val,
  bool disabled,
  facade::slider_renderer renderer)
{
  return facade::slider(id, type, 0, l, min, max, val, disabled, renderer);
}

double facade::slider(
  const std::string &id,
  facade::orientation type,
  double min,
  double max,
  double val,
  bool disabled,
  facade::slider_renderer renderer)
{
  return facade::slider(id, type, 0, 0, min, max, val, disabled, renderer);
}

double facade::slider(
  const std::string &id,
  facade::orientation type,
  double min,
  double max,
  double val,
  facade::slider_renderer renderer)
{
  return facade::slider(id, type, 0, 0, min, max, val, false, renderer);
}

#endif // FACADE_SLIDER_CC_INCLUDED
