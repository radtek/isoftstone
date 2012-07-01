
find  .  -name  '*.exe'  -type  f  -print  -exec  rm  -rf  {} \;
find  .  -name  '*.dll'  -type  f  -print  -exec  rm  -rf  {} \;
find  .  -name  '*.pdb'  -type  f  -print  -exec  rm  -rf  {} \;
find  .  -name  '*.ncb'  -type  f  -print  -exec  rm  -rf  {} \;
find  .  -name  '*.vcproj'  -type  f  -print  -exec  rm  -rf  {} \;
find  .  -name  '*.user'  -type  f  -print  -exec  rm  -rf  {} \;
find  .  -name  '*.idb'  -type  f  -print  -exec  rm  -rf  {} \;
find  .  -name  '*.suo'  -type  f  -print  -exec  rm  -rf  {} \;
find  .  -name  '*.sln'  -type  f  -print  -exec  rm  -rf  {} \;
find  .  -name  '*.Debug'  -type  f  -print  -exec  rm  -rf  {} \;
find  .  -name  '*.Release'  -type  f  -print  -exec  rm  -rf  {} \; 
find  .  -name  'core*'  -type  f  -print  -exec  rm  -rf  {} \;
find  .  -name  '*.o'  -type  f  -print  -exec  rm  -rf  {} \;
find  .  -name  'Makefile'  -type  f  -print  -exec  rm  -rf  {} \;

find . -name "*.svn" -exec rm -rf {} \;
find . -name "Debug" -exec rm -rf {} \;
find . -name "Release" -exec rm -rf {} \;
find . -name "debug" -exec rm -rf {} \;
find . -name "release" -exec rm -rf {} \;
find . -name "obj" -exec rm -rf {} \;