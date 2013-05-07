mkdir Product
copy /B "Release\Policlinic.exe" Product\
copy "Policlinic\qt_ru.qm" Product\
copy "Policlinic\translate_ru.qm" Product\
copy "Policlinic\translate_en.qm" Product\
copy %QTDIR32%\bin\QtGui4.dll Product\
copy %QTDIR32%\bin\QtCore4.dll Product\