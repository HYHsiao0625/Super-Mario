# OOPL
---
## 主題
- Super Mario Bro.
### TODO
- 開頭選擇
    - [x] 可選擇遊戲模式
    - [ ] 雙人遊玩
        - 還沒做
- 遊戲
    - Mario
        - 素材
            - [x] 待機
            - [x] 走路
            - [x] 跳
            - [x] 死亡
        - 基本移動
            - [x] 水平移動
                - 基本左移右移
            - [ ] 垂直移動
                - 感覺有跳但是他沒有，要找時間物理公式==
            - [ ] 左右碰撞
                - 進行中
            - [ ] 垂直碰撞
                - 只有完成一開始的地板，但之後要修改
        
    - 小怪
        - 素材
            - [x] goomba
        - 基本移動
            - [x] 水平移動
                - 基本左移右移
            - [ ] 垂直移動
                - 感覺有跳但是他沒有，要找時間物理公式==
            - [ ] 左右碰撞
                - 進行中
            - [ ] 垂直碰撞
                - 只有完成一開始的地板，但之後要修改
- 關卡
    - 地圖
        - 1-1
            - [x] 背景素材
            - [x] 地圖素材
            - [x] 2維圖案
            - [ ] 深淵 (未完成所有)
            - [ ] 地下空間
- 生命數
    - [ ] TBD
    

## 製作進度
- 0309
    - [name=蕭宏元]
        - 開頭選擇
            - 可選擇遊戲模式
            - 雙人遊玩還沒做
        - 馬力歐素材
            - 待機
            - 走路
            - 跳
        - 1-1 關卡地圖
            - 背景素材
            - 地圖素材
                - 深淵未製作
        - 基本移動
            - 水平移動
                - 基本左移右移
            - 垂直移動
                - 感覺有跳但是他沒有，要找時間物理公式==

        - 地圖
            - 地圖限制(鏡頭不會飄出地圖)
            - 馬力歐限制(不能走出地圖)
        - 製作時間:4HR
- 0313
    - [name=蕭宏元]
        - 更改遊戲框架為1.1.2
        - 更新素材
        - 修改了一些小BUG
        - 製作時間:1HR

- 0321
    - [name=蕭宏元]
        - 更改遊戲框架為1.1.3
        - 修改了一些小BUG
        - 新增mario class
        - 新增goomba class
        - 新增map class
        - 製作時間:6HR

- 0329
    - [name=蕭宏元]
        - 死掉會重新返回原點
        - 將地圖修改成2維而不是一張圖片了
        - 程式碼整理
        - 製作時間:3HR
    - [name=陳宇倫]
        - 地圖繪製
        - 地圖素材
        - 人物左右碰撞
        - 程式碼整理
        - 製作時間:3HR
- 0404
    - [name=陳宇倫]
        - 跳躍修復(不會卡地板 但是靠近方塊邊緣會小順移)
        - 跳躍修復(不會黏在牆壁上)
        - 撞方塊(未完成 按著空白鍵會一直上下彈)
        - Goomba繼承Enemy(還有一些像不會跟隨視窗移動也在裡面)
        - 製作時間:3HR

- 0427
    - [name=蕭宏元]
        - 跳躍修改 
            - 可正常跳躍不會黏牆了
            - 頭頂方塊正常移動
        - 問題
            - 不確定是因為一次性載入全部地圖造成卡頓(問助教)

        - 製作時間:2HR
