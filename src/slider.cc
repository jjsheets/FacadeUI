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

void facade::initSlider() {
  state_default_slider_renderer = nullptr;
}

double facade::slider(std::u8string id, facade::slider_type type, int w, int l, double min, double max, double val,
    facade::slider_renderer renderer) {
  int x = 0;
  int y = 0;
  w = w > 0 ? w : 20;
  if (type == facade::slider_type::horizontal) {
    facade::updateLayout(x, y, l, w, l == 0);
  } else {
    l = l > 0 ? l : 160;
    facade::updateLayout(x, y, w, l, w == 0);
  }
  // check/update hover and active.
  const int regionW = type == facade::slider_type::horizontal ? l : w;
  const int regionH = type == facade::slider_type::horizontal ? w : l;
  if (facade::mouseInRegion(x, y, regionW, regionH)) {
    facade::setHoverItem(id);
    if (facade::noActiveItem() && facade::getLeftMouseButton()) {
      facade::setActiveItem(id);
    }
  }
  // update as needed
  if (facade::isActiveItem(id)) {
    int mouseOffset = (type == facade::slider_type::horizontal ? facade::getMouseX() - x : facade::getMouseY() - y) - w / 2;
    mouseOffset = mouseOffset < 0 ? 0 : (mouseOffset > l - w ? l - w : mouseOffset);
    val = min + (mouseOffset * (max - min)) / (l - w);
  }
  // render the button
  auto _renderer = renderer ? renderer : state_default_slider_renderer;
  if (!_renderer) {
    throw u8"No slider renderer provided.";
  }
  if (facade::getLeftMouseButton() && facade::isActiveItem(id)) {
    _renderer(type, x, y, w, l, val, facade::display_state::pressed);
  } else if (facade::isHoverItem(id)) {
    _renderer(type, x, y, w, l, val, facade::display_state::hovered);
  } else {
    _renderer(type, x, y, w, l, val, facade::display_state::enabled);
  }
  return val;
}

double facade::slider(std::u8string id, slider_type type, int l, double min, double max, double val, facade::slider_renderer renderer) {
  return facade::slider(id, type, 0, l, min, max, val, renderer);
}

double facade::slider(std::u8string id, slider_type type, double min, double max, double val, facade::slider_renderer renderer) {
  return facade::slider(id, type, 0, 0, min, max, val, renderer);
}

void facade::setDefaultSliderRenderer(facade::slider_renderer renderer) {
  state_default_slider_renderer = renderer;
}

#endif // FACADE_SLIDER_CC_INCLUDED
