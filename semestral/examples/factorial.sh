#!/bin/bash
num=$1
fact=1


echo "<!DOCTYPE html>
<html>
<body>
<h1>Simple factorial script</h1><p>"

if [[ "$#" -ne 1 ]]; then
  echo "Usage: 127.0.0.1:8080/factorial?num"
else
while [ $num -gt 1 ]
  do
    fact=$((fact * num))  #fact = fact * num
    num=$((num - 1))      #num = num - 1
  done
  echo "Factorial of $1 is $fact."
fi

echo "</p>
</body>
</html>"
