#
# HumanActivityRecognition/Makefile
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

VERSION = 1.0.0
SRCDIR = initial-release

all:
	(cd build;cmake .;make)

clean:
	rm -rf build/CMakeFiles build/main.dir build/Makefile \
	build/CMakeCache.txt build/cmake_install.cmake
	rm -rf *~ src/*~ src/.gout* include/*~ main
	rm -rf database/kick0/*~ database/kick1/~ \
	database/kick2/*~
	rm -rf build/*~

backup:	clean
	(cd ..;tar -zcvf har-$(VERSION).tar.gz $(SRCDIR))
