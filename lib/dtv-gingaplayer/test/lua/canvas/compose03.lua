-- Testea #compose() intentando componer un nuevo canvas en una posici�n inv�lida
local pathImage = "resources/cuadrado_rojo.jpg"
local canvasImage = canvas:new(pathImage)
canvas:compose(0,-50,canvasImage)
canvas:flush()