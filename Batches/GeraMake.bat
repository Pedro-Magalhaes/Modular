@ECHO  OFF
REM  Gera script de make
REM    Sintaxe   GeraMake <NomeArquivoComposicao>

pushd  .

if ""=="%1" goto erro

cd ..\Compos
gmake /c%1 /b..\Compos
goto sai

:erro
echo Falta nome do arquivo de diretivas de composicao

:sai
popd
