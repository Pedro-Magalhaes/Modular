@ECHO  OFF
REM  Gera todos os scripts de make

cls

pushd  .

gmake  /b..\Compos  /cTesteGrafo

gmake  /b..\Compos  /cTesteLista

gmake  /b..\Compos /cUsuario
popd
