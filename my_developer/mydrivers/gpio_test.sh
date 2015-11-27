#!/bin/bash
chmod 777  /drivers/gpio_test.o
for i in 0 1 0 1 0 1 0 1 0 1 0
do
 /drivers/gpio_test.o "1" "$i"
 sleep 1
done & # Run this loop in background.

