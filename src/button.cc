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

#ifndef FACADE_BUTTON_CC_INCLUDED
#define FACADE_BUTTON_CC_INCLUDED

#include "facade.h"

facade::button_renderer state_default_button_renderer;

void facade::initButton() {
  state_default_button_renderer = nullptr;
}

bool facade::button(std::u8string id, std::u8string label, int x, int y, int w, int h, bool disabled, facade::button_renderer renderer) {
  // check/update hover and active.
  if (!disabled && facade::mouseInRegion(x, y, w, h)) {
    facade::setHoverItem(id);
    if (facade::isActiveItem(u8"") && facade::getLeftMouseButton()) {
      facade::setActiveItem(id);
    }
  }
  // render the button
  auto _renderer = renderer ? renderer : state_default_button_renderer;
  if (!_renderer) {
    throw u8"No button renderer provided.";
  }
  if (disabled) {
    _renderer(label, x, y, w, h, facade::display_state::disabled);
  } else if (facade::getLeftMouseButton() && facade::isActiveItem(id)) {
    _renderer(label, x, y, w, h, facade::display_state::pressed);
  } else if (facade::isHoverItem(id)) {
    _renderer(label, x, y, w, h, facade::display_state::hovered);
  } else {
    _renderer(label, x, y, w, h, facade::display_state::enabled);
  }
  // return true if the button is clicked
  return (!disabled && !facade::getLeftMouseButton() && facade::isHoverItem(id) && facade::isActiveItem(id));
}

void facade::setDefaultButtonRenderer(facade::button_renderer renderer) {
  state_default_button_renderer = renderer;
}

#endif // FACADE_FACADE_CC_INCLUDED
