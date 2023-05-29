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
                ~~- 基本左移右移~~
                - 0329更新:已修好
            - [x] 垂直移動
                - ~~感覺有跳但是他沒有，要找時間物理公式==~~
                - 0526更新:已修好
            - [x] 左右碰撞
                ~~- 進行中~~
                - 0427更新:已完成
            - [x] 垂直碰撞
                ~~- 只有完成一開始的地板，但之後要修改~~
                -0412更新:已完成
        
    - 小怪
        - 素材
            - [x] 栗寶寶
            - [x] 慢慢龜
            - [ ] 庫巴
        - 基本移動
            - [x] 水平移動
                - 基本左移右移
            - [x] 垂直移動
                - 感覺有跳但是他沒有，要找時間物理公式==
            - [x] 左右碰撞
                - 進行中
            - [x] 垂直碰撞
                - 只有完成一開始的地板，但之後要修改
    - 物品
        - 素材
            - [x] 蘑菇
            - [x] 火焰花
            - [ ] 超級星星
- 關卡
    - 地圖
        - [x] 1-1
        - [ ] 1-2
        - [ ] 1-3
        - 其他待定

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
- 0412
    - [name=蕭宏元]
        - 垂直碰撞
            - 可以正常判斷是否在地上
        - 製作時間:2HR
- 0427
    - [name=蕭宏元]
        - 跳躍修改 
            - 可正常跳躍不會黏牆了
            - 頭頂方塊可以正常移動
        - 問題
            - 不確定是因為一次性載入全部地圖造成卡頓

        - 製作時間:2HR

- 0512
    - [name=蕭宏元]
        - 吃蘑菇會變大了
            - 但他沒有被刪掉記憶體會卡在那裡會LAG BRUH
        - 新增R鍵RESET
            - 但RESET尚未完成，目前可以回起點
        - 
        - 製作時間:2HR

- 0519
    - [name=蕭宏元]
        - 物品有基本物理行為了(碰撞)
        - 整理程式碼
        - 製作時間:2HR

- 0526
    - [name=蕭宏元]
        - 修改移動問題
            - 至少馬力歐可以移動得更順暢了 ㄏㄏ
        - 修理之前所遺留程式的BUG
        - TBD
            - 頭黏住
            - 物品瘋狂射出
            - 大馬力歐受傷變小
            - 小怪死亡後記憶體刪除
            - 地圖顯示與不要浪費記憶體
            - 切地圖
        - 製作時間:3HR

- 0529
    - [name=蕭宏元]
        - 物品現在不會隨著鏡頭移動了
        - 修理之前所遺留程式的BUG
        - 大馬力歐受傷變小完成
        - 頭黏住改完
        - TBD
            ~~- 但小怪無法產生在512以外的位置~~
            ~~- 頭黏住~~
            ~~- 大馬力歐受傷變小~~
            - 一堆問題出來
            - 切地圖
        - 製作時間:6HR