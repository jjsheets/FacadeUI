// The latest version of this library is available on GitHub;
// https://github.com/jjsheets/FacadeUI
// License text can be found at the end of this file.

#ifndef FACADE_TEST_LAYOUT_H_INCLUDED
#define FACADE_TEST_LAYOUT_H_INCLUDED

UTEST(layout, simpleLayout) {
  facade::init(2560);
  int x = 0;
  int y = 0;
  int w = 0;
  int h = 0;
  // Initialization complete
  facade::preFrame();
  facade::beginLayout(20, 40, 400);
    facade::controlBounds(x, y, w, h);
    ASSERT_EQ(20, x); ASSERT_EQ(40, y); ASSERT_EQ(400, w); ASSERT_EQ(20, h);
    facade::indent(10);
    w = 0;
    facade::controlBounds(x, y, w, h);
    ASSERT_EQ(30, x); ASSERT_EQ(64, y); ASSERT_EQ(390, w); ASSERT_EQ(20, h);
    facade::indent(-10);
    w = 0;
    facade::controlBounds(x, y, w, h);
    ASSERT_EQ(20, x); ASSERT_EQ(88, y); ASSERT_EQ(400, w); ASSERT_EQ(20, h);
    facade::indent(10);
    w = 0;
    facade::controlBounds(x, y, w, h);
    ASSERT_EQ(30, x); ASSERT_EQ(112, y); ASSERT_EQ(390, w); ASSERT_EQ(20, h);
    facade::indent(-10);
    w = 0;
    facade::controlBounds(x, y, w, h);
    ASSERT_EQ(20, x); ASSERT_EQ(136, y); ASSERT_EQ(400, w); ASSERT_EQ(20, h);
    facade::indent(10);
    w = 0;
    facade::controlBounds(x, y, w, h);
    ASSERT_EQ(30, x); ASSERT_EQ(160, y); ASSERT_EQ(390, w); ASSERT_EQ(20, h);
    facade::indent(-10);
  facade::endLayout();
}

UTEST(layout, sideBySideLayout) {
  facade::init(2560);
  int x = 0;
  int y = 0;
  int w = 0;
  int h = 0;
  // Initialization complete
  facade::preFrame();
  facade::beginLayout(20, 40, 400);
    w = 80;
    facade::controlBounds(x, y, w, h);
    ASSERT_EQ(20, x); ASSERT_EQ(40, y); ASSERT_EQ(80, w); ASSERT_EQ(20, h);
    w = 0;
    facade::controlBounds(x, y, w, h);
    ASSERT_EQ(104, x); ASSERT_EQ(40, y); ASSERT_EQ(316, w); ASSERT_EQ(20, h);
    w = 80;
    facade::controlBounds(x, y, w, h);
    ASSERT_EQ(20, x); ASSERT_EQ(64, y); ASSERT_EQ(80, w); ASSERT_EQ(20, h);
    w = 400;
    facade::controlBounds(x, y, w, h);
    ASSERT_EQ(20, x); ASSERT_EQ(88, y); ASSERT_EQ(400, w); ASSERT_EQ(20, h);
    w = 80;
    facade::controlBounds(x, y, w, h);
    ASSERT_EQ(20, x); ASSERT_EQ(112, y); ASSERT_EQ(80, w); ASSERT_EQ(20, h);
    w = 0;
    h = 40;
    facade::controlBounds(x, y, w, h);
    ASSERT_EQ(104, x); ASSERT_EQ(112, y); ASSERT_EQ(316, w); ASSERT_EQ(40, h);
    w = 0;
    h = 0;
    facade::controlBounds(x, y, w, h);
    ASSERT_EQ(20, x); ASSERT_EQ(156, y); ASSERT_EQ(400, w); ASSERT_EQ(20, h);
  facade::endLayout();
}

#endif // FACADE_TEST_LAYOUT_H_INCLUDED

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
