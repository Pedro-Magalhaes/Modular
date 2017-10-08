@ECHO  OFF
REM  Gera todos os scripts de make

cls

pushd  .

cd ..\..\ferramnt

gmake  /b..\grafo\Compos  /cTesteGrafo


popd
