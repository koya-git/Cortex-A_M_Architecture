#! /bin/bash

while true; do
   echo 0 13 > /dev/GPIO_koya
   sleep 0.2
   echo 1 19 > /dev/GPIO_koya
   sleep 0.2
   echo 0 26 > /dev/GPIO_koya
   sleep 0.2
   echo 1 13 > /dev/GPIO_koya
   sleep 0.2
   echo 0 19 > /dev/GPIO_koya
   sleep 0.2
   echo 1 26 > /dev/GPIO_koya
   sleep 0.2
done
