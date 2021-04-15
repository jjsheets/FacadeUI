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

namespace {
  facade::button_renderer state_default_button_renderer;
}

void facade::initButton()
{
  state_default_button_renderer = nullptr;
}

void facade::setDefaultButtonRenderer(
  facade::button_renderer renderer)
{
  state_default_button_renderer = renderer;
}

bool facade::button(
  const std::string &id,
  const std::string &label,
  int w,
  int h,
  bool disabled,
  facade::button_renderer renderer)
{
  int x = 0;
  int y = 0;
  facade::controlBounds(x, y, w, h, w == 0);
  facade::updateControlState(id, x, y, w, h, disabled);
  auto _render = renderer ? renderer : state_default_button_renderer;
  _render(label, x, y, w, h, facade::displayState(id, disabled));
  return (
    !disabled &&
    !facade::leftMouseDown() &&
    facade::isHoverItem(id) &&
    facade::isActiveItem(id));
}

// Overloads

bool facade::button(
  const std::string &id,
  const std::string &label,
  int w,
  bool disabled,
  facade::button_renderer renderer)
{
  return facade::button(id, label, w, 0, disabled, renderer);
}

bool facade::button(
  const std::string &id,
  const std::string &label,
  bool disabled,
  facade::button_renderer renderer)
{
  return facade::button(id, label, 0, 0, disabled, renderer);
}

bool facade::button(
  const std::string &id,
  const std::string &label,
  facade::button_renderer renderer)
{
  return facade::button(id, label, 0, 0, false, renderer);
}

bool facade::button(
  const std::string &id,
  const std::string &label,
  int w)
{
  return facade::button(id, label, w, 0, false, nullptr);
}

#endif // FACADE_Button_CC_INCLUDED
