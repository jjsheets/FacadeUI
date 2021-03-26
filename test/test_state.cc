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

#ifndef JJSHEETS_TEST_STATE_CC_INCLUDED
#define JJSHEETS_TEST_STATE_CC_INCLUDED

#include "facade_test.h"

TEST_CASE(test_init) {
  facade::_state state;
  facade::init(&state);
  ASSERT_EQ(state.mouse_x, 0, "%d");
  ASSERT_EQ(state.mouse_y, 0, "%d");
  ASSERT_FALSE(state.mouse_left_down);
  ASSERT_FALSE(state.mouse_middle_down);
  ASSERT_FALSE(state.mouse_right_down);
  ASSERT_TRUE(state.hover_item == nullptr);
  ASSERT_TRUE(state.active_item == nullptr);
}

TEST_CASE(test_setMouseXY) {
  facade::_state state;
  facade::init(&state);
  facade::setMouseXY(&state, 10, 15);
  ASSERT_EQ(state.mouse_x, 10, "%d");
  ASSERT_EQ(state.mouse_y, 15, "%d");
}

TEST_CASE(test_setLeftMouseButton) {
  facade::_state state;
  facade::init(&state);
  facade::setLeftMouseButton(&state, true);
  ASSERT_TRUE(state.mouse_left_down);
  facade::setLeftMouseButton(&state, false);
  ASSERT_FALSE(state.mouse_left_down);
}

TEST_CASE(test_setMiddleMouseButton) {
  facade::_state state;
  facade::init(&state);
  facade::setMiddleMouseButton(&state, true);
  ASSERT_TRUE(state.mouse_middle_down);
  facade::setMiddleMouseButton(&state, false);
  ASSERT_FALSE(state.mouse_middle_down);
}

TEST_CASE(test_setRightMouseButton) {
  facade::_state state;
  facade::init(&state);
  facade::setRightMouseButton(&state, true);
  ASSERT_TRUE(state.mouse_right_down);
  facade::setRightMouseButton(&state, false);
  ASSERT_FALSE(state.mouse_right_down);
}

#endif // JJSHEETS_TEST_STATE_CC_INCLUDED
