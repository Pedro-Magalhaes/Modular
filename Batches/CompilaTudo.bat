ECHO compila todos os programas exemplo
REM Requer o ambiente (environment) inicializado para compilar com o VisualStudio Microsoft
cls

del ..\produto\*.err
del ..\produto\TesteGrafo.exe
del ..\produto\TesteLista.exe
del ..\objetos\*.obj

REM compila TesteGrafo
pushd .
nmake /F..\Compos\TesteGrafo.make 
del ..\objetos\*.obj
REM Compila TesteLista
nmake /F..\Compos\TesteLista.make

popd

copy ..\produto\*.err ..\produto\tudo.err

notepad ..\produto\tudo.err




