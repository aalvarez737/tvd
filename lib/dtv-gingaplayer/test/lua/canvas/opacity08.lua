-- Testea que #attrOpacity no funcione con un valor fuera de rango mayor a 256 como par�metro.
local opacity = 670
local image = canvas:new("resources/lifia.png")
image:attrOpacity(opacity)
canvas:compose(0,0,image)
canvas:flush()