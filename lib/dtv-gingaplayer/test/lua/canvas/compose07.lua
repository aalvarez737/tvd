--  Muestra una imagen a partir de la posici�n (0,0) de 108x108 pixels.
-- Testea #compose pas�ndole s�lo algunos de los par�metros opcionales.
local newCanvas = canvas:new("resources/lifia.png")
canvas:compose(0,0,newCanvas,0,0,128,128)
canvas:flush()