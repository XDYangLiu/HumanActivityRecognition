#
# HumanActivityRecognition/build/CMakeLists.txt
# 
# Copyright (C) 2016 Debashis Barman (debashisbarman.in)
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
#

cmake_minimum_required(VERSION 2.8)
project( HumanActivityRecognition )
find_package( OpenCV REQUIRED )
add_executable( ../main ../src/avg.cpp ../src/detect.cpp ../src/dft.cpp ../src/frames.cpp ../src/gmm.cpp ../src/lib.cpp ../src/main.cpp )
target_link_libraries( ../main ${OpenCV_LIBS} )
