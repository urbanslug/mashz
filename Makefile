include make-include.mak

default: build_lastz

lastz_32: build_lastz_32

#---------
# builds/installation
#---------

build: build_lastz

build_lastz:
	cd src/common/lastz/src && ${MAKE} lastz lastz_D

build_lastz_32:
	cd src/common/lastz/src && ${MAKE} lastz_32

build_test_version:
	cd src/common/lastz/src && ${MAKE} lastz-test lastz_D-test

install: install_lastz

install_lastz:
	cd src/common/lastz/src && ${MAKE} install

install_32:
	cd src/common/lastz/src && ${MAKE} install_32

install_test_version:
	cd src/common/lastz/src && ${MAKE} install_test_version

# cleanup

clean:
	cd src/common/lastz/src && ${MAKE} clean

cleano:
	cd src/common/lastz/src && ${MAKE} cleano

#---------
# testing
#
# test:
#	A small test to give some comfort level that the program has built properly,
#	or that changes you've made to the source code haven't broken it. If the
#	test succeeds, there will be no output from the diff.
# base_tests:
#	More extensive tests (but still small). The results should be of this form:
#	SUCCESS: ../test_data/xxx and ../test_results/yyy are equivalent
#---------

test:
	cd src/common/lastz/src && ${MAKE} test

base_tests:
	cd src/common/lastz/src && ${MAKE} base_tests

clean_test: clean_tests

clean_tests:
	cd src/common/lastz/src && ${MAKE} clean_tests

