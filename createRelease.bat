mkdir Product
copy /B "Release\Policlinic.exe" Product\
copy "Policlinic\qt_ru.qm" Product\
copy "Policlinic\translate_ru.qm" Product\
copy %QTDIR32%\bin\QtGui4.dll Product\
copy %QTDIR32%\bin\QtCore4.dll Product\
copy docsBAD.txt Product\Doctors.txt
copy pacients.txt Product\Pacients.txt