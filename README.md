# FacadeUI

FacadeUI is meant to be a minimalist immediate mode GUI library in C++17/20, designed for use in games, with an absolute minimum of dependencies to ensure it is as portable and unintrusive as possible. Despite being programmed in C++, the methodology used is generally functional, rather than object oriented.

## UI Elements

* *Label:* A rectangle + text, generally rendered as just the text contained within the bounds of the rectangle.
* *Panel:* Simply a rectangle. Can be used to display a background color, but also capable of displaying an image. **(NOT YET IMPLEMENTED)**
* *Button:* A typical button styled control, represented by a rectangle and text. When called it will return true if the button is clicked, making it useful as the conditional in an if statement. Also takes a disabled parameter which changes the rendering and ignores all interaction attempts.
* *Checkbox:* Similar to the button, however, you also provide it with a boolean value. Returns the value of the control, which is toggled when it is clicked. Can be used with different renderers and logic handling to create toggle buttons, toggle switches, radio buttons, and as part of complex controls like an accordion layout. **TODO:** Update this to be able to be disabled.
* *Slider:* A control which allows for the selection of a number within a range of numbers. Can be horizontal or vertical. The exact set of numbers allowed can be continuous in the set of real numbers within the given range, and programming logic is capable of adjusting the returned numbers to a desired set of values (e.g.: integers, or real numbers with one digit after the decimal point). Sliders can also be used to implement scrollbars. Sliders use a minimum, maximum, and value as inputs, and return the value that results from whatever user interaction occurs, if any. **TODO:** Update this to be able to be disabled.
* *Range Slider:* A slider control with two separate slider nodes that can be used to select two numbers within the range allowed. Generally used to allow the user to define a range of numbers rather than select a single number within a range. Uses a minimum, maximum, and two values as inputs. The values are passed by reference, and updated due to any user input. **(NOT YET IMPLEMENTED)**
* *Text Box:* A control allowing for single-line text input and editing. Takes in the text by reference, the horizontal offset, and the current cursor location within the text. Each are passed by reference, and when the text changes it is directly updated. Can be disabled, which reduces the textbox to a glorified label. **(NOT YET IMPLEMENTED)**
* *Multiline Text Box:* A multiline editing control, intended for editing longer text. Takes in the text, a vertical offset, and the cursor location within the text. Text is expected to be word wrapped by the renderer. **(NOT YET IMPLEMENTED)**
* *Progress Bar:* A non-interactive display of a process. Takes in the minimum and maximum values, the current progress, as well as optional text which the renderer can display above the bar. **(NOT YET IMPLEMENTED)**
* *Tooltip:* A control for displaying multiline text relevant to another control in a small float intended to be rendered above other UI elements. **(NOT YET IMPLEMENTED)**

## TODO

* Finish creating unit tests and widgets to satisfy them.
* Develop the renderer systems and supply default renderers for use with each widget.
* Start writing demos, documentation, and examples for each widget.
