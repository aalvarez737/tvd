-- Testea #new intentando crear un nuevo canvas a partir de un path inv�lido.

local pathImage = "resources/imagenQueNoExiste.jpg"
local canvasImage = canvas:new(pathImage)
canvas:compose(0,0,canvasImage)
canvas:flush()