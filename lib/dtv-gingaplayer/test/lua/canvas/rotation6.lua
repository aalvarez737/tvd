-- Testea que #attrRotation no tenga ning�n efecto si se le pasa como par�metro un n�mero negativo
local rotation = -90
local image = canvas:new("resources/lifia.png")
image:attrRotation(rotation)
canvas:compose(0,0,image)
canvas:flush()