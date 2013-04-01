#!/bin/sh

g++ -Wall -o soa-test test/*.cpp src/*.cpp -DUNITTEST -lcppunit
[ $? -eq 0 ] && ./soa-test

