-- Testea #drawEllipse pas�ndole como par�metro un n�mero negativo en la coordenada x
local xc,yc = -10,260
local width,height = 320,320
local ang_start, ang_end = 0,360
canvas:attrColor("red")
canvas:drawEllipse("fill",xc,yc,width,height,ang_start,ang_end)
canvas:flush()