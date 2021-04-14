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

#ifndef FACADE_TEST_PROGRESS_H_INCLUDED
#define FACADE_TEST_PROGRESS_H_INCLUDED

UTEST(progress, noRenderer) {
  facade::init(2560);
  bool exceptionThrown = false;
  // Initialization complete
  facade::preFrame();
  facade::beginLayout(10, 15, 160);
    try {
      facade::progress("Progress Label", facade::orientation::horizontal, 0.0, 100.0, 0.0);
    } catch (...) {
      exceptionThrown = true;
    }
    ASSERT_TRUE(exceptionThrown);
}

UTEST(progress, defaultRenderer) {
  facade::init(2560);
  bool rendered = false;
  facade::setDefaultProgressRenderer(
    [&](std::string label, facade::orientation type, int x, int y, int w, int l, double val) {
      rendered = true;
    }
  );
  // Initialization complete
  facade::preFrame();
  facade::beginLayout(10, 15, 160);
    facade::progress("Progress Label", facade::orientation::horizontal, 0.0, 100.0, 0.0);
    ASSERT_TRUE(rendered);
}

UTEST(progress, progressRenderer) {
  facade::init(2560);
  bool rendered = false;
  // Initialization complete
  facade::preFrame();
  facade::beginLayout(10, 15, 160);
    facade::progress("Progress Label", facade::orientation::horizontal, 0.0, 100.0, 0.0,
      [&](std::string label, facade::orientation type, int x, int y, int w, int l, double val) {
        rendered = true;
      }
    );
    ASSERT_TRUE(rendered);
}

UTEST(progress, progressRendererParameters) {
  facade::init(2560);
  // Initialization complete
  facade::preFrame();
  facade::beginLayout(10, 15, 160);
    facade::progress("Horizontal Label", facade::orientation::horizontal, 0.0, 100.0, 0.0,
      [&](std::string label, facade::orientation type, int x, int y, int w, int l, double val) {
        ASSERT_TRUE(type == facade::orientation::horizontal);
        ASSERT_TRUE("Horizontal Label" == label);
        ASSERT_EQ(x, 10);
        ASSERT_EQ(y, 15);
        ASSERT_EQ(w, 20);
        ASSERT_EQ(l, 160);
        ASSERT_EQ(val, 0.0);
      }
    );
  facade::endLayout();
  facade::postFrame();

  facade::preFrame();
  facade::beginLayout(10, 15, 160);
    facade::progress("Vertical Label", facade::orientation::vertical, 0.0, 100.0, 0.0,
      [&](std::string label, facade::orientation type, int x, int y, int w, int l, double val) {
        ASSERT_TRUE(type == facade::orientation::vertical);
        ASSERT_TRUE("Vertical Label" == label);
        ASSERT_EQ(x, 10);
        ASSERT_EQ(y, 15);
        ASSERT_EQ(w, 20);
        ASSERT_EQ(l, 160);
        ASSERT_EQ(val, 0.0);
      }
    );
}

#endif // FACADE_TEST_PROGRESS_H_INCLUDED
