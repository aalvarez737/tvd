-- Testea que el m�todo #attrFont no funcione si se le pasa el tercer parametro como string vacio
local texto = "Fuente Tiresias "
canvas:attrFont("Tiresias",20, "")
canvas:attrColor("blue")
canvas:drawText(10,0,texto)
canvas:flush()