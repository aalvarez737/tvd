-- Testea #new intentando crear un nuevo canvas a partir de un string vac�o como path
local pathImage = ""
local canvasImage = canvas:new(pathImage)
canvas:compose(0,0,canvasImage)
canvas:flush()