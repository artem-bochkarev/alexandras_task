%QTDIR32%\bin\lupdate.exe Policlinic.pri -ts translate_en.ts
%QTDIR32%\bin\lupdate.exe Policlinic.pri -ts translate_ru.ts

%QTDIR32%\bin\lrelease.exe translate_en.ts -qm translate_en.qm
%QTDIR32%\bin\lrelease.exe translate_ru.ts -qm translate_ru.qm