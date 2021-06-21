#!/bin/bash
echo "<!DOCTYPE html>
<html>
<body>
<h1>Simple sum script</h1>
<p>"

if [[ "$#" -ne 2 ]]; then
  echo "Usage: 127.0.0.1:8080/sum?X=num&Y=num"
else
  for arg in "$@"
  do
    index=$(echo $arg | cut -f1 -d=)
    val=$(echo $arg | cut -f2 -d=)
    case $index in
      X) x=$val;;
      Y) y=$val;;
      *)
    esac
  done
  ((result=x+y))
  echo "X+Y=$x+$y=$result."
fi

echo "</p>
</body>
</html>"
