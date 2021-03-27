#!/bin/bash

tup
if [ $? -eq 0 ]; then
  if test -f "test/facade_test"; then
    test/facade_test
  fi
fi
