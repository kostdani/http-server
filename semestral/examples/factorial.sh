#!/bin/bash

num=$1
fact=1

while [ $num -gt 1 ]
do
  fact=$((fact * num))  #fact = fact * num
  num=$((num - 1))      #num = num - 1
done

echo "<!DOCTYPE html>
<html>
<body>
<h1>Simple factorial script</h1>
<p>Factorial of $1 is $fact.</p>
</body>
</html>"
