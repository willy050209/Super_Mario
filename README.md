#	已知問題 :

1. Mybgm 在非windows平台無法使用。
2. 圖片縮放在非windows平台無法使用。
3. mario的圖片站立時與跳躍時寬度不同，導致判定有誤。

#	解決方法:

1. 改用SDL函數解決。
2. 改用SDL函數解決。
3. 待討論。

# 新功能

2025/03/23 mario移動時切換圖片，優化Objenc::inRange()方法
2025/03/24 放棄C#改用SDL2做圖片縮放(ImageResizer.hpp)。
2025/03/24 mario移動時切換圖片，加上左右