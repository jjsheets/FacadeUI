// The latest version of this library is available on GitHub;
// https://github.com/jjsheets/FacadeUI
// License text can be found at the end of this file.

#ifndef FACADE_TEST_STATE_H_INCLUDED
#define FACADE_TEST_STATE_H_INCLUDED

UTEST(state, init) {
  facade::init(2560);
  ASSERT_EQ(facade::getMouseX(), 0);
  ASSERT_EQ(facade::getMouseY(), 0);
  ASSERT_FALSE(facade::leftMouseDown());
  ASSERT_FALSE(facade::middleMouseDown());
  ASSERT_FALSE(facade::rightMouseDown());
  ASSERT_TRUE(facade::isHovered(""));
  ASSERT_TRUE(facade::isActive(""));
}

UTEST(state, setMouseXY) {
  facade::init(2560);
  facade::setMouseXY(10, 15);
  ASSERT_EQ(facade::getMouseX(), 10);
  ASSERT_EQ(facade::getMouseY(), 15);
}

UTEST(state, setLeftMouseButton) {
  facade::init(2560);
  facade::setLeftMouseButton(true);
  ASSERT_TRUE(facade::leftMouseDown());
  facade::setLeftMouseButton(false);
  ASSERT_FALSE(facade::leftMouseDown());
}

UTEST(state, setMiddleMouseButton) {
  facade::init(2560);
  facade::setMiddleMouseButton(true);
  ASSERT_TRUE(facade::middleMouseDown());
  facade::setMiddleMouseButton(false);
  ASSERT_FALSE(facade::middleMouseDown());
}

UTEST(state, setRightMouseButton) {
  facade::init(2560);
  facade::setRightMouseButton(true);
  ASSERT_TRUE(facade::rightMouseDown());
  facade::setRightMouseButton(false);
  ASSERT_FALSE(facade::rightMouseDown());
}

UTEST(state, mouseInRegion) {
  facade::init(2560);
  const int x = 50;
  const int y = 50;
  const int w = 50;
  const int h = 50;
  facade::setMouseXY(x - 1,     y + h / 2);
  ASSERT_FALSE(facade::mouseInRegion(x, y, w, h));
  facade::setMouseXY(x,         y + h / 2);
  ASSERT_TRUE(facade::mouseInRegion(x, y, w, h));
  facade::setMouseXY(x + w - 1, y + h / 2);
  ASSERT_TRUE(facade::mouseInRegion(x, y, w, h));
  facade::setMouseXY(x + w,     y + h / 2);
  ASSERT_FALSE(facade::mouseInRegion(x, y, w, h));
  facade::setMouseXY(x + w / 2, y - 1);
  ASSERT_FALSE(facade::mouseInRegion(x, y, w, h));
  facade::setMouseXY(x + w / 2, y);
  ASSERT_TRUE(facade::mouseInRegion(x, y, w, h));
  facade::setMouseXY(x + w / 2, y + h - 1);
  ASSERT_TRUE(facade::mouseInRegion(x, y, w, h));
  facade::setMouseXY(x + w / 2, y + h);
  ASSERT_FALSE(facade::mouseInRegion(x, y, w, h));
}

#endif // FACADE_TEST_STATE_H_INCLUDED

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
