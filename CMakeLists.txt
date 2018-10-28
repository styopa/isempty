# Copyright 2018 Styopa Semenukha
# This file is part of isempty, see COPYING
cmake_minimum_required(VERSION 2.8.11)
project(isempty C)

add_executable(isempty isempty.c)

install(TARGETS isempty)
