rem testa todos os scripts

cls

if exist ..\Scripts\estatisticas.estat  del ..\Scripts\estatisticas.estat

..\produto\TesteGrafo        /s..\Produto\TesteGrafo             /l..\Scripts\TesteGrafo              /a..\Scripts\estatisticas
if errorlevel 4 goto sai

..\produto\TesteLista        /s..\Produto\TesteLista             /l..\Scripts\TesteLista              /a..\Scripts\estatisticas
if errorlevel 4 goto sai


..\Scripts\exbestat /e..\scripts\estatisticas

:sai

