FileManager hecho por Manuel Cabrera Liñán.

Aspectos a tener en cuenta a la hora de usar el programa fileManager:

	1. En archivo serialize.hpp está implementado por la posibilidad de serializar el vector de punteros a strings
	   para enviarlo por mensaje.
	
	2. En el constructor del main del cliente (main_fm.cpp) hay que poner el directorio de prueba que se desee,
	   en el enunciado se informaba de usar dirprueba/ pero en mi caso no funcionaba ya que la carpeta compartida
	   estaba creada en el cliente y me daba problemas el intentar acceder a esta desde el servidor. Aún así,
	   esta carpeta fileManager/ dispone de una carpeta dirprueba/ con ficheros y todo disponible para usarse.
	   
	3. Es posible que a la hora de hacer Upload, tarde varios segundos en actualizar la información en el fichero
	   que se le ha indicado.