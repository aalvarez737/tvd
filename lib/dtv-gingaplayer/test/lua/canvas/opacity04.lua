-- Testea que #attrOpacity no tenga ning�n efecto sobre el canvas principal.
local opacity = 100
canvas:attrColor("red")
canvas:drawRect("fill",0,0,720,576)
canvas:flush()

canvas:attrOpacity(opacity)
canvas:flush()