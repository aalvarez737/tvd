-- Testea que el m�todo #attrFont funcione cu�ndo s�lo se le pasa como par�metro la fuente y el tama�o
local texto = "Fuente Tiresias "
canvas:attrFont("Tiresias",20)
canvas:attrColor("blue")
canvas:drawText(10,0,texto)
canvas:flush()