# FacadeUI Control Documentation

## button

The minimum you need to use a button control is to call the `button` function,
which returns true or false if the button is clicked:

```C++
if (button("buttonID", "Click Me!")) {
  // ...
}
```

This will render a button which will fill the current row of the active layout.
Often you will want to specify a width for your button.

```C++
if (button("buttonID", "Click Me!", 80)) {
  // ...
}
```

This will try to force the button to be 80 pixels wide. If there isn't room in
the current row of the active layout, it will try to place the button one row
down. It will only reduce the width if the current state of the layout cannot
support the desired width.

You may also want to specify a height.

```C++
if (button("buttonID", "Click Me!", 80, 40)) {
  // ...
}
```

This will try to force the button to be 80 pixels wide and 40 pixels high.
Generally, the height of a control will not be limited. If you only want to
specify a height, use a width of `0`.

Buttons can be disabled, which prevents interaction with them and typically changes their appearance.

```C++
if ((button("buttonID", "Click Me!", false))) {
  // This will never run.
}
```

The boolean to disable a button will be last, or second to last if a custom renderer is specified.

## button Renderers

`button` renderers are functions or function objects which match the following
function declaration:

```C++
void buttonRenderer(
  const std::string & label,
  int x,
  int y,
  int w,
  int h,
  facade::display_state displayState);
```

When run, they should render a button with the given parameters. `displayState`
will be one of the following: `facade::display_state::enabled`,
`facade::display_state::hovered`, `facade::display_state::pressed`, or
`facade::display_state::disabled`. It is up to the renderer function to
determine any other details related to how the button should be rendered,
including whether the actual drawing commands remain limited to the given
coordinates and size (which logically only represent the clickable area of the
button).
