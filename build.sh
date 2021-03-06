#!/bin/bash

export PATH=$PATH:/opt/Qt5.5.0/5.5/gcc_64/bin/

build_release_version() {
	cd sources2/Solar_S
	qmake --version
	qmake
	if [ -e "Makefile" ]; then
		make --version
		make
	else
		echo "Makefile does not exist"
		echo "Build release version failure!"
		return 1
	fi
	cd ../..
}

build_debug_version() {
	cd sources2/Solar_S
	cloc --version
	cloc --by-file --xml --out=../../report/cloc_result *
	qmake --version
	qmake "QMAKE_CXXFLAGS+=-fprofile-arcs -ftest-coverage -fPIC -O0 -g --coverage" "LIBS+=-lgcov"
	if [ -e "Makefile" ]; then
		make --version
		make
		Test/tst_testcore -xml -o ../../report/test_results || true 
		cppcheck --version
		cppcheck --enable=all -v  --xml  * 2> ../../report/cppcheck_result
		gcovr --version
		gcovr -r . --xml --exclude='tst*' -o ../../report/gcovr_result
		
		valgrind --version
		valgrind --leak-check=full --xml=yes --xml-file=/opt/tomcat/.jenkins/jobs/SolarSystem/workspace/report/tst_testtest.%p.result /opt/tomcat/.jenkins/jobs/SolarSystem/workspace/sources2/Solar_S/Test/tst_testtest || true


	else
		echo "Makefile does not exist"
		echo "Build debug version failure!"

		return 1
	fi

	cd ../..  
}

make_report() {
	cd report
	if [ -e "doxygen.ini" ]; then
			doxygen --version
			doxygen doxygen.ini
		else
			echo "Doxygen failed"
			echo "doxygen.ini does not exist"
		fi
	cd latex
	if [ -e "Makefile" ]; then
		make --version
		make
		cd ../..
	else
		echo "Makefile does not exist"
		echo "Report failure!"
		cd ../..
		return 1
	fi
}

zip_files() {
	if [ -z ${JOB_NAME} ] || [ -z ${BUILD_NUMBER}]; then
		echo "Vars JOB_NAME/BUILD_NUMBER are unset"
		echo "Zip failure!"
		return 1
	fi

	TITLE="${JOB_NAME}${BUILD_NUMBER}"
	mkdir "$TITLE"

	if [ -e "sources2/Solar_S/App/App" ]; then
		cp sources2/Solar_S/App/App $TITLE/App${BUILD_NUMBER}
		if [ -e "report/latex/refman.pdf" ]; then
			cp report/latex/refman.pdf $TITLE/refmanDoxygen${BUILD_NUMBER}.pdf
		fi
		zip --version
		zip $TITLE.zip $TITLE/*
	else
		echo "ConsoleApp does not exist"
		echo "Zip failure!"
		return 1
	fi

}

clean() {
	git clean -f -e *.zip *.pdf
}
