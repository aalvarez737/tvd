-- Testea #drawEllipse pas�ndole como par�metro un n�mero negativo como �ngulo de inicio de la elipse
local xc,yc = 360,260
local width,height = 320,320
local ang_start, ang_end = -10,100
canvas:attrColor("red")
canvas:drawEllipse("fill",xc,yc,width,height,ang_start,ang_end)
canvas:flush()