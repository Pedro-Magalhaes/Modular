ECHO compila todos os programas exemplo
REM Requer o ambiente (environment) inicializado para compilar com o VisualStudio Microsoft
cls

del ..\produto\*.err
del ..\produto\TesteGrafo.exe
del ..\objetos\*.obj

REM compila para producao sem otimizacoes
pushd .
nmake /F..\Compos\TesteGrafo.make 

copy ..\produto\*.err ..\produto\tudo.err

notepad ..\produto\tudo.err

popd




