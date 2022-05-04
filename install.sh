###
 # @Description: 
 # @version: 
 # @Author: Hubery-Lee
 # @E-mail: hrbeulh@126.com
 # @Date: 2021-12-09 14:53:30
 # @LastEditTime: 2021-12-15 22:15:47
 # @LastEditors: Hubery-Lee
### 
cd bin
rm -rf *
cd ../build
rm -rf *
cmake .. 
make 
make install
cd ../bin

# touch SpectrumCov.desktop
# echo "[Desktop Entry]">SpectrumCov.desktop
# echo "Version=1.0">>SpectrumCov.desktop
# echo "Terminal=false">>SpectrumCov.desktop
# echo "Type=Application">>SpectrumCov.desktop
# # echo "Encoding=UTF-8">>SpectrumCov.desktop
# echo "Name=SpectrumCov">>SpectrumCov.desktop
# echo "Exec="$(pwd)/SpectrumCov"">>SpectrumCov.desktop
# echo "Icon=$(pwd)/winapp.ico">>SpectrumCov.desktop

# cp SpectrumCov.desktop ~/.local/share/applications