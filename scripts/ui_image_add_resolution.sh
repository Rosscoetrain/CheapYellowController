#!/bin/bash

for directory in *; do
  echo $directory
  cd $directory
  for filename in ui_image_*; do
    echo $filename

    echo '#include "../../defines.h"' > temp.text
    echo >> temp.text
    echo "#ifdef RES${directory}" >> temp.text
    echo >> temp.text

    cat $filename >> temp.text

    echo >> temp.text
    echo "#endif // RES${directory}" >> temp.text
    echo >> temp.text

    mv temp.text $filename

  done
  cd ..
done
