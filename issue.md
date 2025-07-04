currently i have this issue and idk how to cpp :sob:

```console
$ pwd
Creates/build
$ cmake --build ./
[ 14%] Built target sfml-system
[ 57%] Built target sfml-window
[ 95%] Built target sfml-graphics
[ 97%] Linking CXX executable bin/Creates
/usr/bin/ld: CMakeFiles/Creates.dir/src/UIProcessor/Events/TempName.cpp.o: warning: relocation against `_ZN4data8mousePosE' in read-only section `.text'
/usr/bin/ld: CMakeFiles/Creates.dir/src/main.cpp.o: in function `main':
/home/hitoya/Downloads/programs/cpp/logic_sim/src/main.cpp:16:(.text+0x3b): undefined reference to `data::mousePos'
/usr/bin/ld: /home/hitoya/Downloads/programs/cpp/logic_sim/src/main.cpp:40:(.text+0x34e): undefined reference to `data::mousePos'
/usr/bin/ld: /home/hitoya/Downloads/programs/cpp/logic_sim/src/main.cpp:42:(.text+0x455): undefined reference to `data::mousePos'
/usr/bin/ld: /home/hitoya/Downloads/programs/cpp/logic_sim/src/main.cpp:51:(.text+0x7e6): undefined reference to `data::mousePos'
/usr/bin/ld: CMakeFiles/Creates.dir/src/UIProcessor/Events/TempName.cpp.o: in function `processEvents(sf::Window&)':
/home/hitoya/Downloads/programs/cpp/logic_sim/src/UIProcessor/Events/TempName.cpp:21:(.text+0xe0): undefined reference to `data::mousePos'
/usr/bin/ld: warning: creating DT_TEXTREL in a PIE
collect2: error: ld returned 1 exit status
gmake[2]: *** [CMakeFiles/Creates.dir/build.make:145: bin/Creates] Error 1
gmake[1]: *** [CMakeFiles/Makefile2:203: CMakeFiles/Creates.dir/all] Error 2
gmake: *** [Makefile:136: all] Error 2
```
