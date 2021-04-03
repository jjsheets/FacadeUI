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

#ifndef FACADE_TEXTBOX_H_INCLUDED
#define FACADE_TEXTBOX_H_INCLUDED

namespace facade {

  // Buttons also support a rendering function, which allows for custom rendering of buttons
  typedef std::function<void (int, int, int, int, std::u8string, int, int, display_state)> textbox_renderer;

  void initTextbox();
  void textbox(std::u8string id, std::u8string &text, int &cursorStart, int &cursorEnd, int w, int h, bool disabled = false,
    textbox_renderer renderer = nullptr);
  void textbox(std::u8string id, std::u8string &text, int &cursorStart, int &cursorEnd, int w, bool disabled = false,
    textbox_renderer renderer = nullptr);
  void textbox(std::u8string id, std::u8string &text, int &cursorStart, int &cursorEnd, bool disabled = false, textbox_renderer renderer = nullptr);
  void textbox(std::u8string id, std::u8string &text, int &cursorStart, int &cursorEnd, textbox_renderer renderer);
  void setDefaultTextboxRenderer(textbox_renderer renderer);

}

#endif // FACADE_TEXTBOX_H_INCLUDED
