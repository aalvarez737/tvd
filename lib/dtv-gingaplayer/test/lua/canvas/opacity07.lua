-- Testea que #attrOpacity con 256 como par�metro.
local opacity = 256
local image = canvas:new("resources/lifia.png")
image:attrOpacity(opacity)
canvas:compose(0,0,image)
canvas:flush()