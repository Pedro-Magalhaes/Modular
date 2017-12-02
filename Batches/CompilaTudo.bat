ECHO compila todos os programas exemplo
REM Requer o ambiente (environment) inicializado para compilar com o VisualStudio Microsoft
cls

del ..\produto\*.err
del ..\produto\TesteGrafo.exe
del ..\produto\TesteLista.exe
del ..\produto\Usuario.exe
del ..\objetos\*.obj

REM compila TesteGrafo
pushd .
nmake /F..\Compos\TesteGrafo.make 
del ..\objetos\*.obj

REM Compila TesteLista
pushd .
nmake /F..\Compos\TesteLista.make
del ..\objetos\*.obj

REM Compila Usuario
pushd .
nmake /F..\Compos\Usuario.make
del ..\objetos\*.obj

REM Compila Rede
pushd .
nmake /F..\Compos\Rede.make
del ..\objetos\*.obj

popd

copy ..\produto\*.err ..\produto\tudo.err

notepad ..\produto\tudo.err




