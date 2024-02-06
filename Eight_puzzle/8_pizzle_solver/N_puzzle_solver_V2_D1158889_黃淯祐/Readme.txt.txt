D1158889 黃淯祐 N-Puzzle solver program

使用方法:
1 先使用Puzzle_Gen_V2.exe產生初始題目，產生goal.txt及ini.txt

2 執行N_puzzle_solver.exe，確認題目後會開始執行，執行完會輸出步驟到move.txt

3 使用Puzzle_Sol_Ver_V2.exe來確認move.txt的moves是否能解出該題目

#註1: 正常來說1秒內就能給出答案



//  N_puzzle_solver.c說明
使用的方法: 盲解法，或是說 逐塊歸位法

主要利用整個puzzle的右下2x2的位置來當作buffer及swap的空間
將要復原的塊set up至buffer，接著four move swap，然後undo set up moves，再一次four move swap

其中有些特殊情況，以15 puzzle為例，11或12的歸位需看當下total swap times，跟交換次數的的奇偶數有關
因為每做一次four move swap，11和12的位置就會相互交換

15的歸位也是特殊情況，需與其他未歸位的塊做交換，來開始新的一個cycle，因為15必須最後歸位

4跟8也稍微算是特殊情況，set up的方式與其他塊不同

詳細解法可參考:
https://www.youtube.com/watch?v=4hRvVgrYwyY
https://www.youtube.com/watch?v=YKI369c-nXU



//  使用這個方法的好處
1 可快速得到一種解
2 相較於搜尋法，這個方法不占記憶體空間
3 相較於搜尋法，這個方法每一步都是有目的的在移動

//  壞處
1 無法得到最佳解(最短步數)
2 N越大，檔案大小增加的速度越快