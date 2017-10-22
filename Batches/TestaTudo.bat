rem testa todos os scripts

cls

if exist ..\Scripts\estatisticas.estat  del ..\Scripts\estatisticas.estat

..\Produto\TesteGrafo        /s..\Scripts\TesteGrafo             /l..\Scripts\TesteGrafo              /a..\Scripts\estatisticas
if errorlevel 4 goto sai

..\Produto\TesteLista        /s..\Scripts\TesteLista             /l..\Scripts\TesteLista              /a..\Scripts\estatisticas
if errorlevel 4 goto sai


..\Scripts\exbestat /e..\scripts\estatisticas

:sai

