# gCosm
Server for streaming, receiving and transcoding video with support of AV1 format. Additionally enables to receive additional data on HTTP (like space coordinates). Supports hls and rtsp. Part of my engineering project, the second one is avaliable here: https://github.com/Swistusmen/Space-Seal

<h2> Tech stack </h2>

  - C++
  
  - C
  - Google Test
  - Cpp Rest SDK (Casablanca)
  - CMake
  - Python
  - PyTest

<h2> How to build </h2>

 ```sh scripts/prepare_env.sh```
 
  ```sh scripts/build.sh```

<h2> Tests </h2>
<br> Unit tests- parser component only </br>

 ```sh scripts/test.sh```
 
 <br> User acceptance/black tests</br>
 
 ```sh scripts/uat.sh```
 
<h2>How does it work </h2>
As an input application takes congig.json, or if any arguments were added creates such an object. With a -h flag you can learn about the opportunities which application gives. Design of an app let developers to extend json freely.
<br> Scheme </br>

![image](https://user-images.githubusercontent.com/49188328/142444987-8ec92138-2499-44d9-8b79-f4cc6c20765e.png)

<br> Every of steps which follows after parsing json is not obligatory. For hls streaming application demands http server working on seleceted position </br>

<h2> Purpose and extra notes </br>

