-- Testea #compose() intentando componer un nuevo canvas en una 
-- posici�n fuera de los l�mites del canvas
local pathImage = "resources/cuadrado_rojo.jpg"
local canvasImage = canvas:new(pathImage)
canvas:compose(0,1000000,canvasImage)
canvas:flush()