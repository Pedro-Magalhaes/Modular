@ECHO  OFF
REM  Gera todos os scripts de make

cls

pushd  .

gmake  /b..\Compos  /cTesteLista

gmake  /b..\Compos  /cTesteGrafo

gmake  /b..\Compos /cUsuario

gmake  /b..\Compos /cRede

gmake  /b..\Compos /cChat

popd
