# Docker-wrapper
Un wrapper per l'esecuzione di **Podman** come se fosse **Docker**.  

# Scopo
La soluzione più semblice sarebbe creare un file `docker.cmd` da mettere nel *path* o dove c'è **Podman**.  
Questo file è molto semplice ed è fatto così:  

    @podman %*

Se invece vuoi proprio creare un eseguibile ad hoc, sei nel posto giusto!  

## Compilazione
Per compilare il programma in Windows è stato utilizzato [w64devkit](https://github.com/skeeto/w64devkit).  

Si possono usare i segunti comandi:  

    windres res\docker.rc -O coff -o docker_res.o
    g++ -O2 -s -static src/docker.cpp docker_res.o -o docker.exe

Oppure il classico makefile

    make

## Utilizzo
Si copia l'eseguibile in una directory presente nel *path* o si aggiunge la direcetory dove c'è l'eseguible al *path*.  
Se il file di **Podman** non è nella directory d'installazione standard si può creare il file di configurazione `docker.json` nella stessa directory dove è stato messo l'eseguibile.  
In [cfg](cfg) si trova un esempio di `docker.json` dove impostare il corretto persorso di **Podman** modificando il valore di *podman_path*.  

## Rigraziamenti
Se ti è piaciuto questo repository [offrimi un caffè virtuale](https://ko-fi.com/erebox_github).