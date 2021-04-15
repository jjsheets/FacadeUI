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

#ifndef FACADE_CHECKBOX_CC_INCLUDED
#define FACADE_CHECKBOX_CC_INCLUDED

#include "facade.h"

namespace {
  facade::checkbox_renderer state_default_checkbox_renderer;
}

void facade::initCheckbox() {
  state_default_checkbox_renderer = nullptr;
}

bool facade::checkbox(std::string id, std::string label, int w, int h, bool val, bool disabled, facade::checkbox_renderer renderer) {
  int x = 0;
  int y = 0;
  facade::controlBounds(x, y, w, h, w == 0);
  // check/update hover and active.
  facade::updateControlState(id, x, y, w, h, disabled);
  // return true if the button is clicked
  if (!disabled && !facade::leftMouseDown() && facade::isHoverItem(id) && facade::isActiveItem(id)) {
    val = !val;
  }
  // render the button
  auto _renderer = renderer ? renderer : state_default_checkbox_renderer;
  if (disabled) {
    _renderer(label, x, y, w, h, val, facade::display_state::disabled);
  } else if (facade::leftMouseDown() && facade::isActiveItem(id)) {
    _renderer(label, x, y, w, h, val, facade::display_state::pressed);
  } else if (facade::isHoverItem(id)) {
    _renderer(label, x, y, w, h, val, facade::display_state::hovered);
  } else {
    _renderer(label, x, y, w, h, val, facade::display_state::enabled);
  }
  return val;
}

bool facade::checkbox(std::string id, std::string label, int w, bool val, bool disabled, checkbox_renderer renderer) {
  return facade::checkbox(id, label, w, 0, val, disabled, renderer);
}

bool facade::checkbox(std::string id, std::string label, bool val, bool disabled, checkbox_renderer renderer) {
  return facade::checkbox(id, label, 0, 0, val, disabled, renderer);
}

bool facade::checkbox(std::string id, std::string label, bool val, checkbox_renderer renderer) {
  return facade::checkbox(id, label, 0, 0, val, false, renderer);
}

void facade::setDefaultCheckboxRenderer(facade::checkbox_renderer renderer) {
  state_default_checkbox_renderer = renderer;
}

#endif // FACADE_CHECKBOX_CC_INCLUDED
