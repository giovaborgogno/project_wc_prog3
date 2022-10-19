# project_wc_prog3

### Manual de uso:
#### Uso normal:  
wce file.txt  
#### Argumentos posibles:
-palabras [n]: Mostrará las n primeras palabras en orden alfabético. Si n no es ingresado o vale 0, mostrará
todas las palabras.  
Ej: wce -palabras 4 file.txt

-ocurrencias [n]: Mostrará las n palabras y la cantidad de ocurrencias de c/u ordenadas de mayor a menor
por ocurrencia. Si n no es ingresado o vale 0, mostrará todas las palabras.  
Ej: wce -ocurrencia 5 file.txt

-mostrar [palabra] [palabra] : Mostrará la o las palabras pasadas como argumento ordenadas por
ocurrencia.

-excluir [palabra] [palabra] : Modifica los comandos ocurrencias y palabras haciendo que no muestren las
palabras pasadas como argumentos.  
Ej: wce -ocurrencia -excluir "hola chau" file.txt

-excluirf [archivo.txt] : Modifica los comandos ocurrencias y palabras haciendo que no muestren las
palabras que contiene el archivo.txt.  
Ej: wce -ocurrencia -excluir ign.txt file.txt
