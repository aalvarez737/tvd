-- Testea que #attrRotation no tenga ning�n efecto si se le pasa como par�metro un n�mero que no es m�ltiplo de 90
local rotation = 94
local image = canvas:new("resources/lifia.png")
image:attrRotation(rotation)
canvas:compose(0,0,image)
canvas:flush()