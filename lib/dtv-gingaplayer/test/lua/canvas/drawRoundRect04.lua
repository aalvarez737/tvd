-- Testea #drawRoundRect pas�ndole como mode un string vac�o
local x,y = 10,20
local width,height = 60,60
local arcWidth, arcHeight = 10,10
canvas:attrColor("red")
canvas:drawRoundRect("",x,y,width,height,arcWidth, arcHeight)
canvas:flush()