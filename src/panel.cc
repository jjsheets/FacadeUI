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

#ifndef FACADE_PANEL_CC_INCLUDED
#define FACADE_PANEL_CC_INCLUDED

#include "facade.h"

namespace {
  facade::panel_renderer state_default_panel_renderer;
}

void facade::initPanel()
{
  facade::setDefaultPanelRenderer(nullptr);
}

void facade::setDefaultPanelRenderer(facade::panel_renderer renderer)
{
  state_default_panel_renderer = renderer;
}

void facade::panel(
  int w,
  int h,
  facade::panel_renderer renderer)
{
  int x = 0;
  int y = 0;
  facade::controlBounds(x, y, w, h, w == 0);
  auto _renderer = renderer ? renderer : state_default_panel_renderer;
  _renderer(x, y, w, h);
}

void facade::panel(
  int w,
  facade::panel_renderer renderer)
{
  facade::panel(w, 0, renderer);
}

void facade::panel(
  facade::panel_renderer renderer)
{
  facade::panel(0, 0, renderer);
}

#endif // FACADE_PANEL_CC_INCLUDED
