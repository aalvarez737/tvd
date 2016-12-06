-- Testea que #drawRect dibuje s�lo la parte del recuadro que est� dentro de los l�mites del canvas
local pathImage = "resources/cuadrado_rojo.jpg"
local canvasImage = canvas:new(pathImage)
local x,y = 0,0
local width,height = 320,320
canvasImage:attrColor("green")
canvasImage:drawRect("frame",x,y,width,height)
canvas:compose(0,0,canvasImage)
canvas:flush()
