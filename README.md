# FacadeUI

FacadeUI is meant to be a minimalist immediate mode GUI library in C++, designed for use in games, with an absolute minimum of dependencies to ensure it is as portable and unintrusive as possible.

## TODO

* Finish creating unit tests and widgets to satisfy them. The list of widgets to be added can be found in src/facade.h as commented out #include directives.
* Layout system: Convert to a layout system where a layout begin/end function pair sets a default width, and maintains an x, y parameter, so the programmer doesn't need to maintain such info. Instead it can be stored in a layout structure and used by the UI state (via a stack), to determine where to draw the next widget at.
** beginLayout(x, y, w, rowHeight, xSpacing, ySpacing) - Starts a new layout at x, y, with width w. Spacing can be used to add spacing between the rows of the layout.
** endLayout() - exits out of the current layout, returning to the previous layout.
** indent(w) - indent the current layout's x parameter by w pixels to the right. The parameter x can be negative, which allows it to be used to remove existing indents. That said, the current indent in a layout cannot be less than 0.
** layoutX(), layoutY() - returns the current rendering cursor coords, which can be used by widget functions instead of a user provided coord.
** need some functions to maintain the next row's y coord and update it if a widget uses more than the row Height.
* Updates to widgets will require maintenance of a remaining width variable, which can be used to format widgets left to right on a single row of the layout. This should even be automatic, so a programmer can supply no width for a control to use the remaining width and then move to the next row. Or the programmer can supply a width which will result in the min of the desired width and the remaining width. Either way, once the width is used up, the remaining width is reset to the layout width minus the current indent, and the y parameter is moved down to the next row (rowHeight + spacing).
* The eventual goal is to basically make controls auto layout in a convenient fashion, but not add too much complexity (such as trying to replicate what an HTML DOM can produce). Such a DOM should only be considered when it comes to rendering multi-line text, and even that is something I'd like to avoid if at all possible.
